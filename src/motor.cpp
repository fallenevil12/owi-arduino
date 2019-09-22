#include "Arduino.h"
#include "motor.hh"

motor::motor() {

}

void motor::update(dir direction, uint8_t power) {
    setDirection(direction);
    setPower(power);
}

void motor::setDirection(dir direction) {
    Dir = direction;
}

void motor::setPower(uint8_t power) {
    pwm = power;
}

L298N::L298N(unsigned enPin, unsigned in1Pin, unsigned in2Pin) :
             enP(enPin), in1P(in1Pin), in2P(in2Pin), dur(0) {
    pinMode(enP, OUTPUT);
    pinMode(in1P, OUTPUT);
    pinMode(in2P, OUTPUT);
}

void L298N::setDuration(unsigned long duration) {
    dur = duration;
}

void L298N::output() {
    switch (Dir) {
        case dir::CW:
            digitalWrite(in1P, 0);
            digitalWrite(in2P, 1);
            break;

        case dir::CCW:
            digitalWrite(in1P, 1);
            digitalWrite(in2P, 0);
            break;

        default:
            break;
    }

    analogWrite(enP, pwm);
    delay(dur);
    analogWrite(enP, 0);
}