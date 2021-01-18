#ifdef __cplusplus
extern "C" {
#endif
#ifndef _MILLISECONDTIMER_H_
#define _MILLISECONDTIMER_H_
#include "config.h"

void initialise(void);
void delay(uint32_t millis_);
uint32_t millis();
void reset();

#endif // _MILLISECONDTIMER_H_ 
#ifdef __cplusplus
}
#endif



