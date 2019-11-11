#include <Arduino.h>
#include "rotsensor.hh"

POTENTIO::POTENTIO(uint8_t _pin, unsigned bits, float range, float _scale):
    pin(_pin), res(range/pow(2,bits)), scale(_scale) {}

int POTENTIO::getRawVal() {
    // //averaging filter
    // rawVal = 0;
    // for (int i = 0; i < 4; i++) {
    //     rawVal += analogRead(pin);
    // }
    // rawVal /= 4;
    rawVal = analogRead(pin);
    return rawVal;
}

float POTENTIO::getVoltVal() {
    getRawVal();
    volt = rawVal * res;
    return volt; 
}

float POTENTIO::getDegreeVal() {
    getVoltVal();
    // low pass filter
    static bool firstpass = true;
    static const float coef = 0.5;
    if (firstpass) {
        degree = volt*scale;
        firstpass = false;
    } else {
        degree = coef*degree + (1.0 - coef)*(volt * scale);
    }

    return degree;
}
