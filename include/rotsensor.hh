#ifndef ROTSENSOR_HH
#define ROTSENSOR_HH

#include <stdint.h>

class ROTENCODER {
public:
    virtual int getRawVal() = 0;

    virtual float getDegreeVal();

protected:
    int rawVal{0};
    float degree{0.0};

}; //class ROTENCODER

class POTENTIO : public ROTENCODER {
public:
     /**
     * constructor
     * @param pin analog input pin
     * @param bits bits of resolution
     * @param range analog read voltage range
     * @param scale conversion factor to rotation degree
     */
    POTENTIO(uint8_t pin, unsigned bits, float range, float scale);

    int getRawVal() override;

    float getVoltVal();

    float getDegreeVal() override;

    void setScale(float scale);

private:
    const uint8_t pin;
    const float res;
    float volt{0.0};
    float scale;
    bool firstpass = true;

}; //class POTENTIO

#endif //ROTSENSOR_HH