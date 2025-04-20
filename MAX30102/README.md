# MAX30102心率传感器

[🔗原仓库链接](https://github.com/lamik/MAX30102_STM32_HAL)

1.  引入头文件

```c
#include "MAX30102.h"
```

2.  STM32CubeMX初始化**硬件I2C**，设为hi2c1，设置外部中断引脚，打开中断，并在回调函数中调用`Max30102_InterruptCallback()`

```c
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	Max30102_InterruptCallback();
}
```

3.  初始化传感器

```c
Max30102_Init(&hi2c1);
```

4.  超循环中调用`Max30102_Task()`

```c
while(1)
{
    Max30102_Task();
}
```

5.  得到数据

```c
printf("HR: %d,SpO2: %d\r\n",Max30102_GetHeartRate(), Max30102_GetSpO2Value());
```