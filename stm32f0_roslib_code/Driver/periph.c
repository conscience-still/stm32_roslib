#define PERIPH_EXTER_DEFIN
#include "periph.h"


void NVIC_Config(FunctionalState state,const IRQn_Type a_irq,uint8_t priority)
{
	if (state == ENABLE)
	{
		NVIC_EnableIRQ(a_irq);
		NVIC_SetPriority(a_irq, priority);
	}
	else
	{
		NVIC_DisableIRQ(a_irq);
	}
}
/*left wheel*/

static void GPIO_WheelConfig(void)
{

    /* GPIOA, GPIOB and GPIOE Clocks enable */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB|RCC_AHBPeriph_GPIOC|RCC_AHBPeriph_GPIOE, ENABLE);
	
    /* GPIOA Configuration: Channel 1,SetMCU_LW_DIR 2, 3, 4 and Channel 1N as alternate function push-pull */
 	MCU_LW_CTRL_GPIO->MODER |=MCU_LW_CTRL_MODE; /*left wheelctrl */
	
	MCU_LW_CTRL_HIGH;
	
	MCU_LW_DIR_GPIO->MODER |= MCU_LW_DIR_MODE; /*left wheel CW */
	
	/*---Set IO for left wheel in Dir Controler---*/ 
	MCU_LW_PWM_GPIO->MODER |=  MCU_LW_PWM_MODE;	// left wheel pwm	
	MCU_LW_PWM_GPIO->AFR[MCU_LW_PWM_IDEX]|=  MCU_LW_PWM_AFR;	

	/*right*/
	MCU_RW_CTRL_GPIO->MODER |=MCU_RW_CTRL_MODE; /*ctrl */
	
	MCU_RW_CTRL_HIGH;
	
	MCU_RW_DIR_GPIO->MODER |= MCU_RW_DIR_MODE; /*//En or CW */
	
	/*---Set IO for RWbrush in Dir Controler---*/ 
	MCU_RW_PWM_GPIO->MODER |=  MCU_RW_PWM_MODE;	//pwm	
	MCU_RW_PWM_GPIO->AFR[MCU_RW_PWM_IDEX]|=  MCU_RW_PWM_AFR;

   
}

static void TIM_WheelConfig(void)
{

    // TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    // TIM_OCInitTypeDef TIM_OCInitStructure;
    /* Compute CCR1 value to generate a duty cycle at 50% for channel 1 and 1N */
    //Channel1Pulse = 0;
    /* Compute CCR2 value to generate a duty cycle at 37.5%  for channel 2 and 2N */
    //Channel2Pulse = 0;

    /* TIM1 clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM17, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    /* Time Base configuration */
    // TIM_TimeBaseStructure.TIM_Prescaler = 0;
    // TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    // TIM_TimeBaseStructure.TIM_Period = 2000;
    // TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    // TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    // TIM_TimeBaseInit(MCU_RW_TIMX, &TIM_TimeBaseStructure);

    // /* Channel 1, 2,3 and 4 Configuration in PWM mode */
    // TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
    // TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    // TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
    // TIM_OCInitStructure.TIM_Pulse = 0;
    // TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    // TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
    // TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
    // TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
    // //WHEEL  //L
    // TIM_OC2Init(MCU_RW_TIMX, &TIM_OCInitStructure);
	
    // //R    /* Time Base configuration */
    // TIM_OC1Init(MCU_RW_TIMX, &TIM_OCInitStructure);

    // /* TIM1 counter enable */
    // TIM_Cmd(MCU_RW_TIMX, ENABLE);

    // /* TIM1 Main Output Enable */
    // TIM_CtrlPWMOutputs(TIM1, ENABLE);
	MCU_LW_TIMX->ARR = 2000;
	MCU_LW_TIMX->PSC = 0;
	MCU_LW_TIMX->EGR = TIM_EGR_UG;
	MCU_LW_TIMX->BDTR = TIM_BDTR_MOE;
	MCU_LW_TIMX->MCU_LW_CMR_CH |= MCU_LW_CMR_SET;
	MCU_LW_TIMX->CCER  |= MCU_LW_CCER_SET;				
	MCU_LW_TIMX->CR1   |=TIM_CR1_CEN|TIM_CR1_ARPE;	

	/*Right TIM1CH1 PE9*/
	MCU_RW_TIMX->MCU_RW_CMR_CH |= MCU_RW_CMR_SET;
	MCU_RW_TIMX->CCER  |= MCU_RW_CCER_SET;				
	MCU_RW_TIMX->CR1   |=TIM_CR1_CEN|TIM_CR1_ARPE;	


}


static void EXTI4_15_Config(void)
{
 

	/*left*/
	EXTI->IMR |=  MCU_LW_FG_EXTI_SET ;	
	EXTI->FTSR |= MCU_LW_FG_EXTI_SET ;	
	
	EXTI->RTSR |= MCU_LW_FG_EXTI_SET;	
	
	SYSCFG->EXTICR[MCU_LW_FG_EXTI_INDEX] |= (MCU_LW_FG_EXTI_CR);	//R_WHEEL_SPEED/*PD10 L Wheel speed 2019.12.5 lyn*/   		
	
	/*right*/
	EXTI->IMR |=  MCU_RW_FG_EXTI_SET ;	
	EXTI->FTSR |= MCU_RW_FG_EXTI_SET ;	
	
	EXTI->RTSR |= MCU_RW_FG_EXTI_SET;	
	
	SYSCFG->EXTICR[MCU_RW_FG_EXTI_INDEX] |= (MCU_RW_FG_EXTI_CR);	//R_WHEEL_SPEED/*PD10 L Wheel speed 2019.12.5 lyn*/   		
  
        NVIC_Config(ENABLE,MCU_LW_FG_EXTI_IRQ,1);
	NVIC_Config(ENABLE,MCU_RW_FG_EXTI_IRQ,1);
}


void PeriphInit(void)
{
    GPIO_WheelConfig();
    TIM_WheelConfig();
	EXTI4_15_Config();
}
#ifdef __cplusplus
extern "C" {
#endif
void EXTI0_1_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line0) != RESET) {
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
    if (EXTI_GetITStatus(EXTI_Line1) != RESET) {
        EXTI_ClearITPendingBit(EXTI_Line1);

    }
}
void EXTI2_3_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line2) != RESET) {
       EXTI_ClearITPendingBit(EXTI_Line2);

    }
    if (EXTI_GetITStatus(EXTI_Line3) != RESET) {
        EXTI_ClearITPendingBit(EXTI_Line3);
    }    
}

void EXTI4_15_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line4) != RESET) {
        g_fbWheelLCnt++;
        /* Clear the EXTI line 2 pending bit */
        EXTI_ClearITPendingBit(EXTI_Line4);
    } 
    if (EXTI_GetITStatus(EXTI_Line6) != RESET) {
        /* Clear the EXTI line 2 pending bit */
        EXTI_ClearITPendingBit(EXTI_Line6);
    }  
    if (EXTI_GetITStatus(EXTI_Line7) != RESET) {
        /* Clear the EXTI line 2 pending bit */
        EXTI_ClearITPendingBit(EXTI_Line7);
    } 
    if (EXTI_GetITStatus(EXTI_Line8) != RESET) {

        /* Clear the EXTI line 2 pending bit */
        EXTI_ClearITPendingBit(EXTI_Line8);
    }    
    if (EXTI_GetITStatus(EXTI_Line9) != RESET) {
        /* Clear the EXTI line 2 pending bit */
        EXTI_ClearITPendingBit(EXTI_Line9);
    }
    if (EXTI_GetITStatus(EXTI_Line10) != RESET) {
        /* Clear the EXTI line 2 pending bit */
        EXTI_ClearITPendingBit(EXTI_Line10);
    }

    if (EXTI_GetITStatus(EXTI_Line11) != RESET) {
        /* Clear the EXTI line 2 pending bit */
        EXTI_ClearITPendingBit(EXTI_Line11);
    }
    if (EXTI_GetITStatus(EXTI_Line12) != RESET) {
        /* Clear the EXTI line 2 pending bit */
        EXTI_ClearITPendingBit(EXTI_Line12);
    }
    if (EXTI_GetITStatus(EXTI_Line13) != RESET) {
        /* Clear the EXTI line 2 pending bit */
        EXTI_ClearITPendingBit(EXTI_Line13);
    }
     if (EXTI_GetITStatus(EXTI_Line14) != RESET) {
        /* Clear the EXTI line 2 pending bit */
        EXTI_ClearITPendingBit(EXTI_Line14);
    }  
     if (EXTI_GetITStatus(EXTI_Line15) != RESET) {
        /* Clear the EXTI line 2 pending bit */
        EXTI_ClearITPendingBit(EXTI_Line15);
    }       
}
#ifdef __cplusplus
}
#endif

