#include <Servo.h>

Servo servoLeft;
Servo servoRight;

int irLeft, irRight;

void setup()
{
  pinMode(10, INPUT); // left receiver
  pinMode(9, OUTPUT); // left IR LED
  
  pinMode(3, INPUT); // right receiver
  pinMode(2, OUTPUT); // right IR LED
  
  tone(4, 3000, 1000);
  delay(1000);
  
  servoLeft.attach(13);
  servoRight.attach(12);
}

void loop()
{
  // check IR receivers
  irLeft = irDetect(9, 10, 38000);
  irRight = irDetect(2, 3, 38000);
  
  // make move according to detection
  if ((irLeft == 0) && (irRight == 0))
  {
    maneuver(-200, -200, 20);
  }
  else if (irLeft == 0)
  {
    maneuver(200, -200, 20);
  }
  else if (irRight == 0)
  {
    maneuver(-200, 200, 20);
  }
  else
  {
    maneuver(200, 200, 20);
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
