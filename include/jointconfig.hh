#ifndef JOINTCONFIG_HH
#define JOINTCONFIG_HH

#include <Arduino.h>
#include "owijoint.hh"

JOINT::CONFIG joint0conf {
    .enPin = 2,
    .dirPin1 = 22,
    .dirPin2 = 24,
    .potPin = A0,
    .degOffset = 130.0,
    .degMin = -100.0,
    .degMax = 100.0,
    .pid = PID(0.02, 0.001, 0.05)
};

JOINT::CONFIG joint1conf {
    .enPin = 3,
    .dirPin1 = 26,
    .dirPin2 = 28,
    .potPin = A1,
    .degOffset = 40.0,
    .degMin = 20.0,
    .degMax = 160,
    .pid = PID(0.02, 0.001, 0.05)
};

JOINT::CONFIG joint2conf {
    .enPin = 4,
    .dirPin1 = 30,
    .dirPin2 = 32,
    .potPin = A2,
    .degOffset = 130.0,
    .degMin = -100.0,
    .degMax = 100.0,
    .pid = PID(0.02, 0.001, 0.05)
};
JOINT::CONFIG joint3conf {
    .enPin = 5,
    .dirPin1 = 34,
    .dirPin2 = 36,
    .potPin = A3,
    .degOffset = 130.0,
    .degMin = -45.0,
    .degMax = 45.0,
    .pid = PID(0.02, 0.001, 0.05)
};

    JOINT::CONFIG joint4conf {
    .enPin = 6,
    .dirPin1 = 38,
    .dirPin2 = 40,
    .potPin = A4,
    .degOffset = 130.0,
    .degMin = -45.0,
    .degMax = 45.0,
    .pid = PID(0.02, 0.001, 0.05)
};

#endif //JOINTCONFIG_HH


