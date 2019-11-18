#include <Arduino.h>
#include "pid.hh"

#define ACCURACY 3.0

PID::PID(float _kp, float _ki, float _kd):
    kp(_kp), ki(_ki), kd(_kd) {}

void PID::setCoef(float _kp, float _ki, float _kd) {
    kp = _kp;
    ki = _ki;
    kd = _kd;
}

float PID::pidCal(float _val, float _refVal) {
    val = _val;
    refVal = _refVal;
    prevErr = err;
    err = val - refVal;

    // just return 0 gain if error stayed within accuracy for a while
    if (fabs(err) < ACCURACY) {
        count++;
        if (count > 10) {
            count = 10;
            return 0.0;
        }
    } else {
        count = 0;
    }
    Serial.println(err);
    // add i term to reduce small error
    if (fabs(err) < 2*ACCURACY) {
        if (fabs(ki*accmlErr) < 0.5) accmlErr = accmlErr + err; //prevent windup saturation
    } else {
        accmlErr = 0;
    }


    gain = kp*err + ki*accmlErr + kd*(err-prevErr);
    if (gain > 1.0) gain = 1.0;
    if (gain < -1.0) gain = -1.0;
    return gain;
}