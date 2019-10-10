#include <Arduino.h>
#include "pid.hh"

PID::PID(double _kp, double _ki, double _kd):
    kp(_kp), ki(_ki), kd(_kd) {}

void PID::setGain(double _kp, double _ki, double _kd) {
    kp = _kp;
    ki = _ki;
    kd = _kd;
}

void PID::reset() {
    err = 0.0;
    prevErr = 0.0;
    accmlErr = 0.0;
}

double PID::pidCal(double _val, double _refVal) {
    val = _val;
    refVal = _refVal;
    prevErr = err;
    err = val - refVal;

    accmlErr = accmlErr + err;
    if (ki*accmlErr > 0.5) accmlErr = 0.5/ki; //anti windup

    gain = kp*err + ki*accmlErr + kd*(err-prevErr);
    if (gain < -1.0) gain = -1.0;
    if (gain > 1.0) gain = 1.0;
    return gain;
}