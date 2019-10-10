#include <Arduino.h>
#include "rotsensor.hh"

POTENTIO::POTENTIO(uint8_t _pin, unsigned bits, double range, double _scale):
    pin(_pin), res(range/pow(2,bits)), scale(_scale) {}

int POTENTIO::getRawVal() {
    rawVal = analogRead(pin);
    return rawVal;
}

double POTENTIO::getVoltVal() {
    getRawVal();
    //Serial.println(res, 10);
    volt = rawVal * res;
    return volt; 
}

double POTENTIO::getDegreeVal() {
    getVoltVal();
    degree = volt * scale;
    return degree;
}

void POTENTIO::setScale(double _scale) {
    scale = _scale;
}