#ifndef _PERIPH
#define _PERIPH
#ifdef __cplusplus
extern "C" {
#endif
#include "stm32f0xx.h"

#ifdef  PERIPH_EXTER_DEFIN
    #define PERIPH_EXTER 
#else
    #define PERIPH_EXTER extern
#endif



#define GPIO_AFRL_AFR0_1		((uint32_t)0x00000001)
#define GPIO_AFRL_AFR0_2		((uint32_t)0x00000002)
#define GPIO_AFRL_AFR0_3		((uint32_t)0x00000003)

#define GPIO_AFRL_AFR1_1		((uint32_t)0x00000010)
#define GPIO_AFRL_AFR1_2		((uint32_t)0x00000020)
#define GPIO_AFRL_AFR1_3		((uint32_t)0x00000030)

#define GPIO_AFRL_AFR2_1		((uint32_t)0x00000100)
#define GPIO_AFRL_AFR2_2		((uint32_t)0x00000200)
#define GPIO_AFRL_AFR2_3		((uint32_t)0x00000300)

#define GPIO_AFRL_AFR3_1		((uint32_t)0x00001000)
#define GPIO_AFRL_AFR3_2		((uint32_t)0x00002000)
#define GPIO_AFRL_AFR3_3		((uint32_t)0x00003000)

#define GPIO_AFRL_AFR4_1		((uint32_t)0x00010000)
#define GPIO_AFRL_AFR4_2		((uint32_t)0x00020000)
#define GPIO_AFRL_AFR4_3		((uint32_t)0x00030000)

#define GPIO_AFRL_AFR5_1		((uint32_t)0x00100000)
#define GPIO_AFRL_AFR5_2		((uint32_t)0x00200000)
#define GPIO_AFRL_AFR5_3		((uint32_t)0x00300000)
	
#define GPIO_AFRL_AFR6_1		((uint32_t)0x01000000)
#define GPIO_AFRL_AFR6_2		((uint32_t)0x02000000)
#define GPIO_AFRL_AFR6_3		((uint32_t)0x03000000)

#define GPIO_AFRL_AFR7_1		((uint32_t)0x10000000)
#define GPIO_AFRL_AFR7_2		((uint32_t)0x20000000)
#define GPIO_AFRL_AFR7_3		((uint32_t)0x30000000)

#define GPIO_AFRH_AFR8_1		((uint32_t)0x00000001)
#define GPIO_AFRH_AFR8_2		((uint32_t)0x00000002)
#define GPIO_AFRH_AFR8_3		((uint32_t)0x00000003)

#define GPIO_AFRH_AFR9_1		((uint32_t)0x00000010)
#define GPIO_AFRH_AFR9_2		((uint32_t)0x00000020)
#define GPIO_AFRH_AFR9_3		((uint32_t)0x00000030)

#define GPIO_AFRH_AFR10_1		((uint32_t)0x00000100)
#define GPIO_AFRH_AFR10_2		((uint32_t)0x00000200)
#define GPIO_AFRH_AFR10_3		((uint32_t)0x00000300)

#define GPIO_AFRH_AFR11_1		((uint32_t)0x00001000)
#define GPIO_AFRH_AFR11_2		((uint32_t)0x00002000)
#define GPIO_AFRH_AFR11_3		((uint32_t)0x00003000)

#define GPIO_AFRH_AFR12_1		((uint32_t)0x00010000)
#define GPIO_AFRH_AFR12_2		((uint32_t)0x00020000)
#define GPIO_AFRH_AFR12_3		((uint32_t)0x00030000)

#define GPIO_AFRH_AFR13_1		((uint32_t)0x00100000)
#define GPIO_AFRH_AFR13_2		((uint32_t)0x00200000)
#define GPIO_AFRH_AFR13_3		((uint32_t)0x00300000)
#define GPIO_AFRH_AFR13_4		((uint32_t)0x00400000)
#define GPIO_AFRH_AFR13_5		((uint32_t)0x00500000)

#define GPIO_AFRH_AFR14_1		((uint32_t)0x01000000)
#define GPIO_AFRH_AFR14_2		((uint32_t)0x02000000)
#define GPIO_AFRH_AFR14_3		((uint32_t)0x03000000)
#define GPIO_AFRH_AFR14_4		((uint32_t)0x04000000)
#define GPIO_AFRH_AFR14_5		((uint32_t)0x05000000)

#define GPIO_AFRH_AFR15_1		((uint32_t)0x10000000)
#define GPIO_AFRH_AFR15_2		((uint32_t)0x20000000)
#define GPIO_AFRH_AFR15_3		((uint32_t)0x30000000)


PERIPH_EXTER __IO uint32_t g_fbWheelLCnt ;
PERIPH_EXTER __IO uint32_t g_fbWheelRCnt ;





/*left wheel*/
#define MCU_LW_CTRL_GPIO   GPIOB
#define MCU_LW_CTRL_MODE   GPIO_MODER_MODER3_0
#define MCU_LW_CTRL_BR	   GPIO_BSRR_BS_3
#define MCU_LW_CTRL_HIGH   MCU_LW_CTRL_GPIO->BSRR  |= MCU_LW_CTRL_BR;	
#define MCU_LW_CTRL_LOW	   MCU_LW_CTRL_GPIO->BRR  |= MCU_LW_CTRL_BR;

#define MCU_LW_DIR_GPIO    GPIOD
#define MCU_LW_DIR_MODE    GPIO_MODER_MODER7_0 
#define MCU_LW_DIR_BR	   GPIO_BSRR_BS_7
#define MCU_LW_DIR_HIGH    MCU_LW_DIR_GPIO->BSRR  |= MCU_LW_DIR_BR;	
#define MCU_LW_DIR_LOW	   MCU_LW_DIR_GPIO->BRR   |= MCU_LW_DIR_BR;

/* //����ʹ��
#define MCU_LW_BREAK_MODE  GPIO_MODER_MODER4_0
#define MCU_LW_BREAK_GPIO  GPIOB
*/

#define MCU_LW_FG_GPIO        GPIOD
#define MCU_LW_FG_PUPDR       GPIO_PUPDR_PUPDR4_0
#define MCU_LW_FG_EXTI_NUM    4 /*NUM =IO idex */
#define MCU_LW_FG_EXTI_SET    0x1UL << MCU_LW_FG_EXTI_NUM
#define MCU_LW_FG_EXTI_CR     SYSCFG_EXTICR2_EXTI4_PD  /* 0 - 3 : CR1 4 - 7 : CR2 8 - 11 : CR3 12 - 15 : CR4*/
#define MCU_LW_FG_EXTI_INDEX  1    /* 0 - 3 : 0  4 - 7 : 1  8 - 11 : 2  12 - 15 : 3*/
#define MCU_LW_FG_EXTI_IRQ    EXTI4_15_IRQn

#define MCU_LW_PWM_GPIO    GPIOE
#define MCU_LW_PWM_MODE    GPIO_MODER_MODER1_1
#define MCU_LW_PWM_AFR     0 /*��ѯ�����ֲῴ���ù��ܾ������� idle.h*/
#define MCU_LW_PWM_IDEX    0 /*0-7 :0 AFRL  8 -15 :1 AFRH */

#define MCU_LW_TIMX       TIM17
#define MCU_LW_TIM_CH     TIM17->CCR1
#define MCU_LW_CMR_CH     CCMR1  /*1 - 2 CCMR1 3 - 4 CCMR2*/
#define MCU_LW_CMR_SET    (TIM_CCMR1_OC1PE|TIM_CCMR1_OC1M_1|TIM_CCMR1_OC1M_2)/*0 - 1 CCMR1 2 - 4 CCMR2*/
#define MCU_LW_CCER_SET   (TIM_CCER_CC1E|TIM_CCER_CC1P)
#define MCU_LW_CCER_RESET (~TIM_CCER_CC1E)


/*right wheel*/
#define MCU_RW_CTRL_GPIO   GPIOE
#define MCU_RW_CTRL_MODE   GPIO_MODER_MODER12_0
#define MCU_RW_CTRL_BR	   GPIO_BSRR_BS_12
#define MCU_RW_CTRL_HIGH   MCU_RW_CTRL_GPIO->BSRR  |= MCU_RW_CTRL_BR;	
#define MCU_RW_CTRL_LOW	   MCU_RW_CTRL_GPIO->BRR  |= MCU_RW_CTRL_BR;

#define MCU_RW_DIR_GPIO    GPIOE
#define MCU_RW_DIR_MODE    GPIO_MODER_MODER10_0 
#define MCU_RW_DIR_BR	   GPIO_BSRR_BS_10
#define MCU_RW_DIR_HIGH    MCU_RW_DIR_GPIO->BSRR  |= MCU_RW_DIR_BR;	
#define MCU_RW_DIR_LOW	   MCU_RW_DIR_GPIO->BRR   |= MCU_RW_DIR_BR;



/* //����ʹ��
#define MCU_RW_BREAK_MODE  GPIO_MODER_MODER11_0
#define MCU_RW_BREAK_GPIO  GPIOE
*/

#define MCU_RW_FG_GPIO        GPIOE
#define MCU_RW_FG_PUPDR       GPIO_PUPDR_PUPDR9_0
#define MCU_RW_FG_EXTI_NUM    9 /*NUM =IO idex */
#define MCU_RW_FG_EXTI_SET    0x1UL << MCU_RW_FG_EXTI_NUM
#define MCU_RW_FG_EXTI_CR     SYSCFG_EXTICR3_EXTI9_PE  /* 0 - 3 : CR1 4 - 7 : CR2 8 - 11 : CR3 12 - 15 : CR4*/
#define MCU_RW_FG_EXTI_INDEX  2    /* 0 - 3 : 0  4 - 7 : 1  8 - 11 : 2  12 - 15 : 3*/
#define MCU_RW_FG_EXTI_IRQ    EXTI4_15_IRQn

#define MCU_RW_PWM_GPIO    GPIOE
#define MCU_RW_PWM_MODE    GPIO_MODER_MODER5_1
#define MCU_RW_PWM_AFR     0 /*��ѯ�����ֲῴ���ù��ܾ������� idle.h*/
#define MCU_RW_PWM_IDEX    1 /*0-7 :0 AFRL  8 -15 :1 AFRH */

#define MCU_RW_TIMX     TIM3
#define MCU_RW_TIM_CH   TIM3->CCR3
#define MCU_RW_CMR_CH   CCMR2  /*1 - 2 CCMR1 3 - 4 CCMR2*/
#define MCU_RW_CMR_SET  (TIM_CCMR2_OC3PE|TIM_CCMR2_OC3M_1|TIM_CCMR2_OC3M_2)/*0 - 1 CCMR1 2 - 4 CCMR2*/
#define MCU_RW_CCER_SET (TIM_CCER_CC3E|TIM_CCER_CC3P )
#define MCU_RW_CCER_RESET (~TIM_CCER_CC3E)





#define SetWheelLPwm(v) (MCU_LW_TIM_CH = v)
#define SetWheelLDir(d)  GPIO_WriteBit(MCU_LW_DIR_GPIO,MCU_LW_DIR_BR,(BitAction)d)
#define SetWheelRPwm(v)  (MCU_RW_TIM_CH = v)
#define SetWheelRDir(d)  GPIO_WriteBit(MCU_RW_DIR_GPIO,MCU_RW_DIR_BR,(BitAction)d)
//

void PeriphInit(void);




#ifdef __cplusplus
}
#endif
#endif