#include <Arduino.h>
#include "motor.hh"
#include "rotsensor.hh"
#include "SerialHelper.hh"
#include "owijoint.hh"
#include "pid.hh"

/** put your setup code here, to run once */
void setup() {
    Serial.begin(9600);
}

/** put your main code here, to run repeatedly */
void loop() {
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

    JOINT joint1(joint1conf);

    int target = 0;
    do {
        Serial.println("Enter target angle (30 to 110)");
        while(!Serial.available());
        target = getInt();
    } while (target < 30 || target > 110);
    while (!joint1.driveTo(target)) {
        delay(10);
    }
}

// void motor_dir_test() {
//     static JOINT joint[5] = { JOINT(6, 13, 12),
//                               JOINT(3, 26, 28),
//                               JOINT(4, 22, 24),
//                               JOINT(5, 26, 28),
//     Serial.println(pot[0].getDegreeVal());

//     Serial.println(pot[1].getDegreeVal());
//     oLoopCtrl userInput = manualStep();
//     joint[userInput.i].update(userInput.direction, userInput.pwm);
//     joint[userInput.i].setDuration(userInput.duration);
//     joint[userInput.i].output();
//     delay(1000);
// }
