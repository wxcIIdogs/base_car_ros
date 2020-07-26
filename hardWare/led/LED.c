#include "define.h"
/*
*author:Wxc
*info:
*data: 2020-07-26
*/



static stu_ledOpt sg_stuLedOpt[10];
/***********************************
*func:
*parm:
*return:
*info:
***********************************/
void initLed(int count)
{
	for(int  i = 0 ; i < count ; i ++)
	{
		sg_stuLedOpt[i].index = i;
		sg_stuLedOpt[i].count = LED_OPT_NORMAL;
		sg_stuLedOpt[i].sleepTime = 500;
		sg_stuLedOpt[i].status = LED_OPT_KEEP;
		sg_stuLedOpt[i].runTime = 0;

	}
}
/***********************************
*func:
*parm:
*return:
*info:
***********************************/

void led_register(int index,GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,int openStatus)
{			
	sg_stuLedOpt[index].gpio = GPIOx;
	sg_stuLedOpt[index].pin = GPIO_Pin;
	sg_stuLedOpt[index].openStatus = openStatus;
}
/***********************************
*func:
*parm:
*return:
*info:
***********************************/
void led_setStatus(int index,int count,int sleep)
{
	sg_stuLedOpt[index].count = count;
	sg_stuLedOpt[index].sleepTime = sleep;
	if(sleep == 0 || count == 0)
		sg_stuLedOpt[index].status = LED_OPT_KEEP;	
	else
		sg_stuLedOpt[index].status = LED_OPT_TOGGLE;	
}
/***********************************
*func:
*parm:
*return:
*info:
***********************************/
void led_cleanStatus(int index)
{
	sg_stuLedOpt[index].count = LED_OPT_NORMAL;
	sg_stuLedOpt[index].sleepTime = 0;
	sg_stuLedOpt[index].status = LED_OPT_KEEP;
}
/***********************************
*func:
*parm:
*return:
*info:
***********************************/
//100ms
void LedLoop()
{
	static int timeCount = 0;
	timeCount++;
	for(int i = 0 ; i <10 ; i ++ )
	{
		if(sg_stuLedOpt[i].status == LED_OPT_NONE)
		{
			continue;
		}
		if(sg_stuLedOpt[i].status == LED_OPT_KEEP)
		{
			HAL_GPIO_WritePin(sg_stuLedOpt[i].gpio,sg_stuLedOpt[i].pin,(GPIO_PinState)sg_stuLedOpt[i].openStatus);
		}
		if(sg_stuLedOpt[i].status == LED_OPT_TOGGLE)
		{
			if(sg_stuLedOpt[i].count == LED_OPT_NORMAL)
			{
				if(HAL_GetTick() - sg_stuLedOpt[i].runTime >=  sg_stuLedOpt[i].sleepTime)		//1s
				{
					HAL_GPIO_TogglePin(sg_stuLedOpt[i].gpio,sg_stuLedOpt[i].pin);
					sg_stuLedOpt[i].runTime = HAL_GetTick();
				}
			}
			else if(sg_stuLedOpt[i].count --)
			{
				if(HAL_GetTick() - sg_stuLedOpt[i].runTime >=  sg_stuLedOpt[i].sleepTime)
				{
					HAL_GPIO_TogglePin(sg_stuLedOpt[i].gpio,sg_stuLedOpt[i].pin);
					sg_stuLedOpt[i].runTime = HAL_GetTick();
				}
			}
			else
			{
				sg_stuLedOpt[i].status = LED_OPT_KEEP;
			}			
		}
	}
}

