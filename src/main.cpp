#include <Arduino.h>
#include "motor.hh"
#include "SerialHelper.hh"

/** put your setup code here, to run once */
void setup() {
    Serial.begin(9600);
}

/** put your main code here, to run repeatedly */
void loop() {
    static L298N joint[5] = { L298N(6, 13, 12),
                              L298N(3, 26, 28),
                              L298N(5, 11, 10),
                              L298N(4, 22, 24),
                              L298N(2, 30, 32)  };

    oLoopCtrl userInput = getCtrInput();
    joint[userInput.i].update(userInput.direction, userInput.pwm);
    joint[userInput.i].setDuration(userInput.duration);
    joint[userInput.i].output();

}

