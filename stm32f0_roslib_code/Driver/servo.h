#ifndef _SERVO_H_
#define _SERVO_H_

#include "config.h"

class Servo
{
  public:
    void init();
    void ServoControl(uint8_t id,int v);

  private:
    uint16_t Channel1Pulse;
    uint16_t Channel2Pulse;
};

#endif //_LED_H_