//Zach, Milan, Peter

#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *rightMotor = AFMS.getMotor(4);

Adafruit_DCMotor *leftMotor = AFMS.getMotor(3);

long duration, distance;


void setup() {
  AFMS.begin();
  pinMode(7, OUTPUT);
  pinMode(8, INPUT);
  Serial.begin(9600);

}

  void fowards(){
  rightMotor->setSpeed(450);//go straight
  leftMotor->setSpeed(450);

  rightMotor->run(FORWARD);
  leftMotor->run(FORWARD);
  }

  void right(){
  rightMotor->setSpeed(500);
  leftMotor->setSpeed(500);//right turn

  rightMotor->run(FORWARD);
  leftMotor->run(BACKWARD);
  }

void left(){
  rightMotor->setSpeed(500);
  leftMotor->setSpeed(500);//left turn

  rightMotor->run(BACKWARD);
  leftMotor->run(FORWARD);
}

void backward(){
  rightMotor->setSpeed(300);
  leftMotor->setSpeed(300);//left turn

  rightMotor->run(BACKWARD);
  leftMotor->run(BACKWARD);
}



long distanceTest(){
  digitalWrite(7, LOW);
  delayMicroseconds(2);
  digitalWrite(7, HIGH);
  delayMicroseconds(10);
  digitalWrite(7, LOW);
  duration = pulseIn(8, HIGH);
  distance = (duration/2) / 29.1;
  Serial.print(distance);
  return distance;
}

void loop() {
  // put your main code here, to run repeatedly:
long dist = distanceTest(); // Get the distance from the ultrasonic sensor
Serial.print("Distance: ");
Serial.println(dist); // Output the distance for debugging

if (dist > 20) 
{
fowards();
} 

else {
rightMotor->run(RELEASE);
leftMotor->run(RELEASE);
delay(500); // Pause for 500 milliseconds

// Attempt to avoid obstacle
right(); 
delay(250); // Allow time to turn before moving again
fowards(); // Continue moving forward
}

delay(100); // Small delay to allow car to respond to changes
}
