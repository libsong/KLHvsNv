#include "adc.h"	
#include "stdio.h"
#include "string.h"
#include "os.h"

float AD_V1G,AD_V12,AD_V34,AD_V56,AD_HALL;
float ToHostQuery[5];
u8 			g_OcOverLimit = 0;

//初始化ADC															   
void  ADC1_Init(void)
{    
	GPIO_InitTypeDef  GPIO_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //使能ADC1时钟

	//先初始化ADC1通道 IO口
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//模拟输入
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//不带上下拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化   

	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);	  //ADC1复位
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);	//复位结束	 


	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//独立模式
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//两个采样阶段之间的延迟5个时钟
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMA失能
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;//预分频4分频。ADCCLK=PCLK2/4=84/4=21Mhz,ADC时钟最好不要超过36Mhz 
	ADC_CommonInit(&ADC_CommonInitStructure);//初始化

	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12位模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;//非扫描模式	
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//关闭连续转换
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//禁止触发检测，使用软件触发
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//右对齐	
	ADC_InitStructure.ADC_NbrOfConversion = 1;//1个转换在规则序列中 也就是只转换规则序列1 
	ADC_Init(ADC1, &ADC_InitStructure);//ADC初始化

	ADC_Cmd(ADC1, ENABLE);//开启AD转换器	
}

void  ADC3_Init(void)
{    
	GPIO_InitTypeDef  GPIO_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//使能时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE); //使能时钟

	//先初始化ADC通道
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 \
									| GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//模拟输入
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//不带上下拉
	GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化  

	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3,ENABLE);	  
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3,DISABLE);	//复位结束	 

	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//独立模式
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//两个采样阶段之间的延迟5个时钟
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMA失能
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;//预分频4分频。ADCCLK=PCLK2/4=84/4=21Mhz,ADC时钟最好不要超过36Mhz 
	ADC_CommonInit(&ADC_CommonInitStructure);//初始化

	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12位模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;//非扫描模式	
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//关闭连续转换
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//禁止触发检测，使用软件触发
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//右对齐	
	ADC_InitStructure.ADC_NbrOfConversion = 1;//1个转换在规则序列中 也就是只转换规则序列1 
	ADC_Init(ADC3, &ADC_InitStructure);//ADC初始化

	ADC_Cmd(ADC3, ENABLE);//开启AD转换器	
}	  

/****************************************************************************
* 名    称: u16 Get_Adc(u8 ch) 
* 功    能：获得ADC值
* 入口参数：ch: 通道值 0~16取值范围为：ADC_Channel_0~ADC_Channel_16
* 返回参数：12位ADC有效值
* 说    明：       
****************************************************************************/
u16 Get_Adc(u8 ch)   
{
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_480Cycles );	//ADC1,ADC通道,480个周期,提高采样时间可以提高精确度			    
  
	ADC_SoftwareStartConv(ADC1);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}

u16 Get_Adc3(u8 ch)   
{
	ADC_RegularChannelConfig(ADC3, ch, 1, ADC_SampleTime_480Cycles );	//ADC1,ADC通道,480个周期,提高采样时间可以提高精确度			    
  
	ADC_SoftwareStartConv(ADC3);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC3, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC3);	//返回最近一次ADC1规则组的转换结果
}

/****************************************************************************
* 名    称: u16 Get_Adc_Average(u8 ch,u8 times) 
* 功    能：获取通道ch的转换值，取times次,然后平均 
* 入口参数：ch: 通道值 0~16取值范围为：ADC_Channel_0~ADC_Channel_16
*           times:获取次数
* 返回参数：通道ch的times次转换结果平均值
* 说    明：       
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

	adc_data = Get_Adc3_Average(ADC_Channel_9,ADC_GETAVERAGE_K);//获取通道的转换值，20次取平均
	AD_V1G = (float)adc_data*(ADVCC_K/4096) - OPVREF_K;            //获取计算后的带小数的实际电压值，比如5.1141
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





