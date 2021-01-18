#include "servo.h"


void Servo::init(void)
{
    // NVIC_InitTypeDef NVIC_InitStructure;
	// TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	// TIM_OCInitTypeDef TIM_OCInitStructure;
	// GPIO_InitTypeDef GPIO_InitStructure;

	// /* GPIOA, GPIOB and GPIOE Clocks enable */
	// RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
	// /* GPIOA Configuration: Channel 1, 2, 3, 4 and Channel 1N as alternate function push-pull */
	// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_11;
	// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	// GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	// GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	// GPIO_Init(GPIOE, &GPIO_InitStructure);
	// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_8;
	// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	// GPIO_Init(GPIOE, &GPIO_InitStructure);

	// GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_0);
	// GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_0);

	// /* Compute CCR1 value to generate a duty cycle at 50% for channel 1 and 1N */
	// Channel1Pulse = 0;
	// /* Compute CCR2 value to generate a duty cycle at 37.5%  for channel 2 and 2N */
	// Channel2Pulse = 0;

	// /* TIM1 clock enable */
	// RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	// /* TIM3 clock enable */
	// RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	// /* Time Base configuration */
	// TIM_TimeBaseStructure.TIM_Prescaler = 4 - 1;
	// TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	// TIM_TimeBaseStructure.TIM_Period = 1000;
	// TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	// TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	// TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);



	// /* Channel 1, 2,3 and 4 Configuration in PWM mode */
	// TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	// TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	// TIM_OCInitStructure.TIM_Pulse = Channel1Pulse;
	// TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	// TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
	// TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	// TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

	// TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	// TIM_OCInitStructure.TIM_Pulse = Channel2Pulse;
	// TIM_OC2Init(TIM1, &TIM_OCInitStructure);

	// /* TIM1 counter enable */
	// TIM_Cmd(TIM1, ENABLE);

	// /* TIM1 Main Output Enable */
	// TIM_CtrlPWMOutputs(TIM1, ENABLE);

}
// void Servo::ServoControl(uint8_t id,int v)
// {
//     switch(id){
//         case 0x01:
        
//         break


//     }


// }