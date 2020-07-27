#include "define.h"
/*
*author:Wxc
*info:
*data: 2020-07-27
*/


/***********************************
*func:
*parm:
*return:
*info:
***********************************/

static stu_motorOpt sg_motorOpt[4];
void initMotorPwm()
{
	int index = 0;
	sg_motorOpt[index].tim = &htim5;
	sg_motorOpt[index].ch1 = TIM_CHANNEL_1;
	sg_motorOpt[index++].ch2 = TIM_CHANNEL_2;	

	sg_motorOpt[index].tim = &htim5;
	sg_motorOpt[index].ch1 = TIM_CHANNEL_3;
	sg_motorOpt[index++].ch2 = TIM_CHANNEL_4;	

	sg_motorOpt[index].tim = &htim9;
	sg_motorOpt[index].ch1 = TIM_CHANNEL_1;
	sg_motorOpt[index++].ch2 = TIM_CHANNEL_2;	

	sg_motorOpt[index].tim = &htim12;
	sg_motorOpt[index].ch1 = TIM_CHANNEL_1;
	sg_motorOpt[index++].ch2 = TIM_CHANNEL_2;	
	
	for(int i = 0 ; i < 4 ; i ++)
	{
		HAL_TIM_PWM_Start(sg_motorOpt[i].tim, sg_motorOpt[i].ch1);
		HAL_TIM_PWM_Start(sg_motorOpt[i].tim, sg_motorOpt[i].ch2);
	}


}


void setPwmSetValue(int index,int16_t value)
{
	int gndIndex;
	int valueIndex;
	if(value > 0)
	{
		gndIndex = sg_motorOpt[index].ch2;
		valueIndex = sg_motorOpt[index].ch1;
	}
	else if(value <= 0)
	{
		gndIndex = sg_motorOpt[index].ch1;
		valueIndex = sg_motorOpt[index].ch2;
		value = value * -1;
	}
    TIM_OC_InitTypeDef sConfigOC;
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = (uint32_t)value;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(sg_motorOpt[index].tim, &sConfigOC, valueIndex);
    HAL_TIM_PWM_Start(sg_motorOpt[index].tim, valueIndex);  

    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(sg_motorOpt[index].tim, &sConfigOC, gndIndex);
    HAL_TIM_PWM_Start(sg_motorOpt[index].tim, gndIndex);  	
}
SHELL_EXPORT_CMD(setMotor,setPwmSetValue,set motor value);


void setPwmMotorStop()
{
	for(int i = 0 ; i < 4 ; i ++)
	{
		HAL_TIM_PWM_Stop(sg_motorOpt[i].tim, sg_motorOpt[i].ch1);
		HAL_TIM_PWM_Stop(sg_motorOpt[i].tim, sg_motorOpt[i].ch2);
	}

}
SHELL_EXPORT_CMD(stopMotor,setPwmMotorStop,set motor stop);


