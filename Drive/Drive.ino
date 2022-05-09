#include <Servo.h>

#define trigPin1 A0
#define echoPin1 A1


int speed;
int ch2;
int motor1pin1 = 7;
int motor1pin2 = 8;
long duration;
int prevDist = 0;

bool manual = false;
bool stopped = false;

int targetDist = 20;
// 0 = center 1 = right -1 = left
int steerDir = 0;
int throttleCounter = 10;

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

  steering.attach(10);
}

void loop() {
      
  // ch2 = map(ch2, 995, 1990, 0, 255);

  if (manual)
  {
    ch2 = pulseIn(5, HIGH);
    Serial.println(ch2);
    if (ch2 > 1480) {
      ch2  = map(ch2, 1480, 1980, 0, 255);
      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, HIGH);
      analogWrite(11, ch2);
    }
    else if (ch2 < 1460) {
      ch2 = map(ch2, 1050, 1470, 0 , 255);
      digitalWrite(motor1pin1, HIGH);
      digitalWrite(motor1pin2, LOW);
      analogWrite(11, ch2);
    }
    else{
      digitalWrite(motor1pin1, 0);
      digitalWrite(motor1pin2, 0);
      analogWrite(11, 255);
    }
    
  }

  else
  {
    long dist = getDistance();
    Serial.println(dist);
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
      
      if(throttleCounter > 20){
        Serial.println("drive");
        throttleCounter = 0;
        speed = 200;
      }
      else
      {
        speed = 70;
      }
    
      stopped = false;
      targetDist = 30;
      
      steerDir = 0;
      
      setDir(true);

      analogWrite(11, speed);
    }

    checkSteer();
    
    throttleCounter += 1;
    prevDist = dist;
  } 

  
}



void setDir(boolean forward)
{
  // Forward
  if(forward)
  {
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, HIGH);
  }
  // Reverse
  else
  {
    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);
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
  steering.write(5);
}

void turnLeft() {
  steering.write(75);
}

void center() {
  steering.write(37);
}

void checkSteer()
{
  switch(steerDir)
  {
    case 0:
      center();
      break;
    case 1:
      turnRight();
      break;
    case -1:
      turnLeft();
      break;
  }
}

void brake() {
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  analogWrite(11, 230);
  delay(200);
  speed = 0;

  steerDir = -1;

  checkSteer();
    
  count = 0;

  setDir(false);
  speed = 150;
  analogWrite(11, speed);
  delay(1000);
}
