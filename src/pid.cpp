#include <Arduino.h>
#include "pid.hh"

#define ACCURACY 3.0

PID::PID(float _kp, float _ki, float _kd):
    kp(_kp), ki(_ki), kd(_kd) {}

void PID::setGain(float _kp, float _ki, float _kd) {
    kp = _kp;
    ki = _ki;
    kd = _kd;
}

void PID::reset() {
    err = 0.0;
    prevErr = 0.0;
    accmlErr = 0.0;
}

float PID::pidCal(float _val, float _refVal) {
    val = _val;
    refVal = _refVal;
    prevErr = err;
    err = val - refVal;
    static int count = 0;

    // return 0 if error stayed within accuracy for a while
    // add i term to reduce small error
    if (fabs(err) < ACCURACY) {
        count++;
        if (fabs(ki*accmlErr) < 0.5) accmlErr = accmlErr + err; // anti windup
        if (count > 100) {
            count = 0;
            reset();
            return 0.0;
        }
    } else {
        count = 0;
        accmlErr = 0;
    }

    gain = kp*err + ki*accmlErr + kd*(err-prevErr);
    if (gain < -1.0) gain = -1.0;
    if (gain > 1.0) gain = 1.0;
    return gain;
}