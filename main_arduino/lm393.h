#ifndef LM393_H
#define LM393_H

#include <Arduino.h>

class LM393 {
  private:
    int pin;         
    char reading[64]; 

  public:
    LM393(int p) : pin(p) {}
    void begin() {
      pinMode(pin, INPUT);
    }

    int read() {
      return analogRead(pin);
    }

    void WriteToBuff() {
      sprintf(reading, "{\"LM393\":%d}", read());
    }

    const char* getReading() {
      return reading;
    }
};

#endif
