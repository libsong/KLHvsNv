#ifndef __ADC_H
#define __ADC_H	
#include "comm.h" 

//////////////////////////////////////////////////////////////////////////////////	 
 							   
void	ADC1_Init(void); 				//ADCͨ����ʼ��
void  ADC3_Init(void);
u16  	Get_Adc(u8 ch); 				//���ĳ��ͨ��ֵ 
u16  	Get_Adc3(u8 ch); 
u16 	Get_Adc_Average(u8 ch,u8 times);//�õ�ĳ��ͨ����������������ƽ��ֵ  
u16 	Get_Adc3_Average(u8 ch,u8 times);
void 	WeGetAdcOneByOne(void);

#endif 















