#include <stdint.h>

class motor {
public:

    enum class dir {
        CW = 0,
        CCW = 1
    };

    motor();

    void update(dir direction, uint8_t power);

    virtual void output() = 0;

    void setDirection(dir direction);

    void setPower(uint8_t power);

protected:

    dir Dir{dir::CW};

    uint8_t pwm{0};

    unsigned pos{0};
};

class L298N : public motor {
public:

    L298N(unsigned enPin, unsigned in1Pin, unsigned in2Pin);

    void setDuration(unsigned long duration);
    
    void output() override;

private:

    const unsigned enP;

    const unsigned in1P;

    const unsigned in2P;

    unsigned long dur;
};