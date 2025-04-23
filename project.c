// Motor Control Pins
const int LEFT_PWM  = 31;  // PC5 (M0PWM0) - Left Motor Speed 
const int RIGHT_PWM = 36;  // PC4 (M0PWM1) - Right Motor Speed 
const int LEFT_IN1  = 11;  // PA2 - Left Motor Direction 1 
const int LEFT_IN2  = 25;  // PD2 - Left Motor Direction 2 
const int RIGHT_IN3 = 37;  // PC4 - Right Motor Direction 1 
const int RIGHT_IN4 = 38;  // PB3 - Right Motor Direction 2

const int trigFront = 7, echoFront = 27;  // Front Sensor
const int trigLeft = 32, echoLeft = 12;    // Left Sensor
const int trigRight = 3, echoRight = 4;  // Right Sensor

long cmFront, cmLeft, cmRight;

int stop_distance = 20;    // Stop when front wall is within 20 cm

int turn_speed = 160;       // Speed for minor adjustments
int correction_speed = 120; // Speed for adjusting to maintain wall gap

int wall_distance = 9;
char bluetoothCmd = 'S';  // Default to stopped
bool isRunning = false;  // Flag to control movement

void setup() { 
  Serial.begin(9600);
    Serial3.begin(9600);

    pinMode(LEFT_IN1, OUTPUT); 
    pinMode(LEFT_IN2, OUTPUT); 
    pinMode(RIGHT_IN3, OUTPUT); 
    pinMode(RIGHT_IN4, OUTPUT); 
    pinMode(LEFT_PWM, OUTPUT); 
    pinMode(RIGHT_PWM, OUTPUT);

    pinMode(trigFront, OUTPUT);
    pinMode(echoFront, INPUT);
    pinMode(trigLeft, OUTPUT);
    pinMode(echoLeft, INPUT);
    pinMode(trigRight, OUTPUT);
    pinMode(echoRight, INPUT);
}

void loop() { 
    cmFront = getDistance(trigFront, echoFront);
    cmLeft = getDistance(trigLeft, echoLeft);
    cmRight = getDistance(trigRight, echoRight);
    Serial3.print("cmFront: ");
    Serial3.print(cmFront);
    Serial3.print("\n");
    Serial3.print("cmLeft: ");
    Serial3.print(cmLeft);
    Serial3.print("\n");
    Serial3.print("cmRight: ");
    Serial3.print(cmRight);
    Serial3.print("\n");
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
    if (isRunning==true){

    if (cmFront<20 && cmLeft>15 && cmRight>15){  // Stop at the end
      Stop_Motors();
    }
    else if (cmLeft>30) {       //Turn left if no wall on left
      delay(100);
      Stop_Motors();
    delay(500);
      Move_Left();
      
    } 
    // Adjust right if too close to left wall
    else 
    if (cmLeft > 0 && cmLeft < cmRight) {
        //Serial.println("Too close to left wall, adjusting right.");
        Adjust_Right();
    } 
   
    // Adjust left if too close to right wall
    else if (cmRight > 0 && cmRight < cmLeft) {
        //Serial.println("Too close to right wall, adjusting left.");
        Adjust_Left();
    }
    // Move forward normally
    else { 
        Move_Forward();
    }
    
    delay(5);  // Small delay for sensor stabilization
    }
}

void Move_Right() { 
    digitalWrite(LEFT_IN1, HIGH); 
    digitalWrite(LEFT_IN2, LOW); 
    digitalWrite(RIGHT_IN3, HIGH); 
    digitalWrite(RIGHT_IN4, LOW); 
    analogWrite(LEFT_PWM, 144);  
    analogWrite(RIGHT_PWM, 120); 
    delay(600); 
    Stop_Motors();
    delay(200);
    Move_Forward();
    delay(300);
    

}
void Adjust_Right() { 
    digitalWrite(LEFT_IN1, HIGH); 
    digitalWrite(LEFT_IN2, LOW); 
    digitalWrite(RIGHT_IN3, LOW); 
    digitalWrite(RIGHT_IN4, HIGH); 
    analogWrite(LEFT_PWM, 192);  
    analogWrite(RIGHT_PWM, correction_speed); 
}

// Move Slightly Left (Correct right wall proximity)
void Adjust_Left() { 
    digitalWrite(LEFT_IN1, HIGH); 
    digitalWrite(LEFT_IN2, LOW); 
    digitalWrite(RIGHT_IN3, LOW); 
    digitalWrite(RIGHT_IN4, HIGH); 
    analogWrite(LEFT_PWM, 144);  
    analogWrite(RIGHT_PWM, turn_speed);  
}
// Move Left (Turn left to avoid obstacle)
void Move_Left() { 
    digitalWrite(LEFT_IN1, LOW); 
    digitalWrite(LEFT_IN2, HIGH); 
    digitalWrite(RIGHT_IN3, LOW); 
    digitalWrite(RIGHT_IN4, HIGH); 
    analogWrite(LEFT_PWM, 144);  
    analogWrite(RIGHT_PWM, 120); // Slow down right wheel for turning
    delay(600);  // Adjust experimentally for a 90° turn
    Stop_Motors();
    delay(500);
    Move_Forward();
    delay(300);
}
// Move Forward
void Move_Forward() { 
    digitalWrite(LEFT_IN1, HIGH); 
    digitalWrite(LEFT_IN2, LOW); 
    digitalWrite(RIGHT_IN3, LOW); 
    digitalWrite(RIGHT_IN4, HIGH); 
    analogWrite(LEFT_PWM, 130);  
    analogWrite(RIGHT_PWM, 125); 
}

// Stop Motors
void Stop_Motors() { 
    analogWrite(LEFT_PWM, 0);  
    analogWrite(RIGHT_PWM, 0); 
}
// Convert Time to Distance
long microsecondsToCentimeters(long microseconds) {
    return (microseconds * 0.0343) / 2;  // More accurate conversion factor
}

// Get Distance from Ultrasonic Sensor
long getDistance(int trigPin, int echoPin) {
    long total = 0, count = 0;

        digitalWrite(trigPin, LOW);
        delay(2);
        digitalWrite(trigPin, HIGH);
        delay(10);
        digitalWrite(trigPin, LOW);

        long duration = pulseIn(echoPin, HIGH, 10000); // 20ms timeout
        long distance = microsecondsToCentimeters(duration);

        if (distance > 1) { // Ignore noise (less than 1 cm is unrealistic)
          total = distance;

        }
      return total;
}