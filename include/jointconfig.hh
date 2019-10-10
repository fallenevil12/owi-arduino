#ifndef JOINTCONFIG_HH
#define JOINTCONFIG_HH

#include <Arduino.h>
#include "owijoint.hh"

JOINT::CONFIG joint0conf {
    .enPin = 3,
    .dirPin1 = 26,
    .dirPin2 = 28,
    .potPin = A0,
    .degOffset = 40.0,
    .degMin = 20.0,
    .degMax = 120,
    .pid = PID(0.02, 0.001, 0.01)
};

JOINT::CONFIG joint1conf {
    .enPin = 3,
    .dirPin1 = 26,
    .dirPin2 = 28,
    .potPin = A0,
    .degOffset = 40.0,
    .degMin = 20.0,
    .degMax = 120,
    .pid = PID(0.02, 0.001, 0.01)
};

JOINT::CONFIG joint2conf {
    .enPin = 3,
    .dirPin1 = 26,
    .dirPin2 = 28,
    .potPin = A0,
    .degOffset = 130.0,
    .degMin = -90.0,
    .degMax = 90.0,
    .pid = PID(0.02, 0.001, 0.01)
};
JOINT::CONFIG joint3conf {
    .enPin = 3,
    .dirPin1 = 26,
    .dirPin2 = 28,
    .potPin = A0,
    .degOffset = 40.0,
    .degMin = 20.0,
    .degMax = 120,
    .pid = PID(0.02, 0.001, 0.01)
};

    JOINT::CONFIG joint4conf {
    .enPin = 3,
    .dirPin1 = 26,
    .dirPin2 = 28,
    .potPin = A0,
    .degOffset = 40.0,
    .degMin = 20.0,
    .degMax = 120,
    .pid = PID(0.02, 0.001, 0.01)
};

#endif //JOINTCONFIG_HH


