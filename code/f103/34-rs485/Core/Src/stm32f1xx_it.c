/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f1xx_it.c
  * @brief   Interrupt Service Routines.
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
#include "main.h"
#include "stm32f1xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "gpio.h"
#include <stdio.h>
#include "usart.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
void USER_UART_IRQHandler(UART_HandleTypeDef *huart);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern CAN_HandleTypeDef hcan;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M3 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
   while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles DMA1 channel5 global interrupt.
  */
void DMA1_Channel5_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel5_IRQn 0 */

  /* USER CODE END DMA1_Channel5_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart1_rx);
  /* USER CODE BEGIN DMA1_Channel5_IRQn 1 */

  /* USER CODE END DMA1_Channel5_IRQn 1 */
}

/**
  * @brief This function handles DMA1 channel6 global interrupt.
  */
void DMA1_Channel6_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel6_IRQn 0 */

  /* USER CODE END DMA1_Channel6_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart2_rx);
  /* USER CODE BEGIN DMA1_Channel6_IRQn 1 */

  /* USER CODE END DMA1_Channel6_IRQn 1 */
}

/**
  * @brief This function handles USB low priority or CAN RX0 interrupts.
  */
void USB_LP_CAN1_RX0_IRQHandler(void)
{
  /* USER CODE BEGIN USB_LP_CAN1_RX0_IRQn 0 */

  /* USER CODE END USB_LP_CAN1_RX0_IRQn 0 */
  HAL_CAN_IRQHandler(&hcan);
  /* USER CODE BEGIN USB_LP_CAN1_RX0_IRQn 1 */

  /* USER CODE END USB_LP_CAN1_RX0_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[9:5] interrupts.
  */
void EXTI9_5_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI9_5_IRQn 0 */

  /* USER CODE END EXTI9_5_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(KEY_LEFT_Pin);
  HAL_GPIO_EXTI_IRQHandler(KEY_ESC_Pin);
  /* USER CODE BEGIN EXTI9_5_IRQn 1 */

  /* USER CODE END EXTI9_5_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */

  /* USER CODE END USART1_IRQn 0 */
  HAL_UART_IRQHandler(&huart1);
  /* USER CODE BEGIN USART1_IRQn 1 */
	USER_UART_IRQHandler(&huart1);       //新添加的函数，用来处理串口空闲中断
  /* USER CODE END USART1_IRQn 1 */
}

/**
  * @brief This function handles USART2 global interrupt.
  */
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */

  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */
	USER_UART_IRQHandler(&huart2);       //新添加的函数，用来处理串口空闲中断
  /* USER CODE END USART2_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[15:10] interrupts.
  */
void EXTI15_10_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI15_10_IRQn 0 */

  /* USER CODE END EXTI15_10_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(KEY_OK_Pin);
  HAL_GPIO_EXTI_IRQHandler(KEY_UP_Pin);
  HAL_GPIO_EXTI_IRQHandler(KEY_DOWN_Pin);
  HAL_GPIO_EXTI_IRQHandler(KEY_RIGHT_Pin);
  /* USER CODE BEGIN EXTI15_10_IRQn 1 */

  /* USER CODE END EXTI15_10_IRQn 1 */
}

/* USER CODE BEGIN 1 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	static uint32_t old_uwTick =0; 
	if( (uwTick - old_uwTick) < 200 )  return ; 	
	// uwTick 是全局变量, 每隔1ms 累加一次
	// 第1次进入时 , 时间差会大于200 , if( (uwTick - old_uwTick) < 200 ) 这个条件不成立 
	// 第2次进入时 小时200ms时 不满足条件, 会直接返回 
	// 等时间差大于200ms时, 可以再次触发中断
	old_uwTick = uwTick ; 
	
	// PB13  按键的UP 
	if( GPIO_Pin ==  KEY_UP_Pin)  // 表示 Up 按键按下后触发的中断 
	{
			LED_Control(LED1,ON); // led1 on
			Key_Value = KEY_UP;
			printf("Key Up   Pressed\n");
	}
	else if( GPIO_Pin ==  KEY_DOWN_Pin) 
	{
			LED_Control(LED1,OFF); // led1 off
			Key_Value = KEY_DOWN;
			printf("Key Down Pressed\n");
	}
	else if( GPIO_Pin ==  KEY_LEFT_Pin) 
	{
			LED_Control(LED2,ON); // led2 on
			Key_Value = KEY_LEFT;
			printf("Key Left Pressed\n");
	}
	else if( GPIO_Pin ==  KEY_RIGHT_Pin) 
	{
			LED_Control(LED2,OFF); // led2 off
			Key_Value = KEY_RIGHT;
			printf("Key Right Pressed\n");
	}
	else if( GPIO_Pin ==  KEY_OK_Pin) 
	{
			BEEP_Control(ON); // beep on
			Key_Value = KEY_OK;
			printf("Key OK    Pressed\n");
	}
	else if( GPIO_Pin ==  KEY_ESC_Pin) 
	{
			BEEP_Control(OFF); // beep off
			Key_Value = KEY_ESC;
			printf("Key ESC   Pressed\n");
	}
}



// DMA 接收到一半的中断 
void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart)
{
		if(huart->Instance == USART1)
		{
			uint8_t Length  =  DMA_BUF_SIZE/2 - RX1_Offset ; 
			//printf("HLength=%d\n",Length);
			
			//  RS485_WR ENABLE 高电平  发送模式
			HAL_GPIO_WritePin(RS485_WR_GPIO_Port, RS485_WR_Pin, GPIO_PIN_SET);
			HAL_UART_Transmit(&huart2,RX1_Buf+RX1_Offset,Length,HAL_MAX_DELAY); 
			// 低电平  默认为接收模式	
			HAL_GPIO_WritePin(RS485_WR_GPIO_Port, RS485_WR_Pin, GPIO_PIN_RESET);
			
			RX1_Offset += Length; 		
		}
		else if(huart->Instance == USART2)
		{
			uint8_t Length  =  DMA_BUF_SIZE/2 - RX2_Offset ; 
			//printf("HLength=%d\n",Length);
			
			HAL_UART_Transmit(&huart1,RX2_Buf+RX2_Offset,Length,HAL_MAX_DELAY); 
			
			RX2_Offset += Length; 
		
		}
}

// DMA传输完成中断   , 就是接收满了的时候 触发中断
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if(huart->Instance == USART1)
    {
        uint8_t Length  =  DMA_BUF_SIZE - RX1_Offset ; 
			
				//  RS485_WR ENABLE 高电平  发送模式
				HAL_GPIO_WritePin(RS485_WR_GPIO_Port, RS485_WR_Pin, GPIO_PIN_SET);
        HAL_UART_Transmit(&huart2,RX1_Buf+RX1_Offset,Length,HAL_MAX_DELAY); 
				// 低电平  默认为接收模式	
				HAL_GPIO_WritePin(RS485_WR_GPIO_Port, RS485_WR_Pin, GPIO_PIN_RESET);
			
        //printf("CLength=%d\n",Length);
        RX1_Offset = 0 ; // 清空dma 位置基准值
    }
		else  if(huart->Instance == USART2)
    {
        uint8_t Length  =  DMA_BUF_SIZE - RX2_Offset ; 
        HAL_UART_Transmit(&huart1,RX2_Buf+RX2_Offset,Length,HAL_MAX_DELAY); 
        //printf("CLength=%d\n",Length);
        RX2_Offset = 0 ; // 清空dma 位置基准值
    }
}

// 用户自定义的函数 ， 处理串口空闲中断
void USER_UART_IRQHandler(UART_HandleTypeDef *huart)
{
		
    if(huart->Instance == USART1)                                   //判断是否是串口1
    {
			
				if((__HAL_UART_GET_FLAG(huart, UART_FLAG_FE) ||  
            __HAL_UART_GET_FLAG(huart, UART_FLAG_NE) )== SET )   //判断是否是帧错误或者噪音中断
        {
            __HAL_UART_CLEAR_FLAG(huart, UART_FLAG_FE);
            __HAL_UART_CLEAR_FLAG(huart, UART_FLAG_NE);

            huart->ErrorCode &= HAL_UART_ERROR_FE; // 清除错误标志位
            huart->ErrorCode &= HAL_UART_ERROR_NE; // 清除错误标志位
            HAL_UART_DMAStop(huart); // 关闭DMA
            HAL_UART_Receive_DMA(huart,RX1_Buf,DMA_BUF_SIZE);// 重新启动DMA
        }
        if(__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE) != RESET )   //判断是否是空闲中断
        {
            __HAL_UART_CLEAR_IDLEFLAG(huart);    //清除空闲中断标志（否则会一直不断进入中断）

            //计算接收到的数据长度 : BUFFER_SIZE - __HAL_DMA_GET_COUNTER(&hdma_usart1_rx)
            uint8_t Length  =  DMA_BUF_SIZE - __HAL_DMA_GET_COUNTER(&hdma_usart1_rx) - RX1_Offset;
						//  RS485_WR ENABLE 高电平  发送模式
						HAL_GPIO_WritePin(RS485_WR_GPIO_Port, RS485_WR_Pin, GPIO_PIN_SET);
            HAL_UART_Transmit(&huart2,RX1_Buf+RX1_Offset,Length,HAL_MAX_DELAY); 
						// 低电平  默认为接收模式	
						HAL_GPIO_WritePin(RS485_WR_GPIO_Port, RS485_WR_Pin, GPIO_PIN_RESET);
            RX1_Offset += Length; 
					  //printf("ILength=%d\n",Length);					   
        }
    }
		else if(huart->Instance == USART2)                                  //判断是否是串口2
    {
			  if((__HAL_UART_GET_FLAG(huart, UART_FLAG_FE) ||  
            __HAL_UART_GET_FLAG(huart, UART_FLAG_NE) )== SET )   //判断是否是帧错误或者噪音中断
        {
            __HAL_UART_CLEAR_FLAG(huart, UART_FLAG_FE);
            __HAL_UART_CLEAR_FLAG(huart, UART_FLAG_NE);

            huart->ErrorCode &= HAL_UART_ERROR_FE; // 清除错误标志位
            huart->ErrorCode &= HAL_UART_ERROR_NE; // 清除错误标志位
            HAL_UART_DMAStop(huart); // 关闭DMA
            HAL_UART_Receive_DMA(huart,RX1_Buf,DMA_BUF_SIZE);// 重新启动DMA
        }
        if(__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE) != RESET )   //判断是否是空闲中断
        {
            __HAL_UART_CLEAR_IDLEFLAG(huart);    //清除空闲中断标志（否则会一直不断进入中断）

            //计算接收到的数据长度 : BUFFER_SIZE - __HAL_DMA_GET_COUNTER(&hdma_usart1_rx)
            uint8_t Length  =  DMA_BUF_SIZE - __HAL_DMA_GET_COUNTER(&hdma_usart2_rx) - RX2_Offset;
            HAL_UART_Transmit(&huart1,RX2_Buf+RX2_Offset,Length,HAL_MAX_DELAY); 
            RX2_Offset += Length; 
					  //printf("ILength=%d\n",Length);					   
        }
    }
		
}



uint8_t RX_Message[8] = {0};  // 接收消息的数组
CAN_RxHeaderTypeDef RX_Header; // 接收数据包头
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	if(hcan->Instance == CAN1)
	{
			if( HAL_CAN_GetRxMessage(hcan,CAN_RX_FIFO0,&RX_Header,RX_Message) == HAL_OK)
			{				
					printf("%#x:",RX_Header.StdId);
					HAL_UART_Transmit(&huart1,RX_Message,8,HAL_MAX_DELAY); 
			}

	}
}

/* USER CODE END 1 */
