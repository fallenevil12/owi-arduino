#ifndef ROTSENSOR_HH
#define ROTSENSOR_HH

#include <stdint.h>

class ROTENCODER {
public:
    virtual int getRawVal() = 0;

    virtual double getDegreeVal();

protected:
    int rawVal{0};
    double degree{0.0};

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
    POTENTIO(uint8_t pin, unsigned bits, double range, double scale);

    int getRawVal() override;

    double getVoltVal();

    double getDegreeVal() override;

    void setScale(double scale);

private:
    const uint8_t pin;
    const double res;
    double volt{0.0};
    double scale;

}; //class POTENTIO

#endif //ROTSENSOR_HH