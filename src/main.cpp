#include <Arduino.h>
#include "SerialHelper.hh"
#include "motor.hh"
#include "owijoint.hh"
#include "jointconfig.hh"

/** put your setup code here, to run once */
void setup() {
    Serial.begin(9600);
}

/** put your main code here, to run repeatedly */
void loop() {


    static JOINT joint[5] = { JOINT(joint0conf),
                              JOINT(joint1conf),
                              JOINT(joint2conf),
                              JOINT(joint3conf),
                              JOINT(joint4conf) };

    int target = 0;
    do {
        Serial.println("Enter target angle (30 to 110)");
        while(!Serial.available());
        target = getInt();
    } while (target < 30 || target > 110);
    while (!joint[1].driveTo(target)) {
        delay(10);
    }
}

/** 
 * Manually stepping to test if the rotation directions are as expected
 * make sure joints has enough room to move about 10degree, as this is open loop and has no safety check
 */
// void rotate_dir_test() {
//     static L298N motor[5] = { L298N(join0conf.enPin, joint0conf.dirPin1, joint0conf.dirPin2),
//                               L298N(join1conf.enPin, joint1conf.dirPin1, joint1conf.dirPin2),
//                               L298N(join2conf.enPin, joint2conf.dirPin1, joint2conf.dirPin2),
//                               L298N(join3conf.enPin, joint3conf.dirPin1, joint3conf.dirPin2),
//                               L298N(join4conf.enPin, joint4conf.dirPin1, joint4conf.dirPin2) }

//     oLoopCtrl userInput = manualStep();
//     joint[userInput.i].update(userInput.direction, userInput.pwm);
//     joint[userInput.i].setDuration(userInput.duration);
//     joint[userInput.i].output();
//     delay(1000);
// }
