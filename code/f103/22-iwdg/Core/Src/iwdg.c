/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    iwdg.c
  * @brief   This file provides code for the configuration
  *          of the IWDG instances.
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
#include "iwdg.h"

/* USER CODE BEGIN 0 */
#include "oled.h"
#include "gpio.h"
/* USER CODE END 0 */

IWDG_HandleTypeDef hiwdg;

/* IWDG init function */
void MX_IWDG_Init(void)
{

  /* USER CODE BEGIN IWDG_Init 0 */

  /* USER CODE END IWDG_Init 0 */

  /* USER CODE BEGIN IWDG_Init 1 */

  /* USER CODE END IWDG_Init 1 */
  hiwdg.Instance = IWDG;
  hiwdg.Init.Prescaler = IWDG_PRESCALER_64;
  hiwdg.Init.Reload = 1250;
  if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN IWDG_Init 2 */

  /* USER CODE END IWDG_Init 2 */

}

/* USER CODE BEGIN 1 */

void IWDG_Test(void)
{
	OLED_ShowStr(16,0, (unsigned char*)"IWDG Test", 2);	
	// 获取按键 ESC , 如果ESC 按键按下就喂狗 , 否则不喂狗, 让系统复位 
	if(Key_Value == KEY_ESC) 
	{
        Key_Value = 0 ; // 键值清空为0 
        HAL_IWDG_Refresh(&hiwdg) ; // 喂狗指令 , 2秒后系统复位 
        BEEP_Control(ON);
        HAL_Delay(20);
        BEEP_Control(OFF);
	}
	HAL_Delay(500); // 延时500ms 
		
}
/* USER CODE END 1 */
