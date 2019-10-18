#ifndef SERIALHELPER_HH
#define SERIALHELPER_HH

#include <ros.h>
#include <std_msgs/String.h>
#include <owi/joint_state.h>
#include <owi/position_cmd.h>
#include "motor.hh"

#define adnoserial Serial

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
int displayMenu(const char* menu, int numOfChoice);

/**
 * initilization and helper methods of a rosnode,
 * publisher, subscriber through serial1
 */
class ROSSERIAL {
public:
    ROSSERIAL(void(*cmdCallback)(const owi::position_cmd&));
    void init(long baud);
    void pushMsg(const char *message);
    void pushState(float *jointAngle, int numOfJoint);
    void update();
protected:
    static ros::NodeHandle node;
    std_msgs::String msg;
    owi::joint_state state;
    owi::position_cmd cmd;
    ros::Publisher msgPub;
    ros::Publisher statePub;
    ros::Subscriber<owi::position_cmd> cmdSub;
}; //class ROSSERIAL

#endif //SERIALHELPER_HH