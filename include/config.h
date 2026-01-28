#ifndef CONFIG_H
#define CONFIG_H

#include <Energia.h>

// Motor Control Pins
const int LEFT_PWM  = 31;  // PC5 (M0PWM0) - Left Motor Speed 
const int RIGHT_PWM = 36;  // PC4 (M0PWM1) - Right Motor Speed 
const int LEFT_IN1  = 11;  // PA2 - Left Motor Direction 1 
const int LEFT_IN2  = 25;  // PD2 - Left Motor Direction 2 
const int RIGHT_IN3 = 37;  // PC4 - Right Motor Direction 1 
const int RIGHT_IN4 = 38;  // PB3 - Right Motor Direction 2

// Ultrasonic Sensor Pins
const int trigFront = 7;   // PD0
const int echoFront = 27;  // PE5 or similar (verify mapping)
const int trigLeft = 32;   // PD7
const int echoLeft = 12;   // PA3
const int trigRight = 3;   // PB5
const int echoRight = 4;   // PB0

// Movement Parameters
const int STOP_DISTANCE = 20;     // cm
const int TURN_SPEED = 160;       // PWM value
const int CORRECTION_SPEED = 120; // PWM value
const int BASE_SPEED = 144;       // PWM value (for Move_Left, etc)

#endif // CONFIG_H
