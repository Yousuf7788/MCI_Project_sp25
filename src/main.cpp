#include <Energia.h>
#include "config.h"
#include "motor.h"
#include "sensor.h"

// State variables
long cmFront, cmLeft, cmRight;
char bluetoothCmd = 'S'; 
bool isRunning = false;

void setup() { 
    Serial.begin(9600);   // Debug UART
    Serial3.begin(9600);  // Bluetooth UART
    
    Motor_Init();
    Sensor_Init();
    
    Serial.println("System Initialized");
}

void loop() { 
    // 1. Read Sensors
    cmFront = getDistance(trigFront, echoFront);
    cmLeft = getDistance(trigLeft, echoLeft);
    cmRight = getDistance(trigRight, echoRight);
    
    // 2. Telemetry (Optional: Limit frequency if needed)
    /* 
    Serial3.print("cmFront: "); Serial3.println(cmFront);
    Serial3.print("cmLeft: "); Serial3.println(cmLeft);
    */
    
    // 3. Handle Bluetooth Commands
    if (Serial3.available() > 0) {
        bluetoothCmd = Serial3.read();
        if (bluetoothCmd == 'G' || bluetoothCmd == 'g') {
            isRunning = true;
            Serial3.println("Received: G (Go)");
        } else if (bluetoothCmd == 'S' || bluetoothCmd == 's') {
            isRunning = false;
            Stop_Motors();
            Serial3.println("Received: S (Stop)");
        }
    }

    // 4. Control Logic
    if (isRunning) {
        if (cmFront < STOP_DISTANCE && cmLeft > 15 && cmRight > 15) {
            // Wall in front, open space on sides -> Stop (End of maze?)
            Stop_Motors();
        }
        else if (cmLeft > 30) {
            // No wall on left -> Turn Left
            delay(100);
            Stop_Motors();
            delay(500);
            Move_Left();
        } 
        else if (cmLeft > 0 && cmLeft < cmRight) {
            // Too close to left wall -> Adjust Right
            Adjust_Right();
        } 
        else if (cmRight > 0 && cmRight < cmLeft) {
            // Too close to right wall -> Adjust Left
            Adjust_Left();
        }
        else { 
            // Path clear -> Forward
            Move_Forward();
        }
        
        delay(5);  // Stabilization delay
    }
}
