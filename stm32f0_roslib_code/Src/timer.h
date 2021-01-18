#ifndef _TIMER_H
#define _TIMER_H

#ifdef __cplusplus
extern "C" {
#endif
#include "stm32f0xx.h"





uint8_t GetTimer1msFlag(void);
void SetTImerImsFlag(uint8_t f);



void TimerInit(void);
#ifdef __cplusplus
}
#endif

#endif


