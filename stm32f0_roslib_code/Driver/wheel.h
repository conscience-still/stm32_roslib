#ifndef _WHEEL_
#define _WHEEL_

#ifdef __cplusplus
extern "C" {
#endif
#include "stm32f0xx.h"


void WheelInit(void);
void ControlServo(void);
void SetWheelGeometry(float v,float w);
void GetWheelGeometry(float* v,float* w);
void GetWheelVel(float * vl,float* vr);

#ifdef __cplusplus
}
#endif
#endif