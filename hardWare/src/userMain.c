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
void initBoard()
{
//	HAL_TIM_Encoder_Start(&htim5,TIM_CHANNEL_ALL);
//	HAL_TIM_Encoder_Start(&htim8,TIM_CHANNEL_ALL);

	
	
}
/***********************************
*func:
*parm:
*return:
*info:
***********************************/
//10ms
void mainLoop()
{
	static int timeCount = 0;
	if(timeCount++ == 10)
	{
		//100ms
	}
}

