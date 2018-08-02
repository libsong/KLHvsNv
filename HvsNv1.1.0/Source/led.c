#include "stm32f4xx.h"
#include "led.h"

#define  LED_PORT      GPIOG
#define  LED_PIN       GPIO_Pin_11
#define  LED_ON_LEVEL     1     //当为0时，表示低电平时，LED亮；当为1时，表示高电平LED亮

extern void LedOff(void)
{
	#if  LED_ON_LEVEL == 1
	  GPIO_ResetBits(LED_PORT,LED_PIN);
	#else	
	  GPIO_SetBits(LED_PORT,LED_PIN);
	#endif
}

extern void LedOn(void)
{
	#if LED_ON_LEVEL == 1	
	  GPIO_SetBits(LED_PORT,LED_PIN);
	#else
		GPIO_ResetBits(LED_PORT,LED_PIN);
	#endif
	
}

extern void LedToggle(void)
{
	GPIO_ToggleBits(LED_PORT,LED_PIN);	
}

extern void LedInit(void)
{
	GPIO_InitTypeDef LedPortConfig;
	if(LED_PORT == GPIOA)
	{			
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	}		
	else if (LED_PORT == GPIOB)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	}
	else if (LED_PORT == GPIOC)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	}
	else if (LED_PORT == GPIOD)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	}
	else if (LED_PORT == GPIOE)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	}
	else if (LED_PORT == GPIOF)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
	}
	else if (LED_PORT == GPIOG)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG,ENABLE);
	}
	else if (LED_PORT == GPIOH)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH,ENABLE);
	}
	else if (LED_PORT == GPIOI)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI,ENABLE);
	}
	else if (LED_PORT == GPIOJ)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOJ,ENABLE);
	}
	else if (LED_PORT == GPIOK)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOK,ENABLE);
	}
	else //LED端口不在芯片的IO端口
	{
	}	
	LedPortConfig.GPIO_Pin = LED_PIN;
	LedPortConfig.GPIO_Mode = GPIO_Mode_OUT;
	LedPortConfig.GPIO_OType  = GPIO_OType_PP;
	LedPortConfig.GPIO_Speed = GPIO_Speed_100MHz;
	LedPortConfig.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(LED_PORT,&LedPortConfig);	
}

extern void LedPortDeInit(void)
{
	GPIO_DeInit(LED_PORT);
}

/************************ (C) COPYRIGHT GoldSea *****END OF FILE****/






