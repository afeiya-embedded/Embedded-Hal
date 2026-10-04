/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.c
  * @brief   This file provides code for the configuration
  *          of the CAN instances.
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
#include "can.h"

/* USER CODE BEGIN 0 */
#include "stdio.h"

static CAN_TxHeaderTypeDef TxMessage; //CAN发送的消息的消息头
static CAN_RxHeaderTypeDef RxMessage; //CAN发送的消息的消息头

uint32_t TxMailbox;
/* USER CODE END 0 */

CAN_HandleTypeDef hcan1;
CAN_HandleTypeDef hcan2;

/* CAN1 init function */
void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 21;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_2TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_1TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */

  /* USER CODE END CAN1_Init 2 */

}
/* CAN2 init function */
void MX_CAN2_Init(void)
{

  /* USER CODE BEGIN CAN2_Init 0 */

  /* USER CODE END CAN2_Init 0 */

  /* USER CODE BEGIN CAN2_Init 1 */

  /* USER CODE END CAN2_Init 1 */
  hcan2.Instance = CAN2;
  hcan2.Init.Prescaler = 21;
  hcan2.Init.Mode = CAN_MODE_NORMAL;
  hcan2.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan2.Init.TimeSeg1 = CAN_BS1_2TQ;
  hcan2.Init.TimeSeg2 = CAN_BS2_1TQ;
  hcan2.Init.TimeTriggeredMode = DISABLE;
  hcan2.Init.AutoBusOff = DISABLE;
  hcan2.Init.AutoWakeUp = DISABLE;
  hcan2.Init.AutoRetransmission = DISABLE;
  hcan2.Init.ReceiveFifoLocked = DISABLE;
  hcan2.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN2_Init 2 */

  /* USER CODE END CAN2_Init 2 */

}

static uint32_t HAL_RCC_CAN1_CLK_ENABLED=0;

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    HAL_RCC_CAN1_CLK_ENABLED++;
    if(HAL_RCC_CAN1_CLK_ENABLED==1){
      __HAL_RCC_CAN1_CLK_ENABLE();
    }

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**CAN1 GPIO Configuration
    PB8     ------> CAN1_RX
    PB9     ------> CAN1_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(CAN1_TX_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(CAN1_TX_IRQn);
    HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspInit 1 */

  /* USER CODE END CAN1_MspInit 1 */
  }
  else if(canHandle->Instance==CAN2)
  {
  /* USER CODE BEGIN CAN2_MspInit 0 */

  /* USER CODE END CAN2_MspInit 0 */
    /* CAN2 clock enable */
    __HAL_RCC_CAN2_CLK_ENABLE();
    HAL_RCC_CAN1_CLK_ENABLED++;
    if(HAL_RCC_CAN1_CLK_ENABLED==1){
      __HAL_RCC_CAN1_CLK_ENABLE();
    }

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**CAN2 GPIO Configuration
    PB12     ------> CAN2_RX
    PB13     ------> CAN2_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN CAN2_MspInit 1 */

  /* USER CODE END CAN2_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    HAL_RCC_CAN1_CLK_ENABLED--;
    if(HAL_RCC_CAN1_CLK_ENABLED==0){
      __HAL_RCC_CAN1_CLK_DISABLE();
    }

    /**CAN1 GPIO Configuration
    PB8     ------> CAN1_RX
    PB9     ------> CAN1_TX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8|GPIO_PIN_9);

    /* CAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(CAN1_TX_IRQn);
    HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
  else if(canHandle->Instance==CAN2)
  {
  /* USER CODE BEGIN CAN2_MspDeInit 0 */

  /* USER CODE END CAN2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN2_CLK_DISABLE();
    HAL_RCC_CAN1_CLK_ENABLED--;
    if(HAL_RCC_CAN1_CLK_ENABLED==0){
      __HAL_RCC_CAN1_CLK_DISABLE();
    }

    /**CAN2 GPIO Configuration
    PB12     ------> CAN2_RX
    PB13     ------> CAN2_TX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_12|GPIO_PIN_13);

  /* USER CODE BEGIN CAN2_MspDeInit 1 */

  /* USER CODE END CAN2_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

//设置筛选器,要在完成CAN初始化之后调用此函数
HAL_StatusTypeDef CAN1_SetFilters(void)
{
	CAN_FilterTypeDef canFilter;
	
	//Configure the CAN Filter
	canFilter.FilterBank = 0;						//筛选器组编号
	canFilter.FilterMode = CAN_FILTERMODE_IDMASK;	//ID掩码模式
	canFilter.FilterScale = CAN_FILTERSCALE_32BIT;	//32位长度
	
	//接收所有帧
	canFilter.FilterIdHigh = 0x0000;		//CAN_FxR1 的高16位
	canFilter.FilterIdLow = 0x0000;			//CAN_FxR1 的低16位
	canFilter.FilterMaskIdHigh = 0x0000;	//CAN_FxR2的高16位 所有位任意
	canFilter.FilterMaskIdLow = 0x0000;		//CAN_FxR2的低16位， 所有位任意
	
	canFilter.FilterFIFOAssignment = CAN_FilterFIFO0;	//应用于FIFO0
	canFilter.FilterActivation = ENABLE;				//使能筛选器
	canFilter.SlaveStartFilterBank = 14;				//从CAN控制器筛选器起始的Bank
	
	HAL_StatusTypeDef result = HAL_CAN_ConfigFilter(&hcan1, &canFilter);
	
	return result;
}

//设置筛选器,要在完成CAN初始化之后调用此函数
HAL_StatusTypeDef CAN2_SetFilters(void)
{
	CAN_FilterTypeDef canFilter;
	
	//Configure the CAN Filter
	canFilter.FilterBank = 14;						//筛选器组编号
	canFilter.FilterMode = CAN_FILTERMODE_IDMASK;	//ID掩码模式
	canFilter.FilterScale = CAN_FILTERSCALE_32BIT;	//32位长度
	
	//接收所有帧
	canFilter.FilterIdHigh = 0x0000;		//CAN_FxR1 的高16位
	canFilter.FilterIdLow = 0x0000;			//CAN_FxR1 的低16位
	canFilter.FilterMaskIdHigh = 0x0000;	//CAN_FxR2的高16位 所有位任意
	canFilter.FilterMaskIdLow = 0x0000;		//CAN_FxR2的低16位， 所有位任意
	
	canFilter.FilterFIFOAssignment = CAN_FilterFIFO0;	//应用于FIFO0
	canFilter.FilterActivation = ENABLE;				//使能筛选器
	canFilter.SlaveStartFilterBank = 14;				//从CAN控制器筛选器起始的Bank
	
	HAL_StatusTypeDef result = HAL_CAN_ConfigFilter(&hcan2, &canFilter);
	
	return result;
}

void CAN_Init(void)
{
	//CAN1
	if(CAN1_SetFilters() == HAL_OK)		//设置筛选器
	{
		printf("CAN1 SetFilters\n");
	}
	if(HAL_CAN_Start(&hcan1) == HAL_OK)	///启动CAN1模块
	{
		printf("CAN1 Start\n");
	}
	
	//启用CAN1发送/接收中断
	if(HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING | CAN_IT_TX_MAILBOX_EMPTY) != HAL_OK)
	{
		printf("CAN_IT_RX_FIFO0_MSG_PENDING enable fail\n");
		Error_Handler();
	}
	
	
	//CAN2
	if(CAN2_SetFilters() == HAL_OK)		//设置筛选器
	{
		printf("CAN2 SetFilters\n");
	}
	if(HAL_CAN_Start(&hcan2) == HAL_OK)	///启动CAN1模块
	{
		printf("CAN2 Start\n");
	}
	
	//启用CAN2发送/接收中断
	if(HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING | CAN_IT_TX_MAILBOX_EMPTY) != HAL_OK)
	{
		printf("CAN_IT_RX_FIFO0_MSG_PENDING enable fail\n");
		Error_Handler();
	}
}

void CAN1_Send_Test(void)
{
	uint8_t data[8] = {1,2,3,4,5,6,7,8};
	TxMessage.IDE = CAN_ID_STD;		//设置ID类型
	TxMessage.StdId = 0x12;			//设置ID号
	TxMessage.RTR = CAN_RTR_DATA;	//设置传送数据帧
	TxMessage.DLC = 8;				//设置数据长度
	
	if(HAL_CAN_AddTxMessage(&hcan1, &TxMessage, data, &TxMailbox) != HAL_OK)
	{
		printf("CAN1 Send data fail\r\n");
		Error_Handler();
	}
}

void CAN2_Send_Test(void)
{
	uint8_t data[8] = {0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18};
	TxMessage.IDE = CAN_ID_STD;		//设置ID类型
	TxMessage.StdId = 0x13;			//设置ID号
	TxMessage.RTR = CAN_RTR_DATA;	//设置传送数据帧
	TxMessage.DLC = 8;				//设置数据长度
	
	if(HAL_CAN_AddTxMessage(&hcan2, &TxMessage, data, &TxMailbox) != HAL_OK)
	{
		printf("CAN2 Send data fail\r\n");
		Error_Handler();
	}
}

// CAN接收中断处理函数
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	uint8_t data[8];
	HAL_StatusTypeDef status;
	if(hcan == &hcan1)
	{
		status = HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxMessage, data);
		if(HAL_OK == status)
		{
			printf("CAN1 Received \r\n");
			printf("ID:%#x\n", RxMessage.StdId);
			printf("Data:");
			for(uint8_t i = 0; i < 8; i++)
			{
				printf("0x%02x ",data[i]);
			}
			printf("\n");
		}
	}
	else if(hcan == &hcan2)
	{
		status = HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxMessage, data);
		if(HAL_OK == status)
		{
			printf("CAN2 Received \r\n");
			printf("ID:%#x\n", RxMessage.StdId);
			printf("Data:");
			for(uint8_t i = 0; i < 8; i++)
			{
				printf("0x%02x ",data[i]);
			}
			printf("\n");
		}
	}
}

//CAN发送完成中断处理函数
void HAL_CAN_TxMailbox0CompleteCallback(CAN_HandleTypeDef *hcan)
{
	if(hcan == &hcan1)
	{
		printf("CAN1 Send data ok\r\n");
	}
	else if(hcan == &hcan2)
	{
		printf("CAN2 Send data ok\r\n");
	}
}

/* USER CODE END 1 */
