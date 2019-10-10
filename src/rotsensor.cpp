#include <Arduino.h>
#include "rotsensor.hh"

POTENTIO::POTENTIO(uint8_t _pin, unsigned bits, double range, double _scale):
    pin(_pin), res(range/pow(2,bits)), scale(_scale) {
        degree = analogRead(pin) * res * scale;
    }

int POTENTIO::getRawVal() {
    rawVal = analogRead(pin);
    return rawVal;
}

double POTENTIO::getVoltVal() {
    getRawVal();
    volt = rawVal * res;
    return volt; 
}

double POTENTIO::getDegreeVal() {
    getVoltVal();
    // low pass filter
    static const double coef = 0.5;
    degree = coef*degree + (1.0 - coef)*(volt * scale);

    return degree;
}

void POTENTIO::setScale(double _scale) {
    scale = _scale;
}