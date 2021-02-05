/********************************************************************************************************
**                                 Copyright (c)   2017          CASIC
**                                                 All Rights Reserved
**
**                                 Email:ustbyf@126.com   QQ:316969230
**-------------------------------------------------------------------------------------------------------
**  MCU        : STM32F103C8T6 (STMicroelectronics)
**  Compiler   : uVision V5.24.2.0
**  Module Name: CRC16.h
**  Module Date: 2017-07-22
**  Module Auth: YunFeng
**  Description:
**  Version    : V1.0
**  Notes      :
**-------------------------------------------------------------------------------------------------------
**  Version    :
**  Modified By:
**  Date       :
**  Content    :
**  Notes      :
********************************************************************************************************/

#ifndef __CRC16_H__
#define __CRC16_H__

/*-----------------------------------------  I N C L U D E S  -----------------------------------------*/
#include <stdint.h>
/*---------------------------------------  D E F I N I T I O N  ---------------------------------------*/

/*-------------------------------------------  M A C R O S  -------------------------------------------*/
#define CRC16_POLYNOMIAL                       (0x1021)
#define CRC16_INITIAL_REMAINDER                (0xFFFF)
#define CRC16_FINAL_XOR_VALUE                  (0x0000)

/*--------------------------------------  D E C L A R A T I O N  --------------------------------------*/
/* Internal Variable */

/* External Variable */

/* Internal Function */

/* External Function */
extern uint16_t CRC16(uint8_t* pData, uint32_t length);

#endif

//===========================================  End Of File  ===========================================//
