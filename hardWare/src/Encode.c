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
static stuEncodeData sg_stuEncodeData;
const int32_t DecodeMaxData = 25000;
stuEncodeData getEncodeData(void)
{
	static int32_t pro_l_encodeCount = 0;
	static int32_t pro_r_encodeCount = 0;	

	int32_t htim5Count = __HAL_TIM_GetCounter(&htim5);
	int32_t htim8Count = __HAL_TIM_GetCounter(&htim8);	
	sg_stuEncodeData.IC_R_EncodeCount = 0;
	sg_stuEncodeData.IC_L_EncodeCount = 0;
	if(__HAL_TIM_DIRECTION_STATUS(&htim5)==0)
	{
		sg_stuEncodeData.IC_R_EncodeCount = htim5Count;
		sg_stuEncodeData.R_Direct =MOTOR_CURRENT_BACK;
	}
	else
	{
		if(htim5Count!=0)
		{
			sg_stuEncodeData.IC_R_EncodeCount= (0xFFFF - htim5Count+1);				
			sg_stuEncodeData.R_Direct = MOTOR_CURRENT_FORWARD;			
		}
	}
	__HAL_TIM_SetCounter(&htim5,0);


	if(__HAL_TIM_DIRECTION_STATUS(&htim8)==0)
	{
		sg_stuEncodeData.IC_L_EncodeCount = htim8Count;
		sg_stuEncodeData.L_Direct =  MOTOR_CURRENT_FORWARD;
	}
	else
	{
		if(htim8Count!=0)
		{
			sg_stuEncodeData.IC_L_EncodeCount= (0xFFFF - htim8Count+1);				
			sg_stuEncodeData.L_Direct = MOTOR_CURRENT_BACK;			
		}
	}
	__HAL_TIM_SetCounter(&htim8,0);
	

	if(sg_stuEncodeData.IC_R_EncodeCount > DecodeMaxData)
	{
		sg_stuEncodeData.IC_R_EncodeCount  = pro_r_encodeCount;
	}
	else
	{
		pro_r_encodeCount = sg_stuEncodeData.IC_R_EncodeCount;
	}


	if(sg_stuEncodeData.IC_L_EncodeCount > DecodeMaxData)
	{
		sg_stuEncodeData.IC_L_EncodeCount  = pro_l_encodeCount;
	}
	else
	{
		pro_l_encodeCount = sg_stuEncodeData.IC_L_EncodeCount;
	}
	return sg_stuEncodeData;
}

