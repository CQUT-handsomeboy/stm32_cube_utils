# 项目简介

STM32 Cube 生成的代码主要提供了驱动配置和调度的框架。

STM32_cube_utils实现了硬件初始化和驱动函数,为外部应用提供了易用的接口。

两者实现了良好的解耦设计:内部库负责通用逻辑,外部框架侧重于应用开发,以提高可维护性和可扩展性。

# 工具代码片段

## 串口输出重定向

```c
int fputc(int ch, FILE *f)
{
	uint8_t temp[1] = {ch};
	HAL_UART_Transmit(
        &huart1 // 自定义串口号
    , temp, 1, 2); 
	return ch;
}
```

## GPIO中断回调函数

```c
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
```

## 串口中断回调函数

```c
HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
```

## 定时器中断回调函数

```c
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
```
