#include <Arduino.h>
#include "robotjoint.hh"
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
    ratio(config.ratio),
    safemin(config.degMin),
    safemax(config.degMax),
    target((safemin + safemax)/2) {}

void JOINT::setTarget(float targetAngle) {
    target = targetAngle;
}

float JOINT::getAngle(bool fresh=true) {
    if (fresh == true) {
        angle = (pot.getDegreeVal() - offset)/ratio;
    }

    if (angle <= safemin || angle >= safemax) {
        halt();
        char buffer[100];
        sprintf(buffer, "\n!!!Critical: Joint angle (%d) out of safety bound. Operation halted.\n", static_cast<int>(angle));
        Serial.println(buffer);
    }

    return angle;
}

void JOINT::halt() {
    driver.setDuration(-1);
    driver.setPower(0);
    driver.output();
}
bool JOINT::actuate() {
    getAngle();

    if (target <= safemin + 5 || target >= safemax - 5) {
        halt();
        char buffer[100];
        sprintf(buffer, "\n!!!Warning: Target %d out of safety bound. Halt movement!\n", static_cast<int>(target));
        Serial.println(buffer);
        return true;
    }

    float k = pid.pidCal(angle, target);

    if (k < 0) {
        k = fabs(k);
        driver.setDirection(MOTOR::DIR::POS);
    } else {
        driver.setDirection(MOTOR::DIR::NEG);
    }
    driver.setDuration(-1);
    driver.setPower(k*MAXPWM);
    driver.output();

    if (k == 0.0) return true; // expecting 0.0 value that pidCal would return if reached setpoint
    else return false;
}

bool JOINT::test_step_pos() {
    int temp_angle = pot.getDegreeVal();
    driver.setDirection(MOTOR::DIR::POS);
    driver.setDuration(500);
    driver.setPower(200);
    driver.output();
    
    delay(500);
    if (pot.getDegreeVal() - temp_angle > 3.0) return true;
    else return false;
}

bool JOINT::test_step_neg() {
    int temp_angle = pot.getDegreeVal();
    driver.setDirection(MOTOR::DIR::NEG);
    driver.setDuration(500);
    driver.setPower(200);
    driver.output();

    delay(500);
    if (pot.getDegreeVal() - temp_angle < -3.0) return true;
    else return false;
}

void JOINT::pid_test() {
    char buffer[100];
    sprintf(buffer, "Enter target angle degree (%d to %d)", static_cast<int>(safemin+5), static_cast<int>(safemax-5));

    do {
        Serial.println(buffer);
        target = getInt();
    } while (target < safemin || target > safemax);

    while (!actuate()) {
        Serial.println(angle);
    }
}



