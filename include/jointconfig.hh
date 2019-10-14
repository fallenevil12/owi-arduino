#ifndef JOINTCONFIG_HH
#define JOINTCONFIG_HH

#include <Arduino.h>
#include "owijoint.hh"

JOINT::CONFIG joint0conf {
    .enPin = 2,
    .dirPin1 = 23,
    .dirPin2 = 25,
    .potPin = A0,
    .degOffset = 130.0,
    .degMin = -100.0,
    .degMax = 100.0,
    .pid = PID(0.1, 0.001, 0.3)
};

JOINT::CONFIG joint1conf {
    .enPin = 3,
    .dirPin1 = 29,
    .dirPin2 = 27,
    .potPin = A1,
    .degOffset = 40.0,
    .degMin = 20.0,
    .degMax = 160,
    .pid = PID(0.1, 0.001, 0.3)
};

JOINT::CONFIG joint2conf {
    .enPin = 4,
    .dirPin1 = 33,
    .dirPin2 = 31,
    .potPin = A2,
    .degOffset = 130.0,
    .degMin = -100.0,
    .degMax = 100.0,
    .pid = PID(0.1, 0.001, 0.3)
};
JOINT::CONFIG joint3conf {
    .enPin = 5,
    .dirPin1 = 35,
    .dirPin2 = 37,
    .potPin = A3,
    .degOffset = 130.0,
    .degMin = -60.0,
    .degMax = 60.0,
    .pid = PID(0.1, 0.00, 0.3)
};

    JOINT::CONFIG joint4conf {
    .enPin = 6,
    .dirPin1 = 39,
    .dirPin2 = 41,
    .potPin = A4,
    .degOffset = 130.0,
    .degMin = -60.0,
    .degMax = 60.0,
    .pid = PID(0.1, 0.001, 0.3)
};

#endif //JOINTCONFIG_HH


