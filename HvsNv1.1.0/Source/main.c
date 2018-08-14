#include "stm32f4xx.h"
#include "led.h"
#include "os.h"
#include "os_cpu_bsp.h"
#include "netconf.h"
#include "net_config.h"
#include "comm.h"
#include "stmflash.h"
#include "adc.h"

extern u8 TemperetureCheckAndActions(void);
extern u8 g_OcOverLimit;

#define MCUMULCASTPACKETLEN 200
extern void Multicast_Config(void);
extern int McuInfoInit(u8* buf);
extern void multicast_send_data(unsigned char * data,unsigned short len);
u8 g_udpinited = 0;

u8 g_IpAllModified = 1;
extern u8 IP_ADDR0_m;   
extern u8 IP_ADDR1_m;   
extern u8 IP_ADDR2_m;   
extern u8 IP_ADDR3_m; 
extern u16 LOCAL_UDPPORT_m;
extern u8 NETMASK_ADDR0_m;   
extern u8 NETMASK_ADDR1_m;   
extern u8 NETMASK_ADDR2_m;   
extern u8 NETMASK_ADDR3_m;
extern u8 GW_ADDR0_m;   
extern u8 GW_ADDR1_m;   
extern u8 GW_ADDR2_m;   
extern u8 GW_ADDR3_m;

#define  APP_TASK_START_STK_SIZE                    2048
#define  APP_TASK_LED1_STK_SIZE                     1024
#define  APP_TASK_NET_STK_SIZE                      1536
#define  APP_TASK_ADCGET_STK_SIZE                   1024

//数值越低 优先级越高
//#define  APP_TASK_START_PRIO                        7
//#define  APP_TASK_LED1_PRIO                         8
//#define  APP_TASK_NET_PRIO                          9
//#define  APP_TASK_ADCGET_PRIO                       10
#define  APP_TASK_START_PRIO                        7
#define  APP_TASK_LED1_PRIO                         8
#define  APP_TASK_NET_PRIO                          10
#define  APP_TASK_ADCGET_PRIO                       9

static OS_TCB AppTaskStartTCB;
static OS_TCB AppTaskLED1TCB;
static OS_TCB AppTaskNETTCB;
static OS_TCB AppTaskADCGETTCB;

static CPU_STK AppTaskStartStk[APP_TASK_START_STK_SIZE];
static CPU_STK AppTaskLED1Stk[APP_TASK_LED1_STK_SIZE];
static CPU_STK AppTaskNETStk[APP_TASK_NET_STK_SIZE];
static CPU_STK AppTaskADCGETStk[APP_TASK_ADCGET_STK_SIZE];

void RelayPin_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA\
												| RCC_AHB1Periph_GPIOB\
												| RCC_AHB1Periph_GPIOC\
												| RCC_AHB1Periph_GPIOD\
												| RCC_AHB1Periph_GPIOE\
												| RCC_AHB1Periph_GPIOF\
												| RCC_AHB1Periph_GPIOG\
												| RCC_AHB1Periph_GPIOH\
												| RCC_AHB1Periph_GPIOI,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType  = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_10 | GPIO_Pin_9\
																| GPIO_Pin_8 | GPIO_Pin_6 | GPIO_Pin_4;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//PB
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 |GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_6\
																| GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9\
																| GPIO_Pin_14 | GPIO_Pin_15; 	
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//PC
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 |GPIO_Pin_11 | GPIO_Pin_10 | GPIO_Pin_6\
																| GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9; 	
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	//PD
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 |GPIO_Pin_6 | GPIO_Pin_5 | GPIO_Pin_4\
																| GPIO_Pin_3 | GPIO_Pin_2 | GPIO_Pin_8 | GPIO_Pin_9\
																|GPIO_Pin_10 |GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13\
																|GPIO_Pin_14 |GPIO_Pin_15; 	
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	//PE
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 |GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10\
																| GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14\
																|GPIO_Pin_15 |GPIO_Pin_0 | GPIO_Pin_1; 	
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	//PF
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13\
																| GPIO_Pin_14|GPIO_Pin_15; 	
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	
	//PG(GPIO_Pin_11 | GPIO_Pin_14 | GPIO_Pin_13\| )
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_15 | GPIO_Pin_9 | GPIO_Pin_10\
																| GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4\
																| GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8\
																| GPIO_Pin_0 | GPIO_Pin_1; 	
	GPIO_Init(GPIOG, &GPIO_InitStructure);	
	
	//PH
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13\
																| GPIO_Pin_14|GPIO_Pin_15  | GPIO_Pin_3\
																| GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8; 	
	GPIO_Init(GPIOH, &GPIO_InitStructure);
	GPIO_WriteBit(GPIOH, GPIO_Pin_7,Bit_SET);	//RN led
	
	//PI
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2\
																| GPIO_Pin_5 | GPIO_Pin_4  | GPIO_Pin_3\
																| GPIO_Pin_6 | GPIO_Pin_7; 	
	GPIO_Init(GPIOI, &GPIO_InitStructure);
}

void udpecho_init(void);
void tcpecho_init(void);

void AppTaskNET(void * pdata)
{
	u8 tmp[FLASH_PROCHEAD_SIZE];
	int i;
	//int size = sizeof(tmp)+((sizeof(tmp)%4)?1:0);
	
	//read flash to check if ip... modified or not
	//20s 0x55aa present modified
	STMFLASH_Read(FLASH_PROCHEAD,(u32 *)tmp,FLASH_PROCHEAD_SIZE/4);
	for (i=0;i<FLASH_PROCHEAD_SIZE;i=i+2) {
		if (tmp[i] == 0xaa && tmp[i+1] == 0x55) {
			
		}
		else {
			g_IpAllModified = 0;
		}
	}
	if (g_IpAllModified == 1) {
		STMFLASH_Read(FLASH_IP_PORT,(u32 *)tmp,2);
		IP_ADDR0_m = tmp[0];   
		IP_ADDR1_m = tmp[1];   
		IP_ADDR2_m = tmp[2];  
		IP_ADDR3_m = tmp[3];
		
		LOCAL_UDPPORT_m = ((tmp[5] << 8) | tmp[4]);
		
		STMFLASH_Read(FLASH_NM_GW,(u32 *)tmp,2);
		NETMASK_ADDR0_m = tmp[0];
		NETMASK_ADDR1_m = tmp[1];
		NETMASK_ADDR2_m = tmp[2];
		NETMASK_ADDR3_m = tmp[3];
		GW_ADDR0_m = tmp[4];
		GW_ADDR1_m = tmp[5];
		GW_ADDR2_m = tmp[6];
		GW_ADDR3_m = tmp[7];
	}
	
	/* Configure ethernet (GPIOs, clocks, MAC, DMA) */
	init_ethernet();

	/* Initilaize the LwIP stack */
	LwIP_Init();
	
	udpecho_init();
	//tcpecho_init();
	
	g_udpinited = 1;
	/* Infinite loop */
  while (1)
  {
    /* check if any packet received */
    if (ETH_CheckFrameReceived())
    {
      /* process received ethernet packet */
      LwIP_Pkt_Handle();
    }
  }
}

void AppTaskLED1(void * pdata)
{
	OS_ERR err;
	u8 data[MCUMULCASTPACKETLEN] = {0};
	int len;

	BEEP_ON;
	OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &err);
	BEEP_OFF;
	
	while(1)
	{
//		LedToggle();
		//LedOff();
		//BEEP_ON;
		OSTimeDlyHMSM(0, 0, 0, 500, OS_OPT_TIME_HMSM_STRICT, &err);
		//LedOn();
		//BEEP_OFF;
		OSTimeDlyHMSM(0, 0, 0, 500, OS_OPT_TIME_HMSM_STRICT, &err);
		
		if (g_udpinited == 1) {
			Multicast_Config();
			g_udpinited = 0;
			
			len = McuInfoInit(data);
		}
		multicast_send_data(data,len);
	}
}

void AppTaskADCGET(void * pdata)
{
	OS_ERR err;
	u8 	TempCheckRet = 0;
	while(1)
	{
		OSTimeDlyHMSM(0, 0, 6, 0, OS_OPT_TIME_HMSM_STRICT, &err);
		TempCheckRet = TemperetureCheckAndActions();
		if(TempCheckRet != 0 || g_OcOverLimit == 1){
			BEEP_ON;
		}
		WeGetAdcOneByOne();
	}
}

void AppTaskStart(void *p_arg)
{
	OS_ERR err;

	(void)p_arg;
	
	CPU_Init();
	Mem_Init();
	
	RelayPin_Init();
	//
	ADC1_Init();
	ADC3_Init();         //初始化ADC
	
	BSP_Tick_Init();
	
	#if OS_CFG_STAT_TASK_EN > 0u
	OSStatTaskCPUUsageInit(&err);                               
	#endif

	CPU_IntDisMeasMaxCurReset();

	OSTaskCreate((OS_TCB     *)&AppTaskLED1TCB,
							 (CPU_CHAR   *)"App Task LED1",
							 (OS_TASK_PTR ) AppTaskLED1,
							 (void       *) 0,
							 (OS_PRIO     ) APP_TASK_LED1_PRIO,
							 (CPU_STK    *)&AppTaskLED1Stk[0],
							 (CPU_STK_SIZE) APP_TASK_LED1_STK_SIZE / 10,
							 (CPU_STK_SIZE) APP_TASK_LED1_STK_SIZE,
							 (OS_MSG_QTY  ) 5u,
							 (OS_TICK     ) 0u,
							 (void       *) 0,
							 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
							 (OS_ERR     *)&err);

	OSTaskCreate((OS_TCB     *)&AppTaskNETTCB,
							 (CPU_CHAR   *)"App Task NET",
							 (OS_TASK_PTR ) AppTaskNET,
							 (void       *) 0,
							 (OS_PRIO     ) APP_TASK_NET_PRIO,
							 (CPU_STK    *)&AppTaskNETStk[0],
							 (CPU_STK_SIZE) APP_TASK_NET_STK_SIZE / 10,
							 (CPU_STK_SIZE) APP_TASK_NET_STK_SIZE,
							 (OS_MSG_QTY  ) 5u,
							 (OS_TICK     ) 0u,
							 (void       *) 0,
							 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
							 (OS_ERR     *)&err);
							 
	OSTaskCreate((OS_TCB     *)&AppTaskADCGETTCB,
							 (CPU_CHAR   *)"App Task ADCGET",
							 (OS_TASK_PTR ) AppTaskADCGET,
							 (void       *) 0,
							 (OS_PRIO     ) APP_TASK_ADCGET_PRIO,
							 (CPU_STK    *)&AppTaskADCGETStk[0],
							 (CPU_STK_SIZE) APP_TASK_ADCGET_STK_SIZE / 10,
							 (CPU_STK_SIZE) APP_TASK_ADCGET_STK_SIZE,
							 (OS_MSG_QTY  ) 5u,
							 (OS_TICK     ) 0u,
							 (void       *) 0,
							 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
							 (OS_ERR     *)&err);
							 						
	OSTaskDel(&AppTaskStartTCB, &err);
}

int main(void)
{
	OS_ERR err;
	
	OSInit(&err);
	
	OSTaskCreate((OS_TCB     *)&AppTaskStartTCB,
							 (CPU_CHAR   *)"App Task Start",
							 (OS_TASK_PTR ) AppTaskStart,
							 (void       *) 0,
							 (OS_PRIO     ) APP_TASK_START_PRIO,
							 (CPU_STK    *)&AppTaskStartStk[0],
							 (CPU_STK_SIZE) APP_TASK_START_STK_SIZE / 10,
							 (CPU_STK_SIZE) APP_TASK_START_STK_SIZE,
							 (OS_MSG_QTY  ) 5u,
							 (OS_TICK     ) 0u,
							 (void       *) 0,
							 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
							 (OS_ERR     *)&err);
	
	OSStart(&err);
}
