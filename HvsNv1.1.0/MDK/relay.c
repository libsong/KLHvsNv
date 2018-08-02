#include "comm.h"

extern u8 relay1_84[RELAY1_84_LEN];

void relay_clear(void) 
{
	//PA
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	GPIO_ResetBits(GPIOA,GPIO_Pin_6);
	GPIO_ResetBits(GPIOA,GPIO_Pin_8);
	GPIO_ResetBits(GPIOA,GPIO_Pin_9);
	GPIO_ResetBits(GPIOA,GPIO_Pin_10);
	GPIO_ResetBits(GPIOA,GPIO_Pin_15);
	//B
	GPIO_ResetBits(GPIOB,GPIO_Pin_2);
	GPIO_ResetBits(GPIOB,GPIO_Pin_3);
	GPIO_ResetBits(GPIOB,GPIO_Pin_4);
	GPIO_ResetBits(GPIOB,GPIO_Pin_6);
	GPIO_ResetBits(GPIOB,GPIO_Pin_7);
	GPIO_ResetBits(GPIOB,GPIO_Pin_8);
	GPIO_ResetBits(GPIOB,GPIO_Pin_9);
	GPIO_ResetBits(GPIOB,GPIO_Pin_14);
	GPIO_ResetBits(GPIOB,GPIO_Pin_15);
	//C
	GPIO_ResetBits(GPIOC,GPIO_Pin_6);
	GPIO_ResetBits(GPIOC,GPIO_Pin_7);
	GPIO_ResetBits(GPIOC,GPIO_Pin_8);
	GPIO_ResetBits(GPIOC,GPIO_Pin_9);
	GPIO_ResetBits(GPIOC,GPIO_Pin_10);
	GPIO_ResetBits(GPIOC,GPIO_Pin_11);
	GPIO_ResetBits(GPIOC,GPIO_Pin_12);
	//D
	GPIO_ResetBits(GPIOD,GPIO_Pin_2);
	GPIO_ResetBits(GPIOD,GPIO_Pin_3);
	GPIO_ResetBits(GPIOD,GPIO_Pin_4);
	GPIO_ResetBits(GPIOD,GPIO_Pin_5);
	GPIO_ResetBits(GPIOD,GPIO_Pin_6);
	GPIO_ResetBits(GPIOD,GPIO_Pin_7);
	GPIO_ResetBits(GPIOD,GPIO_Pin_8);
	GPIO_ResetBits(GPIOD,GPIO_Pin_9);
	GPIO_ResetBits(GPIOD,GPIO_Pin_10);
	GPIO_ResetBits(GPIOD,GPIO_Pin_11);
	GPIO_ResetBits(GPIOD,GPIO_Pin_12);
	GPIO_ResetBits(GPIOD,GPIO_Pin_13);
	GPIO_ResetBits(GPIOD,GPIO_Pin_14);
	GPIO_ResetBits(GPIOD,GPIO_Pin_15);
	//E
	GPIO_ResetBits(GPIOE,GPIO_Pin_0);
	GPIO_ResetBits(GPIOE,GPIO_Pin_1);
	GPIO_ResetBits(GPIOE,GPIO_Pin_7);
	GPIO_ResetBits(GPIOE,GPIO_Pin_8);
	GPIO_ResetBits(GPIOE,GPIO_Pin_9);
	GPIO_ResetBits(GPIOE,GPIO_Pin_10);
	GPIO_ResetBits(GPIOE,GPIO_Pin_11);
	GPIO_ResetBits(GPIOE,GPIO_Pin_12);
	GPIO_ResetBits(GPIOE,GPIO_Pin_13);
	GPIO_ResetBits(GPIOE,GPIO_Pin_14);
	GPIO_ResetBits(GPIOE,GPIO_Pin_15);
	//F
	GPIO_ResetBits(GPIOF,GPIO_Pin_11);
	GPIO_ResetBits(GPIOF,GPIO_Pin_12);
	GPIO_ResetBits(GPIOF,GPIO_Pin_13);
	GPIO_ResetBits(GPIOF,GPIO_Pin_14);
	GPIO_ResetBits(GPIOF,GPIO_Pin_15);
	//G
	GPIO_ResetBits(GPIOG,GPIO_Pin_All);
	//H
	GPIO_ResetBits(GPIOH,GPIO_Pin_3);
	GPIO_ResetBits(GPIOH,GPIO_Pin_5);
	GPIO_ResetBits(GPIOH,GPIO_Pin_6);
	GPIO_ResetBits(GPIOH,GPIO_Pin_8);
	GPIO_ResetBits(GPIOH,GPIO_Pin_11);
	GPIO_ResetBits(GPIOH,GPIO_Pin_12);
	GPIO_ResetBits(GPIOH,GPIO_Pin_13);
	GPIO_ResetBits(GPIOH,GPIO_Pin_14);
	GPIO_ResetBits(GPIOH,GPIO_Pin_15);
	//I
	GPIO_ResetBits(GPIOI,GPIO_Pin_0);
	GPIO_ResetBits(GPIOI,GPIO_Pin_1);
	GPIO_ResetBits(GPIOI,GPIO_Pin_2);
	GPIO_ResetBits(GPIOI,GPIO_Pin_3);
	GPIO_ResetBits(GPIOI,GPIO_Pin_4);
	GPIO_ResetBits(GPIOI,GPIO_Pin_5);
	GPIO_ResetBits(GPIOI,GPIO_Pin_6);
	GPIO_ResetBits(GPIOI,GPIO_Pin_7);
}

void relay_active(void) 
{
	//RELAY 1~8
	//GPIO_WriteBit(GPIOI, GPIO_Pin_7,((relay1_84[0]>>0)&0x1)); //从属同步于 relay 28 
	GPIO_WriteBit(GPIOI, GPIO_Pin_6,((relay1_84[0]>>1)&0x1));
	GPIO_WriteBit(GPIOI, GPIO_Pin_5,((relay1_84[0]>>2)&0x1));
	//GPIO_WriteBit(GPIOI, GPIO_Pin_4,((relay1_84[0]>>3)&0x1));	//从属同步于 relay 18 
	GPIO_WriteBit(GPIOE, GPIO_Pin_1,((relay1_84[0]>>4)&0x1));
	//GPIO_WriteBit(GPIOE, GPIO_Pin_0,((relay1_84[0]>>5)&0x1));	////从属同步于 relay 38 或 58
	if (((relay1_84[4]>>5)&0x1) || ((relay1_84[7]>>1)&0x1)) {
		GPIO_WriteBit(GPIOE, GPIO_Pin_1,Bit_SET);
	}
	else {
		GPIO_WriteBit(GPIOE, GPIO_Pin_1,Bit_RESET);
	}
	//GPIO_WriteBit(GPIOB, GPIO_Pin_9,((relay1_84[0]>>6)&0x1));	//从属同步于 relay 26 
	GPIO_WriteBit(GPIOB, GPIO_Pin_8,((relay1_84[0]>>7)&0x1));
	
	//RELAY9~16
	//GPIO_WriteBit(GPIOB, GPIO_Pin_7,((relay1_84[1]>>0)&0x1));	//从属同步于 relay 32
	//GPIO_WriteBit(GPIOB, GPIO_Pin_6,((relay1_84[1]>>1)&0x1));	//从属同步于 relay 30
	GPIO_WriteBit(GPIOB, GPIO_Pin_4,((relay1_84[1]>>2)&0x1));
	//GPIO_WriteBit(GPIOB, GPIO_Pin_3,((relay1_84[1]>>3)&0x1));		//从属同步于 relay 36 或 21
	if (((relay1_84[4]>>3)&0x1) || ((relay1_84[2]>>4)&0x1)) {
		GPIO_WriteBit(GPIOB, GPIO_Pin_3,Bit_SET);
	}
	else {
		GPIO_WriteBit(GPIOB, GPIO_Pin_3,Bit_RESET);
	}
	//GPIO_WriteBit(GPIOG, GPIO_Pin_15,((relay1_84[1]>>4)&0x1));	//从属同步于 relay 34 
//	GPIO_WriteBit(GPIOG, GPIO_Pin_7,((relay1_84[1]>>5)&0x1));	//
	GPIO_WriteBit(GPIOH, GPIO_Pin_10,((relay1_84[1]>>6)&0x1));
	//GPIO_WriteBit(GPIOG, GPIO_Pin_12,((relay1_84[1]>>7)&0x1));	//从属同步于 relay 19 
	
	//RELAY17~24
	GPIO_WriteBit(GPIOH, GPIO_Pin_11,((relay1_84[2]>>0)&0x1));
	GPIO_WriteBit(GPIOG, GPIO_Pin_10,((relay1_84[2]>>1)&0x1)); 	GPIO_WriteBit(GPIOI, GPIO_Pin_4,((relay1_84[2]>>1)&0x1));
	GPIO_WriteBit(GPIOG, GPIO_Pin_9,((relay1_84[2]>>2)&0x1));	GPIO_WriteBit(GPIOG, GPIO_Pin_12,((relay1_84[2]>>2)&0x1));
	GPIO_WriteBit(GPIOD, GPIO_Pin_7,((relay1_84[2]>>3)&0x1));
	GPIO_WriteBit(GPIOD, GPIO_Pin_6,((relay1_84[2]>>4)&0x1));	
	GPIO_WriteBit(GPIOD, GPIO_Pin_5,((relay1_84[2]>>5)&0x1));
	GPIO_WriteBit(GPIOD, GPIO_Pin_4,((relay1_84[2]>>6)&0x1));
	GPIO_WriteBit(GPIOD, GPIO_Pin_3,((relay1_84[2]>>7)&0x1));
	
	//RELAY25~32
	GPIO_WriteBit(GPIOD, GPIO_Pin_2,((relay1_84[3]>>0)&0x1));
	GPIO_WriteBit(GPIOC, GPIO_Pin_12,((relay1_84[3]>>1)&0x1));	GPIO_WriteBit(GPIOB, GPIO_Pin_9,((relay1_84[3]>>1)&0x1));
	GPIO_WriteBit(GPIOC, GPIO_Pin_11,((relay1_84[3]>>2)&0x1));
	GPIO_WriteBit(GPIOC, GPIO_Pin_10,((relay1_84[3]>>3)&0x1));	GPIO_WriteBit(GPIOI, GPIO_Pin_7,((relay1_84[3]>>3)&0x1));
	GPIO_WriteBit(GPIOA, GPIO_Pin_15,((relay1_84[3]>>4)&0x1));
	GPIO_WriteBit(GPIOI, GPIO_Pin_3,((relay1_84[3]>>5)&0x1));	GPIO_WriteBit(GPIOB, GPIO_Pin_6,((relay1_84[3]>>5)&0x1));
	GPIO_WriteBit(GPIOI, GPIO_Pin_2,((relay1_84[3]>>6)&0x1));
	GPIO_WriteBit(GPIOI, GPIO_Pin_1,((relay1_84[3]>>7)&0x1));	GPIO_WriteBit(GPIOB, GPIO_Pin_7,((relay1_84[3]>>7)&0x1));
	
	//RELAY33~40
	GPIO_WriteBit(GPIOI, GPIO_Pin_0,((relay1_84[4]>>0)&0x1));
	GPIO_WriteBit(GPIOH, GPIO_Pin_15,((relay1_84[4]>>1)&0x1));	GPIO_WriteBit(GPIOG, GPIO_Pin_15,((relay1_84[4]>>1)&0x1));
	GPIO_WriteBit(GPIOH, GPIO_Pin_14,((relay1_84[4]>>2)&0x1));
	GPIO_WriteBit(GPIOH, GPIO_Pin_13,((relay1_84[4]>>3)&0x1));		
	GPIO_WriteBit(GPIOA, GPIO_Pin_10,((relay1_84[4]>>4)&0x1));
	GPIO_WriteBit(GPIOA, GPIO_Pin_9,((relay1_84[4]>>5)&0x1));	
	GPIO_WriteBit(GPIOA, GPIO_Pin_8,((relay1_84[4]>>6)&0x1));
	GPIO_WriteBit(GPIOC, GPIO_Pin_9,((relay1_84[4]>>7)&0x1));
	
	//RELAY41~48
	GPIO_WriteBit(GPIOC, GPIO_Pin_8,((relay1_84[5]>>0)&0x1));
	GPIO_WriteBit(GPIOC, GPIO_Pin_7,((relay1_84[5]>>1)&0x1));
	GPIO_WriteBit(GPIOC, GPIO_Pin_6,((relay1_84[5]>>2)&0x1));
	GPIO_WriteBit(GPIOG, GPIO_Pin_8,((relay1_84[5]>>3)&0x1));
	GPIO_WriteBit(GPIOG, GPIO_Pin_7,((relay1_84[5]>>4)&0x1));
	GPIO_WriteBit(GPIOG, GPIO_Pin_6,((relay1_84[5]>>5)&0x1));
	GPIO_WriteBit(GPIOG, GPIO_Pin_5,((relay1_84[5]>>6)&0x1));
	GPIO_WriteBit(GPIOG, GPIO_Pin_4,((relay1_84[5]>>7)&0x1));
	
	//RELAY49~56
	GPIO_WriteBit(GPIOG, GPIO_Pin_3,((relay1_84[6]>>0)&0x1));
	GPIO_WriteBit(GPIOG, GPIO_Pin_2,((relay1_84[6]>>1)&0x1));
	GPIO_WriteBit(GPIOD, GPIO_Pin_15,((relay1_84[6]>>2)&0x1));
	GPIO_WriteBit(GPIOD, GPIO_Pin_14,((relay1_84[6]>>3)&0x1));
	GPIO_WriteBit(GPIOD, GPIO_Pin_13,((relay1_84[6]>>4)&0x1));
	GPIO_WriteBit(GPIOD, GPIO_Pin_12,((relay1_84[6]>>5)&0x1));
	GPIO_WriteBit(GPIOD, GPIO_Pin_11,((relay1_84[6]>>6)&0x1));
	GPIO_WriteBit(GPIOD, GPIO_Pin_10,((relay1_84[6]>>7)&0x1));
	
	//RELAY57~64
	GPIO_WriteBit(GPIOD, GPIO_Pin_9,((relay1_84[7]>>0)&0x1));
	GPIO_WriteBit(GPIOD, GPIO_Pin_8,((relay1_84[7]>>1)&0x1));
	GPIO_WriteBit(GPIOB, GPIO_Pin_15,((relay1_84[7]>>2)&0x1));
	GPIO_WriteBit(GPIOB, GPIO_Pin_14,((relay1_84[7]>>3)&0x1));
	GPIO_WriteBit(GPIOH, GPIO_Pin_12,((relay1_84[7]>>4)&0x1));
	GPIO_WriteBit(GPIOH, GPIO_Pin_3,((relay1_84[7]>>5)&0x1));
	GPIO_WriteBit(GPIOH, GPIO_Pin_5,((relay1_84[7]>>6)&0x1));
	GPIO_WriteBit(GPIOA, GPIO_Pin_4,((relay1_84[7]>>7)&0x1));
	
	//RELAY65~72
	GPIO_WriteBit(GPIOA, GPIO_Pin_6,((relay1_84[8]>>0)&0x1));
	GPIO_WriteBit(GPIOF, GPIO_Pin_11,((relay1_84[8]>>1)&0x1));
	GPIO_WriteBit(GPIOB, GPIO_Pin_2,((relay1_84[8]>>2)&0x1));
	GPIO_WriteBit(GPIOF, GPIO_Pin_13,((relay1_84[8]>>3)&0x1));
	GPIO_WriteBit(GPIOF, GPIO_Pin_12,((relay1_84[8]>>4)&0x1));
	GPIO_WriteBit(GPIOF, GPIO_Pin_15,((relay1_84[8]>>5)&0x1));
	GPIO_WriteBit(GPIOF, GPIO_Pin_14,((relay1_84[8]>>6)&0x1));
	GPIO_WriteBit(GPIOG, GPIO_Pin_1,((relay1_84[8]>>7)&0x1));
	
	//RELAY73~80
	GPIO_WriteBit(GPIOG, GPIO_Pin_0,((relay1_84[9]>>0)&0x1));
	GPIO_WriteBit(GPIOE, GPIO_Pin_8,((relay1_84[9]>>1)&0x1));
	GPIO_WriteBit(GPIOE, GPIO_Pin_7,((relay1_84[9]>>2)&0x1));
	GPIO_WriteBit(GPIOE, GPIO_Pin_10,((relay1_84[9]>>3)&0x1));
	GPIO_WriteBit(GPIOE, GPIO_Pin_9,((relay1_84[9]>>4)&0x1));
	GPIO_WriteBit(GPIOE, GPIO_Pin_12,((relay1_84[9]>>5)&0x1));
	GPIO_WriteBit(GPIOE, GPIO_Pin_11,((relay1_84[9]>>6)&0x1));
	GPIO_WriteBit(GPIOE, GPIO_Pin_14,((relay1_84[9]>>7)&0x1));
	
	//RELAY81~84
	GPIO_WriteBit(GPIOE, GPIO_Pin_13,((relay1_84[10]>>0)&0x1));
	GPIO_WriteBit(GPIOH, GPIO_Pin_6,((relay1_84[10]>>1)&0x1));
	GPIO_WriteBit(GPIOE, GPIO_Pin_15,((relay1_84[10]>>2)&0x1));
	GPIO_WriteBit(GPIOH, GPIO_Pin_8,((relay1_84[10]>>3)&0x1));
	
	#if 0
	//RELAY 1~8
	GPIO_WriteBit(GPIOI, GPIO_Pin_7,((relay1_84[0]>>0)&0x1));
	GPIO_WriteBit(GPIOI, GPIO_Pin_6,((relay1_84[0]>>1)&0x1));
	GPIO_WriteBit(GPIOI, GPIO_Pin_5,((relay1_84[0]>>2)&0x1));
	GPIO_WriteBit(GPIOI, GPIO_Pin_4,((relay1_84[0]>>3)&0x1));
	GPIO_WriteBit(GPIOE, GPIO_Pin_1,((relay1_84[0]>>4)&0x1));
	GPIO_WriteBit(GPIOE, GPIO_Pin_0,((relay1_84[0]>>5)&0x1));
	GPIO_WriteBit(GPIOB, GPIO_Pin_9,((relay1_84[0]>>6)&0x1));
	GPIO_WriteBit(GPIOB, GPIO_Pin_8,((relay1_84[0]>>7)&0x1));
	//RELAY9~16
	GPIO_WriteBit(GPIOB, GPIO_Pin_7,((relay1_84[1]>>0)&0x1));
	GPIO_WriteBit(GPIOB, GPIO_Pin_6,((relay1_84[1]>>1)&0x1));
	GPIO_WriteBit(GPIOB, GPIO_Pin_4,((relay1_84[1]>>2)&0x1));
	GPIO_WriteBit(GPIOB, GPIO_Pin_3,((relay1_84[1]>>3)&0x1));
	GPIO_WriteBit(GPIOG, GPIO_Pin_15,((relay1_84[1]>>4)&0x1));
//	GPIO_WriteBit(GPIOG, GPIO_Pin_14,((relay1_84[1]>>5)&0x1));
//	GPIO_WriteBit(GPIOG, GPIO_Pin_13,((relay1_84[1]>>6)&0x1));
	GPIO_WriteBit(GPIOG, GPIO_Pin_12,((relay1_84[1]>>7)&0x1));
	//RELAY17~24
//	GPIO_WriteBit(GPIOG, GPIO_Pin_11,((relay1_84[2]>>0)&0x1));
	GPIO_WriteBit(GPIOG, GPIO_Pin_10,((relay1_84[2]>>1)&0x1));
	GPIO_WriteBit(GPIOG, GPIO_Pin_9,((relay1_84[2]>>2)&0x1));
	GPIO_WriteBit(GPIOD, GPIO_Pin_7,((relay1_84[2]>>3)&0x1));
	GPIO_WriteBit(GPIOD, GPIO_Pin_6,((relay1_84[2]>>4)&0x1));
	GPIO_WriteBit(GPIOD, GPIO_Pin_5,((relay1_84[2]>>5)&0x1));
	GPIO_WriteBit(GPIOD, GPIO_Pin_4,((relay1_84[2]>>6)&0x1));
	GPIO_WriteBit(GPIOD, GPIO_Pin_3,((relay1_84[2]>>7)&0x1));
	//RELAY25~32
	GPIO_WriteBit(GPIOD, GPIO_Pin_2,((relay1_84[3]>>0)&0x1));
	GPIO_WriteBit(GPIOC, GPIO_Pin_12,((relay1_84[3]>>1)&0x1));
	GPIO_WriteBit(GPIOC, GPIO_Pin_11,((relay1_84[3]>>2)&0x1));
	GPIO_WriteBit(GPIOC, GPIO_Pin_10,((relay1_84[3]>>3)&0x1));
	GPIO_WriteBit(GPIOA, GPIO_Pin_15,((relay1_84[3]>>4)&0x1));
	GPIO_WriteBit(GPIOI, GPIO_Pin_3,((relay1_84[3]>>5)&0x1));
	GPIO_WriteBit(GPIOI, GPIO_Pin_2,((relay1_84[3]>>6)&0x1));
	GPIO_WriteBit(GPIOI, GPIO_Pin_1,((relay1_84[3]>>7)&0x1));
	//RELAY33~40
	GPIO_WriteBit(GPIOI, GPIO_Pin_0,((relay1_84[4]>>0)&0x1));
	GPIO_WriteBit(GPIOH, GPIO_Pin_15,((relay1_84[4]>>1)&0x1));
	GPIO_WriteBit(GPIOH, GPIO_Pin_14,((relay1_84[4]>>2)&0x1));
	GPIO_WriteBit(GPIOH, GPIO_Pin_13,((relay1_84[4]>>3)&0x1));
	GPIO_WriteBit(GPIOA, GPIO_Pin_10,((relay1_84[4]>>4)&0x1));
	GPIO_WriteBit(GPIOA, GPIO_Pin_9,((relay1_84[4]>>5)&0x1));
	GPIO_WriteBit(GPIOA, GPIO_Pin_8,((relay1_84[4]>>6)&0x1));
	GPIO_WriteBit(GPIOC, GPIO_Pin_9,((relay1_84[4]>>7)&0x1));
	//RELAY41~48
	GPIO_WriteBit(GPIOC, GPIO_Pin_8,((relay1_84[5]>>0)&0x1));
	GPIO_WriteBit(GPIOC, GPIO_Pin_7,((relay1_84[5]>>1)&0x1));
	GPIO_WriteBit(GPIOC, GPIO_Pin_6,((relay1_84[5]>>2)&0x1));
	GPIO_WriteBit(GPIOG, GPIO_Pin_8,((relay1_84[5]>>3)&0x1));
	GPIO_WriteBit(GPIOG, GPIO_Pin_7,((relay1_84[5]>>4)&0x1));
	GPIO_WriteBit(GPIOG, GPIO_Pin_6,((relay1_84[5]>>5)&0x1));
	GPIO_WriteBit(GPIOG, GPIO_Pin_5,((relay1_84[5]>>6)&0x1));
	GPIO_WriteBit(GPIOG, GPIO_Pin_4,((relay1_84[5]>>7)&0x1));
	//RELAY49~56
	GPIO_WriteBit(GPIOG, GPIO_Pin_3,((relay1_84[6]>>0)&0x1));
	GPIO_WriteBit(GPIOG, GPIO_Pin_2,((relay1_84[6]>>1)&0x1));
	GPIO_WriteBit(GPIOD, GPIO_Pin_15,((relay1_84[6]>>2)&0x1));
	GPIO_WriteBit(GPIOD, GPIO_Pin_14,((relay1_84[6]>>3)&0x1));
	GPIO_WriteBit(GPIOD, GPIO_Pin_13,((relay1_84[6]>>4)&0x1));
	GPIO_WriteBit(GPIOD, GPIO_Pin_12,((relay1_84[6]>>5)&0x1));
	GPIO_WriteBit(GPIOD, GPIO_Pin_11,((relay1_84[6]>>6)&0x1));
	GPIO_WriteBit(GPIOD, GPIO_Pin_10,((relay1_84[6]>>7)&0x1));
	//RELAY57~64
	GPIO_WriteBit(GPIOD, GPIO_Pin_9,((relay1_84[7]>>0)&0x1));
	GPIO_WriteBit(GPIOD, GPIO_Pin_8,((relay1_84[7]>>1)&0x1));
	GPIO_WriteBit(GPIOB, GPIO_Pin_15,((relay1_84[7]>>2)&0x1));
	GPIO_WriteBit(GPIOB, GPIO_Pin_14,((relay1_84[7]>>3)&0x1));
	GPIO_WriteBit(GPIOH, GPIO_Pin_12,((relay1_84[7]>>4)&0x1));
	GPIO_WriteBit(GPIOH, GPIO_Pin_3,((relay1_84[7]>>5)&0x1));
	GPIO_WriteBit(GPIOH, GPIO_Pin_5,((relay1_84[7]>>6)&0x1));
	GPIO_WriteBit(GPIOA, GPIO_Pin_4,((relay1_84[7]>>7)&0x1));
	//RELAY65~72
	GPIO_WriteBit(GPIOA, GPIO_Pin_6,((relay1_84[8]>>0)&0x1));
	GPIO_WriteBit(GPIOF, GPIO_Pin_11,((relay1_84[8]>>1)&0x1));
	GPIO_WriteBit(GPIOB, GPIO_Pin_2,((relay1_84[8]>>2)&0x1));
	GPIO_WriteBit(GPIOF, GPIO_Pin_13,((relay1_84[8]>>3)&0x1));
	GPIO_WriteBit(GPIOF, GPIO_Pin_12,((relay1_84[8]>>4)&0x1));
	GPIO_WriteBit(GPIOF, GPIO_Pin_15,((relay1_84[8]>>5)&0x1));
	GPIO_WriteBit(GPIOF, GPIO_Pin_14,((relay1_84[8]>>6)&0x1));
	GPIO_WriteBit(GPIOG, GPIO_Pin_1,((relay1_84[8]>>7)&0x1));
	//RELAY73~80
	GPIO_WriteBit(GPIOG, GPIO_Pin_0,((relay1_84[9]>>0)&0x1));
	GPIO_WriteBit(GPIOE, GPIO_Pin_8,((relay1_84[9]>>1)&0x1));
	GPIO_WriteBit(GPIOE, GPIO_Pin_7,((relay1_84[9]>>2)&0x1));
	GPIO_WriteBit(GPIOE, GPIO_Pin_10,((relay1_84[9]>>3)&0x1));
	GPIO_WriteBit(GPIOE, GPIO_Pin_9,((relay1_84[9]>>4)&0x1));
	GPIO_WriteBit(GPIOE, GPIO_Pin_12,((relay1_84[9]>>5)&0x1));
	GPIO_WriteBit(GPIOE, GPIO_Pin_11,((relay1_84[9]>>6)&0x1));
	GPIO_WriteBit(GPIOE, GPIO_Pin_14,((relay1_84[9]>>7)&0x1));
	//RELAY81~84
	GPIO_WriteBit(GPIOE, GPIO_Pin_13,((relay1_84[10]>>0)&0x1));
	GPIO_WriteBit(GPIOH, GPIO_Pin_6,((relay1_84[10]>>1)&0x1));
	GPIO_WriteBit(GPIOE, GPIO_Pin_15,((relay1_84[10]>>2)&0x1));
	GPIO_WriteBit(GPIOH, GPIO_Pin_8,((relay1_84[10]>>3)&0x1));
	#endif
}

















