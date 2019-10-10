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

}; //class JOINT

#endif //OWIJOINT_HH