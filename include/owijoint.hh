#ifndef OWIJOINT_HH
#define OWIJOINT_HH

#include "motor.hh"
#include "rotsensor.hh"
#include "pid.hh"

/** Represent a joint (and coresponding link) on OWI robot with control methods */
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
        double degOffset;
        /** safe min angle */
        double degMin;
        /** safe max anle */
        double degMax;
        /** pid parametters */
        PID pid;
    };

    /** 
     * construcotr 
     * @param config configuration parametters for a joint
    */
    JOINT(CONFIG config);

    /**
     * <WARNING> at this time this method has to be called within a 
     * loop without excessive delay </WARNING>
     * rotate joint to angle
     * @param target angle value in degree
     * @return true once reached target (within defined accuracy)
     */
    bool driveTo(double target);

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

    /** 
     * get joint angle value in degree, according to D-H convention
     */
    double getAngle();

private:
    /* motor driver */
    L298N driver;
    /* potentiometer driver */
    POTENTIO pot;
    /* pid */
    PID pid;
    /* position of 0 degree (D-H convention) relative to raw angle  */
    double offset;
    /* operating angle lower bound */
    double safemin;
    /* operating angle upper bound */
    double safemax;
    /* corresponding link angle */
    double angle;

}; //class JOINT

/** 
 * Initial stepping to test if the rotation directions are as expected
 * make sure joints has enough room to move about 10degree, as this is open loop and has no safety check
 */
void init_step_test(JOINT *joint);


#endif //OWIJOINT_HH