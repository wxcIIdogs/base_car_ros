/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
#include "define.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 1024 * 4
};
/* Definitions for myTaskShell */
osThreadId_t myTaskShellHandle;
const osThreadAttr_t myTaskShell_attributes = {
  .name = "myTaskShell",
  .priority = (osPriority_t) osPriorityNormal1,
  .stack_size = 1024 * 4
};
/* Definitions for myTimer01 */
osTimerId_t myTimer01Handle;
const osTimerAttr_t myTimer01_attributes = {
  .name = "myTimer01"
};
/* Definitions for myTimer02 */
osTimerId_t myTimer02Handle;
const osTimerAttr_t myTimer02_attributes = {
  .name = "myTimer02"
};
/* Definitions for myMutex01 */
osMutexId_t myMutex01Handle;
const osMutexAttr_t myMutex01_attributes = {
  .name = "myMutex01"
};
/* Definitions for myRecursiveMutex01 */
osMutexId_t myRecursiveMutex01Handle;
const osMutexAttr_t myRecursiveMutex01_attributes = {
  .name = "myRecursiveMutex01",
  .attr_bits = osMutexRecursive,
};
/* Definitions for myBinarySemKey */
osSemaphoreId_t myBinarySemKeyHandle;
const osSemaphoreAttr_t myBinarySemKey_attributes = {
  .name = "myBinarySemKey"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartTaskShell(void *argument);
void Callback01(void *argument);
void Callback02(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* creation of myMutex01 */
  myMutex01Handle = osMutexNew(&myMutex01_attributes);

  /* Create the recursive mutex(es) */
  /* creation of myRecursiveMutex01 */
  myRecursiveMutex01Handle = osMutexNew(&myRecursiveMutex01_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of myBinarySemKey */
  myBinarySemKeyHandle = osSemaphoreNew(1, 1, &myBinarySemKey_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* creation of myTimer01 */
  myTimer01Handle = osTimerNew(Callback01, osTimerPeriodic, NULL, &myTimer01_attributes);

  /* creation of myTimer02 */
  myTimer02Handle = osTimerNew(Callback02, osTimerPeriodic, NULL, &myTimer02_attributes);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of myTaskShell */
  myTaskShellHandle = osThreadNew(StartTaskShell, NULL, &myTaskShell_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  initEspWifi();
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  initBoard();
  initPidTask();

  //open timer
  osTimerStart(myTimer01Handle,100);
  osTimerStart(myTimer02Handle,100);
  initLed(2);
  led_register(0,LED_R_GPIO_Port,LED_R_Pin,GPIO_PIN_SET);
  led_register(1,LED_G_GPIO_Port,LED_G_Pin,GPIO_PIN_SET);  
  led_setStatus(0,1,1000);
  led_setStatus(1,LED_OPT_NORMAL,2000);
  for(;;)
  {
	pidTask();
	mainLoop();
    osDelay(10);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartTaskShell */
/**
* @brief Function implementing the myTaskShell thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskShell */
void StartTaskShell(void *argument)
{
  /* USER CODE BEGIN StartTaskShell */
  /* Infinite loop */
  initShellusart();
  //shell.read = shellRead;
  shell.write = shellWriteDebug;
  shellInit(&shell);
  initRosNode();
  
  for(;;)
  {
	rosSpinOnce();
    osDelay(100);
  }
  /* USER CODE END StartTaskShell */
}

/* Callback01 function */
void Callback01(void *argument)
{
  /* USER CODE BEGIN Callback01 */
  LedLoop();
  /* USER CODE END Callback01 */
}

/* Callback02 function */
void Callback02(void *argument)
{
  /* USER CODE BEGIN Callback02 */
  char buff[100] = {"hello ros node"};
  sprintf(buff,"%s:%d",buff,HAL_GetTick());
  rosSendPushData(buff);
  /* USER CODE END Callback02 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
