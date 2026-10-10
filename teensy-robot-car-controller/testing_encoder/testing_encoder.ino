#include <Encoder.h>

Encoder rearEnc(4,5);

void setup() {
  Serial.begin(9600);
  Serial.println("Encoder Test");
}

void loop() {
  long position = rearEnc.read();
  Serial.println(position);
  delay(100);
}