#ifndef __MOTOR_H_
#define __MOTOR_H_

#include "define.h"
/********************begin define  *****************************************/


/**********************end define *****************************************/



/********************begin  type *****************************************/
typedef struct
{
	TIM_HandleTypeDef* tim;
	int ch1;
	int ch2;
}stu_motorOpt;


/**********************end  type *****************************************/



/********************begin parm *****************************************/

/**********************end  parm *****************************************/


/********************begin func *****************************************/
extern void setPwmMotorStop(void);
extern void initMotorPwm(void);
extern void setPwmSetValue(int index,int16_t value);

/**********************end func *****************************************/

#endif
