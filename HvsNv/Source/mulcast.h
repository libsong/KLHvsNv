#pragma once

#include "stm32f4xx.h"
#include "lwip/udp.h"  
#include "lwip/pbuf.h"  
#include "lwip/igmp.h"  

//
#define MCUPACKETTYPE 1	//数据包种类: 1设备发基本信息
#define DEVTYPECODE 0x0300 //设备种类标识，0x0100电源类 0x0200故障类 0x0300高压模拟类
#define DEVNAME "HighValtageBox"
#define MCUTYPE "STM32F407"
#define DEVSN "SN1-180911"

#define MCUSV_MAJOR 1	//主版本号 
#define MCUSV_MINOR 2  //次版本
#define MCUSV_DEBUG 0  //bug修改

#define MCUHV_MAJOR 1	//主版本号 
#define MCUHV_MINOR 1  //次版本 , 深圳航盛项目

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



