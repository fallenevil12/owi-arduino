#include <Arduino.h>
#include "owijoint.hh"

#define ANALOG_BITS 10
#define ANALOG_RANGE 5.0
#define VOLT2DEG_SCALE 50.0
#define ACCURACY 1.0
#define MAXPWM 100

JOINT::JOINT(CONFIG config):
    driver(config.enPin, config.dirPin1, config.dirPin2), 
    pot(config.potPin, ANALOG_BITS, ANALOG_RANGE, VOLT2DEG_SCALE),
    pid(config.pid),
    offset(config.degOffset),
    safemin(config.degMin),
    safemax(config.degMax) {}

bool JOINT::driveTo(double target) {
    double angle = pot.getDegreeVal() - offset;

    if (angle < safemin || angle > safemax || target < safemin || target > safemax) {
        driver.setDuration(-1);
        driver.setPower(0);
        driver.output();
        Serial.println("Critical: Joint angle or target out of safety bound. Operation halted.");
        while(1);
    }

    if (fabs(target - angle) < ACCURACY) {
        driver.setDuration(-1);
        driver.setPower(0);
        driver.output();
        pid.reset();
        return true;
    }

    double k = pid.pidCal(angle, target);

    if (k < 0) {
        k = fabs(k);
        driver.setDirection(MOTOR::dir::CW);
    } else {
        driver.setDirection(MOTOR::dir::CCW);
    }
    driver.setDuration(-1);
    driver.setPower(k*MAXPWM);
    driver.output();
    
    Serial.println(angle);
    return false;

}