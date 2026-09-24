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
osThreadId LED1Handle;
osThreadId LED2Handle;
osThreadId BEEPHandle;
osMessageQId QueueLED1Handle;
osMessageQId QueueLED2Handle;
osTimerId Timer1Handle;
osTimerId Timer2Handle;
osMutexId myMutex01Handle;
osSemaphoreId BinarySem1Handle;
osSemaphoreId BinarySem2Handle;
osSemaphoreId BinarySem3Handle;
osSemaphoreId CountingSem1Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
#define   LED1CMD    (0x1<<0)
#define   LED2CMD    (0x1<<1)
#define   BEEPCMD    (0x1<<2)
/* USER CODE END FunctionPrototypes */

void StartDefalutTask(void const * argument);
void LED1Task(void const * argument);
void LED2Task(void const * argument);
void BeepTask(void const * argument);
void Timer1Callback(void const * argument);
void Timer2Callback(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* GetTimerTaskMemory prototype (linked to static allocation support) */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize );

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

/* USER CODE BEGIN GET_TIMER_TASK_MEMORY */
static StaticTask_t xTimerTaskTCBBuffer;
static StackType_t xTimerStack[configTIMER_TASK_STACK_DEPTH];

void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize )
{
  *ppxTimerTaskTCBBuffer = &xTimerTaskTCBBuffer;
  *ppxTimerTaskStackBuffer = &xTimerStack[0];
  *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
  /* place for user code */
}
/* USER CODE END GET_TIMER_TASK_MEMORY */

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

  /* Create the timer(s) */
  /* definition and creation of Timer1 */
  osTimerDef(Timer1, Timer1Callback);
  Timer1Handle = osTimerCreate(osTimer(Timer1), osTimerOnce, NULL);

  /* definition and creation of Timer2 */
  osTimerDef(Timer2, Timer2Callback);
  Timer2Handle = osTimerCreate(osTimer(Timer2), osTimerPeriodic, NULL);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
	osTimerStart(Timer1Handle,1000);// 启动定时器1
	osTimerStart(Timer2Handle,1000);// 启动定时器2
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

  /* definition and creation of LED1 */
  osThreadDef(LED1, LED1Task, osPriorityNormal, 0, 128);
  LED1Handle = osThreadCreate(osThread(LED1), NULL);

  /* definition and creation of LED2 */
  osThreadDef(LED2, LED2Task, osPriorityNormal, 0, 128);
  LED2Handle = osThreadCreate(osThread(LED2), NULL);

  /* definition and creation of BEEP */
  osThreadDef(BEEP, BeepTask, osPriorityNormal, 0, 128);
  BEEPHandle = osThreadCreate(osThread(BEEP), NULL);

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
		if(Key_Value == KEY_UP)
		{
				Key_Value = 0 ; 
				osSignalSet (LED1Handle, LED1CMD); 
		}
		else	if(Key_Value == KEY_DOWN)
		{
				Key_Value = 0 ; 
				osSignalSet (LED2Handle, LED2CMD); 
		}
		else	if(Key_Value == KEY_LEFT)
		{
				Key_Value = 0 ; 
				osSignalSet (BEEPHandle, BEEPCMD); 
		}
    osDelay(100);
  }
  /* USER CODE END StartDefalutTask */
}

/* USER CODE BEGIN Header_LED1Task */
/**
* @brief Function implementing the LED1 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LED1Task */
void LED1Task(void const * argument)
{
  /* USER CODE BEGIN LED1Task */
  /* Infinite loop */
	osEvent  ret;
  for(;;)
  {
		ret =  osSignalWait(LED1CMD, osWaitForever) ; 
		if(ret.status == osEventSignal)
		{
				if(ret.value.signals  & LED1CMD) // 接收内容为 LED1CMD
				{
						printf("Recv Data:%x\n",ret.value.signals);
						HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
				}
				
		}
    osDelay(100);
  }
  /* USER CODE END LED1Task */
}

/* USER CODE BEGIN Header_LED2Task */
/**
* @brief Function implementing the LED2 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LED2Task */
void LED2Task(void const * argument)
{
  /* USER CODE BEGIN LED2Task */
  /* Infinite loop */
	osEvent ret; 
  for(;;)
  {
			ret =  osSignalWait(LED2CMD, osWaitForever) ; 
			if(ret.status == osEventSignal)
			{
					if(ret.value.signals  & LED2CMD) // 接收内容为 LED2CMD
					{
							printf("Recv Data:%x\n",ret.value.signals);
							HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);
					}
					
			}
			osDelay(100);
  }
  /* USER CODE END LED2Task */
}

/* USER CODE BEGIN Header_BeepTask */
/**
* @brief Function implementing the BEEP thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_BeepTask */
void BeepTask(void const * argument)
{
  /* USER CODE BEGIN BeepTask */
  /* Infinite loop */
	osEvent ret;
  for(;;)
  {
				ret =  osSignalWait(BEEPCMD, osWaitForever) ; 
				if(ret.status == osEventSignal)
				{
						if(ret.value.signals  & BEEPCMD) // 接收内容为 BEEPCMD
						{
								printf("Recv Data:%x\n",ret.value.signals);
								HAL_GPIO_TogglePin(BEEP_GPIO_Port,BEEP_Pin);
						}
						
				}
				osDelay(100);
  }
  /* USER CODE END BeepTask */
}

/* Timer1Callback function */
void Timer1Callback(void const * argument)
{
  /* USER CODE BEGIN Timer1Callback */
	printf("Timer1 Timeout\n");
  /* USER CODE END Timer1Callback */
}

/* Timer2Callback function */
void Timer2Callback(void const * argument)
{
  /* USER CODE BEGIN Timer2Callback */
	printf("Timer2 Timeout\n");
  /* USER CODE END Timer2Callback */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

