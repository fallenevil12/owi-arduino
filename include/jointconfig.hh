#ifndef JOINTCONFIG_HH
#define JOINTCONFIG_HH

#include <Arduino.h>
#include "robotjoint.hh"

JOINT::CONFIG joint0conf {
    .enPin = 2,
    .dirPin1 = 23,
    .dirPin2 = 25,
    .potPin = A0,
    .degOffset = 115.0,
    .degMin = -100.0,
    .degMax = 100.0,
    .pid = PID(0.08, 0.0002, 0.2)
};

JOINT::CONFIG joint1conf {
    .enPin = 3,
    .dirPin1 = 29,
    .dirPin2 = 27,
    .potPin = A1,
    .degOffset = 40.0,
    .degMin = 20.0,
    .degMax = 160,
    .pid = PID(0.08, 0.0002, 0.2)
};

JOINT::CONFIG joint2conf {
    .enPin = 4,
    .dirPin1 = 33,
    .dirPin2 = 31,
    .potPin = A2,
    .degOffset = 130.0,
    .degMin = -120.0,
    .degMax = 120.0,
    .pid = PID(0.08, 0.0002, 0.2)
};
JOINT::CONFIG joint3conf {
    .enPin = 5,
    .dirPin1 = 35,
    .dirPin2 = 37,
    .potPin = A3,
    .degOffset = 130.0, //TODO: joint 3 has different gear ratio
    .degMin = -125.0,
    .degMax = 125.0,
    .pid = PID(0.05, 0.0002, 0.9)
};

    JOINT::CONFIG joint4conf {
    .enPin = 6,
    .dirPin1 = 39,
    .dirPin2 = 41,
    .potPin = A4,
    .degOffset = 130.0,
    .degMin = -40.0,
    .degMax = 50.0,
    .pid = PID(0.05, 0.0002, 0.9)
};

#endif //JOINTCONFIG_HH


