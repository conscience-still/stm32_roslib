#define BRUSHVUUC_EXTER_DEFIN

#include "brushandVuuc.h"

#include <string.h>

#include "math.h"
#include "periph.h"
#include "pid.h"

static PID_typedef PID[5];

#define BrushPid PID[0]
#define SideBrushLPid PID[1]
#define SideBrushRPid PID[2]
#define VuucLPid PID[3]
#define VuucRPid PID[4]

#define BRUSH_REVOLUTION 1
#define SIDEBURSHL_REVOLUTION 1
#define SIDEBURSHR_REVOLUTION 1
#define VACUUML_REVOLUTION 1
#define VACUUMR_REVOLUTION 1

static float ControExp[5] = {0};
static int8_t ControDir[5] = {1, 1, 1, 1, 1};
static uint16_t Revolution[5] = {BRUSH_REVOLUTION, SIDEBURSHL_REVOLUTION,
                                 SIDEBURSHR_REVOLUTION, VACUUML_REVOLUTION,
                                 VACUUMR_REVOLUTION};
#define BrushDir ControDir[0]
#define SideBrushLDir ControDir[1]
#define SideBrushRDir ControDir[2]
#define VaccumLDir ControDir[3]
#define VaccumRDir ControDir[4]
//ï¿½ï¿½Ð¡ï¿½ï¿½ï¿½ï¿½
// g_fBrushExp = 1600
// g_fSideBrushLExp = 100
// g_fVaccumLExp =500
//ï¿½ï¿½ï¿½g_ActulBrushVel =11760
//ï¿½ï¿½ï¿½g_ActulSideBrushLVel =1480
// g_fSideBrushLExp
//
#define g_fBrushExp ControExp[0]
#define g_fSideBrushLExp ControExp[1]
#define g_fSideBrushRExp ControExp[2]
#define g_fVaccumLExp ControExp[3]
#define g_fVaccumRExp ControExp[4]
#define BRUSHPWM_BASE 270

__IO int32_t g_ActulBrushVel;
__IO int32_t g_ActulSideBrushLVel;
__IO int32_t g_ActulSideBrushRVel;
__IO uint32_t g_ActulVacuumLVel;
__IO uint32_t g_ActulVacuumRVel;

void SetBruAndVuucExpVel(int id, float exp) {
  ControExp[id] = exp;
  if (fabs(ControExp[0]) < BRUSHPWM_BASE ) ControExp[0] = 0;
}
void SetVacuumExpvel(float exp) {
  ControExp[3] = exp;
  ControExp[4] = 0;
}
int32_t GetBruAndVuucActulVel(int id) {
  switch (id) {
    case 0:
      return g_ActulBrushVel;
    case 1:
      return g_ActulSideBrushLVel;
    case 2:
      return g_ActulSideBrushRVel;
    case 3:
      return g_ActulVacuumLVel;
    case 4:
      return g_ActulVacuumLVel;
    default:
      return 0;
  }
}

#define TIME_CONST 20  // 50MS
void BrushAndVuucControl(void) {
  g_ActulBrushVel = ControDir[0] * g_fbBrushCnt * TIME_CONST;
  g_ActulSideBrushLVel = ControDir[1] * g_fbSideBrushLCnt * TIME_CONST;
  g_ActulSideBrushRVel = ControDir[2] * g_fbSideBrushRCnt * TIME_CONST;
//  g_ActulVacuumLVel = (adc_value.Vacuum_Current/4096 * 3.3*3.5-0.082)*(adc_value.Charge_A_Voltage/4096 * 3.3*11.73) ;
   g_ActulVacuumLVel = g_fbVacuumLCnt * TIME_CONST;
  g_ActulVacuumRVel = g_fbVacuumRCnt * TIME_CONST;

  int32_t fbcnt[3] = {g_ActulBrushVel, g_ActulSideBrushLVel,
                      g_ActulSideBrushRVel};
  uint32_t fbcnt1[2] = {g_ActulVacuumLVel, g_ActulVacuumRVel};

  g_fbVacuumLCnt = 0;
  g_fbVacuumRCnt = 0;
  g_fbBrushCnt = 0;
  g_fbSideBrushLCnt = 0;
  g_fbSideBrushRCnt = 0;

  float out[5] = {0};
  for (int i = 0; i < 3; i++) {
    float exp = ControExp[i] * Revolution[i];
    float m = fbcnt[i];
    out[i] = GetPid(&PID[i], m, exp);
    if (out[i] < 0) {
      ControDir[i] = -1;
    } else {
      ControDir[i] = 1;
    }
  }
  /*·ç¹Äµç»ú*/
  {
    float exp = ControExp[3] * Revolution[3];
    out[3] = GetPid(&VuucLPid, g_ActulVacuumLVel, exp);  
  }
//  for (int i = 3; i < 5; i++) {
//    float exp = ControExp[i] * Revolution[i];
//    out[i] = GetPid(&PID[i], fbcnt1[i - 3], exp);
//  }
//  if(out[0] == 0){
//    MCU_MAIN_CTRL_LOW;
//  }
//  else
//  {
//    MCU_MAIN_CTRL_HIGH;
//  }
  if (fabs(out[0]) < BRUSHPWM_BASE) {
    out[0] = 0;
    // BrushPid._iter = 0;
    SetBurshPwm(out[0]);
  } else {
    if (BrushDir < 0) {
      SetBurshDir(0);
      SetBurshPwm(-out[0]);
    } else {
      SetBurshDir(1);
      SetBurshPwm(out[0]);
    }
  }

  

  if (SideBrushLDir < 0) {
    SetSideBrushLDir(1);
    SetSideBrushLPwm(-out[1]);
  } else {
    SetSideBrushLDir(0);
    SetSideBrushLPwm(out[1]);
  }

  if (SideBrushRDir < 0) {
    SetSideBrushRDir(0);
    SetSideBrushRPwm(-out[2]);
  } else {
    SetSideBrushRDir(1);
    SetSideBrushRPwm(out[2]);
  }

  if (out[3] < 0) out[3] = 0;
  if (out[4] < 0) out[4] = 0;
  for (int i = 0; i < 3; i++) {
    if (ControExp[i] == 0.0f && fabs(out[i] < 120.f)) {
      PID[i]._iter = 0.0f;
    }
  }

  if (g_fVaccumLExp > 1) {
    SetVacuumLEn(1);
  } else {
    out[3] = 0;
    SetVacuumLEn(0);
    VuucLPid._iter = 0;
  }
  
  out[3] =  2000 -out[3];
  SetVacuumLPwm(out[3]);
}

void BrushAndVuccInit(void) {
  memset(PID, 0, sizeof(PID));

  BrushPid._alph = 0.2;
  BrushPid._imax = (1999);
  BrushPid._imin = -(1999);
  BrushPid._omax = (1999);
  BrushPid._omin = -(1999);
  SetPidPra(&BrushPid, 0.05, 0.5, 0);
  SideBrushLPid._alph = 0.2;
  SideBrushLPid._imax = 1999;
  SideBrushLPid._imin = -1999;
  SideBrushLPid._omax = 1999;
  SideBrushLPid._omin = -1999;
  SetPidPra(&SideBrushLPid, 0.5, 0.05, 0.01);
  SideBrushRPid._alph = 0.2;
  SideBrushRPid._imax = 1999;
  SideBrushRPid._imin = -1999;
  SideBrushRPid._omax = 1999;
  SideBrushRPid._omin = -1999;
  SetPidPra(&SideBrushRPid, 0.5, 0.05, 0.01);

  VuucLPid._alph = 0.2;
  VuucLPid._imax = 2000;
  VuucLPid._imin = 115;
  VuucLPid._omax = 2000;
  VuucLPid._omin = 115;
  SetPidPra(&VuucLPid, 0.6, 0.02, 0);

}
