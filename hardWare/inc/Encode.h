#ifndef __ENCODE__H
#define __ENCODE__H
#include "define.h"


/********************begin define  *****************************************/
#define MOTOR_CURRENT_FORWARD		0x01
#define MOTOR_CURRENT_BACK			0x02

/**********************end define *****************************************/

/********************begin  type *****************************************/
typedef struct encodeData
{
	int32_t IC_L_EncodeCount;
	int32_t IC_R_EncodeCount;	
	int8_t 	L_Direct;
	int8_t 	R_Direct;	
}stuEncodeData;
/**********************end  type *****************************************/

/********************begin parm *****************************************/

/**********************end  parm *****************************************/

/********************begin func *****************************************/

extern stuEncodeData getEncodeData(void);


/**********************end func *****************************************/


#endif
