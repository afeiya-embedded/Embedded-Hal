/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED2_Pin|LED1_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : LED2_Pin LED1_Pin */
  GPIO_InitStruct.Pin = LED2_Pin|LED1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */

/**
  * @brief  控制LED1 LED2 亮灭的函数
  *
  * @note   详细描述细节，ON 用来控制led亮， OFF用来控制LED熄灭
  *
  * @param  device: 可以是LED1, LED2 , 是两个宏，定义在gpio.h中
  * @param  cmd: 用来控制LED的亮灭命令
	*           ON  : 点亮LED  
	*           OFF ：熄灭LED
  * @retval None
  */
void LED_Control(uint8_t device,uint8_t cmd)
{
	if(device == LED1)
	{
		if(cmd == ON ) // LED1 ON 
		{
			HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET); 
		}
		else if(cmd == OFF)  // LED1 OFF
		{
			HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET); 
		}
	}
	else if(device == LED2)
	{
		if(cmd == ON ) // LED2 ON 
		{
			HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET); 
		}
		else if(cmd == OFF) // LED2 OFF
		{
			HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET); 
		}
	}

}

/**
  * @brief  LED1 LED2 测试函数
  *
  * @note   验证LED1 LED2的功能
  *
  * @retval None
  */
void LED_Test(void)
{
		LED_Control(LED1,ON); 
		LED_Control(LED2,OFF); 
		HAL_Delay(500); 
		LED_Control(LED1,OFF); 
		LED_Control(LED2,ON); 
		HAL_Delay(500); 
}


/* USER CODE END 2 */
