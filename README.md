# STM32 HAL 学习笔记

本仓库整理 STM32F103 与 STM32 HAL 库的基础知识、外设原理和典型使用方式。内容从 Cortex-M3 内核开始，逐步覆盖常用片上外设、工业通信总线及无线通信模块，适合作为 STM32 入门到综合项目开发的查阅索引。

> 完整讲义见 `STM32HAL.md`。本文档用于快速定位主题与建立学习路径。

## 内容概览

| 模块 | 学习重点 |
| --- | --- |
| Cortex-M3 | 内核组成、寄存器、Thumb-2 指令集、运行模式、异常与中断、存储器映射、低功耗 |
| RCC 与启动 | 复位来源、时钟树、STM32F103 启动流程、向量表与 ARM 汇编基础 |
| GPIO / EXTI | 输入输出模式、上拉下拉、推挽与开漏、外部中断及事件配置 |
| 定时器 | SysTick、通用定时器和 PWM 输出 |
| USART / DMA | 串口收发、按键消抖、DMA 定长与不定长数据接收 |
| I2C | 时序、起始/停止信号，以及 AT24C02、OLED、AHT20、INA226 的通信思路 |
| 系统可靠性 | 独立/窗口看门狗、RTC、备份寄存器与 PWR 低功耗模式 |
| ADC | 采样时间、转换时间、轮询读取与电压/温度换算 |
| SPI | 四线通信、CPOL/CPHA 四种模式、W25Q32 Flash |
| CAN / RS485 | 差分传输、物理层、仲裁/终端匹配及收发配置 |
| 联网模块 | ESP8266 Wi-Fi AT 指令、ML307R-DC 4G 模块 AT 指令 |

## 推荐学习路径

1. **打好底层基础**：Cortex-M3、RCC、启动流程与 GPIO。
2. **掌握事件与时间**：EXTI、SysTick、通用定时器、PWM。
3. **完成数据采集与显示**：USART、DMA、I2C、ADC。
4. **增强系统稳定性**：看门狗、RTC、PWR 低功耗。
5. **扩展存储与通信能力**：SPI Flash、CAN、RS485、Wi-Fi 和 4G。

## HAL 开发要点

典型的 HAL 外设开发流程如下：

1. 在 STM32CubeMX 中选择芯片并配置时钟、引脚和外设参数。
2. 生成初始化代码，确认 `HAL_Init()`、系统时钟配置与对应的 `MX_*_Init()` 已执行。
3. 使用 HAL API 启动外设，并根据需求选择轮询、中断或 DMA 传输方式。
4. 在回调函数或中断服务函数中处理异步事件。
5. 所有 HAL 调用均应检查返回值；失败时进入统一的 `Error_Handler()`。

### 常见 API 速查

| 场景 | 常用 HAL API |
| --- | --- |
| GPIO 读写 | `HAL_GPIO_WritePin()`、`HAL_GPIO_ReadPin()`、`HAL_GPIO_TogglePin()` |
| 外部中断 | `HAL_GPIO_EXTI_Callback()` |
| 延时与时基 | `HAL_Delay()`、`HAL_GetTick()` |
| UART | `HAL_UART_Transmit()`、`HAL_UART_Receive()`、`HAL_UART_Receive_DMA()` |
| DMA | `HAL_DMA_Start()`、DMA 完成回调 |
| I2C | `HAL_I2C_Master_Transmit()`、`HAL_I2C_Master_Receive()` |
| ADC | `HAL_ADC_Start()`、`HAL_ADC_PollForConversion()`、`HAL_ADC_GetValue()` |
| SPI | `HAL_SPI_Transmit()`、`HAL_SPI_Receive()`、`HAL_SPI_TransmitReceive()` |
| CAN | `HAL_CAN_ConfigFilter()`、`HAL_CAN_Start()`、`HAL_CAN_AddTxMessage()` |

## 关键提示

- GPIO 输入脚需要通过上拉或下拉避免悬空；开漏输出通常需要外部或内部上拉。
- 外部中断的配置顺序是：配置 GPIO、映射 EXTI 线、设置触发沿与 NVIC、实现回调处理。
- ADC 转换时间由采样时间和 12.5 个 ADC 时钟周期组成；模拟源阻抗较高时应适当增加采样时间。
- SPI 通信前必须使主从设备的 CPOL/CPHA 配置一致；W25Q 系列的片选通常由普通 GPIO 软件控制。
- CAN 总线两端应设置终端电阻，多个节点同时发送时通过标识符仲裁决定优先级。
- RS485 是半双工差分通信，收发方向控制和总线终端匹配是稳定通信的关键。

## 参考主题

- ESP8266：STA/AP/STA+AP 模式、联网、TCP/UDP 连接与透传。
- ML307R-DC：设备身份查询、网络注册、信号强度、Socket 与 MQTT 等 DTU 任务配置。
- RTC：利用备份域保存时间基准，配合备用电源实现掉电保持。

## 适用范围

- STM32F103 系列的 HAL 库学习与实验
- 传感器采集、显示、存储和通信综合练习
- 基于 STM32CubeMX 的外设驱动开发

## 文档来源

本 README 根据 `STM32HAL.md` 的章节内容整理。涉及寄存器位定义、电气参数、时钟上限和模块专有 AT 指令时，请以芯片参考手册、数据手册及模块厂商最新文档为准。
