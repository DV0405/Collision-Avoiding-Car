// Second version of DriveTest
// Author: Daniel Vigna, Brandon Cordrey
// Car will detect a targetDistance and stop at that distance from the wall or object

#include <Servo.h>

// Ultrasonic Sensor Globals
#define trigPin1 A0
#define echoPin1 A1

long duration;
long distance;
////////////////////////////

// Drive Globals ///////////
int driveMotorPin1 = 7;
int driveMotorPin2 = 8;

int speed;
int  targetDist = 20;
int  prevDist   = 0;
bool stopped    = false;
int throttleCounter = 10;

int count = 0;

////////////////////////////

// Servo ///////////////////
Servo steering;

void setup() {
  pinMode(5, INPUT);
  
  Serial.begin (9600);
  
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  pinMode(driveMotorPin1, OUTPUT);
  pinMode(driveMotorPin2, OUTPUT);

  pinMode(11, OUTPUT);

  steering.attach(10);
  
}

void loop() {

  drive(0);

  throttleCounter += 1;
  }

long getDistance() {

  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin1, HIGH);
  
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  
  return distance;
}

void turnLeft() {
  steering.write(105);
}

void centerSteering() {
  steering.write(85);
}

void turnRight() {
  steering.write(-90);
}

void drive(int dir) {

  // Essentially a null check
  if (dir != 0 || dir != 1) return;

  // Setting directions //
  
  // Forwards
  else if (dir == 1) {
    digitalWrite(driveMotorPin1, HIGH);
    digitalWrite(driveMotorPin2, LOW);
  }

  // Backwards
  else {
    digitalWrite(driveMotorPin1, LOW);
    digitalWrite(driveMotorPin2, HIGH);
  }

 // Actual drive code //
  long dist = getDistance();
  if(abs(dist - prevDist) > targetDist)
  {
    count = 0;
  }
  if(dist < targetDist) {
    count++;
    if (!stopped && count >= 10) {
      brake();
      stopped = true;
      targetDist = 40;
    }
  }
  else {
    if(throttleCounter > 10){
      throttleCounter = 0;
      speed = 200;
  }
  else
  {
    speed = 50;
  }

  analogWrite(11, speed);
  stopped = false;
  targetDist = 30;
}

  
}

void brake() {
  digitalWrite(driveMotorPin1, HIGH);
  digitalWrite(driveMotorPin2, LOW);
  analogWrite(11, 230);
  delay(200);
  speed = 0;

  turnRight();

  count = 0;
}
