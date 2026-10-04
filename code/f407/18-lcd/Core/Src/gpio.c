/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LCD_BLK_GPIO_Port, LCD_BLK_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED_SYS_Pin|LED2_Pin|LED1_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(FLASH_CS_GPIO_Port, FLASH_CS_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin : LCD_BLK_Pin */
  GPIO_InitStruct.Pin = LCD_BLK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(LCD_BLK_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : BEEP_Pin LED_SYS_Pin LED2_Pin LED1_Pin */
  GPIO_InitStruct.Pin = BEEP_Pin|LED_SYS_Pin|LED2_Pin|LED1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : KEY_OK_Pin */
  GPIO_InitStruct.Pin = KEY_OK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(KEY_OK_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : KEY_ESC_Pin */
  GPIO_InitStruct.Pin = KEY_ESC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(KEY_ESC_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : FLASH_CS_Pin */
  GPIO_InitStruct.Pin = FLASH_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(FLASH_CS_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

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

/**
  * @brief  控制蜂鸣器的函数
  *
  * @note   详细描述细节，ON 用来控制beep响， OFF用来控制beep不响
  *
  * @param  cmd: 用来控制BEEP的响与不响命令
  *           ON  : BEEP响 
  *           OFF ：不响
  * @retval None
  */
void BEEP_Control(uint8_t cmd)
{
	if(cmd == ON ) // BEEP ON 
	{
		HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_SET); 
	}
	else if(cmd == OFF)  // BEEP OFF
	{
		HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_RESET); 
	}
}

/**
  * @brief  LED1 LED2 测试函数
  *
  * @note   验证LED1 LED2的功能
  *
  * @retval None
  */
void BEEP_Test(void)
{
	BEEP_Control(ON); 
	HAL_Delay(200); 
	BEEP_Control(OFF); 
	HAL_Delay(800); 
}

/**
  * @brief 获取按键的值
  * 
  * @note 详细描述细节， 根据按下的按键返回按键的键值
  * 
  * @param 无
  * @retval 按下的键值 ， 定义在gpio.h 当中
 */
uint8_t KEY_Scan(void)
{
	uint8_t keyval = 0;
	if(HAL_GPIO_ReadPin(KEY_OK_GPIO_Port, KEY_OK_Pin) == GPIO_PIN_RESET)
	{
		keyval = KEY_OK;
	}
	else if(HAL_GPIO_ReadPin(KEY_ESC_GPIO_Port, KEY_ESC_Pin) == GPIO_PIN_RESET)
	{
		keyval = KEY_ESC;
	}	

	return keyval;
}

void KEY_Test(void)
{
	uint8_t keyval = KEY_Scan();
	if(keyval > 0)
	{
		if(keyval == KEY_OK)
		{
			LED_Control(LED1, ON);
		}
		else if(keyval == KEY_ESC)
		{
			LED_Control(LED1, OFF);
		}
	}

}


/* USER CODE END 2 */
