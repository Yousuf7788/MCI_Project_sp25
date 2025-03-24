//initial commit


// Motor Control Pins
const int LEFT_PWM  = 14;  // PB6 (M0PWM0) - Left Motor Speed 
const int RIGHT_PWM = 15;  // PB7 (M0PWM1) - Right Motor Speed 
const int LEFT_IN1  = 11;  // PA2 - Left Motor Direction 1 
const int LEFT_IN2  = 25;  // PD2 - Left Motor Direction 2 
const int RIGHT_IN3 = 19;  // PB2 - Right Motor Direction 1 
const int RIGHT_IN4 = 38;  // PB3 - Right Motor Direction 2

cmFront = getDistance(trigFront, echoFront);
cmLeft = getDistance(trigLeft, echoLeft);
cmRight = getDistance(trigRight, echoRight);

int straight_speed = 255;  // Speed for straight-line motion (0-255) 
int stop_distance = 10;    // Stop when obstacle is within 30 cm
int turn_speed2 = 200;      // Speed for turning
int reverse_speed = 100;   // Speed for reversing
int turn_speed = 180;       // Speed for minor adjustments
int correction_speed = 130; // Speed for adjusting to maintain 5cm wall gap

int wall_distance = 5;

void setup() { 
    Serial.begin(9600);

    pinMode(LEFT_IN1, OUTPUT); 
    pinMode(LEFT_IN2, OUTPUT); 
    pinMode(RIGHT_IN3, OUTPUT); 
    pinMode(RIGHT_IN4, OUTPUT); 
    pinMode(LEFT_PWM, OUTPUT); 
    pinMode(RIGHT_PWM, OUTPUT);

}

void loop() { 

    Move_Forward();
    delay(5);  // Small delay for sensor stabilization
    if (cmFront > 0 && cmFront < stop_distance) {

        Move_Right();
          // Serial.println("Obstacle detected! Turning Right.");
      } 
      // Adjust right if too close to left wall
      else if (cmLeft > 0 && cmLeft < wall_distance) {
          Serial.println("Too close to left wall, adjusting right.");
          Adjust_Right();
      } 
      // Adjust left if too close to right wall
      else if (cmRight > 0 && cmRight < wall_distance) {
          Serial.println("Too close to right wall, adjusting left.");
          Adjust_Left();
      }
      // Move forward normally
      else { 
          Move_Forward();
  
}
}

void Move_Right() { 
    digitalWrite(LEFT_IN1, LOW); 
    digitalWrite(LEFT_IN2, HIGH); 
    digitalWrite(RIGHT_IN3, LOW); 
    digitalWrite(RIGHT_IN4, HIGH); 
    analogWrite(LEFT_PWM, turn_speed2);  
    analogWrite(RIGHT_PWM, 50); // Slow down right wheel for turning
    delay(900);  // Adjust experimentally for a 90° turn

}


// Move Left (Turn left to avoid obstacle)
void Move_Left() { 
    digitalWrite(LEFT_IN1, LOW); 
    digitalWrite(LEFT_IN2, HIGH); 
    digitalWrite(RIGHT_IN3, LOW); 
    digitalWrite(RIGHT_IN4, HIGH); 
    analogWrite(LEFT_PWM, 50);  // Slow down left wheel for turning
    analogWrite(RIGHT_PWM, turn_speed2);  
    delay(900);  // Adjust experimentally for a 90° turn
//    Stop_Motors();
}

// Move Forward
void Move_Forward() { 
    digitalWrite(LEFT_IN1, LOW); 
    digitalWrite(LEFT_IN2, HIGH); 
    digitalWrite(RIGHT_IN3, LOW); 
    digitalWrite(RIGHT_IN4, HIGH); 
    analogWrite(LEFT_PWM, 150);  
    analogWrite(RIGHT_PWM, 150); 
}

// Stop Motors
void Stop_Motors() { 
    analogWrite(LEFT_PWM, 0);  
    analogWrite(RIGHT_PWM, 0); 
}
