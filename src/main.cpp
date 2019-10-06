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
//     static L298N joint[5] = { L298N(6, 13, 12),
//                               L298N(3, 26, 28),
//                               L298N(4, 22, 24),
//                               L298N(5, 26, 28),
//                               L298N(2, 30, 32)  };

//     static POTENTIO pot[2] = { POTENTIO(A0, 10, 5.0, 50),
//                                POTENTIO(A1, 10, 5.0, 50) };
//     Serial.println(pot[0].getDegreeVal());
//     Serial.println(pot[1].getDegreeVal());
//     oLoopCtrl userInput = manualStep();
//     joint[userInput.i].update(userInput.direction, userInput.pwm);
//     joint[userInput.i].setDuration(userInput.duration);
//     joint[userInput.i].output();
//     delay(1000);
    PID pid= PID(0.02, 0.001, 0.02);
    JOINT joint1 = JOINT(3, 26, 28, A0, pid);

    int target = 130;
    do {
        while(!Serial.available());
        Serial.println("Enter target angle (100-150)");
        target = getInt();
    } while (target < 100 || target > 150);
    while (!joint1.driveTo(target)) {
        delay(10);
    }
}

