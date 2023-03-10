/*
 * OV9655.c
 *
 *  Created on: Feb 28, 2023
 *      Author: Eng.Hazem
 */

#include "OV9655.h"
extern DCMI_HandleTypeDef hdcmi;
extern DMA_HandleTypeDef hdma_dcmi;

extern I2C_HandleTypeDef hi2c1;

extern UART_HandleTypeDef huart3;


/************************************************************************************************/
/***********************many array of character use for debugging *******************************/
/************************************************************************************************/
#if DEBUG_MODE==OPEN_DEBUG
uint8_t array_I2C_Ok[]="every thing is very good\n\r";
uint8_t array_I2C_Error[]="HAL_ERROR Occur in i2c\n\r";
uint8_t array_I2C_Busy[]="HAL_BUSY Occur in i2c\n\r";
uint8_t array_I2C_Timeout[]="HAL_TIMEOUT Occur in i2c\n\r";
uint8_t array_READY[]="the device iS Ready\n\r";
uint8_t array_NOT_READY[]="the device iS not  Ready\n\r";
uint8_t array_DCMI_Ok[]="the camera take snapshot \n\r";
uint8_t array_DCMI_Error[]="DCMI_ERROR Occur in snapshot function\n\r";
uint8_t array_DCMI_Busy[]="DCMI_BUSY Occur in snapshot function\n\r";
uint8_t array_DCMI_Timeout[]="DCMI_TIMEOUT Occur in snapshot function\n\r";
#endif

/*****************************************************************************************************/
/*************array of configration from application note st******************************************/
/****************************************************************************************************/
const unsigned char OV9655_YUV_QVGA [ ][2]=
{ { 0x12, 0x80 },{ 0x00, 0x00 },{ 0x01, 0x80 },{ 0x02, 0x80 },{ 0x03, 0x02
},{ 0x04, 0x03 },{ 0x0e, 0x61 }, { 0x0f, 0x42 },{ 0x11, 0x01 },{ 0x12, 0x62
},{ 0x13, 0xe7 },{ 0x14, 0x3a },{ 0x16, 0x24 },{ 0x17, 0x18 }, { 0x18, 0x04
},{ 0x19, 0x01 },{ 0x1a, 0x81 } ,{ 0x1e, 0x04 },{ 0x24, 0x3c },{ 0x25, 0x36
},{ 0x26, 0x72 }, { 0x27, 0x08 },{ 0x28, 0x08 },{ 0x29, 0x15 },{ 0x2a, 0x00
},{ 0x2b, 0x00 },{ 0x2c, 0x08 },{ 0x32, 0x24 }, { 0x33, 0x00 },{ 0x34, 0x3f
},{ 0x35, 0x00 },{ 0x36, 0x3a },{ 0x38, 0x72 },{ 0x39, 0x57 } ,{ 0x3a, 0x0c
},{ 0x3b, 0x04 },{ 0x3d, 0x99 },{ 0x3e, 0x0e },{ 0x3f, 0xc1 },{ 0x40, 0xc0}
,{ 0x41, 0x01 },{ 0x42, 0xc0 },{ 0x43, 0x0a },{ 0x44, 0xf0 },{ 0x45, 0x46
},{ 0x46, 0x62} ,{ 0x47, 0x2a },{ 0x48, 0x3c },{ 0x4a, 0xfc }, { 0x4b, 0xfc
},{ 0x4c, 0x7f },{ 0x4d, 0x7f}, { 0x4e, 0x7f },{ 0x52, 0x28 },{ 0x53, 0x88
},{ 0x54, 0xb0 }, { 0x4f, 0x98 },{ 0x50, 0x98} ,{ 0x51, 0x00 },{ 0x58, 0x1a
},{ 0x59, 0x85 },{ 0x5a, 0xa9 },{ 0x5b, 0x64 } ,{ 0x5c, 0x84 },{ 0x5d, 0x53
},{ 0x5e, 0x0e },{ 0x5f, 0xf0 },{ 0x60, 0xf0 },{ 0x61, 0xf0 } ,{ 0x62, 0x00
}, { 0x63, 0x00 },{ 0x64, 0x02 },{ 0x65, 0x20 },{ 0x66, 0x00 },{ 0x69, 0x0a
},{ 0x6b, 0x5a },{ 0x6c, 0x04 }, { 0x6d, 0x55 },{ 0x6e, 0x00 },{ 0x6f, 0x9d
},{ 0x70, 0x21 },{ 0x71, 0x78 },{ 0x72, 0x11 },{ 0x73, 0x01 }, { 0x74, 0x10
},{ 0x75, 0x10 } ,{ 0x76, 0x01 },{ 0x77, 0x02 },{ 0x7a, 0x12 },{ 0x7b, 0x08
},{ 0x7c, 0x15 }, { 0x7d, 0x24 },{ 0x7e, 0x45 },{ 0x7f, 0x55 },{ 0x80, 0x6a
},{ 0x81, 0x78 },{ 0x82, 0x87 },{ 0x83, 0x96 }, { 0x84, 0xa3 },{ 0x85, 0xb4
},{ 0x86, 0xc3 },{ 0x87, 0xd6 },{ 0x88, 0xe6 } ,{ 0x89, 0xf2 },{ 0x8a, 0x24
}, { 0x8c, 0x80 },{ 0x90, 0x7d },{ 0x91, 0x7b },{ 0x9d, 0x02 } ,{ 0x9e, 0x02
},{ 0x9f, 0x7a },{ 0xa0, 0x79 }, { 0xa1, 0x40 },{ 0xa4, 0x50 },{ 0xa5, 0x68
},{ 0xa6, 0x4a },{ 0xa8, 0xc1 },{ 0xa9, 0xef },{ 0xaa, 0x92 }, { 0xab, 0x04
} ,{ 0xac, 0x80 },{ 0xad, 0x80 },{ 0xae, 0x80 },{ 0xaf, 0x80 },{ 0xb2, 0xf2
},{ 0xb3, 0x20 } ,{ 0xb4, 0x20 },{ 0xb5, 0x00 },{ 0xb6, 0xaf },{ 0xbb, 0xae
},{ 0xbc, 0x7f },{ 0xbd, 0x7f } ,{ 0xbe, 0x7f },{ 0xbf, 0x7f },{ 0xc0, 0xaa
},{ 0xc1, 0xc0 },{ 0xc2, 0x01 },{ 0xc3, 0x4e } ,{ 0xc6, 0x05 },{ 0xc7, 0x81
},{ 0xc9, 0xe0 },{ 0xca, 0xe8 },{ 0xcb, 0xf0 },{ 0xcc, 0xd8 } ,{ 0xcd, 0x93
}, { 0xcd, 0x93 },{ 0xFF, 0xFF } };
/*****************************************************************************************************/
/*************this function initialize all register and setting for camara module OV9655**************/
/*****************************************************************************************************/
void OV9655_Init(void)
{

	HAL_StatusTypeDef Ret_Check=HAL_OK;
	uint32_t index;
	/************************1-hardware reset************************/
	HAL_GPIO_WritePin(GPIOG, CAMERA_RESET_Pin, RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOG, CAMERA_RESET_Pin, SET);
	HAL_Delay(100);
	Ret_Check=HAL_I2C_IsDeviceReady(&hi2c1, OV9655_ADDRESS_WRITE, 2,100);
#if DEBUG_MODE==OPEN_DEBUG
	if(Ret_Check==HAL_OK)
	{
		HAL_UART_Transmit(&huart3, array_READY, sizeof(array_READY), 100);
	}else
	{
		HAL_UART_Transmit(&huart3, array_NOT_READY, sizeof(array_NOT_READY), 100);
	}
#endif
	/***** Resets all registers to default values********************/
	OV9655_Reg_Write(0x12,0x80);

	/***************Configure all register in OV9655****************/

	 for(index=0; index<(sizeof(OV9655_YUV_QVGA)/2); index++)
	 {
		 OV9655_Reg_Write(OV9655_YUV_QVGA[index][0], OV9655_YUV_QVGA[index][1]);
		 HAL_Delay(10);
	 }
}






/****************************************************************************************************/
/*******************this function write in REG in OV9655 using i2C HAL FUNCTION*********************/
/****************************************************************************************************/

void OV9655_Reg_Write(uint8_t reg_addr, uint8_t data)
{
	uint8_t buff[2]={0};
	HAL_StatusTypeDef Ret_check=HAL_OK;
	buff[0]=reg_addr;
	buff[1]=data;


	Ret_check=HAL_I2C_Master_Transmit(&hi2c1, OV9655_ADDRESS_WRITE, buff, 2, 100);

#if DEBUG_MODE==OPEN_DEBUG
	if(Ret_check==HAL_OK)
	{
		HAL_UART_Transmit(&huart3, array_I2C_Ok, sizeof(array_I2C_Ok), 100);
	}else if(Ret_check==HAL_ERROR)
	{
		HAL_UART_Transmit(&huart3, array_I2C_Error, sizeof(array_I2C_Error), 100);
	}else if(Ret_check==HAL_BUSY)
	{
		HAL_UART_Transmit(&huart3, array_I2C_Busy, sizeof(array_I2C_Busy), 100);
	}
	else if(Ret_check==HAL_TIMEOUT)
		{
			HAL_UART_Transmit(&huart3, array_I2C_Timeout, sizeof(array_I2C_Timeout), 100);
		}
#endif
}





/****************************************************************************************************/
/**********************this function to take the snap shot *****************************************/
/***************************************************************************************************/
void OV9655_CaptureSnapshot(uint32_t *frameBuffer, int length)
{
	HAL_StatusTypeDef Ret_check=HAL_OK;
	Ret_check=HAL_DCMI_Start_DMA(&hdcmi, DCMI_MODE_SNAPSHOT , (uint32_t )frameBuffer, length);
#if DEBUG_MODE==OPEN_DEBUG
	if(Ret_check==HAL_OK)
	{
		HAL_UART_Transmit(&huart3, array_DCMI_Ok, sizeof(array_DCMI_Ok), 100);
	}else if(Ret_check==HAL_ERROR)
	{
		HAL_UART_Transmit(&huart3, array_DCMI_Error, sizeof(array_DCMI_Error), 100);
	}else if(Ret_check==HAL_BUSY)
	{
		HAL_UART_Transmit(&huart3, array_DCMI_Busy, sizeof(array_DCMI_Busy), 100);
	}
	else if(Ret_check==HAL_TIMEOUT)
		{
			HAL_UART_Transmit(&huart3, array_DCMI_Timeout, sizeof(array_DCMI_Timeout), 100);
		}
#endif
	HAL_Delay(2000);
}
