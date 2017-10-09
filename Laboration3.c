#include <Servo.h>

Servo servoLeft;
Servo servoRight;

bool lightCheck = false;

int irLeft, irRight, speed = 60;

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
    irLeft = irDetect(9, 10, 37000);
    irRight = irDetect(2, 3, 37000);
    
    // make move according to detection
    if ((irLeft == 0) && (irRight == 0))
    {
      maneuver(-speed, -speed, 20);
      digitalWrite(7, HIGH);
      digitalWrite(8, HIGH);
    }
    else if (irLeft == 0)
    {
      maneuver(speed, -speed, 20);
      digitalWrite(7, LOW);
      digitalWrite(8, HIGH);
    }
    else if (irRight == 0)
    {
      maneuver(-speed, speed, 20);
      digitalWrite(7, HIGH);
      digitalWrite(8, LOW);
    }
    else
    {
      maneuver(speed, speed, 20);
      digitalWrite(7, LOW);
      digitalWrite(8, LOW);
    }
    
    Serial.println(rcTime(6));
    
    if (rcTime(6) < 1000)
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

long rcTime(int pin) // rcTime measures decay at pin
{
  pinMode(pin, OUTPUT); // Charge capacitor
  digitalWrite(pin, HIGH); // ..by setting pin ouput-high
  delay(5); // ..for 5 ms
  pinMode(pin, INPUT); // Set pin to input
  digitalWrite(pin, LOW); // ..with no pullup
  long time = micros(); // Mark the time
  while(digitalRead(pin)); // Wait for voltage < threshold
  time = micros() - time; // Calculate decay time
  return time; // Returns decay time
}
