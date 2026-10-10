#include <Servo.h>

Servo myservo;

int pos = 0;

void setup() {
  Serial.begin(9600);
  myservo.attach(8);
}

void loop() {
  Serial.println("Moving forward");
  // goes from 10 degrees to 170 degrees
  for (pos = 1; pos < 50; pos += 1) {
    myservo.write(pos);
    delay(15);
  }

  Serial.println("Moving backwards");
  // goes from 180 degrees to 0 degrees
  for (pos = 50; pos >= 1; pos-=1) {
    myservo.write(pos);
    delay(15);
  }
}