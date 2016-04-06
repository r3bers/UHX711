#include <Arduino.h>
#include "UHX711.h"

UHX711::UHX711(byte output_pin, byte clock_pin) {
  CLOCK_PIN  = clock_pin;
  OUT_PIN  = output_pin;
  GAIN = 1;
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(OUT_PIN, INPUT);
}

UHX711::~UHX711() {
}

uint8_t UHX711::simpleShiftIn(uint8_t dataPin, uint8_t clockPin) { // ShiftIn without bitorder
	uint8_t value = 0;
	uint8_t i;

	for (i = 0; i < 8; ++i) {
		digitalWrite(clockPin, HIGH);
		value |= digitalRead(dataPin) << (7 - i);
		digitalWrite(clockPin, LOW);
	}
	return value;
}


bool UHX711::readyToSend() {
  return digitalRead(OUT_PIN) == LOW;
}

void UHX711::setGain(byte gain) {
  switch (gain) {
    case 128:
      GAIN = 1;
      break;
    case 64:
      GAIN = 3;
      break;
    case 32:
      GAIN = 2;
      break;
  }

  digitalWrite(CLOCK_PIN, LOW);
  read();
}

long UHX711::read() {
   while (!readyToSend());

  byte data[3];

  for (byte j = 3; j--;) {
      data[j] = simpleShiftIn(OUT_PIN,CLOCK_PIN); // Erase «MSBFIRST» to simplify code and to work on other platforms
  }

  // set gain
  for (int i = 0; i < GAIN; i++) {
    digitalWrite(CLOCK_PIN, HIGH);
    digitalWrite(CLOCK_PIN, LOW);
  }

  data[2] ^= 0x80;
  return ((uint32_t) data[2] << 16) | ((uint32_t) data[1] << 8) | (uint32_t) data[0];
}
