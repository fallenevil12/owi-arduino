#include <Arduino.h>
#include "SerialHelper.hh"


oLoopCtrl getCtrInput() {
    oLoopCtrl recv = {};
    
    Serial1.print("!!!Data has to be sent with endline character!!!\n");

    int number = -1;
    while (number < 0 || number > 4) {
        Serial1.print("\nEnter joint index\n");
        number = getInt();
    }
    recv.i = number;

    char dir = ' ';
    while (dir != 'r' && dir !='l') {
        Serial1.print("\nEnter direction (l/r)\n");
        while(!Serial1.available());
        dir = Serial1.read();
    }
    (dir == 'r') ? (recv.direction = MOTOR::dir::CW) : 
                   (recv.direction = MOTOR::dir::CCW);

    number = -1;
    while (number < 0 || number > 255) {
        Serial1.print("\nEnter power (0-255)\n");
        number = getInt();
    }
    recv.pwm = number;

    number = -1;
    while (number < 0) {
        Serial1.print("\nEnter duration (ms)\n");
        number = getInt();
    }
    recv.duration = number;

    return recv;
}


int getInt() {
    char buffer[32];

    while(!Serial1.available()); //spin and wait for incoming data
    int length = Serial1.readBytesUntil('\n', buffer, 31);
    buffer[length] = '\0';      //terminate received string
    int number = atoi(buffer);
    Serial1.println(number);
    return number;
}

int displayMenu(String menu, int numOfChoices) {
    Serial1.print(menu);
    int choice = -1;
    do {
        while(!Serial1.available());
        choice = getInt();
    } while (choice < 0 || choice > numOfChoices - 1);
    return choice;
}


ros::NodeHandle ROSSERIAL::node;

ROSSERIAL::ROSSERIAL():
    msgPub("message", &msg), statePub("joint_state", &state) {
    node.initNode();
    node.advertise(msgPub);
    node.advertise(statePub);
}


void ROSSERIAL::print(const char *message) {
    msg.data = message;
    msgPub.publish(&msg);
    node.spinOnce();
}

void ROSSERIAL::sendState(float *jointAngle, int numOfJoint) {
    state.position_length = numOfJoint;
    state.position = jointAngle;
    statePub.publish(&state);
    node.spinOnce();
}
