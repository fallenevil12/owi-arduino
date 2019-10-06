#include <Arduino.h>
#include "SerialHelper.hh"

oLoopCtrl getCtrInput() {
    oLoopCtrl recv = {};
    
    Serial.print("!!!Data has to be sent with endline character!!!\n");

    int number = -1;
    while (number < 0 || number > 4) {
        Serial.print("\nEnter joint index\n");
        number = getInt();
    }
    recv.i = number;

    char dir = ' ';
    while (dir != 'r' && dir !='l') {
        Serial.print("\nEnter direction (l/r)\n");
        while(!Serial.available());
        dir = Serial.read();
    }
    (dir == 'r') ? (recv.direction = MOTOR::dir::CW) : 
                   (recv.direction = MOTOR::dir::CCW);

    number = -1;
    while (number < 0 || number > 255) {
        Serial.print("\nEnter power (0-255)\n");
        number = getInt();
    }
    recv.pwm = number;

    number = -1;
    while (number < 0) {
        Serial.print("\nEnter duration (ms)\n");
        number = getInt();
    }
    recv.duration = number;

    return recv;
}

oLoopCtrl manualStep() {
    oLoopCtrl recv = {0, MOTOR::dir::CW, 100, 200};

    int number = -1;
    while (number < 0 || number > 9) {
        Serial.print("\nEnter joint index (0,1,2,3,4 for CW... 5,6,7,8,9 for CCW\n");
        number = getInt();
    }
    recv.i = number % 5;
    (number < 4) ? (recv.direction = MOTOR::dir::CW) :
                   (recv.direction = MOTOR::dir::CCW);


    return recv;
}

int getInt() {
    char buffer[32];

    while(!Serial.available()); //spin and wait for incoming data
    int length = Serial.readBytesUntil('\n', buffer, 31);
    buffer[length] = '\0';      //terminate received string
    int number = atoi(buffer);
    Serial.println(number);
    return number;
}

