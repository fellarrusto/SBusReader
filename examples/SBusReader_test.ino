#include "SBusReader.h""

SBusReader receiver(6);

void setup() {
  Serial.begin(115200);
  receiver.begin();
}

void loop() {
  receiver.update();

  for (int i = 0; i < 6; i++) {
    Serial.print(" c");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(receiver.getChannel(i));
  }
  Serial.println("");
  delay(50);
}
