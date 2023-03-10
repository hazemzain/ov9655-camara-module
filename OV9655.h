/*
 * OV9655.h
 *
 *  Created on: Feb 28, 2023
 *      Author: Eng.Hazem
 */

#ifndef INC_OV9655_H_
#define INC_OV9655_H_
#include "stm32f4xx_hal.h"

#include "main.h"



/*************************MACROS FOR USER CONFIGRATION***************************/
/**************COOSE FROM ----->OPEN_DEBUG
 * ***********************----->CLOSE_DEBUG

 *******************************************************************************/
#define OPEN_DEBUG 1
#define CLOSE_DEBUG 0

#define DEBUG_MODE CLOSE_DEBUG
/*******************macros define *****************************************/
#define OV9655_ADDRESS_WRITE   0x60
#define OV9655_ADDRESS_READ   0x61
/****************prototype function***************************************/
void OV9655_Reg_Write(uint8_t reg_addr, uint8_t data);
void OV9655_Init(void);

void OV9655_CaptureSnapshot(uint32_t *frameBuffer, int length);


#endif /* INC_OV9655_H_ */
