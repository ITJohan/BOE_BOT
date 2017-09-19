#import <Servo.h>

// define speeds
const int idle = 1500;
const int maxRight = 1300;
const int maxLeft = 1700;
const int minRight = 1700;
const int minLeft = 1300;
const int acceleration = 4;

// define distances
const int shortDist = 250;
const int longDist = 1000;
const int rightTurn = 570;
const int leftTurn = 700;
const int oneEighty = 320;

// servo setup
Servo servoRight;
Servo servoLeft;

// pins setup
const int rightServoPin = 10;
const int leftServoPin = 11;
const int piezo = 4;

// setup notes
int note [] = {1046, 1318, 1568, 2093, 1568, 2093};
int noteLength [] = {200, 200, 200, 400, 200, 1000};

void setup() {
  
  // setup in/outs
  pinMode(piezo, OUTPUT);
  servoRight.attach(rightServoPin);
  servoLeft.attach(leftServoPin);
  
  // reset the servos
  servoRight.writeMicroseconds(idle);
  servoLeft.writeMicroseconds(idle);
  
  // run Z track
  forward(shortDist);
  turnRight(rightTurn);
  forward(longDist);
  turnLeft(leftTurn);
  forward(shortDist);
  fanfare();
  uTurn(oneEighty);
  forward(shortDist);
  turnRight(rightTurn);
  forward(longDist);
  turnLeft(leftTurn);
  forward(shortDist);
}

void loop() {  
  // nothing to loop
}

// runs forward
void forward(int time) {
  // accelerate servos
  for (int i = 0; i <= 200; i += acceleration) {
    servoRight.writeMicroseconds(idle - i);
    servoLeft.writeMicroseconds(idle + i);
    delay(10);
  }
  
  servoRight.writeMicroseconds(1300);
  servoLeft.writeMicroseconds(1610);
  delay(time);
  
  // decelerate servos
  for (int i = 0; i <= 200; i += acceleration) {
    servoRight.writeMicroseconds(maxRight + i);
    servoLeft.writeMicroseconds(maxLeft - i);
    delay(10);
  }
}

// turns right
void turnRight(int time) {
  // accelerate servo
  for (int i = 0; i <= 200; i += acceleration) {
    servoLeft.writeMicroseconds(idle + i);
    delay(10);
  }
  
  delay(time);
  
  // decelerate servo
  for (int i = 0; i <= 200; i += acceleration) {
    servoLeft.writeMicroseconds(maxLeft - i);
    delay(10);
  }
}

// turns left
void turnLeft(int time) {
  // accelerate servo
  for (int i = 0; i <= 200; i += acceleration) {
    servoRight.writeMicroseconds(idle - i);
    delay(10);
  }
  
  delay(time);
  
  // decelerate servo
  for (int i = 0; i <= 200; i += acceleration) {
    servoRight.writeMicroseconds(maxRight + i);
    delay(10);
  }
}

// makes a uturn
void uTurn(int time) {
  // accelerate servos
  for (int i = 0; i <= 200; i += acceleration) {
    servoRight.writeMicroseconds(idle - i);
    servoLeft.writeMicroseconds(idle - i);
    delay(10);
  }
  
  delay(time);
  
  // decelerate servos
  for (int i = 0; i <= 200; i += acceleration) {
    servoRight.writeMicroseconds(maxRight + i);
    servoLeft.writeMicroseconds(minLeft + i);
    delay(10);
  }
  
}

// plays fanfare
void fanfare() {
  for (int i = 0; i < sizeof(note)/sizeof(int); i++) {
    tone(4, note[i], noteLength[i]);
    delay(noteLength[i]);
  }
}
