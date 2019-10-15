#include <Arduino.h>
#include "owijoint.hh"
#include "SerialHelper.hh"

#define ANALOG_BITS 10
#define ANALOG_RANGE 5.0
#define VOLT2DEG_SCALE 50.0
#define ACCURACY 1.0
#define MAXPWM 255

JOINT::JOINT(CONFIG config):
    driver(config.enPin, config.dirPin1, config.dirPin2), 
    pot(config.potPin, ANALOG_BITS, ANALOG_RANGE, VOLT2DEG_SCALE),
    pid(config.pid),
    offset(config.degOffset),
    safemin(config.degMin),
    safemax(config.degMax) {}

bool JOINT::driveTo(float target) {
    getAngle();

    if (target < safemin || target > safemax) {
        driver.setDuration(-1);
        driver.setPower(0);
        driver.output();
        char buffer[100];
        sprintf(buffer, "Critical: Target %d out of safety bound. Operation halted.", static_cast<int>(target));
        adnoserial.println(buffer);
        while(1); //spin, need reset
    }

    float k = pid.pidCal(angle, target);

    if (k < 0) {
        k = fabs(k);
        driver.setDirection(MOTOR::dir::CW);
    } else {
        driver.setDirection(MOTOR::dir::CCW);
    }
    driver.setDuration(-1);
    driver.setPower(k*MAXPWM);
    driver.output();
    
    if (k == 0.0) return true; // expecting 0.0 value that pidCal would return if reached setpoint
    else return false;
}

bool JOINT::test_step_pos() {
    angle = pot.getDegreeVal();
    driver.setDirection(MOTOR::dir::CW);
    driver.setDuration(500);
    driver.setPower(200);
    driver.output();

    delay(500);
    if (pot.getDegreeVal() - angle > 3.0) return true;
    else return false;
}

bool JOINT::test_step_neg() {
    angle = pot.getDegreeVal();
    driver.setDirection(MOTOR::dir::CCW);
    driver.setDuration(500);
    driver.setPower(200);
    driver.output();

    delay(500);
    if (pot.getDegreeVal() - angle < -3.0) return true;
    else return false;
}

void JOINT::pid_test() {
    int target = 0;
    char buffer[100];
    sprintf(buffer, "Enter target angle degree (%d to %d)", static_cast<int>(safemin), static_cast<int>(safemax));

    do {
        adnoserial.println(buffer);
        target = getInt();
    } while (target < safemin || target > safemax);

    while (!driveTo(target)) {
        delay(1);
    }
}

float JOINT::getAngle() {
    angle = pot.getDegreeVal() - offset;

    if (angle < safemin || angle > safemax) {
    driver.setDuration(-1);
    driver.setPower(0);
    driver.output();
    char buffer[100];
    sprintf(buffer, "Critical: Joint angle (%d) out of safety bound. Operation halted.", static_cast<int>(angle));
    adnoserial.println(buffer);
    while(1); //spin, need reset
    }

    return angle;
}


