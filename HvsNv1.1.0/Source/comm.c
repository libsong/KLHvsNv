#include "comm.h"

//mcu addr of id
unsigned int mcu_idAddr[]={
	0x1FFFF7AC,  /*STM32F0??ID????*/

                0x1FFFF7E8,  /*STM32F1??ID????*/

                0x1FFF7A10,  /*STM32F2??ID????*/

                0x1FFFF7AC,  /*STM32F3??ID????*/

                0x1FFF7A10,  /*STM32F4??ID????*/

                0x1FF0F420,  /*STM32F7??ID????*/

                0x1FF80050,  /*STM32L0??ID????*/

                0x1FF80050,  /*STM32L1??ID????*/

                0x1FFF7590,  /*STM32L4??ID????*/

                0x1FF0F420 /*STM32H7??ID????*/
}; 

//record our mac addr
u8 g_macid[6] = {0};

//read mcu id
void GetSTM32MCUID(uint32_t *id,MCUTypedef type)
{

  if(id != 0)

  {

    id[0]=*(uint32_t*)(mcu_idAddr[type]);

    id[1]=*(uint32_t*)(mcu_idAddr[type]+4);

    id[2]=*(uint32_t*)(mcu_idAddr[type]+8);

  }

}


















