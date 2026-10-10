#include <Servo.h>
#include <Encoder.h>

int dirPin = 2;
int pwmPin = 3;

int encAPin = 5;
int encBPin = 6;

int servoPin = 8;

Servo frontServo;
Encoder rearEnc(encAPin, encBPin);

void setup() {
  pinMode(dirPin, OUTPUT);  // motor DIR
  pinMode(pwmPin, OUTPUT);  // motor PWM
  digitalWrite(dirPin, HIGH);

  frontServo.attach(servoPin);

  Serial.begin(9600);
}

void loop() {
  // Motor: spin for 2s, stop for 1s
  analogWrite(3, 50);  // capped under 182 for 12V motor safety
  delay(2000);
  analogWrite(3, 0);
  delay(1000);

  // Servo sweep
  for (int pos = 1; pos < 50; pos += 1) {
    frontServo.write(pos);
    delay(15);
  }
  for (int pos = 50; pos >= 1; pos -= 1) {
    frontServo.write(pos);
    delay(15);
  }

  // Encoder: print position
  Serial.print("Encoder position: ");
  Serial.println(rearEnc.read());
}

