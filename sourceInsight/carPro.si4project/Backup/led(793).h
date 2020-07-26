#ifndef __LED_H_
#define __LED_H_

#include "define.h"
/********************begin define  *****************************************/
#define LED_OPT_NONE   	  0
#define LED_OPT_KEEP   	  1
#define LED_OPT_TOGGLE    2
#define LED_OPT_NORMAL	  0xFFFFFFFF
/**********************end define *****************************************/



/********************begin  type *****************************************/

typedef struct 
{
	int index;
	int count;
	int sleepTime;
	int status;
	int openStatus;
	int runTime;
	uint16_t pin;
	GPIO_TypeDef* gpio;	
}stu_ledOpt;

/**********************end  type *****************************************/



/********************begin parm *****************************************/

/**********************end  parm *****************************************/


/********************begin func *****************************************/
extern void LedLoop(void);
extern void led_cleanStatus(int index);
extern void led_setStatus(int index,int count,int sleep);
extern void initLed(int count);
extern void led_register(int index,GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,int openStatus);

/**********************end func *****************************************/

#endif
