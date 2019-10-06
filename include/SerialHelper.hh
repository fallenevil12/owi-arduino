#ifndef SERIALHELPER_HH
#define SERIALHELPER_HH

#include "motor.hh"

/**
 * Struct to store parametters for openloop motor control
 */
struct oLoopCtrl {
    unsigned i;
    MOTOR::dir direction;
    unsigned pwm;
    unsigned long duration;
};

/**
 * get the parametters for manual control of each joints
 */
oLoopCtrl getCtrInput();

/**
 * choose joint to rotate 1 step
 */
oLoopCtrl manualStep();

/**
 * get an interger from Serial stream
 * the method used is not safe, betting on correct data format
 * only used temporarily
 */
int getInt();

#endif //SERIALHELPER_HH