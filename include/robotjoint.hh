#ifndef ROBOTJOINT_HH
#define ROBOTJOINT_HH

#include "motor.hh"
#include "rotsensor.hh"
#include "pid.hh"
#include "SerialHelper.hh"

/** Represent a joint (and coresponding link angle) on OWI robot with control methods */
class JOINT {

public:

    /** configuration parametters for a joint */
    struct CONFIG {
        /** pwm Pin */
        uint8_t enPin;
        /** dir pin 1 */
        uint8_t dirPin1;
        /** dir pin 2 */
        uint8_t dirPin2;
        /** analog in pin */
        uint8_t potPin;
        /** angle of defined 0 degree (D-H convention) relative to raw angle */
        float degOffset;
        /** safe min angle */
        float degMin;
        /** safe max anle */
        float degMax;
        /** pid parametters */
        PID pid;
    };

    /** 
     * constructor
     * @param config configuration parametters for a joint
    */
    JOINT(CONFIG config);

    /**
     * set the target angle, no actuation occur here
     */
    void setTarget(float targetAngle);

    /** 
     * get joint angle value in degree, according to D-H convention
     */
    float getAngle();

    /**
     * safety stop
     */
    void halt();

    /**
     * <WARNING> THIS METHOD HAS TO BE CALLED WITHIN A LOOP </WARNING>
     * rotate joint to target angle
     * @return true if reached target or target out of bound
     */
    bool actuate();

    /**
     * for initial testing of correct wiring of motor and sensor
     * do a small joint movement to see if it is moving in the positive direction of sensor
     * @return true if the movement cause positive change in sensor reading
     */
    bool test_step_pos();

    /**
     * for initial testing of correct wiring or motor and sensor
     * do a small joint movement to see if it is moving in the negative direction of sensor
     * @return true if the movement cause negative change in sensor reading
     */
    bool test_step_neg();

    /**
     * Test pid for a joint
     */
    void pid_test();


private:

    /** motor driver */
    L298N driver;
    /** potentiometer driver */
    POTENTIO pot;
    /** pid */
    PID pid;
    /** position of 0 degree (D-H convention) relative to raw angle  */
    float offset;
    /** operating angle lower bound */
    float safemin;
    /** operating angle upper bound */
    float safemax;
    /** corresponding link angle */
    float angle;
    /** target angle */
    float target;

}; //class JOINT




#endif //ROBOTJOINT_HH