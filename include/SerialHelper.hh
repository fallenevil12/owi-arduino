#ifndef SERIALHELPER_HH
#define SERIALHELPER_HH

#include <ros.h>
#include <std_msgs/String.h>
#include <sensor_msgs/JointState.h>
#include "motor.hh"

/**
 * Struct to store parametters for openloop motor control
 */
struct oLoopCtrl {
    unsigned i;
    MOTOR::dir direction;
    unsigned pwm;
    unsigned long duration;
};

/**
 * get the parametters for manual control of each joints
 */
oLoopCtrl getCtrInput();

/**
 * get an interger from Serial stream
 * the method used is not safe, betting on correct data format
 * only used temporarily
 */
int getInt();

/**
 * display a menu passed in as String, and get user's choice
 * index start at 0 to number of choice - 1
 * @param menu string
 * @param numOfChoice number of choices
 * @return user's input
 */
int displayMenu(String menu, int numOfChoice);

class ROSSERIAL {
public:
    ROSSERIAL();
    void print(const char *message);
    void sendState(float *jointAngle, int numOfJoint);

protected:
    static ros::NodeHandle node;
    std_msgs::String msg;
    sensor_msgs::JointState state;
    ros::Publisher msgPub;
    ros::Publisher statePub;
};

#endif //SERIALHELPER_HH