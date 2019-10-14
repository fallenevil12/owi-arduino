#include <Arduino.h>
#include "SerialHelper.hh"


/**
 *  class ROSSERIAL
 */
ros::NodeHandle ROSSERIAL::node;

ROSSERIAL::ROSSERIAL(void(*cmdCallback)(const trajectory_msgs::JointTrajectoryPoint&)):
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

void ROSSERIAL::print(const char *message) {
    msg.data = message;
    msgPub.publish(&msg);
    node.spinOnce();
}

void ROSSERIAL::pushState(float *jointAngle, int numOfJoint) {
    state.position_length = numOfJoint;
    state.position = jointAngle;
    statePub.publish(&state);
    node.spinOnce();
}

void ROSSERIAL::pullCommand() {
    node.spinOnce();
}

oLoopCtrl getCtrInput() {
    oLoopCtrl recv = {};
    
    int number = -1;
    while (number < 0 || number > 4) {
        adnoserial.print("\nEnter joint index\n");
        number = getInt();
    }
    recv.i = number;

    char dir = ' ';
    while (dir != 'r' && dir !='l') {
        adnoserial.print("\nEnter direction (l/r)\n");
        while(!adnoserial.available());
        dir = adnoserial.read();
    }
    (dir == 'r') ? (recv.direction = MOTOR::dir::CW) : 
                   (recv.direction = MOTOR::dir::CCW);

    number = -1;
    while (number < 0 || number > 255) {
        adnoserial.print("\nEnter power (0-255)\n");
        number = getInt();
    }
    recv.pwm = number;

    number = -1;
    while (number < 0) {
        adnoserial.print("\nEnter duration (ms)\n");
        number = getInt();
    }
    recv.duration = number;

    return recv;
}


int getInt() {
    char buffer[10];

    while(!adnoserial.available()); //spin and wait for incoming data
    int length = adnoserial.readBytesUntil('\n', buffer, 10);
    buffer[length] = '\0';      //terminate received string
    int number = atoi(buffer);
    adnoserial.println(number);
    return number;
}

int displayMenu(String menu, int numOfChoices) {
    adnoserial.print(menu);
    int choice = -1;
    do {
        while(!adnoserial.available());
        choice = getInt();
    } while (choice < 0 || choice > numOfChoices - 1);
    return choice;
}



