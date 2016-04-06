#ifndef UHX711_h
#define UHX711_h
#include "Arduino.h"

class UHX711
{
  private:
    byte CLOCK_PIN;
    byte OUT_PIN;
    byte GAIN;
		uint8_t simpleShiftIn(uint8_t dataPin, uint8_t clockPin);
    void setGain(byte gain = 128);
  public:
    UHX711(byte output_pin, byte clock_pin);
    virtual ~UHX711();
    bool readyToSend();
    long read();
};

#endif /* UHX711_h */
