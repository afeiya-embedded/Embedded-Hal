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
#include "oled.h"
#include "aht20.h"
#include "ina226.h"
#include "adc.h"
#include "rtc.h"
#include "w25qx.h"
#include "wifi4g.h"
#include "usart.h"
#include "can.h"
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
osThreadId UPHandle;
osThreadId DOWNHandle;
osThreadId LEFTHandle;
osThreadId RIGHTHandle;
osThreadId OKHandle;
osThreadId ESCHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void UPTask(void const * argument);
void DownTask(void const * argument);
void LeftTask(void const * argument);
void RightTask(void const * argument);
void OKTask(void const * argument);
void EscTask(void const * argument);

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

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of UP */
  osThreadDef(UP, UPTask, osPriorityNormal, 0, 128);
  UPHandle = osThreadCreate(osThread(UP), NULL);

  /* definition and creation of DOWN */
  osThreadDef(DOWN, DownTask, osPriorityNormal, 0, 128);
  DOWNHandle = osThreadCreate(osThread(DOWN), NULL);

  /* definition and creation of LEFT */
  osThreadDef(LEFT, LeftTask, osPriorityNormal, 0, 128);
  LEFTHandle = osThreadCreate(osThread(LEFT), NULL);

  /* definition and creation of RIGHT */
  osThreadDef(RIGHT, RightTask, osPriorityNormal, 0, 128);
  RIGHTHandle = osThreadCreate(osThread(RIGHT), NULL);

  /* definition and creation of OK */
  osThreadDef(OK, OKTask, osPriorityNormal, 0, 128);
  OKHandle = osThreadCreate(osThread(OK), NULL);

  /* definition and creation of ESC */
  osThreadDef(ESC, EscTask, osPriorityNormal, 0, 128);
  ESCHandle = osThreadCreate(osThread(ESC), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_UPTask */
/**
  * @brief  Function implementing the UP thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_UPTask */
void UPTask(void const * argument)
{
  /* USER CODE BEGIN UPTask */
  /* Infinite loop */
  for(;;)
  {
		if(Key_Value == KEY_UP) 
		{
				OLED_ShowStr(0 ,0, (unsigned char*)"   GPIO Test    ", 2);	
				OLED_ShowStr(0 ,2, (unsigned char*)"                ", 2);	
				OLED_ShowStr(0 ,4, (unsigned char*)"                ", 2);	
				OLED_ShowStr(0 ,6, (unsigned char*)"                ", 2);	
				LED_Control(LED1,ON);
				LED_Control(LED2,ON);
				BEEP_Control(ON);
				RELAY_Control(ON);
				osDelay(1000);
				LED_Control(LED1,OFF);
				LED_Control(LED2,OFF);
				BEEP_Control(OFF);
				RELAY_Control(OFF);
				osDelay(1000);
		}
		osDelay(100);

  }
  /* USER CODE END UPTask */
}

/* USER CODE BEGIN Header_DownTask */
/**
* @brief Function implementing the DOWN thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_DownTask */
void DownTask(void const * argument)
{
  /* USER CODE BEGIN DownTask */
  /* Infinite loop */
  for(;;)
  {
		if(Key_Value == KEY_DOWN) 
		{
				OLED_ShowStr(0 ,0, (unsigned char*)"   AHT20 Test   ", 2);	
				OLED_ShowStr(0 ,2, (unsigned char*)"                ", 2);	
				OLED_ShowStr(0 ,4, (unsigned char*)"                ", 2);	
				OLED_ShowStr(0 ,6, (unsigned char*)"                ", 2);	
				AHT20_Test();
				osDelay(1000);
				OLED_ShowStr(0 ,0, (unsigned char*)"   INA226 Test  ", 2);
				OLED_ShowStr(0 ,2, (unsigned char*)"                ", 2);	
				OLED_ShowStr(0 ,4, (unsigned char*)"                ", 2);	
				OLED_ShowStr(0 ,6, (unsigned char*)"                ", 2);	
				INA226_Test();
				osDelay(1000);
		}
		osDelay(100);
  }
  /* USER CODE END DownTask */
}

/* USER CODE BEGIN Header_LeftTask */
/**
* @brief Function implementing the LEFT thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LeftTask */
void LeftTask(void const * argument)
{
  /* USER CODE BEGIN LeftTask */
  /* Infinite loop */
  for(;;)
  {
    if(Key_Value == KEY_LEFT) 
		{
				OLED_ShowStr(0 ,0, (unsigned char*)" ADC VRCPU Test ", 2);	
				OLED_ShowStr(0 ,2, (unsigned char*)"                ", 2);	
				ADC_VR_CPU_Test();
		}
		osDelay(100);
  }
  /* USER CODE END LeftTask */
}

/* USER CODE BEGIN Header_RightTask */
/**
* @brief Function implementing the RIGHT thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_RightTask */
void RightTask(void const * argument)
{
  /* USER CODE BEGIN RightTask */
  /* Infinite loop */
  for(;;)
  {
    if(Key_Value == KEY_RIGHT) 
		{
				OLED_ShowStr(0 ,0, (unsigned char*)"    RTC Test    ", 2);	
				OLED_ShowStr(0 ,2, (unsigned char*)"                ", 2);	
				RTC_Test();
				osDelay(900);
		}
		osDelay(100);
  }
  /* USER CODE END RightTask */
}

/* USER CODE BEGIN Header_OKTask */
/**
* @brief Function implementing the OK thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_OKTask */
void OKTask(void const * argument)
{
  /* USER CODE BEGIN OKTask */
  /* Infinite loop */
  for(;;)
  {
    if(Key_Value == KEY_OK) 
		{
				OLED_ShowStr(0 ,0, (unsigned char*)"   Flash Test   ", 2);	
				OLED_ShowStr(0 ,2, (unsigned char*)"                ", 2);	
				EEPROM_Test();
				W25Qx_Test();
				osDelay(1000);
		}
		osDelay(100);
  }
  /* USER CODE END OKTask */
}

/* USER CODE BEGIN Header_EscTask */
/**
* @brief Function implementing the ESC thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_EscTask */
void EscTask(void const * argument)
{
  /* USER CODE BEGIN EscTask */
  /* Infinite loop */
  for(;;)
  {
    if(Key_Value == KEY_ESC) 
		{
				Key_Value = 0 ; 
				OLED_ShowStr(0 ,0, (unsigned char*)" WIFI4G CAN 485 ", 2);	
				OLED_ShowStr(0 ,2, (unsigned char*)"                ", 2);	
				OLED_ShowStr(0 ,6, (unsigned char*)"                ", 2);	
				if(WIFI4G_AT_Test() == SET) // AT指令测试OK 
				{
						OLED_ShowStr(0,4,(unsigned char *)"WIFI4G Test OK  ",2); 
				}
				else 
				{
						OLED_ShowStr(0,4,(unsigned char *)"WIFI4G Test Fail",2); 
				}
				
				HAL_GPIO_WritePin(RS485_WR_GPIO_Port, RS485_WR_Pin, GPIO_PIN_SET);
				HAL_UART_Transmit(&huart2,(uint8_t *)"RS485 Test",10,HAL_MAX_DELAY); 
				// 低电平  默认为接收模式	
				HAL_GPIO_WritePin(RS485_WR_GPIO_Port, RS485_WR_Pin, GPIO_PIN_RESET);
				CAN_Test();
		}
		osDelay(100);
  }
  /* USER CODE END EscTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

