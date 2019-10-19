#include <Arduino.h>
#include "SerialHelper.hh"
#include <Arduino_FreeRTOS.h>


/**
 *  class ROSSERIAL
 */
ros::NodeHandle ROSSERIAL::node;

ROSSERIAL::ROSSERIAL(void(*cmdCallback)(const owi::position_cmd&)):
    msgPub("message", &msg),
    statePub("joint_state", &state),
    cmdSub("command", cmdCallback) {
}

void ROSSERIAL::init(long baud) {
    node.getHardware()->setBaud(baud);
    node.initNode();
    node.advertise(msgPub);
    node.advertise(statePub); 
    node.subscribe(cmdSub);
}

void ROSSERIAL::pushMsg(const char *message) {
    msg.data = message;
    msgPub.publish(&msg);
}

void ROSSERIAL::pushState(float *jointAngle, int numOfJoint) {
    //state.position_length = numOfJoint;
    for (int i = 0; i < numOfJoint; i++) {
        state.position[i] = jointAngle[i];
    }
    statePub.publish(&state);
}

void ROSSERIAL::update() {
    node.spinOnce();
}

oLoopCtrl getCtrInput() {
    oLoopCtrl recv = {};
    
    int number = -1;
    while (number < 0 || number > 4) {
        Serial.print("\nEnter joint index\n");
        number = getInt();
    }
    recv.i = number;

    char dir = ' ';
    while (dir != 'r' && dir !='l') {
        Serial.print("\nEnter direction (l/r)\n");
        while(!Serial.available()) vTaskDelay(100/portTICK_PERIOD_MS);
        dir = Serial.read();
    }
    (dir == 'r') ? (recv.direction = MOTOR::dir::pos) : 
                   (recv.direction = MOTOR::dir::neg);

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
    char buffer[10];

    while(!Serial.available()) vTaskDelay(100/portTICK_PERIOD_MS);
    int length = Serial.readBytesUntil('\n', buffer, 10);
    buffer[length] = '\0';      //terminate received string
    int number = atoi(buffer);
    Serial.println(number);
    return number;
}

int displayMenu(const char* menu, int numOfChoices) {
    Serial.print(menu);
    int choice = -1;
    do {
        choice = getInt();
    } while (choice < 0 || choice > numOfChoices - 1);
    return choice;
}



