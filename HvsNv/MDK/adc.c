#include "adc.h"	
#include "stdio.h"
#include "string.h"
#include "os.h"

float AD_V1G,AD_V12,AD_V34,AD_V56,AD_HALL;
float ToHostQuery[5];
u8 			g_OcOverLimit = 0;

//��ʼ��ADC															   
void  ADC1_Init(void)
{    
	GPIO_InitTypeDef  GPIO_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //ʹ��ADC1ʱ��

	//�ȳ�ʼ��ADC1ͨ�� IO��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//ģ������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��   

	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);	  //ADC1��λ
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);	//��λ����	 


	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//����ģʽ
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//���������׶�֮����ӳ�5��ʱ��
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMAʧ��
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;//Ԥ��Ƶ4��Ƶ��ADCCLK=PCLK2/4=84/4=21Mhz,ADCʱ����ò�Ҫ����36Mhz 
	ADC_CommonInit(&ADC_CommonInitStructure);//��ʼ��

	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12λģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;//��ɨ��ģʽ	
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//�ر�����ת��
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//��ֹ������⣬ʹ���������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���	
	ADC_InitStructure.ADC_NbrOfConversion = 1;//1��ת���ڹ��������� Ҳ����ֻת����������1 
	ADC_Init(ADC1, &ADC_InitStructure);//ADC��ʼ��

	ADC_Cmd(ADC1, ENABLE);//����ADת����	
}

void  ADC3_Init(void)
{    
	GPIO_InitTypeDef  GPIO_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//ʹ��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE); //ʹ��ʱ��

	//�ȳ�ʼ��ADCͨ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 \
									| GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//ģ������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//����������
	GPIO_Init(GPIOF, &GPIO_InitStructure);//��ʼ��  

	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3,ENABLE);	  
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3,DISABLE);	//��λ����	 

	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//����ģʽ
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//���������׶�֮����ӳ�5��ʱ��
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMAʧ��
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;//Ԥ��Ƶ4��Ƶ��ADCCLK=PCLK2/4=84/4=21Mhz,ADCʱ����ò�Ҫ����36Mhz 
	ADC_CommonInit(&ADC_CommonInitStructure);//��ʼ��

	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12λģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;//��ɨ��ģʽ	
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//�ر�����ת��
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//��ֹ������⣬ʹ���������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���	
	ADC_InitStructure.ADC_NbrOfConversion = 1;//1��ת���ڹ��������� Ҳ����ֻת����������1 
	ADC_Init(ADC3, &ADC_InitStructure);//ADC��ʼ��

	ADC_Cmd(ADC3, ENABLE);//����ADת����	
}	  

/****************************************************************************
* ��    ��: u16 Get_Adc(u8 ch) 
* ��    �ܣ����ADCֵ
* ��ڲ�����ch: ͨ��ֵ 0~16ȡֵ��ΧΪ��ADC_Channel_0~ADC_Channel_16
* ���ز�����12λADC��Чֵ
* ˵    ����       
****************************************************************************/
u16 Get_Adc(u8 ch)   
{
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_480Cycles );	//ADC1,ADCͨ��,480������,��߲���ʱ�������߾�ȷ��			    
  
	ADC_SoftwareStartConv(ADC1);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}

u16 Get_Adc3(u8 ch)   
{
	ADC_RegularChannelConfig(ADC3, ch, 1, ADC_SampleTime_480Cycles );	//ADC1,ADCͨ��,480������,��߲���ʱ�������߾�ȷ��			    
  
	ADC_SoftwareStartConv(ADC3);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC3, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADC3);	//�������һ��ADC1�������ת�����
}

/****************************************************************************
* ��    ��: u16 Get_Adc_Average(u8 ch,u8 times) 
* ��    �ܣ���ȡͨ��ch��ת��ֵ��ȡtimes��,Ȼ��ƽ�� 
* ��ڲ�����ch: ͨ��ֵ 0~16ȡֵ��ΧΪ��ADC_Channel_0~ADC_Channel_16
*           times:��ȡ����
* ���ز�����ͨ��ch��times��ת�����ƽ��ֵ
* ˵    ����       
****************************************************************************/
u16 Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	OS_ERR err;
	
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		OSTimeDlyHMSM(0, 0, 0, 5, OS_OPT_TIME_HMSM_STRICT, &err);
	}
	return temp_val/times;
}

u16 Get_Adc3_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	OS_ERR err;
	
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc3(ch);
		OSTimeDlyHMSM(0, 0, 0, 5, OS_OPT_TIME_HMSM_STRICT, &err);
	}
	return temp_val/times;
}


extern u8 g_OcOverLimit;
void WeGetAdcOneByOne(void)
{
	u16 adc_data;
	u8 tt[4];
	float temp;

	adc_data = Get_Adc3_Average(ADC_Channel_9,ADC_GETAVERAGE_K);//��ȡͨ����ת��ֵ��20��ȡƽ��
	AD_V1G = (float)adc_data*(ADVCC_K/4096) - OPVREF_K;            //��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������5.1141
	AD_V1G = AD_V1G * ADAPTJUST_K;
	memcpy(&ToHostQuery[0],&AD_V1G,sizeof(float));
	
	adc_data = Get_Adc3_Average(ADC_Channel_14,ADC_GETAVERAGE_K);
	AD_V12 = (float)adc_data*(ADVCC_K/4096) - OPVREF_K;
	AD_V12 = AD_V12 * ADAPTJUST_K;
	memcpy(&ToHostQuery[1],&AD_V12,sizeof(float));
	
	adc_data = Get_Adc3_Average(ADC_Channel_15,ADC_GETAVERAGE_K);
	AD_V34 = (float)adc_data*(ADVCC_K/4096) - OPVREF_K;
	AD_V34 = AD_V34 * ADAPTJUST_K;
	memcpy(&ToHostQuery[2],&AD_V34,sizeof(float));
	
	adc_data =Get_Adc3_Average(ADC_Channel_4,ADC_GETAVERAGE_K);
	AD_V56 = (float)adc_data*(ADVCC_K/4096) - OPVREF_K;
	AD_V56 = AD_V56 * ADAPTJUST_K;
	memcpy(&ToHostQuery[3],&AD_V56,sizeof(float));
	
	adc_data = Get_Adc3_Average(ADC_Channel_5,ADC_GETAVERAGE_K);
	temp = (float)adc_data*(ADVCC_K/4096) - CVREF_K;
	AD_HALL	= temp/CURRENT_K;
	memcpy(&ToHostQuery[4],&AD_HALL,sizeof(float));
	if(AD_HALL > 20 || AD_HALL < -20){
		//LED_OC_ON;
		g_OcOverLimit =1;
	}
	else{
		//LED_OC_OFF;
	}
	//memcpy(&ToHostQuery[4],&adc_data,2);
	
	return ;
}





