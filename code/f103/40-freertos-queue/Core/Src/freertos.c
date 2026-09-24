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
osThreadId LED1Handle;
osThreadId LED2Handle;
osMessageQId QueueLED1Handle;
osMessageQId QueueLED2Handle;
osMutexId myMutex01Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void TaskLED1(void const * argument);
void TaskLED2(void const * argument);

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

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
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
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of LED1 */
  osThreadDef(LED1, TaskLED1, osPriorityNormal, 0, 128);
  LED1Handle = osThreadCreate(osThread(LED1), NULL);

  /* definition and creation of LED2 */
  osThreadDef(LED2, TaskLED2, osPriorityNormal, 0, 128);
  LED2Handle = osThreadCreate(osThread(LED2), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
	osEvent ret;
  /* Infinite loop */
  for(;;)
  {
				if(Key_Value == KEY_UP) 
				{
						Key_Value = 0 ; 
					
						ret.status =  osMessagePut(QueueLED1Handle, 'A', portMAX_DELAY );
						if(ret.status != osOK)
						{
								printf("send failed!\n");
						}

				}
				else if(Key_Value == KEY_DOWN)
				{
						Key_Value = 0 ; 
						ret.status =  osMessagePut(QueueLED2Handle, 'B', portMAX_DELAY );
						if(ret.status != osOK)
						{
								printf("send failed!\n");
						}
				}
				osDelay(100);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_TaskLED1 */
/**
* @brief Function implementing the LED1 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TaskLED1 */
void TaskLED1(void const * argument)
{
  /* USER CODE BEGIN TaskLED1 */
	
	osMutexWait (myMutex01Handle, portMAX_DELAY );
	printf("LED1 Running\n");
	osMutexRelease (myMutex01Handle);
	osEvent ret ; 
  /* Infinite loop */
	
  for(;;)
  {
		ret =  osMessageGet (QueueLED1Handle, portMAX_DELAY) ; 
		if(ret.status == osEventMessage )
		{
				printf("LED1Task recv data:%c",ret.value.v);
		}
		else 
		{
				printf("error:%#x\n",ret.status);
		}
		HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
    osDelay(200);
  }
  /* USER CODE END TaskLED1 */
}

/* USER CODE BEGIN Header_TaskLED2 */
/**
* @brief Function implementing the LED2 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_TaskLED2 */
void TaskLED2(void const * argument)
{
  /* USER CODE BEGIN TaskLED2 */
	
	osMutexWait (myMutex01Handle, portMAX_DELAY );
	printf("LED2 Running\n");
	osMutexRelease (myMutex01Handle);
  /* Infinite loop */
	osEvent ret ; 
  for(;;)
  {
		// osWaitForever 一直等待 
		ret =  osMessageGet (QueueLED2Handle, portMAX_DELAY) ; 
		if(ret.status == osEventMessage )
		{
				printf("LED2Task recv data:%c",ret.value.v);
		}
		else 
		{
				printf("error:%#x\n",ret.status);
		}
		HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);
    osDelay(1000);
  }
  /* USER CODE END TaskLED2 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

