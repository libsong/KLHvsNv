#pragma once

#define RELAY1_ON GPIO_SetBits(GPIOE,GPIO_Pin_10)
#define RELAY2_ON GPIO_SetBits(GPIOE,GPIO_Pin_7)
#define RELAY3_ON GPIO_SetBits(GPIOE,GPIO_Pin_8)

#define RELAY1_OFF GPIO_ResetBits(GPIOE,GPIO_Pin_10)
#define RELAY2_OFF GPIO_ResetBits(GPIOE,GPIO_Pin_7)
#define RELAY3_OFF GPIO_ResetBits(GPIOE,GPIO_Pin_8)

#define RELAY4_ON GPIO_SetBits(GPIOG,GPIO_Pin_0)
#define RELAY4_OFF GPIO_ResetBits(GPIOG,GPIO_Pin_0)







