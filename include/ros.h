#ifndef _ROS_H_
#define _ROS_H_

#include <Arduino.h>
#include <HardwareSerial.h>
#include "ros/node_handle.h"

namespace ros {
  typedef NodeHandle_<ArduinoHardware,25,25,1024,1024> NodeHandle;
}

class ArduinoHardware {
  public:
    ArduinoHardware() {
      iostream = &Serial1;
      baud_ = 115200;
    }
  
    void setBaud(long baud) {
      this->baud_= baud;
    }
  
    int getBaud() {
      return baud_;
    }

    void init() {
      iostream->begin(baud_);
    }

    int read() {
      return iostream->read();
    };

    void write(uint8_t* data, int length) {
      for(int i=0; i<length; i++) {
        iostream->write(data[i]);
      }
    }

    unsigned long time() {
      return millis();
    }

  protected:
    HardwareSerial* iostream;
    long baud_;
};

#endif //_ROS_H_