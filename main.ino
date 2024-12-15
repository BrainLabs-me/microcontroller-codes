#include "BLEHandler.h"
#include "EEGProcessor.h"
void setup() {
  Serial.begin(115200);
  initBLE();
  pinMode(EEG_PIN, INPUT);
}

void loop() {
  static int counter = 0;
  updateBLE(String(processEEGSignal()));
  Serial.println(processEEGSignal());
}
