#include "define.h"
/*
*author:Wxc
*info:
*data: 2019-05-27
*/

static stuUartRevFifo sg_uartRevFifoBuff[UARTINFO_COUNT] = {0};




/***********************************
*func:
*parm:
*return:
*info:
***********************************/
int32_t getFifoIndex(void)
{
	for(int32_t i = 0 ; i < UARTINFO_COUNT ; i ++)
	{
		if(sg_uartRevFifoBuff[i].revCmd == UART_REV_NULL)
			return i;
	}
	return -1;
}




/***********************************
*func:
*parm:
*return:
*info:
***********************************/
int32_t createFifoRev(UART_HandleTypeDef *uart , revFunc revDataFunc,uint32_t revMode)
{	
	int32_t fifoIndex = getFifoIndex();
	if(fifoIndex <0 || fifoIndex >= UARTINFO_COUNT)
		return -1;

	sg_uartRevFifoBuff[fifoIndex].uart = uart;
	sg_uartRevFifoBuff[fifoIndex].revFunc = revDataFunc;
	sg_uartRevFifoBuff[fifoIndex].revCmd = revMode;	
	switch(revMode)
	{
		case UART_REV_DMA:
			setUartDmaIdleRev(sg_uartRevFifoBuff + fifoIndex);
			break;
		case UART_REV_INT:
			setUartIntRev(sg_uartRevFifoBuff + fifoIndex);	
			break;
		case UART_REV_POLL:
			break;			
	}
	return fifoIndex;
}


/***********************************
*func:
*parm:
*return:
*info:
***********************************/
void delFifoRev(int32_t index)
{
	sg_uartRevFifoBuff[index].revCmd = UART_REV_NULL;
}

/***********************************
*func:
*parm:
*return:
*info:
***********************************/
void sendBuffFifo(int32_t index , uint8_t *buff,int32_t len,int32_t sendMode)
{
	if(index < 0 || index >= UARTINFO_COUNT)
	{
		//log: index out
		return;
	}
	memcpy(sg_uartRevFifoBuff[index].sendBuff,buff,len);
	sg_uartRevFifoBuff[index].sendLen = len;
	if(sendMode == UART_SEND_IO)
	{
		HAL_UART_Transmit(sg_uartRevFifoBuff[index].uart,sg_uartRevFifoBuff[index].sendBuff,sg_uartRevFifoBuff[index].sendLen,0x05);
	}
	else if(sendMode == UART_SEND_ANSY)
	{
		HAL_UART_Transmit_IT(sg_uartRevFifoBuff[index].uart,sg_uartRevFifoBuff[index].sendBuff,sg_uartRevFifoBuff[index].sendLen);
	}
}

/***********************************
*func:
*parm:
*return:
*info:
***********************************/
void UsartReceive_IDLE(UART_HandleTypeDef *huart)
{
	stuUartRevFifo *revinfo;
	for(int32_t i = 0 ; i < UARTINFO_COUNT ; i ++)
	{
		if(huart == sg_uartRevFifoBuff[i].uart && sg_uartRevFifoBuff[i].revCmd == UART_REV_DMA)
		{
			// is you 
			 revinfo = &(sg_uartRevFifoBuff[i]);
		}
	}	
	uint32_t temp = 0;
	if((__HAL_UART_GET_FLAG(revinfo->uart,UART_FLAG_IDLE) != RESET))
	{ 
		__HAL_UART_CLEAR_IDLEFLAG(revinfo->uart);
		HAL_UART_DMAStop(revinfo->uart);
		temp = revinfo->uart->hdmarx->Instance->NDTR;
		//rev data count
		if(revinfo->revFunc != NULL)
		{
			revinfo->revFunc(revinfo->revBuff,UARTINFO_SIZE - temp);
		}
		memset(revinfo->revBuff,0,UARTINFO_SIZE);
		HAL_UART_Receive_DMA(revinfo->uart,revinfo->revBuff,UARTINFO_SIZE);
	}
}


/***********************************
*func:
*parm:
*return:
*info:
***********************************/
void setUartIntRev(stuUartRevFifo *revinfo)
{
	HAL_UART_Receive_IT(revinfo->uart,revinfo->revBuff,1);
	__HAL_UART_ENABLE_IT(revinfo->uart, UART_IT_RXNE);
}

/***********************************
*func:
*parm:
*return:
*info:
***********************************/
void setUartDmaIdleRev(stuUartRevFifo *revinfo)
{
	HAL_UART_Receive_DMA(revinfo->uart,revinfo->revBuff, UARTINFO_SIZE);
	__HAL_UART_ENABLE_IT(revinfo->uart, UART_IT_IDLE);
}

/***********************************
*func:
*parm:
*return:
*info:
***********************************/
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//	for(int32_t i = 0 ; i < UARTINFO_COUNT ; i ++)
//	{
//		if(huart == sg_uartRevFifoBuff[i].uart && sg_uartRevFifoBuff[i].revCmd == UART_REV_INT)
//		{
//			// is you 
//			sg_uartRevFifoBuff[i].revFunc(sg_uartRevFifoBuff[i].revBuff,1);
//			HAL_UART_Receive_IT(sg_uartRevFifoBuff[i].uart,sg_uartRevFifoBuff[i].revBuff,1);
//		}		
//	}

//}
/***********************************
*func:
*parm:
*return:
*info:
***********************************/
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	for(int32_t i = 0 ; i < UARTINFO_COUNT ; i ++)
	{
		if(huart == sg_uartRevFifoBuff[i].uart && sg_uartRevFifoBuff[i].revCmd == UART_REV_INT)
		{
			// is you  had error
			//sg_uartRevFifoBuff[i].revFunc(sg_uartRevFifoBuff[i].revBuff[0],1);
		}
		//HAL_UART_Receive_IT(sg_uartRevFifoBuff[i].uart,sg_uartRevFifoBuff[i].revBuff,1);
	}

}












