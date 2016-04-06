#ifndef UHX711_h
#define UHX711_h
#include "Arduino.h"

class UHX711
{
  private:
    byte CLOCK_PIN;
    byte OUT_PIN;
    byte GAIN;
    void setGain(byte gain = 128);
  public:
    UHX711(byte output_pin, byte clock_pin);
    virtual ~UHX711();
    bool readyToSend();
    long read();
};

#endif /* UHX711_h */
