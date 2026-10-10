#include <Servo.h>
#include <Encoder.h>

// Pins
const int dirPin = 2;
const int pwmPin = 3;
const int encAPin = 5;
const int encBPin = 6;
const int servoPin = 8;

// Settings
const int MOTOR_SPEED = 50;
const unsigned long MOTOR_ON_MS = 2000;
const unsigned long MOTOR_OFF_MS = 1000;

const int SERVO_MIN = 1;
const int SERVO_MAX = 49;
const unsigned long SERVO_STEP_MS = 15;

const unsigned long PRINT_MS = 200;

// Hardware
Servo frontServo;
Encoder rearEnc(encAPin, encBPin);

// State
bool motorOn = false;
unsigned long lastMotorChange = 0;

int servoPos = SERVO_MIN;
int servoStep = 1;
unsigned long lastServoStep = 0;

unsigned long lastPrint = 0;

void setup() {
  pinMode(dirPin, OUTPUT);
  pinMode(pwmPin, OUTPUT);
  digitalWrite(dirPin, HIGH);

  frontServo.attach(servoPin);
  frontServo.write(servoPos);

  Serial.begin(9600);

  // Start with the motor spinning
  motorOn = true;
  analogWrite(pwmPin, MOTOR_SPEED);
  lastMotorChange = millis();
}

// Toggles the motor on/off when its time is up
void updateMotor(unsigned long now) {
  unsigned long interval = motorOn ? MOTOR_ON_MS : MOTOR_OFF_MS;
  if (now - lastMotorChange >= interval) {
    motorOn = !motorOn;
    analogWrite(pwmPin, motorOn ? MOTOR_SPEED : 0);
    lastMotorChange = now;
  }
}

// Moves the servo one degree every SERVO_STEP_MS, bouncing between min and max
void updateServo(unsigned long now) {
  if (now - lastServoStep >= SERVO_STEP_MS) {
    servoPos += servoStep;
    if (servoPos >= SERVO_MAX || servoPos <= SERVO_MIN) {
      servoStep = -servoStep; // reverse direction at each end
    }
    frontServo.write(servoPos);
    lastServoStep = now;
  }
}

// Prints the encoder count every PRINT_MS
void updatePrint(unsigned long now) {
  if (now - lastPrint >= PRINT_MS) {
    Serial.print("Encoder position: ");
    Serial.println(rearEnc.read());
    lastPrint = now;
  }
}

void loop() {
  unsigned long now = millis();
  updateMotor(now);
  updateServo(now);
  updatePrint(now);
  // no delay() anywhere, so each task gets checked thousands of times a second
}
