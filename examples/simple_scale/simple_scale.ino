#include <UHX711.h>

const byte hx711_data_pin = A2; // Use A pins not safe for STM32. There are only numbered pins in STM32Duino librares
const byte hx711_clock_pin = A3;

UHX711 hx711(hx711_data_pin, hx711_clock_pin);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(hx711.read()/100.0);
  delay(500);
}
