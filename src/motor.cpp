#include "motor.h"
#include "config.h"

void Motor_Init() {
    pinMode(LEFT_IN1, OUTPUT); 
    pinMode(LEFT_IN2, OUTPUT); 
    pinMode(RIGHT_IN3, OUTPUT); 
    pinMode(RIGHT_IN4, OUTPUT); 
    pinMode(LEFT_PWM, OUTPUT); 
    pinMode(RIGHT_PWM, OUTPUT);
}

void Move_Forward() { 
    digitalWrite(LEFT_IN1, HIGH); 
    digitalWrite(LEFT_IN2, LOW); 
    digitalWrite(RIGHT_IN3, LOW); 
    digitalWrite(RIGHT_IN4, HIGH); 
    analogWrite(LEFT_PWM, 130);  
    analogWrite(RIGHT_PWM, 125); 
}

void Move_Left() { 
    // Turn left to avoid obstacle
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

void Adjust_Left() { 
    // Move Slightly Left (Correct right wall proximity)
    digitalWrite(LEFT_IN1, HIGH); 
    digitalWrite(LEFT_IN2, LOW); 
    digitalWrite(RIGHT_IN3, LOW); 
    digitalWrite(RIGHT_IN4, HIGH); 
    analogWrite(LEFT_PWM, 144);  
    analogWrite(RIGHT_PWM, TURN_SPEED);  
}

void Adjust_Right() { 
    // Move Slightly Right (Correct left wall proximity)
    digitalWrite(LEFT_IN1, HIGH); 
    digitalWrite(LEFT_IN2, LOW); 
    digitalWrite(RIGHT_IN3, LOW); 
    digitalWrite(RIGHT_IN4, HIGH); 
    analogWrite(LEFT_PWM, 192);  
    analogWrite(RIGHT_PWM, CORRECTION_SPEED); 
}

void Stop_Motors() { 
    analogWrite(LEFT_PWM, 0);  
    analogWrite(RIGHT_PWM, 0); 
}
