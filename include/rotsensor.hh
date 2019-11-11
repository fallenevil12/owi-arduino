#ifndef ROTSENSOR_HH
#define ROTSENSOR_HH

#include <stdint.h>

/**
 * Abstract class represent a rotational encoder
 */
class ROTENCODER {
public:
    virtual int getRawVal() = 0;

    virtual float getDegreeVal();

protected:
    int rawVal{0};
    float degree{0.0};

}; //class ROTENCODER

/**
 * Class represent a rotational potentiometer
 */
class POTENTIO : public ROTENCODER {
public:
     /**
     * constructor
     * @param pin analog input pin
     * @param bits bits of resolution
     * @param range analog read voltage range
     * @param scale conversion factor voltage to degree
     */
    POTENTIO(uint8_t pin, unsigned bits, float range, float scale);

    /**
     * get the raw value
     * @return the raw value
     */
    int getRawVal() override;

    /**
     * get the voltage value
     * @return the voltage value
     */
    float getVoltVal();

    /**
     * get the degree value
     * @return the degree value
     */
    float getDegreeVal() override;

private:

    /* analog input pin */
    const uint8_t pin;

    /** adc resolution */
    const float res;

    /** measured voltage */
    float volt{0.0};
    
    /** conversion factor voltage to degree */
    float scale;

}; //class POTENTIO

#endif //ROTSENSOR_HH