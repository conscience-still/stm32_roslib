#ifndef _BRUSHANDVUU_H
#define _BRUSHANDVUU_H
#ifdef __cplusplus
extern "C" {
#endif
#include "stm32f0xx.h"
void SetBruAndVuucExpVel(int id, float exp);
void SetVacuumExpvel(float exp);
int32_t GetBruAndVuucActulVel(int id);

void BrushAndVuccInit(void);
void BrushAndVuucControl(void);
#ifdef __cplusplus
}
#endif
#endif