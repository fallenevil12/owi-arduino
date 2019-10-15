#ifndef PID_HH
#define PID_HH

class PID {
public:    
    PID(float kp, float ki, float kd);
    void setGain(float kp, float ki, float kd);
    float pidCal(float val, float refVal);

private:
    float val;
    float refVal;
    float kp;
    float ki;
    float kd;
    float err{0.0};
    float prevErr{0.0};
    float accmlErr{0.0};
    float gain;

}; //class PID

#endif //PID_HH