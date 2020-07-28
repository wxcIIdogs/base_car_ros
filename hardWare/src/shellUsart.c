#include "define.h"
/*
*author:Wxc
*info:
*data: 2020-04-29
*/

SHELL_TypeDef shell;


void shellRevData(uint8_t *buff,int32_t len)
{
	for(int i = 0 ; i < len ; i ++)
		shellHandler(&shell,buff[i]);
}


/*************************************************
Function: 								// ????
Description: 							// ???????????
Calls: 									// ???????????
Input: 									// ??????,????????
Output: 								// ?????????
Return: 								// ????????
Others: 								// ????
*************************************************/
void initShellusart()
{
	createFifoRev(&huart1,shellRevData,UART_REV_DMA);
}

void shellWriteDebug(char data)
{
	HAL_UART_Transmit(&huart1,(uint8_t *)&data,1,0xFF);
	rosSendPushData(data);
}

