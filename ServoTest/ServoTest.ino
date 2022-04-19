#include<Servo.h>

Servo steering;

void setup() {

  Serial.begin(9600);
  steering.attach(10);
}

void loop() {
  steering.write(85);
}
