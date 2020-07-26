
#include "define.h"
/*
*author:Wxc
*info:
*data: 2020-05-07
*/


/***********************************
*func:
*parm:
*return:
*info:
***********************************/
void WifiRevData(uint8_t *buff,int32_t len)
{
	//printf("%s",buff);
	for(int i = 0 ; i < len ; i ++)
		Wifi_RxCallBack(buff[i]);
	//shellHandler(&shell,buff[i]);
}
/***********************************
*func:
*parm:
*return:
*info:
***********************************/
void initEspWifi()
{
	Wifi_Init();
	createFifoRev(&huart3,WifiRevData,UART_REV_DMA);
}


