#include <Arduino.h>
#include "motor.hh"
#include "SerialHelper.hh"

/** put your setup code here, to run once */
void setup() {
    Serial.begin(9600);
}

/** put your main code here, to run repeatedly */
void loop() {
    static L298N joint[5] = { L298N(13, 22, 24),
                              L298N(12, 26, 28),
                              L298N(11, 30, 32),
                              L298N(10, 34, 36),
                              L298N(9, 36, 38)  };

    oLoopCtrl userInput = getCtrInput();
    joint[userInput.i].update(userInput.direction, userInput.pwm);
    joint[userInput.i].setDuration(userInput.duration);
    joint[userInput.i].output();

}

