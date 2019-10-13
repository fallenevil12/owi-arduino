#ifndef SERIALHELPER_HH
#define SERIALHELPER_HH

#include <ros.h>
#include <std_msgs/String.h>
#include <sensor_msgs/JointState.h>
#include <trajectory_msgs/JointTrajectoryPoint.h>
#include "motor.hh"

/**
 * initilization and helper methods of a rosnode,
 * publisher, subscriber through serial1
 */
class ROSSERIAL {
public:
    ROSSERIAL(void(*cmdCallback)(const trajectory_msgs::JointTrajectoryPoint&));
    void print(const char *message);
    void sendState(float *jointAngle, int numOfJoint);

protected:
    static ros::NodeHandle node;
    std_msgs::String msg;
    sensor_msgs::JointState state;
    trajectory_msgs::JointTrajectoryPoint cmd;
    ros::Publisher msgPub;
    ros::Publisher statePub;
    //ros::Subscriber<trajectory_msgs::JointTrajectoryPoint> cmdSub;
}; //class ROSSERIAL

/**
 * this class wrap around a chosen arduino Serial port#
 * and provides helpers for communication
 */
class ADNOSERIAL {
public:
    /**
     * Struct to store parametters for openloop motor control
     */
    struct oLoopCtrl {
        unsigned i;
        MOTOR::dir direction;
        unsigned pwm;
        unsigned long duration;
    };

    ADNOSERIAL(HardwareSerial &SerialAlias);

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

    /** alias for the Arduino serial port used */
    HardwareSerial &Serial;
private:
    
}; //class ADNOSERIAL



#endif //SERIALHELPER_HH