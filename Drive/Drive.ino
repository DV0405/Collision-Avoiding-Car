#include <Servo.h>

#define trigPin1 A0
#define echoPin1 A1


int speed;
int ch2;
int motor1pin1 = 7;
int motor1pin2 = 8;
long duration;

bool manual = false;
bool stopped = false;

Servo steering;

int count = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(5, INPUT);
  Serial.begin(9600);
  // Drive Direction
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  // Drive speed
  pinMode(11, OUTPUT);
  //Ultrasonic
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  //steering.attach(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  
      
  // ch2 = map(ch2, 995, 1990, 0, 255);

  if (manual)
  {
    ch2 = pulseIn(7, HIGH);
    Serial.println(ch2);
    if (ch2 > 1480) {
      ch2  = map(ch2, 1480, 1980, 0, 255);
      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, HIGH);
      analogWrite(9, ch2);
    }
    else if (ch2 < 1470) {
      ch2 = map(ch2, 1050, 1470, 0 , 255);
      digitalWrite(motor1pin1, HIGH);
      digitalWrite(motor1pin2, LOW);
      analogWrite(11, ch2);
    }
  }

  else
  {
    long dist = getDistance();
    Serial.println(dist);
    if(dist < 50.0) {
      count++;
      if (!stopped && count >= 3) {
        brake();
        stopped = true;
      }
    }
    else {
      speed = 255;
      stopped = false;
    }

    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, HIGH);
    analogWrite(11, speed);

//    turnLeft();
//    delay(2000);
//    center();
//    delay(2000);
//    turnRight();
//    delay(2000);
//    center();
  }  
}

int getDistance()
{
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin1, HIGH);
  // Calculating the distance
  return duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  
}

void turnRight() {
  steering.write(-90);
}

void turnLeft() {
  steering.write(105);
}

void center() {
  steering.write(85);
}

void brake() {
  speed = 0;

  count = 0;
}
