#ifndef _ROS_owi_position_cmd_h
#define _ROS_owi_position_cmd_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace owi
{

  class position_cmd : public ros::Msg
  {
    public:
      int16_t position[5];

    position_cmd():
      position()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      for( uint32_t i = 0; i < 5; i++){
      union {
        int16_t real;
        uint16_t base;
      } u_positioni;
      u_positioni.real = this->position[i];
      *(outbuffer + offset + 0) = (u_positioni.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_positioni.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->position[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      for( uint32_t i = 0; i < 5; i++){
      union {
        int16_t real;
        uint16_t base;
      } u_positioni;
      u_positioni.base = 0;
      u_positioni.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_positioni.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->position[i] = u_positioni.real;
      offset += sizeof(this->position[i]);
      }
     return offset;
    }

    const char * getType(){ return "owi/position_cmd"; };
    const char * getMD5(){ return "858e4dd0154eda795590f6befb9769d2"; };

  };

}
#endif
