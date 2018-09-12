#pragma once

#include "stm32f4xx.h"
#include "lwip/udp.h"  
#include "lwip/pbuf.h"  
#include "lwip/igmp.h"  

//
#define MCUPACKETTYPE 1	//���ݰ�����: 1�豸��������Ϣ
#define DEVTYPECODE 0x0300 //�豸�����ʶ��0x0100��Դ�� 0x0200������ 0x0300��ѹģ����
#define DEVNAME "HighValtageBox"
#define MCUTYPE "STM32F407"
#define DEVSN "SN1-180911"

#define MCUSV_MAJOR 1	//���汾�� 
#define MCUSV_MINOR 2  //�ΰ汾
#define MCUSV_DEBUG 0  //bug�޸�

#define MCUHV_MAJOR 1	//���汾�� 
#define MCUHV_MINOR 1  //�ΰ汾 , ���ں�ʢ��Ŀ

//define the slave info 
#pragma pack(1)
struct mcuinfo{
	u16		devType;
	u16		port;
	s8		devName[32];
	s8		devSN[16];
	s8		mcuType[16]; 
	u32		mcuUID[3];
	u8		mcuSV[3];
	u8		mcuIP[4];
	u8		mcuNetMask[4];
	u8		mcuGW[4]; 
	u8		mcuMAC[6]; 
	u8		mcuHV[2];
	u8		reserve[1];
};
#pragma pack()


/*port */  
#define UDP_MULTICASE_RECV_PORT 45654    // multicast port for recive  
#define UDP_MULTICASE_SEND_PORT 54345   // multicast port for send  
  
#define  LWIP_DEMO_BUF     2048 



