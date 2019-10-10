#ifndef PID_HH
#define PID_HH

class PID {
public:    
    PID(double kp, double ki, double kd);
    void reset();
    void setGain(double kp, double ki, double kd);
    double pidCal(double val, double refVal);

private:
    double val;
    double refVal;
    double kp;
    double ki;
    double kd;
    double err{0.0};
    double prevErr{0.0};
    double accmlErr{0.0};
    double gain;

}; //class PID

#endif //PID_HH