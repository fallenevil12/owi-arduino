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


int getInt() {
    char buffer[32];

    while(!Serial.available()); //spin and wait for incoming data
    int length = Serial.readBytesUntil('\n', buffer, 31);
    buffer[length] = '\0';      //terminate received string
    int number = atoi(buffer);
    Serial.println(number);
    return number;
}

int displayMenu(String menu, int numOfChoices) {
    Serial.print(menu);
    int choice = -1;
    do {
        while(!Serial.available());
        choice = getInt();
    } while (choice < 0 || choice > numOfChoices - 1);
    return choice;
}