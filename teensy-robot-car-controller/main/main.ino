// NOTES: 
// 
// NEVER GO ABOVE 182 (12V)
// 255 = 16.8V (too much but provided by battery)
// 182 = ~12V (perfect) - highest can go

#include <Encoder.h>

// Communication between teensy and cytron motor driver
int dirPin = 2;  // (tells the motor driver which direction to spin)
int pwmPin = 3;  // (tells the motor driver how fast to spin (0=stop;255=full speed))

Encoder rearEnc(4, 5);

void setup() {
  // initialise digital pin as an outputs
  pinMode(dirPin, OUTPUT);
  pinMode(pwmPin, OUTPUT);

  Serial.begin(9600);  // Sets communcation at 9600 baud (necessary for print statements)
  Serial.println("Cytron with encoder test");
  digitalWrite(dirPin, HIGH);  // Motor driver should spin the motor forward
}

void loop() {
  // motor control
  Serial.println("Sending PWM signal...");
  analogWrite(pwmPin, 128);  // Motor at half speed

  // encoder reading
  long position = rearEnc.read();
  Serial.println(position);
  
  delay(2000);

  // motor control
  analogWrite(pwmPin, 0); // sets PWM to 0;

  // encoder reading
  position = rearEnc.read();
  Serial.println(position);

  delay(1000);
}