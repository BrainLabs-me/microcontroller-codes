#ifndef BLEHANDER_H
#define BLEHANDER_H

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <BLEServer.h>

extern BLECharacteristic *pCharacteristic;
extern bool deviceConnected;

void initBLE();
void updateBLE(String newValue);

#endif
