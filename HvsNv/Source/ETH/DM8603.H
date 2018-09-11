#ifndef    __DM8603_H
  #define __DM8603_H
	
	#define  DM8603_PHY0_ADDR          0x02
	#define  DM8603_PHY1_ADDR          0x03
	
/***************************
		PHY Registers Map 
****************************/
	//Port 0 PHY Registers
	#define  PHY_P0_BASIC_MODE_CTRL                0x40
	#define  PHY_P0_BASIC_MODE_STATUS              0x41 
	#define  PHY_P0_ID1                            0x42
	#define  PHY_P0_ID2                            0x43
	#define  PHY_P0_AUTO_NEGO_ADVERT               0x44
	#define  PHY_P0_AUTO_NEGO_LINK_PARTNER         0x45
	#define  PHY_P0_AUTO_NEGO_EXPANSION            0x46
	#define  PHY_P0_SPECIFIED_CONFIG               0x54
	#define  PHY_P0_POWER_SAVE_CTRL                0x5D
	
	//Port 1 PHY Registers
	#define  PHY_P1_BASIC_MODE_CTRL                0x60
	#define  PHY_P1_BASIC_MODE_STATUS              0x61
	#define  PHY_P1_ID1                            0x62
	#define  PHY_P1_ID2                            0x63
	#define  PHY_P1_AUTO_NEGO_ADVERT               0x64
	#define  PHY_P1_AUTO_NEGO_LINK_PARTNER         0x65
	#define  PHY_P1_AUTO_NEGO_EXPANSION            0x66
	#define  PHY_P1_SPECIFIED_CONFIG               0x74
	#define  PHY_P1_POWER_SAVE_CTRL                0x7D                                    
 
/*
    Switch Registers Map
*/

	//PORT0 ¼Ä´æÆ÷
	#define  SWH_P0_STATUS                          0X110 
	#define  SWH_P0_BASIC_CTRL1                     0X111 
	#define  SWH_P0_BASIC_CTRL2                     0X112  
	#define  SWH_P0_BLOCK_CTRL1                     0X113  
	#define  SWH_P0_BLOCK_CTRL2                     0X114  
	#define  SWH_P0_BANDWIDTH_CTRL                  0X115 
	#define  SWH_P0_VLAN_TAG                        0X116 
	#define  SWH_P0_PRIORITY_VLAN_CTRL              0X117 
	#define  SWH_P0_ADV_CTRL                        0X119 
	//PORT1 ¼Ä´æÆ÷
	#define  SWH_P1_STATUS                          0X130 
	#define  SWH_P1_BASIC_CTRL1                     0X131 
	#define  SWH_P1_BASIC_CTRL2                     0X132  
	#define  SWH_P1_BLOCK_CTRL1                     0X133  
	#define  SWH_P1_BLOCK_CTRL2                     0X134  
	#define  SWH_P1_BANDWIDTH_CTRL                  0X135 
	#define  SWH_P1_VLAN_TAG                        0X136 
	#define  SWH_P1_PRIORITY_VLAN_CTRL              0X137 
	#define  SWH_P1_ADV_CTRL                        0X139 
	//PORT2 ¼Ä´æÆ÷
	#define  SWH_P2_STATUS                          0X150 
	#define  SWH_P2_BASIC_CTRL1                     0X151 
	#define  SWH_P2_BASIC_CTRL2                     0X152  
	#define  SWH_P2_BLOCK_CTRL1                     0X153  
	#define  SWH_P2_BLOCK_CTRL2                     0X154  
	#define  SWH_P2_BANDWIDTH_CTRL                  0X155 
	#define  SWH_P2_VLAN_TAG                        0X156 
	#define  SWH_P2_PRIORITY_VLAN_CTRL              0X157 
	#define  SWH_P2_ADV_CTRL                        0X159 
	//È«¾Ö¼Ä´æÆ÷
	#define  SWH_SWITCH_STATUS                      0X210
	#define  SWH_SWITCH_RESET                       0X211
	#define  SWH_SWITCH_CTRL                        0X212
	#define  SWH_MIRROR_CTRL                        0X213
	#define  SWH_SPECIAL_TAG_ETHER_TYPE             0X214
	#define  SWH_GLOBAL_LEARN_AGE_CTRL              0X215
	#define  SWH_VLAN_PRIO_MAP                      0X217
	#define  SWH_TOS_PRIO_MAP1                      0X218
	#define  SWH_TOS_PRIO_MAP2                      0X219
	#define  SWH_TOS_PRIO_MAP3                      0X21A
	#define  SWH_TOS_PRIO_MAP4                      0X21B
	#define  SWH_TOS_PRIO_MAP5                      0X21C
	#define  SWH_TOS_PRIO_MAP6                      0X21D
	#define  SWH_TOS_PRIO_MAP7                      0X21E
	#define  SWH_TOS_PRIO_MAP8                      0X21F

	#define  SWH_MIB_COUNTER_DISABLE                0X230
	#define  SWH_MIB_COUNTER_CTRL                   0X231
	#define  SWH_MIB_COUNTER_DATA1                  0X232
	#define  SWH_MIB_COUNTER_DATA2                  0X233
	#define  SWH_VLAN_MODE_RULE_CTRL                0X23E

	#define  SWH_VLAN_Table0                        0x270
	#define  SWH_VLAN_Table1                        0x271
	#define  SWH_VLAN_Table2                        0x272
	#define  SWH_VLAN_Table3                        0x273
	#define  SWH_VLAN_Table4                        0x274
	#define  SWH_VLAN_Table5                        0x275
	#define  SWH_VLAN_Table6                        0x276
	#define  SWH_VLAN_Table7                        0x277
	#define  SWH_VLAN_Table8                        0x278
	#define  SWH_VLAN_Table9                        0x279
	#define  SWH_VLAN_Table10                       0x27a
	#define  SWH_VLAN_Table11                       0x27b
	#define  SWH_VLAN_Table12                       0x27c
	#define  SWH_VLAN_Table13                       0x27d
	#define  SWH_VLAN_Table14                       0x27e
	#define  SWH_VLAN_Table15                       0x27f

	#define  SWH_STP_CTRL                            0x292
	#define  SWH_SNOOP_CTRL1                         0x29B  
	#define  SWH_SNOOP_CTRL2                         0x29C
	#define  SWH_ADDR_TAB_CTRL_STATUS                0x2B0
	#define  SWH_ADDR_TAB1                           0x2B1
	#define  SWH_ADDR_TAB2                           0x2B2
	#define  SWH_ADDR_TAB3                           0x2B3
	#define  SWH_ADDR_TAB4                           0x2B4
	#define  SWH_ADDR_TAB5                           0x2B5

	#define  SWH_VENDOR_ID                              0X310
	#define  SWH_PRODUCT_ID                             0x311
	#define  SWH_P2_MAC_CTRL                            0x315
	#define  SWH_EEPROM_CTRL_ADDR                       0x31A
	#define  SWH_EEPROM_DATA                            0x31B
	#define  SWH_STRAP_PIN_CTRL_STATUS                  0x31C

	#define  SWH_SMI_BUS_ERROR_CHECK                    0x339
	#define  SWH_SMI_BUS_CTRL                           0x33A
	#define  SWH_PHY_CTRL                               0x33E

	//¼Ä´æÆ÷Î»¶¨Òå
	#define  DISABLE_ADDR_LEARN                         0x1000

/**--------------------------------------------------------------------------**/
/** 
  * @brief                     Description of common PHY registers
  */ 
/**--------------------------------------------------------------------------**/

/**
  * @}
  */

/** @defgroup PHY_Read_write_Timeouts 
  * @{
  */ 
#define PHY_READ_TO                     ((uint32_t)0x0004FFFF)
#define PHY_WRITE_TO                    ((uint32_t)0x0004FFFF)

/**
  * @}
  */

/** @defgroup PHY_Register_address 
  * @{
  */ 
#define PHY_BCR                          0          /*!< Transceiver Basic Control Register */
#define PHY_BSR                          1          /*!< Transceiver Basic Status Register */

#define IS_ETH_PHY_ADDRESS(ADDRESS) ((ADDRESS) <= 0x20)
#define IS_ETH_PHY_REG(REG) (((REG) == PHY_BCR) || \
                             ((REG) == PHY_BSR) || \
                             ((REG) == PHY_SR))
/**
  * @}
  */

/** @defgroup PHY_basic_Control_register 
  * @{
  */ 
#define PHY_Reset                       ((uint16_t)0x8000)      /*!< PHY Reset */
#define PHY_Loopback                    ((uint16_t)0x4000)      /*!< Select loop-back mode */
#define PHY_FULLDUPLEX_100M             ((uint16_t)0x2100)      /*!< Set the full-duplex mode at 100 Mb/s */
#define PHY_HALFDUPLEX_100M             ((uint16_t)0x2000)      /*!< Set the half-duplex mode at 100 Mb/s */
#define PHY_FULLDUPLEX_10M              ((uint16_t)0x0100)      /*!< Set the full-duplex mode at 10 Mb/s */
#define PHY_HALFDUPLEX_10M              ((uint16_t)0x0000)      /*!< Set the half-duplex mode at 10 Mb/s */
#define PHY_AutoNegotiation             ((uint16_t)0x1000)      /*!< Enable auto-negotiation function */
#define PHY_Restart_AutoNegotiation     ((uint16_t)0x0200)      /*!< Restart auto-negotiation function */
#define PHY_Powerdown                   ((uint16_t)0x0800)      /*!< Select the power down mode */
#define PHY_Isolate                     ((uint16_t)0x0400)      /*!< Isolate PHY from MII */

/**
  * @}
  */

/** @defgroup PHY_basic_status_register 
  * @{
  */ 
#define PHY_AutoNego_Complete           ((uint16_t)0x0020)      /*!< Auto-Negotiation process completed */
#define PHY_Linked_Status               ((uint16_t)0x0004)      /*!< Valid link established */
#define PHY_Jabber_detection            ((uint16_t)0x0002)      /*!< Jabber condition detected */


/*Switch Per Port Status*/
#define SWH_LINK_ON                      ((uint16_t)0x0001) 
#define SWH_FULL_DUPLEX                  ((uint16_t)0x0002)  
#define SWH_100MBPS                      ((uint16_t)0x0004) 
#endif
