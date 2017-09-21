#include <Servo.h>

// setup
Servo servoLeft;
Servo servoRight;

byte wLeftOld;
byte wRightOld;
byte counter;

void setup()
{
  // setup pins
  pinMode(8, INPUT);
  pinMode(6, INPUT);
  pinMode(9, OUTPUT);
  pinMode(2, OUTPUT);
  tone(4, 3000, 1000);
  
  delay(1000);
  
  servoLeft.attach(11);
  servoRight.attach(10);
  
  // initialize variables
  wLeftOld = 0;
  wRightOld = 1;
  counter = 0;
}

void loop()
{
  // read newest whisker values
  byte wLeft = digitalRead(6);
  byte wRight = digitalRead(8);
  
  // u-turn setup
  if(wLeft != wRight)
  {
    if ((wLeft != wLeftOld) && (wRight != wRightOld))
    {
      counter++;
      wLeftOld = wLeft;
      wRightOld = wRight;
      if(counter == 4) // do if 4 crashes
      {
        wLeft = 0;
        wRight = 0;
        counter = 0;
      }
    }
    else
    {
      counter = 0;
    }
  }
  
  // navigation controller
  if((wLeft == 0) && (wRight == 0)) // turn backward and make u-turn
  {
    backward(1000, wLeft, wRight);
    turnLeft(800);
  }
  else if(wLeft == 0) // turn backward and right
  {
    digitalWrite(9,HIGH);
    digitalWrite(2,LOW);
    backward(1000, wLeft, wRight);
    turnRight(400);
  }
  else if(wRight == 0) // turn backward and left
  {
    digitalWrite(9,LOW);
    digitalWrite(2,HIGH);
    backward(1000, wLeft, wRight);
    turnLeft(400);
  }
  else // move forward
  {
    digitalWrite(9,LOW);
    digitalWrite(2,LOW);
    forward(20);
  }
}

void forward(int time) // forward function
{
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1300);
  delay(time);
}

void turnLeft(int time) // left function
{
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1300);
  delay(time);
}

void turnRight(int time) // right function
{
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1700);
  delay(time);
}

// backward function
void backward(int time, int left, int right)
{
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1700);

  if (left == 0 && right == 0) // make sound and blink 3 times if both whiskers are active
  {
    for (int i = 0; i < 3; i++)
    {
      tone(4, 3000, 250);
      digitalWrite(9, HIGH);
      digitalWrite(2, HIGH);
    
      delay(time/6);
    
      digitalWrite(9, LOW);
      digitalWrite(2, LOW);
    
      delay(time/6);
    }
  }
  else // standard case
  {
    delay(time);
  }
}
