#include <stdint.h>

/**
 * Abstract motor driver class
 */
class motor {
public:

    /** direction of motor spin 
     * CW - clockwise
     * CCW - counter clockwise
    */
    enum class dir {
        CW = 0,
        CCW = 1
    };

    /**
     * Constructor
     */
    motor();

    /**
     * new control parametters 
     */
    void update(dir direction, uint8_t power);

    /**
     *  perform the motion
     */
    virtual void output() = 0;

    /** set rotational direction */
    void setDirection(dir direction);

    /** set duty cycle */
    void setPower(uint8_t power);

protected:

    /** rotation direction */
    dir Dir{dir::CW};

    /** duty cycle (0-255) */
    uint8_t pwm{0};

    /** rotational position */
    unsigned pos{0};
};

/**
 * L298N motor driver with arduino
 */
class L298N : public motor {
public:

    /**
     * Constructor
     */
    L298N(unsigned enPin, unsigned in1Pin, unsigned in2Pin);

    /**
     * set duration of the motion
     * @param duration time motor run in ms
     */
    void setDuration(unsigned long duration);
    
    /**
     * perform the motion
     */
    void output() override;

    /**
     * perform reverse of last motion
     */
    void reverse();

private:

    /** enable (PWM) pin */
    const unsigned enP;

    /** direction pin 1 */
    const unsigned in1P;

    /** direction pin 2 */
    const unsigned in2P;

    /** duration of motion */
    unsigned long dur;
};