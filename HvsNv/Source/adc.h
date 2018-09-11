#ifndef __ADC_H
#define __ADC_H	
#include "comm.h" 

//////////////////////////////////////////////////////////////////////////////////	 
 							   
void	ADC1_Init(void); 				//ADC通道初始化
void  ADC3_Init(void);
u16  	Get_Adc(u8 ch); 				//获得某个通道值 
u16  	Get_Adc3(u8 ch); 
u16 	Get_Adc_Average(u8 ch,u8 times);//得到某个通道给定次数采样的平均值  
u16 	Get_Adc3_Average(u8 ch,u8 times);
void 	WeGetAdcOneByOne(void);

#endif 















