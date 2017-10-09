#include <Servo.h>

const int leftRec;

Servo servoLeft;
Servo servoRight;
bool lightCheck = false;

int irLeft, irRight;

void setup()
{
  Serial.begin(9600);
  
  pinMode(10, INPUT); // left receiver
  pinMode(9, OUTPUT); // left IR LED
  
  pinMode(3, INPUT); // right receiver
  pinMode(2, OUTPUT); // right IR LED
  
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  
  tone(4, 3000, 1000);
  delay(1000);
  
  servoLeft.attach(13);
  servoRight.attach(12);
}

void loop()
{
  while (lightCheck != true)
  {
    // check IR receivers
    irLeft = irDetect(9, 10, 34000);
    irRight = irDetect(2, 3, 34000);
    
    // make move according to detection
    if ((irLeft == 0) && (irRight == 0))
    {
      maneuver(-200, -200, 20);
      
      digitalWrite(7, !irRight);
      digitalWrite(8, !irLeft);
    }
    else if (irLeft == 0)
    {
      maneuver(200, -200, 20);
      
      digitalWrite(8, !irLeft);
    }
    else if (irRight == 0)
    {
      maneuver(-200, 200, 20);
      
      digitalWrite(7, !irRight);
    }
    else
    {
      maneuver(200, 200, 20);
      digitalWrite(7, !irRight);
      digitalWrite(8, !irLeft);
    }
    
    Serial.print(rcTime());
    Serial.print("  ");
    Serial.print(irLeft);
    Serial.print("  ");
    Serial.println(irRight);
    
    if (rcTime() < 100)
    {
      lightCheck = true;
      servoLeft.writeMicroseconds(1500);
      servoRight.writeMicroseconds(1500);
    }
  }
}

int irDetect(int irLedPin, int irReceiverPin, long frequency)
{
  tone(irLedPin, frequency, 8);
  delay(1);
  int ir = digitalRead(irReceiverPin);
  delay(1);
  return ir;
}

void maneuver(int speedLeft, int speedRight, int msTime)
{
  servoLeft.writeMicroseconds(1500 + speedLeft);
  servoRight.writeMicroseconds(1500 - speedRight);
  
  if (msTime == -1)
  {
    servoLeft.detach();
    servoRight.detach();
  }
  
  delay(msTime);
}

long rcTime()
{
  pinMode(6, OUTPUT);
  digitalWrite(6, HIGH);
  delay(5);
  pinMode(6, INPUT);
  digitalWrite(6, LOW);
  long time = micros();
  while(digitalRead(6));
  time = micros() - time;
  return time;
}
