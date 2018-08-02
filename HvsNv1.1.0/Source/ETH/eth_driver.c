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
	
	//����PA1 PA2 PA7
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;  
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_ETH); //���Ÿ��õ�����ӿ���
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_ETH);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_ETH);

	//����PC1,PC4 and PC5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource1, GPIO_AF_ETH); //���Ÿ��õ�����ӿ���
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource4, GPIO_AF_ETH);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource5, GPIO_AF_ETH);
	 
	/* Configure PG11, PG14 and PG13 */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_14;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource11, GPIO_AF_ETH);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource13, GPIO_AF_ETH);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource14, GPIO_AF_ETH);

#if 0 
	//����PG11, PB12 and PB13 
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11;
	GPIO_Init(GPIOG, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource11, GPIO_AF_ETH);
	//TXD0��TXD1
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
	NVIC_InitStructure.NVIC_IRQChannel = ETH_IRQn;  //��̫���ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0X00; //�жϼĴ�����2������ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0X00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

//��ʼ��ETH MAC�㼰DMA����
//����ֵ:	ETH_ERROR,����ʧ��(0)
//				ETH_SUCCESS,���ͳɹ�(1)
#define  DP83848_PHY_ADDRESS          0x01
static u8 ETH_MACDMA_Config(void)
{
	u8 rval;
	ETH_InitTypeDef ETH_InitStructure; 
	
	//ʹ����̫��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_ETH_MAC | RCC_AHB1Periph_ETH_MAC_Tx |RCC_AHB1Periph_ETH_MAC_Rx, ENABLE);                       
	ETH_DeInit();  								//AHB����������̫��
	ETH_SoftwareReset();  						//�����������
	while (ETH_GetSoftwareResetStatus() == SET);//�ȴ��������������� 
	ETH_StructInit(&ETH_InitStructure); 	 	//��ʼ������ΪĬ��ֵ  
	///����MAC�������� 
	ETH_InitStructure.ETH_AutoNegotiation = ETH_AutoNegotiation_Enable;   			//������������Ӧ����
	ETH_InitStructure.ETH_LoopbackMode = ETH_LoopbackMode_Disable;					//�رշ���
	ETH_InitStructure.ETH_RetryTransmission = ETH_RetryTransmission_Disable; 		//�ر��ش�����
	ETH_InitStructure.ETH_AutomaticPadCRCStrip = ETH_AutomaticPadCRCStrip_Disable; 	//�ر��Զ�ȥ��PDA/CRC���� 
	ETH_InitStructure.ETH_ReceiveAll = ETH_ReceiveAll_Disable;						//�رս������е�֡
	ETH_InitStructure.ETH_BroadcastFramesReception = ETH_BroadcastFramesReception_Enable;//����������й㲥֡
	ETH_InitStructure.ETH_PromiscuousMode = ETH_PromiscuousMode_Disable;			//�رջ��ģʽ�ĵ�ַ����  
	//ETH_InitStructure.ETH_MulticastFramesFilter = ETH_MulticastFramesFilter_Perfect;//�����鲥��ַʹ��������ַ����   
	ETH_InitStructure.ETH_MulticastFramesFilter = ETH_MulticastFramesFilter_None;
	ETH_InitStructure.ETH_UnicastFramesFilter = ETH_UnicastFramesFilter_Perfect;	//�Ե�����ַʹ��������ַ���� 
	ETH_InitStructure.ETH_ChecksumOffload = ETH_ChecksumOffload_Enable; 			//����ipv4��TCP/UDP/ICMP��֡У���ж��   

	//������ʹ��֡У���ж�ع��ܵ�ʱ��һ��Ҫʹ�ܴ洢ת��ģʽ,�洢ת��ģʽ��Ҫ��֤����֡�洢��FIFO��,
	//����MAC�ܲ���/ʶ���֡У��ֵ,����У����ȷ��ʱ��DMA�Ϳ��Դ���֡,����Ͷ�������֡
	ETH_InitStructure.ETH_DropTCPIPChecksumErrorFrame = ETH_DropTCPIPChecksumErrorFrame_Enable; //��������TCP/IP����֡
	ETH_InitStructure.ETH_ReceiveStoreForward = ETH_ReceiveStoreForward_Enable;     //�����������ݵĴ洢ת��ģʽ    
	ETH_InitStructure.ETH_TransmitStoreForward = ETH_TransmitStoreForward_Enable;   //�����������ݵĴ洢ת��ģʽ  

	ETH_InitStructure.ETH_ForwardErrorFrames = ETH_ForwardErrorFrames_Disable;     	//��ֹת������֡  
	ETH_InitStructure.ETH_ForwardUndersizedGoodFrames = ETH_ForwardUndersizedGoodFrames_Disable;	//��ת����С�ĺ�֡ 
	ETH_InitStructure.ETH_SecondFrameOperate = ETH_SecondFrameOperate_Enable;  		//�򿪴���ڶ�֡����
	ETH_InitStructure.ETH_AddressAlignedBeats = ETH_AddressAlignedBeats_Enable;  	//����DMA����ĵ�ַ���빦��
	ETH_InitStructure.ETH_FixedBurst = ETH_FixedBurst_Enable;            			//�����̶�ͻ������    
	ETH_InitStructure.ETH_RxDMABurstLength = ETH_RxDMABurstLength_32Beat;     		//DMA���͵����ͻ������Ϊ32������   
	ETH_InitStructure.ETH_TxDMABurstLength = ETH_TxDMABurstLength_32Beat;			//DMA���յ����ͻ������Ϊ32������
	ETH_InitStructure.ETH_DMAArbitration = ETH_DMAArbitration_RoundRobin_RxTx_1_1;
	//���˶Դ˿⺯�������޸ģ�����˶�DM8603�ĳ�ʼ��
	rval = ETH_Init(&ETH_InitStructure, DP83848_PHY_ADDRESS);		//����ETH
	if(rval == ETH_SUCCESS)//���óɹ�
	{
		//ETH_DMAITConfig(ETH_DMA_IT_NIS | ETH_DMA_IT_R | ETH_DMA_IT_AIS | ETH_DMA_IT_RBU,ENABLE);  	//ʹ����̫�������ж�	
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
	//��Rx Buffer������λ(RBUS)�����õ�ʱ��,������.�ָ�����
	if((ETH->DMASR & ETH_DMASR_RBUS) != (u32)RESET)
	{ 
		ETH->DMASR = ETH_DMASR_RBUS;//����ETH DMA RBUSλ 
		ETH->DMARPDR = 0;//�ָ�DMA����
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
	//MCU�ڲ�MAC��DMA��ʼ��
	ETH_MACDMA_Config();

/* ������δ�����ethernetif.c��ʵ����
	
	//��STM32F4��MAC��ַ�Ĵ�����д��MAC��ַ
	ETH_MACAddressConfig(ETH_MAC_Address0, macaddress); 
	ETH_DMATxDescChainInit(DMATxDscrTab, &Tx_Buff[0][0], ETH_TXBUFNB);
	ETH_DMARxDescChainInit(DMARxDscrTab, &Rx_Buff[0][0], ETH_RXBUFNB);
  #if 0
	//RL-TCP����ʹ��Ӳ��֡У��
	for(i=0;i<ETH_TXBUFNB;i++)	//ʹ��TCP,UDP��ICMP�ķ���֡У��,TCP,UDP��ICMP�Ľ���֡У����DMA��������
	{
		ETH_DMATxDescChecksumInsertionConfig(&DMATxDscrTab[i], ETH_DMATxDesc_ChecksumTCPUDPICMPFull);
	}
	#endif
	ETH_Start(); //����MAC��DMA	
	
*/
}

