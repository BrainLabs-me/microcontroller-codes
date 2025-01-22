#include "BLEHandler.h"
#include "EEGProcessor.h"

#define ADC_PIN 8 // Pin na koji je spojen delitelj napona (A0 / GPIO0)
#define R1 220000 // Vrednost R1 u omima (220 kΩ)
#define R2 220000 // Vrednost R2 u omima (100 kΩ)
#define MAX_BATTERY_VOLTAGE 4.2 // Maksimalan napon baterije
#define MIN_BATTERY_VOLTAGE 3.0 // Minimalan napon baterije

int led = LED_BUILTIN;
void setup() {
  Serial.begin(921600);
  initBLE();
  pinMode(led, OUTPUT);
  pinMode(EEG_PIN, INPUT);
}

void loop() {
  static int counter = 0;
  digitalWrite(led, HIGH);
  Serial.println(processEEGSignal());


  int rawADC = analogRead(ADC_PIN); // ADC očitavanje (0 - 4095)

  // Pretvori ADC vrednost u izlazni napon delitelja napona (0 - 3.3V)
  float measuredVoltage = (rawADC / 4095.0) * 3.3;

  // Skaliraj nazad na stvarni napon baterije
  float batteryVoltage = measuredVoltage * (R1 + R2) / R2;

  // Izračunaj procenat baterije
  float batteryPercentage = (batteryVoltage - MIN_BATTERY_VOLTAGE) /
                            (MAX_BATTERY_VOLTAGE - MIN_BATTERY_VOLTAGE) * 100;

  batteryPercentage = constrain(batteryPercentage, 0, 100); // Ograniči na 0-100%

  // Prikaz rezultata
  Serial.print("Battery Voltage: ");
  Serial.print(batteryVoltage);
  Serial.print(" V, Battery Percentage: ");
  Serial.print(batteryPercentage);
  Serial.println("%");
  updateBLE(String(rawADC));

}
