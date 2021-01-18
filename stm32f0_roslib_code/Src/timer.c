#define TIMER_EXTER_DEFIN
#include "timer.h"

#define SYSTEM_TIMx                              TIM7
#define SYSTEM_TIMx_PeriphClockCmd               RCC_APB1PeriphClockCmd
#define SYSTEM_TIMx_CLK                          RCC_APB1Periph_TIM7
#define SYSTEM_TIMx_IRQn                         TIM7_IRQn
#define SYSTEM_TIMx_IRQHandler                   TIM7_IRQHandler

static   __IO uint8_t Timer1msFlag = 0;

__IO uint32_t Timer1msCnt = 0;

static  void TIM_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	/* TIM3 clock enable */
	SYSTEM_TIMx_PeriphClockCmd(SYSTEM_TIMx_CLK, ENABLE);

	/* Time Base configuration */
	TIM_TimeBaseStructure.TIM_Prescaler = 48 - 1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = 1000;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(SYSTEM_TIMx, &TIM_TimeBaseStructure);

	/* Enable the TIM3 gloabal Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = SYSTEM_TIMx_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	/* TIM1 counter enable */
	TIM_Cmd(SYSTEM_TIMx, ENABLE);
	/* TIM Interrupts enable */
	TIM_ITConfig(SYSTEM_TIMx, TIM_IT_Update, ENABLE);
}

/**
  * @brief  Configure a SysTick Base time to 10 ms.
  * @param  None
  * @retval None
  */
static void SysTickConfig(void)
{
  
//  SysTick_Config(0xffffff);//49766400/);
//  return 0;
  
  
//  /* Setup SysTick Timer for 10ms interrupts  */
//  if (SysTick_Config(SystemCoreClock / 100))
//  {
//    /* Capture error */
//    while (1);
//  }
//  /* Configure the SysTick handler priority */
//  NVIC_SetPriority(SysTick_IRQn, 0x0);
}

void TimerInit(void)
{
    SysTickConfig();
    TIM_Config();

}

/**/
uint32_t Timer_GetCount(void) {
  uint32_t t1;
  t1 = (0x00ffffff - SYSTEM_TIMx->CNT);
  return t1;
}

/**/
uint32_t Timer_CalDiff(uint32_t OldTime) {

  uint32_t t1 = Timer_GetCount();
  uint32_t t2 = OldTime;
  
  uint32_t rt;
  
  if (t1 < t2)
    rt = (0xffffffff - t2) + t1;
  else
    rt = t1 - t2;

  return rt;
}

/**/
uint32_t Timer_ToUs(uint32_t tx) {
  return tx;
}

/**/
uint32_t Timer_FromUs(uint32_t us) {
  return (us);
}

/**/
uint32_t Timer_ToMs(uint32_t tx) {
  tx /= 1000;
  return tx;
}

/**/
uint32_t Timer_FromMs(uint32_t ms) {
  return (ms *  1000);
}

/**/
void Timer_Delay_ms(uint32_t x) {
  int o_t = Timer_GetCount();
  int t_i;
  do {t_i = Timer_CalDiff(o_t);}while (Timer_ToMs(t_i) < x);
}

/**/
void Timer_DelayUntil_ms(uint32_t *pxPreviousWakeTime, uint32_t xTimeIncrement) {
  while (Timer_ToMs(Timer_CalDiff(*pxPreviousWakeTime)) < xTimeIncrement)
  ;
  *pxPreviousWakeTime = Timer_GetCount();
}

/**/
void Timer_Delay_us(uint32_t x) {
  int o_t = Timer_GetCount();
  int t_i;
  do {t_i = Timer_CalDiff(o_t);}while (Timer_ToUs(t_i) < x);
}

uint8_t GetTimer1msFlag(void)
{
    return Timer1msFlag;
}
void SetTImerImsFlag(uint8_t f)
{
    Timer1msFlag = f;
}

#ifdef __cplusplus
extern "C" {
#endif

void SYSTEM_TIMx_IRQHandler(void)
{
  if (TIM_GetITStatus(SYSTEM_TIMx, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(SYSTEM_TIMx, TIM_IT_Update);
    
    Timer1msCnt++;
    Timer1msFlag = 1;
  }
}
#ifdef __cplusplus
}
#endif