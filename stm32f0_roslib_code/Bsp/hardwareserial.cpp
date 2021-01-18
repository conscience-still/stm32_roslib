#include "hardwareserial.h"

static uint8_t rxbuf[RXBUF_SIZE];
static ring_buffer rb1_recv;

#if 0
#define USARTx USART1
#define USARTx_CLK RCC_APB2ENR_USART1EN
#define USARTx_APBPERIPHCLOCK RCC_APB2PeriphClockCmd
#define USARTx_IRQn USART1_IRQn
#define USARTx_IRQHandler USART1_IRQHandler

#define USARTx_TX_PIN GPIO_Pin_9
#define USARTx_TX_GPIO_PORT GPIOA
#define USARTx_TX_GPIO_CLK RCC_AHBPeriph_GPIOA
#define USARTx_TX_SOURCE GPIO_PinSource9
#define USARTx_TX_AF GPIO_AF_1

#define USARTx_RX_PIN GPIO_Pin_10
#define USARTx_RX_GPIO_PORT GPIOA
#define USARTx_RX_GPIO_CLK RCC_AHBPeriph_GPIOA
#define USARTx_RX_SOURCE GPIO_PinSource10
#define USARTx_RX_AF GPIO_AF_1
#elif 1
#define USARTx USART2
#define USARTx_CLK RCC_APB1Periph_USART2
#define USARTx_APBPERIPHCLOCK RCC_APB1PeriphClockCmd
#define USARTx_IRQn USART2_IRQn
#define USARTx_IRQHandler USART2_IRQHandler

#define USARTx_TX_PIN GPIO_Pin_5
#define USARTx_TX_GPIO_PORT GPIOD
#define USARTx_TX_GPIO_CLK RCC_AHBPeriph_GPIOD
#define USARTx_TX_SOURCE GPIO_PinSource5
#define USARTx_TX_AF GPIO_AF_0

#define USARTx_RX_PIN GPIO_Pin_6
#define USARTx_RX_GPIO_PORT GPIOD
#define USARTx_RX_GPIO_CLK RCC_AHBPeriph_GPIOD
#define USARTx_RX_SOURCE GPIO_PinSource6
#define USARTx_RX_AF GPIO_AF_0
#endif
extern 	uint32_t Timer1msCnt ;

void HardwareSerial::begin(uint32_t baud)
{
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	//RCC_USARTCLKConfig(RCC_USART2CLK_SYSCLK);
	/* Enable GPIO clock */
	RCC_AHBPeriphClockCmd(USARTx_TX_GPIO_CLK | USARTx_RX_GPIO_CLK, ENABLE);
   // RCC_USARTCLKConfig(RCC_USART1CLK_PCLK);
	/* Enable USART clock */
	USARTx_APBPERIPHCLOCK(USARTx_CLK, ENABLE);

	/* Configure USART Tx and Rx as alternate function push-pull */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = USARTx_TX_PIN;
	GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = USARTx_RX_PIN;
	GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStructure);

	/* Connect PXx to USARTx_Tx */
	GPIO_PinAFConfig(USARTx_TX_GPIO_PORT, USARTx_TX_SOURCE, USARTx_TX_AF);


	/* Connect PXx to USARTx_Rx */
	GPIO_PinAFConfig(USARTx_RX_GPIO_PORT, USARTx_RX_SOURCE, USARTx_RX_AF);

	/* USARTx configuration ----------------------------------------------------*/
	/* USARTx configured as follow:
  - BaudRate = 230400 baud  
  - Word Length = 8 Bits
  - One Stop Bit
  - No parity
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled
  */
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USARTx, &USART_InitStructure);


	// USART_ITConfig(USART1, USART_IT_PE, ENABLE);
	// USART_ITConfig(USART1, USART_IT_ERR, ENABLE);

	/* NVIC configuration */
	/* Enable the USARTx Interrupt */

	NVIC_InitStructure.NVIC_IRQChannel = USARTx_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);
	USARTx->CR3 |= USART_CR3_OVRDIS;
	//USART_ITConfig(USARTx, USART_IT_TXE, ENABLE);

	/* Enable USART */
	USART_Cmd(USARTx, ENABLE);

	/** init ringbuf **/

	rb_init(&rb1_recv, sizeof(rxbuf), rxbuf);
}

uint32_t HardwareSerial::available(void)
{
	return rb_full_count(&rb1_recv);

	return 0;
}

uint8_t HardwareSerial::read(void)
{
	Timer1msCnt = 0;
	while (!this->available() && Timer1msCnt<=50)
		;
	return rb_remove(&rb1_recv);

	return 0;
}

uint32_t HardwareSerial::write(uint8_t ch)
{
	USART_SendData(USARTx, ch);
	Timer1msCnt = 0;
	while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET && Timer1msCnt<=50)
		;

	return 1;
}

void HardwareSerial::flush()
{
	rb_reset(&rb1_recv);
}

void HardwareSerial::print(const char *format, ...)
{
	va_list args;
	char buf[256];
	va_start(args, format);
	vsprintf(buf, format, args);
	va_end(args);
	putstr(buf);
}

void HardwareSerial::putstr(const char *str)
{
	int i;
	for (i = 0; i < strlen(str); i++)
	{
		write(str[i]);
	}
}

#ifdef __cplusplus
extern "C"
{
#endif
	void USARTx_IRQHandler(void)
	{	                                    
		unsigned char data;
		if (USART_GetITStatus(USARTx, USART_IT_RXNE) == SET)
		{
			data = USART_ReceiveData(USARTx);
			rb_push_insert(&rb1_recv, data);
			//USART_SendData(USARTx,data);
			//while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
			USART_ClearITPendingBit(USARTx, USART_IT_RXNE);
		}
		USART_ClearFlag(USARTx, USART_FLAG_ORE);
	}

#ifdef __cplusplus
}
#endif
