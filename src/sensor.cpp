#include "sensor.h"
#include "config.h"

void Sensor_Init() {
    pinMode(trigFront, OUTPUT);
    pinMode(echoFront, INPUT);
    pinMode(trigLeft, OUTPUT);
    pinMode(echoLeft, INPUT);
    pinMode(trigRight, OUTPUT);
    pinMode(echoRight, INPUT);
}

// Convert Time to Distance
long microsecondsToCentimeters(long microseconds) {
    return (microseconds * 0.0343) / 2;
}

// Get Distance from Ultrasonic Sensor
long getDistance(int trigPin, int echoPin) {
    long total = 0;

    digitalWrite(trigPin, LOW);
    delay(2);
    digitalWrite(trigPin, HIGH);
    delay(10);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH, 10000); // 10ms timeout (reduced from 20ms for faster blocking)
    long distance = microsecondsToCentimeters(duration);

    if (distance > 1) { // Ignore noise
        total = distance;
    }
    return total;
}
