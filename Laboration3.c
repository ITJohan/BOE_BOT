#include <Servo.h>

Servo servoLeft;
Servo servoRight;

bool lightCheck = false;

int irLeft, irRight, velocity = 60;
const int LEFT_REC = 10, LEFT_IR = 9, LEFT_LED = 7, RIGHT_REC = 3, RIGHT_IR = 2, RIGHT_LED = 8;

void setup()
{
  // pin setup
  pinMode(LEFT_REC, INPUT); // left receiver
  pinMode(LEFT_IR, OUTPUT); // left IR LED
  
  pinMode(RIGHT_REC, INPUT); // right receiver
  pinMode(RIGHT_IR, OUTPUT); // right IR LED
  
  pinMode(LEFT_LED, OUTPUT); // left LED
  pinMode(RIGHT_LED, OUTPUT); // right LED
  
  tone(4, 3000, 1000);
  delay(1000);
  
  servoLeft.attach(13);
  servoRight.attach(12);
}

void loop()
{
  // while photoresistor doesnt detect light
  while (lightCheck != true)
  {
    // check IR receivers
    irLeft = irDetect(LEFT_IR, LEFT_REC, 37000);
    irRight = irDetect(RIGHT_IR, RIGHT_REC, 37000);
    
    // make move according to detection
    if ((irLeft == 0) && (irRight == 0)) // move backward
    {
      maneuver(-velocity, -velocity, 20);
      digitalWrite(LEFT_LED, HIGH);
      digitalWrite(RIGHT_LED, HIGH);
    }
    else if (irLeft == 0) // turn right
    {
      maneuver(velocity, -velocity, 20);
      digitalWrite(LEFT_LED, LOW);
      digitalWrite(RIGHT_LED, HIGH);
    }
    else if (irRight == 0) // turn left
    {
      maneuver(-velocity, velocity, 20);
      digitalWrite(LEFT_LED, HIGH);
      digitalWrite(RIGHT_LED, LOW);
    }
    else // move forward
    {
      maneuver(velocity, velocity, 20);
      digitalWrite(LEFT_LED, LOW);
      digitalWrite(RIGHT_LED, LOW);
    }
    
    // turn off if photoresistor detects light
    if (rcTime(6) < 1000)
    {
      lightCheck = true;
      servoLeft.writeMicroseconds(1500);
      servoRight.writeMicroseconds(1500);
    }
  }
}

// returns 1 if IR, 0 if no IR
int irDetect(int irLedPin, int irReceiverPin, long frequency)
{
  tone(irLedPin, frequency, 8);
  delay(1);
  int ir = digitalRead(irReceiverPin);
  delay(1);
  return ir;
}

// control the wheels
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

// scan for light
long rcTime(int pin)
{
  // charge capacitor
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
  delay(5);
  
  // uncharge capacitor
  pinMode(pin, INPUT);
  digitalWrite(pin, LOW);
  
  // take time until 0
  long time = micros();
  while(digitalRead(pin));
  time = micros() - time;
  return time;
}
