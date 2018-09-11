#include "stm32f4xx.h"
#include "stm32f4x7_eth.h"
#include "eth_driver.h"

void ETH_GPIO_Config_RMII(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	/* Enable GPIOs clocks */
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOD | 
//	                       RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOG , ENABLE);

  ETH_DeInit();
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	SYSCFG_ETH_MediaInterfaceConfig(SYSCFG_ETH_MediaInterface_RMII);
	
	//配置PA1 PA2 PA7
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;  
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_ETH); //引脚复用到网络接口上
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_ETH);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_ETH);

	//配置PC1,PC4 and PC5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource1, GPIO_AF_ETH); //引脚复用到网络接口上
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource4, GPIO_AF_ETH);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource5, GPIO_AF_ETH);
	 
	/* Configure PG11, PG14 and PG13 */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_14;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource11, GPIO_AF_ETH);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource13, GPIO_AF_ETH);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource14, GPIO_AF_ETH);

#if 0 
	//配置PG11, PB12 and PB13 
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource11, GPIO_AF_ETH);
	//TXD0、TXD1
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12 | GPIO_Pin_13;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource12, GPIO_AF_ETH);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_ETH);
	#endif
}

void ConfigPHY_ResetPin(void)
{
	GPIO_InitTypeDef PortConfig;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG,ENABLE);
	PortConfig.GPIO_Pin = GPIO_Pin_7;
	PortConfig.GPIO_Mode = GPIO_Mode_OUT;
	PortConfig.GPIO_OType  = GPIO_OType_PP;
	PortConfig.GPIO_Speed = GPIO_Speed_100MHz;
	PortConfig.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOG,&PortConfig);	
}

void ResetPHY(void)
{
	volatile u32 Delay;
	GPIO_ResetBits(GPIOG,GPIO_Pin_7);
	//os_dly_wait(2);
	Delay = 0xfffff;
	while (Delay--);
	GPIO_SetBits(GPIOG,GPIO_Pin_7);
	//os_dly_wait(2);
	Delay = 0xfffff;
	while (Delay--);
}

void ETHERNET_NVICConfiguration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;	
	NVIC_InitStructure.NVIC_IRQChannel = ETH_IRQn;  //以太网中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0X00; //中断寄存器组2最高优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0X00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

//初始化ETH MAC层及DMA配置
//返回值:	ETH_ERROR,发送失败(0)
//				ETH_SUCCESS,发送成功(1)
#define  DP83848_PHY_ADDRESS          0x01
static u8 ETH_MACDMA_Config(void)
{
	u8 rval;
	ETH_InitTypeDef ETH_InitStructure; 
	
	//使能以太网时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_ETH_MAC | RCC_AHB1Periph_ETH_MAC_Tx |RCC_AHB1Periph_ETH_MAC_Rx, ENABLE);                       
	ETH_DeInit();  								//AHB总线重启以太网
	ETH_SoftwareReset();  						//软件重启网络
	while (ETH_GetSoftwareResetStatus() == SET);//等待软件重启网络完成 
	ETH_StructInit(&ETH_InitStructure); 	 	//初始化网络为默认值  
	///网络MAC参数设置 
	ETH_InitStructure.ETH_AutoNegotiation = ETH_AutoNegotiation_Enable;   			//开启网络自适应功能
	ETH_InitStructure.ETH_LoopbackMode = ETH_LoopbackMode_Disable;					//关闭反馈
	ETH_InitStructure.ETH_RetryTransmission = ETH_RetryTransmission_Disable; 		//关闭重传功能
	ETH_InitStructure.ETH_AutomaticPadCRCStrip = ETH_AutomaticPadCRCStrip_Disable; 	//关闭自动去除PDA/CRC功能 
	ETH_InitStructure.ETH_ReceiveAll = ETH_ReceiveAll_Disable;						//关闭接收所有的帧
	ETH_InitStructure.ETH_BroadcastFramesReception = ETH_BroadcastFramesReception_Enable;//允许接收所有广播帧
	ETH_InitStructure.ETH_PromiscuousMode = ETH_PromiscuousMode_Disable;			//关闭混合模式的地址过滤  
	//ETH_InitStructure.ETH_MulticastFramesFilter = ETH_MulticastFramesFilter_Perfect;//对于组播地址使用完美地址过滤   
	ETH_InitStructure.ETH_MulticastFramesFilter = ETH_MulticastFramesFilter_None;
	ETH_InitStructure.ETH_UnicastFramesFilter = ETH_UnicastFramesFilter_Perfect;	//对单播地址使用完美地址过滤 
	ETH_InitStructure.ETH_ChecksumOffload = ETH_ChecksumOffload_Enable; 			//开启ipv4和TCP/UDP/ICMP的帧校验和卸载   

	//当我们使用帧校验和卸载功能的时候，一定要使能存储转发模式,存储转发模式中要保证整个帧存储在FIFO中,
	//这样MAC能插入/识别出帧校验值,当真校验正确的时候DMA就可以处理帧,否则就丢弃掉该帧
	ETH_InitStructure.ETH_DropTCPIPChecksumErrorFrame = ETH_DropTCPIPChecksumErrorFrame_Enable; //开启丢弃TCP/IP错误帧
	ETH_InitStructure.ETH_ReceiveStoreForward = ETH_ReceiveStoreForward_Enable;     //开启接收数据的存储转发模式    
	ETH_InitStructure.ETH_TransmitStoreForward = ETH_TransmitStoreForward_Enable;   //开启发送数据的存储转发模式  

	ETH_InitStructure.ETH_ForwardErrorFrames = ETH_ForwardErrorFrames_Disable;     	//禁止转发错误帧  
	ETH_InitStructure.ETH_ForwardUndersizedGoodFrames = ETH_ForwardUndersizedGoodFrames_Disable;	//不转发过小的好帧 
	ETH_InitStructure.ETH_SecondFrameOperate = ETH_SecondFrameOperate_Enable;  		//打开处理第二帧功能
	ETH_InitStructure.ETH_AddressAlignedBeats = ETH_AddressAlignedBeats_Enable;  	//开启DMA传输的地址对齐功能
	ETH_InitStructure.ETH_FixedBurst = ETH_FixedBurst_Enable;            			//开启固定突发功能    
	ETH_InitStructure.ETH_RxDMABurstLength = ETH_RxDMABurstLength_32Beat;     		//DMA发送的最大突发长度为32个节拍   
	ETH_InitStructure.ETH_TxDMABurstLength = ETH_TxDMABurstLength_32Beat;			//DMA接收的最大突发长度为32个节拍
	ETH_InitStructure.ETH_DMAArbitration = ETH_DMAArbitration_RoundRobin_RxTx_1_1;
	//本人对此库函数作了修改，添加了对DM8603的初始化
	rval = ETH_Init(&ETH_InitStructure, DP83848_PHY_ADDRESS);		//配置ETH
	if(rval == ETH_SUCCESS)//配置成功
	{
		//ETH_DMAITConfig(ETH_DMA_IT_NIS | ETH_DMA_IT_R | ETH_DMA_IT_AIS | ETH_DMA_IT_RBU,ENABLE);  	//使能以太网接收中断	
	}
	return rval;
}

void LwIP_Pkt_Handle(void);
void ETH_IRQHandler(void)
{
	/* check if any packet received */
	if (ETH_CheckFrameReceived())
	{ 
		/* process received ethernet packet */
		LwIP_Pkt_Handle();
	}
	//当Rx Buffer不可用位(RBUS)被设置的时候,重置它.恢复传输
	if((ETH->DMASR & ETH_DMASR_RBUS) != (u32)RESET)
	{ 
		ETH->DMASR = ETH_DMASR_RBUS;//重置ETH DMA RBUS位 
		ETH->DMARPDR = 0;//恢复DMA接收
	}
	ETH_DMAClearITPendingBit(ETH_DMA_IT_NIS | ETH_DMA_IT_AIS | ETH_DMA_IT_R);
}

void init_ethernet(void)
{
	//u8 macaddress[6]={0x04,0x02,0x35,0x00,0x00,0x01};

	ETH_GPIO_Config_RMII();
//	ConfigPHY_ResetPin();
//	ResetPHY();

	ETHERNET_NVICConfiguration();	
	//MCU内部MAC及DMA初始化
	ETH_MACDMA_Config();

/* 下面这段代码在ethernetif.c里实现了
	
	//向STM32F4的MAC地址寄存器中写入MAC地址
	ETH_MACAddressConfig(ETH_MAC_Address0, macaddress); 
	ETH_DMATxDescChainInit(DMATxDscrTab, &Tx_Buff[0][0], ETH_TXBUFNB);
	ETH_DMARxDescChainInit(DMARxDscrTab, &Rx_Buff[0][0], ETH_RXBUFNB);
  #if 0
	//RL-TCP不能使用硬件帧校验
	for(i=0;i<ETH_TXBUFNB;i++)	//使能TCP,UDP和ICMP的发送帧校验,TCP,UDP和ICMP的接收帧校验在DMA中配置了
	{
		ETH_DMATxDescChecksumInsertionConfig(&DMATxDscrTab[i], ETH_DMATxDesc_ChecksumTCPUDPICMPFull);
	}
	#endif
	ETH_Start(); //开启MAC和DMA	
	
*/
}

