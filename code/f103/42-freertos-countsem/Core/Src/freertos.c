/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "gpio.h"
#include <stdio.h>

#pragma diag_suppress 870
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
osThreadId defaultTaskHandle;
osThreadId PUTHandle;
osThreadId GETHandle;
osMessageQId QueueLED1Handle;
osMessageQId QueueLED2Handle;
osMutexId myMutex01Handle;
osSemaphoreId BinarySem1Handle;
osSemaphoreId BinarySem2Handle;
osSemaphoreId BinarySem3Handle;
osSemaphoreId CountingSem1Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefalutTask(void const * argument);
void PutTask(void const * argument);
void GetTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* definition and creation of myMutex01 */
  osMutexDef(myMutex01);
  myMutex01Handle = osMutexCreate(osMutex(myMutex01));

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of BinarySem1 */
  osSemaphoreDef(BinarySem1);
  BinarySem1Handle = osSemaphoreCreate(osSemaphore(BinarySem1), 1);

  /* definition and creation of BinarySem2 */
  osSemaphoreDef(BinarySem2);
  BinarySem2Handle = osSemaphoreCreate(osSemaphore(BinarySem2), 1);

  /* definition and creation of BinarySem3 */
  osSemaphoreDef(BinarySem3);
  BinarySem3Handle = osSemaphoreCreate(osSemaphore(BinarySem3), 1);

  /* definition and creation of CountingSem1 */
  osSemaphoreDef(CountingSem1);
  CountingSem1Handle = osSemaphoreCreate(osSemaphore(CountingSem1), 10);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
	// 三把锁，关闭锁2， 锁3， 只剩下锁1是开的
	osSemaphoreWait(BinarySem2Handle,osWaitForever); // 让二值信号量的值为0 
	osSemaphoreWait(BinarySem3Handle,osWaitForever); // 让二值信号量的值为0 
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of QueueLED1 */
  osMessageQDef(QueueLED1, 16, uint16_t);
  QueueLED1Handle = osMessageCreate(osMessageQ(QueueLED1), NULL);

  /* definition and creation of QueueLED2 */
  osMessageQDef(QueueLED2, 16, uint16_t);
  QueueLED2Handle = osMessageCreate(osMessageQ(QueueLED2), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefalutTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of PUT */
  osThreadDef(PUT, PutTask, osPriorityIdle, 0, 128);
  PUTHandle = osThreadCreate(osThread(PUT), NULL);

  /* definition and creation of GET */
  osThreadDef(GET, GetTask, osPriorityIdle, 0, 128);
  GETHandle = osThreadCreate(osThread(GET), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefalutTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefalutTask */
void StartDefalutTask(void const * argument)
{
  /* USER CODE BEGIN StartDefalutTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(100);
  }
  /* USER CODE END StartDefalutTask */
}

/* USER CODE BEGIN Header_PutTask */
/**
* @brief Function implementing the PUT thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_PutTask */
void PutTask(void const * argument)
{
  /* USER CODE BEGIN PutTask */
	printf("车位数量为:%d\n",osSemaphoreGetCount(CountingSem1Handle));
  /* Infinite loop */
	osEvent ret; 
  for(;;)
  {
		if(Key_Value == KEY_UP) // 车辆出停车场, 车位增加 
		{
				Key_Value = 0 ; 
				ret.status =  osSemaphoreRelease (CountingSem1Handle) ; 
				if(ret.status == osOK ) 
				{
						printf("车位数量为:%d\n",osSemaphoreGetCount(CountingSem1Handle));
				}
				else 
				{
						printf("车位数量为:%d\n",osSemaphoreGetCount(CountingSem1Handle));
				}
		}
    osDelay(100);
  }
  /* USER CODE END PutTask */
}

/* USER CODE BEGIN Header_GetTask */
/**
* @brief Function implementing the GET thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_GetTask */
void GetTask(void const * argument)
{
  /* USER CODE BEGIN GetTask */
  /* Infinite loop */
	uint32_t ret;
	
  for(;;)
  {
			if(Key_Value == KEY_DOWN) // 车辆进入停车场, 车位减少 
			{
					Key_Value = 0 ; 
					ret =  osSemaphoreWait (CountingSem1Handle,osWaitForever) ; 
					if(ret == osOK ) 
					{
							printf("车位数量为:%d\n",osSemaphoreGetCount(CountingSem1Handle));
					}
					else 
					{
							printf("车位数量为:%d\n",osSemaphoreGetCount(CountingSem1Handle));
					}
			}
			osDelay(1);
  }
  /* USER CODE END GetTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

