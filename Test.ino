void setup()
{
  tone(4, 2000, 1000);
  delay(1000);

  Serial.begin(9600);
}

void loop()
{
  long tLeft = rcTime(8);

  Serial.print("tLeft = ");
  Serial.print(tLeft);
  Serial.println(" us");

  delay(1000);
}

long rcTime(int pin)
{
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);
  delay(1);
  pinMode(pin, INPUT);
  digitalWrite(pin, LOW);
  long time = micros();
  while(digitalRead(pin));
  time = micros() - time;
  return time;
}

