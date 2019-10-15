#include <Arduino.h>
#include "pid.hh"

#define ACCURACY 2.0

PID::PID(float _kp, float _ki, float _kd):
    kp(_kp), ki(_ki), kd(_kd) {}

void PID::setGain(float _kp, float _ki, float _kd) {
    kp = _kp;
    ki = _ki;
    kd = _kd;
}

float PID::pidCal(float _val, float _refVal) {
    val = _val;
    refVal = _refVal;
    prevErr = err;
    err = val - refVal;
    static int count = 0;

    // return 0 gain if error stayed within accuracy for a while
    // add i term to reduce small error
    if (fabs(err) < ACCURACY) {
        count++;
        if (count > 100) {
            count = 100;
            return 0.0;
        } else if (fabs(ki*accmlErr) < 0.5) { // anti windup
            accmlErr = accmlErr + err; 
        }
    } else {
        count = 0;
        accmlErr = 0;
    }

    gain = kp*err + ki*accmlErr + kd*(err-prevErr);
    if (fabs(gain) > 1.0) gain = gain/gain;
    return gain;
}