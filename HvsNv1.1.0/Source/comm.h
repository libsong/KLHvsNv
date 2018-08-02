#pragma once

#include "stm32f4xx.h"

//leave factory port
#define LOCAL_UDPPORT 10000

//cmd
#define COMM_LEN 128	//hoast to mcu communication test cmd len
typedef enum {
  COMM_CMD_TEST,
  COMM_CMD_RELAY_CONF,
	COMM_CMD_RELAY_ACTIVE,
	COMM_CMD_RELAY_RESET,
	COMM_CMD_RELAY_ADC,//GET VAL CUR
  COMM_CMD_IP = 0xc8,
  COMM_CMD_GW = 0xc9,
}COMM_CMD;

//mcu enum
typedef enum {
  STM32F0,
  STM32F1,
  STM32F2,
  STM32F3,
  STM32F4,
  STM32F7,
  STM32L0,
  STM32L1,
  STM32L4,
  STM32H7,
}MCUTypedef;

extern 			u8 g_macid[6];
extern 			u32 mcu_idAddr[];
extern void GetSTM32MCUID(unsigned int *id,MCUTypedef type);

//flash addr to r/w 
#define FLASH_PROC_SIZE 80
#define FLASH_PROCHEAD_SIZE 48 //信息被修改的标识 0xaa55 共24组48个字节
#define FLASH_PROCHEAD  0X080F0000   //proc addr start ,sector11
#define FLASH_IP_PORT  (FLASH_PROCHEAD + 0X40)	//conntent start addr ,(ip+port+netmask+gw)
#define FLASH_NM_GW (FLASH_PROCHEAD + 0X48)

//
#define RELAY1_84_LEN 11

//beep
#define BEEP_ON 					GPIO_WriteBit(GPIOH,GPIO_Pin_11,Bit_SET)
#define BEEP_OFF 					GPIO_WriteBit(GPIOH,GPIO_Pin_11,Bit_RESET)

//adc
#define VOLTAGE_K 1.0
#define CURRENT_K 0.035
#define ADC_GETAVERAGE_K 100
#define OPVREF_K 1.4925
#define CVREF_K 2.48
#define ADVCC_K 3.0
#define ADAPTJUST_K 1.195
#define TEMPLIMITVALUE 750



