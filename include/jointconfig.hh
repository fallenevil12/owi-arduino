#ifndef JOINTCONFIG_HH
#define JOINTCONFIG_HH

#include <Arduino.h>
#include "robotjoint.hh"

/** configuration for joint 0 */
JOINT::CONFIG joint0conf {
    .id = 0,
    .enPin = 2,
    .dirPin1 = 25,
    .dirPin2 = 23,
    .potPin = A0,
    .degOffset = 150.0,
    .ratio = 1.0,
    .degMin = -90.0,
    .degMax = 90.0,
    .pid = PID(0.08, 0.0003, 0.2)
};

/** configuration for joint 1 */
JOINT::CONFIG joint1conf {
    .id = 1,
    .enPin = 3,
    .dirPin1 = 29,
    .dirPin2 = 27,
    .potPin = A1,
    .degOffset = 40.0,
    .ratio = 1.0,
    .degMin = 20.0,
    .degMax = 160,
    .pid = PID(0.08, 0.003, 0.2)
};

/** configuration for joint 2 */
JOINT::CONFIG joint2conf {
    .id = 2,
    .enPin = 4,
    .dirPin1 = 33,
    .dirPin2 = 31,
    .potPin = A2,
    .degOffset = 130.0,
    .ratio = 1.0,
    .degMin = -120.0,
    .degMax = 120.0,
    .pid = PID(0.08, 0.003, 0.2)
};

/** configuration for joint 3 */
JOINT::CONFIG joint3conf {
    .id = 3,
    .enPin = 5,
    .dirPin1 = 35,
    .dirPin2 = 37,
    .potPin = A3,
    .degOffset = 130.0,
    .ratio = 3.0,
    .degMin = -60.0,
    .degMax = 60.0,
    .pid = PID(0.1, 0.0002, 0.2)
};

/** configuration for joint 4 */
JOINT::CONFIG joint4conf {
    .id = 4,
    .enPin = 6,
    .dirPin1 = 39,
    .dirPin2 = 41,
    .potPin = A4,
    .degOffset = 130.0,
    .ratio = 1.0,
    .degMin = -40.0,
    .degMax = 50.0,
    .pid = PID(0.03, 0.0001, 0.05)
};

#endif //JOINTCONFIG_HH


