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
osThreadId BEEPHandle;
osThreadId LED1Handle;
osThreadId LED2Handle;
osMessageQId QueueLED1Handle;
osMessageQId QueueLED2Handle;
osMutexId myMutex01Handle;
osSemaphoreId BinarySem1Handle;
osSemaphoreId BinarySem2Handle;
osSemaphoreId BinarySem3Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void TaskBEEP(void const * argument);
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
  /* definition and creation of BEEP */
  osThreadDef(BEEP, TaskBEEP, osPriorityNormal, 0, 128);
  BEEPHandle = osThreadCreate(osThread(BEEP), NULL);

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

/* USER CODE BEGIN Header_TaskBEEP */
/**
  * @brief  Function implementing the BEEP thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_TaskBEEP */
void TaskBEEP(void const * argument)
{
  /* USER CODE BEGIN TaskBEEP */
	osMutexWait (myMutex01Handle, portMAX_DELAY );
	printf("BEEP Running\n");
	osMutexRelease (myMutex01Handle);
  /* Infinite loop */
  for(;;)
  {
		osSemaphoreWait (BinarySem3Handle, osWaitForever); // 得不到会一直等待
		BEEP_Control(ON);
		printf("BEEP ON\n");
		osDelay(200);
		BEEP_Control(OFF);
		printf("BEEP OFF\n");
		osDelay(800);
		osSemaphoreRelease (BinarySem1Handle);
    osDelay(100);
  }
  /* USER CODE END TaskBEEP */
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
  /* Infinite loop */
	
  for(;;)
  {
		osSemaphoreWait (BinarySem1Handle, osWaitForever); // 得不到会一直等待
		LED_Control(LED1,ON);
		printf("LED1 ON\n");
		osDelay(1000);
		LED_Control(LED1,OFF);
		printf("LED1 OFF\n");
		osSemaphoreRelease (BinarySem2Handle);
		osDelay(100);
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
  for(;;)
  {
		// osWaitForever 一直等待 
		osSemaphoreWait (BinarySem2Handle, osWaitForever); // 得不到会一直等待
		LED_Control(LED2,ON);
		printf("LED2 ON\n");
		osDelay(1000);
		LED_Control(LED2,OFF);
		printf("LED2 OFF\n");
		osSemaphoreRelease (BinarySem3Handle);
    osDelay(100);
  }
  /* USER CODE END TaskLED2 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

