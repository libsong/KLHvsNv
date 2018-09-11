#include <stm32f4xx.h>
#include <string.h>
#include <stdio.h>
#include "mulcast.h"  
#include "comm.h"
  
struct udp_pcb* udp_server_multi_pcb;//组播pcb控制块
struct ip_addr ipgroup_rev,ipgroup_send;  
struct mcuinfo g_MCUinfo;  
extern u8 g_IpAllModified;
extern u16 LOCAL_UDPPORT_m;
extern u8 g_udpinited;
  
u16 lwip_demo_buf_len = 0;   

extern void STMFLASH_Read(u32 ReadAddr,u32 *pBuffer,u32 NumToRead);
extern void STMFLASH_Write(u32 WriteAddr,u32 *pBuffer,u32 NumToWrite);
  
//send
void multicast_send_data(unsigned char * data,unsigned short len)  
{  
	struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT,len, PBUF_RAM);  
  
	if(udp_server_multi_pcb!=NULL){ 
		memcpy(p->payload, data, len);  
		  
		udp_sendto(udp_server_multi_pcb, p,(struct ip_addr *) (&ipgroup_send),UDP_MULTICASE_SEND_PORT); 
	}
	
	pbuf_free(p); 	   
}  
  
//组播接收回调函数
void udp_server_rev(void* arg,struct udp_pcb* upcb,struct pbuf* p,struct ip_addr*addr ,u16_t port)
{  
int i,j; 
	u8 	tmp_flash[FLASH_PROC_SIZE];
	u8_t	tmp_buf[COMM_LEN];
	err_t 	recv_err = ERR_OK;
	u8_t	host_len = 0;
	u8_t	tmp_crc = 0;
	uint32_t uid[3] = {0};
	  
	if(p!=NULL){  
		if((p->tot_len)>=COMM_LEN){         //如果长度过长则额外处理        
			//memcpy(tmp_buf,p->payload,LWIP_DEMO_BUF); 
//			printf("mulcast recv err : comm packet len > %d\n",COMM_LEN);
			return ;
		}else{                
			memcpy(tmp_buf,p->payload,p->tot_len);  
		}  
		
		for (i = 0; i < 8; i++) {
				if (tmp_buf[i] != 0xbe) {
				recv_err = ERR_KLDATA;
			}
		}

		if (recv_err == ERR_OK) 
		{
			host_len = tmp_buf[9];
			for (i = 10; i < 10+host_len; i++) {
			  tmp_crc += tmp_buf[i];
			}
			if (tmp_crc != tmp_buf[10+host_len]) {
			  recv_err = ERR_KLDATA; 
			}
		}

		if (recv_err == ERR_OK) 
		{
			for (i = 11+host_len; i < 19+host_len; i++) {
			  if (tmp_buf[i] != 0xff) {
				recv_err = ERR_KLDATA;
			  }
			}
		}
		if (recv_err == ERR_OK) 
		{
			for (i = 31+host_len; i < 39+host_len; i++) {
			  if (tmp_buf[i] != 0xed) {
				recv_err = ERR_KLDATA;
			  }
			}
		}	
		
		if (recv_err == ERR_OK) {
			memcpy(&uid[0],&tmp_buf[33],4);
			memcpy(&uid[1],&tmp_buf[37],4);
			memcpy(&uid[2],&tmp_buf[41],4);
//			printf("uid = %x - %x - %x\n",uid[0],uid[1],uid[2]);
			for (i = 0; i < 3; i++) {				
			  if (g_MCUinfo.mcuUID[i] != uid[i]) {
				recv_err = ERR_KLDATA;
			  }
			}
			
			if (recv_err == ERR_OK) {
				STMFLASH_Read(FLASH_PROCHEAD,(u32 *)tmp_flash,FLASH_PROC_SIZE/4);
				for (i=0;i<FLASH_PROCHEAD_SIZE;i=i+2) {
					tmp_flash[i] = 0xaa; 
					tmp_flash[i+1] = 0x55;
				}
				
				tmp_flash[64] = tmp_buf[10];
				tmp_flash[65] = tmp_buf[11];
				tmp_flash[66] = tmp_buf[12];
				tmp_flash[67] = tmp_buf[13];
				tmp_flash[68] = tmp_buf[14];
				tmp_flash[69] = tmp_buf[15];
				
				tmp_flash[72] = tmp_buf[16];
				tmp_flash[73] = tmp_buf[17];
				tmp_flash[74] = tmp_buf[18];
				tmp_flash[75] = tmp_buf[19];
				tmp_flash[76] = tmp_buf[20];
				tmp_flash[77] = tmp_buf[21];
				tmp_flash[78] = tmp_buf[22];
				tmp_flash[79] = tmp_buf[23];
				
				STMFLASH_Write(FLASH_PROCHEAD,(u32*)tmp_flash,FLASH_PROC_SIZE/4);
			}
		} 
	}  
}
   
void Multicast_Config(void)   
{  
	int i;  
	
	IP4_ADDR(&ipgroup_rev, 235,236,237,238);//用于接收组播的地址
	IP4_ADDR(&ipgroup_send, 225,226,227,228);//用于发送组播的地址  

	igmp_joingroup(IP_ADDR_ANY,(struct ip_addr *)(&ipgroup_rev));//只需要将接收地址放入igmp组，发送不需要	  
	
	udp_server_multi_pcb = udp_new();   
	if(udp_server_multi_pcb!=NULL){  
		udp_bind(udp_server_multi_pcb,IP_ADDR_ANY,UDP_MULTICASE_RECV_PORT);//组播接收地址
		udp_recv(udp_server_multi_pcb,udp_server_rev,NULL);//  
	}  
}  

int McuInfoInit(u8* buf)
{
	u8 tmp[128];
	int i,j;
	u16 len = 0;
	u8 crc = 0;
	
	for (i=0;i<8;i++) {
		tmp[i] = 0xbe;
	}
	for (i=8;i<16;i++) {
		tmp[i] = 0xaa;
	}
	
	len = sizeof(struct mcuinfo);
	tmp[16] = len&0xff;
	tmp[17] = len>>8;
	tmp[18] = MCUPACKETTYPE;//0x01
	
	g_MCUinfo.devType = DEVTYPECODE;//0x0300
	if (g_IpAllModified == 1) {
		g_MCUinfo.port = LOCAL_UDPPORT_m;
	}
	else
		g_MCUinfo.port = LOCAL_UDPPORT;//0x2710
	memset(g_MCUinfo.devName,'\0',32);
	memset(g_MCUinfo.devSN,'\0',16);
	memset(g_MCUinfo.mcuType,'\0',16);
	strcpy(g_MCUinfo.devName ,DEVNAME);//"HighValtageBox"
	strcpy(g_MCUinfo.devSN,DEVSN);//"SN0"
	strcpy(g_MCUinfo.mcuType,MCUTYPE);//"STM32F407"
	g_MCUinfo.mcuSV[0] = MCUSV_MAJOR;
	g_MCUinfo.mcuSV[1] = MCUSV_MINOR;
	g_MCUinfo.mcuSV[2] = MCUSV_DEBUG;
	g_MCUinfo.mcuHV[0] = MCUHV_MAJOR;
	g_MCUinfo.mcuHV[1] = MCUHV_MINOR;
	
	

	memcpy(&tmp[19],&g_MCUinfo,len);
	for (i=19;i<(19+len);i++) {
		crc += tmp[i];
	}
	tmp[i++] = crc;
	
	for (j=i;j<(i+8);j++){
		tmp[j] = 0x55;
	}
	for (j=i+8;j<(i+8+8);j++){
		tmp[j] = 0xed;
	}
	
	memcpy(buf,tmp,(8+8+2+1+len+1+8+8));
	
	return (8+8+2+1+len+1+8+8);
}