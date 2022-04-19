// Second version of DriveTest
// Author: Daniel Vigna, Brandon Cordrey
// Car will detect a targetDistance and stop at that distance from the wall or object


// Ultrasonic Sensor Globals
#define trigPin1 A0
#define echoPin1 A1

long duration;
long distance;
////////////////////////////

// Drive Globals ///////////
int ch2;
int driveMotorPin1 = 2;
int driveMotorPin2 = 3;
////////////////////////////

void setup() {
  pinMode(5, INPUT);
  
  Serial.begin (9600);
  
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  pinMode(driveMotorPin1, OUTPUT);
  pinMode(driveMotorPin2, OUTPUT);

  pinMode(9, OUTPUT);
  
}

void loop() {
  
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
  
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  ch2 = pulseIn(5, HIGH);

  // Make car drive forwards
  int power = distance * 5;
  digitalWrite(driveMotorPin1, HIGH);
  digitalWrite(driveMotorPin2, LOW);
  analogWrite(9, power);

  if (distance < 7) {
    analogWrite(9, 0);
  }

}
