#ifndef __USERMAIN_H_
#define __USERMAIN_H_


/********************begin define  *****************************************/
//#define LED_R_Pin GPIO_PIN_2
//#define LED_R_GPIO_Port GPIOD

#define LED_RED_ON()		HAL_GPIO_WritePin(LED_R_GPIO_Port,LED_R_Pin,GPIO_PIN_SET)	
#define LED_RED_OFF()		HAL_GPIO_WritePin(LED_R_GPIO_Port,LED_R_Pin,GPIO_PIN_RESET)
#define LED_RED_TOGGLE()	HAL_GPIO_TogglePin(LED_R_GPIO_Port,LED_R_Pin)


#define LED_GRE_ON()		HAL_GPIO_WritePin(LED_G_GPIO_Port,LED_G_Pin,GPIO_PIN_SET)	
#define LED_GRE_OFF()		HAL_GPIO_WritePin(LED_G_GPIO_Port,LED_G_Pin,GPIO_PIN_RESET)
#define LED_GRE_TOGGLE()	HAL_GPIO_TogglePin(LED_G_GPIO_Port,LED_G_Pin)

/**********************end define *****************************************/



/********************begin  type *****************************************/


/**********************end  type *****************************************/



/********************begin parm *****************************************/




/**********************end  parm *****************************************/






/********************begin func *****************************************/
extern void initBoard(void);
extern void mainLoop(void);

/**********************end func *****************************************/

#endif
