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
 * publisher, subscriber through Serial1
 */
class ROSSERIAL {
public:
    /** 
     * constructor
     * @param cmdCallback callback for command subscriber
     */
    ROSSERIAL(void(*cmdCallback)(const owi::position_cmd&));

    /** 
     * init roshandle and topics
     * @param baud rate
     */
    void init(long baud);

    /** 
     * load message to be pushed to message topic 
     * @param message message string to be sent
     */
    void pushMsg(const char *message);

    /** 
     * load message to be pushed to command topic 
     * @param jointAngle array of angle position
     * @param numOfJoint number of joints position
     */
    void pushState(float *jointAngle, int numOfJoint);

    /** push and pull all ROS messages loaded */
    void update();

protected:
    /** ROS node */
    static ros::NodeHandle node;
    
    /** chatter message */
    std_msgs::String msg;
 
    /** joints position state message */
    owi::joint_state state;

    /** joints position command message */
    owi::position_cmd cmd;

    /** message publisher */
    ros::Publisher msgPub;
    
    /** state publisher */
    ros::Publisher statePub;

    /** command subscriber */
    ros::Subscriber<owi::position_cmd> cmdSub;

}; //class ROSSERIAL

#endif //SERIALHELPER_HH