#include <Arduino.h>
#include "owijoint.hh"
#include "SerialHelper.hh"

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
    getAngle();

    if (angle < safemin || angle > safemax || target < safemin || target > safemax) {
        driver.setDuration(-1);
        driver.setPower(0);
        driver.output();
        Serial.println("Critical: Joint angle or target out of safety bound. Operation halted.");
        while(1);
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

    if (k == 0.0) return true; // expecting 0.0 value pidCal would return if reached setpoint
    else return false;
}

bool JOINT::test_step_pos() {
    angle = pot.getDegreeVal();
    driver.setDirection(MOTOR::dir::CW);
    driver.setDuration(500);
    driver.setPower(100);
    driver.output();

    if (pot.getDegreeVal() - angle > 10.0) return true;
    else return false;
}

bool JOINT::test_step_neg() {
    angle = pot.getDegreeVal();
    driver.setDirection(MOTOR::dir::CCW);
    driver.setDuration(200);
    driver.setPower(100);
    driver.output();

    if (pot.getDegreeVal() - angle < -10.0) return true;
    else return false;
}

void JOINT::pid_test() {
    int target = 0;
    char buffer[100];
    sprintf(buffer, "Enter target angle degree (%d to %d)", static_cast<int>(safemin), static_cast<int>(safemax));

    do {
        Serial.println(buffer);
        while(!Serial.available());
        target = getInt();
    } while (target < safemin || target > safemax);

    while (!driveTo(target)) {
        delay(10);
    }
}

double JOINT::getAngle() {
    angle = pot.getDegreeVal() - offset;
    return angle;
}

void init_step_test(JOINT *joint) {
    char buffer[100];
    for (int i = 0; i < 5; i++) {
        if (!joint[i].test_step_pos()) {
            sprintf(buffer, "Joint[%d] tested failed in positive direction", i);
            Serial.println(buffer);
        }
        delay(500);
        if (!joint[i].test_step_neg()) {
            sprintf(buffer, "Joint[%d] tested failed in negative direction", i);
            Serial.println(buffer);
        }
        delay(500);
    }
}

