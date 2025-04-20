# PulseSensor 脉搏传感器

1.  引入头文件

```c
#include "pulsesensor.h"
```

2.  设置定时器，**打开该定时器的全局中断以确保回调函数的正常调用**，以36M主频为例，设置`Prescaler`为7，设置`Counter Period`为1999

$$
1 / (36M / (7+1) * (1999+1))= 1/2250
$$

3.  在定时器回调函数中调用`pulseSensorCycleDepartureCallback()`

```c
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    pulseSensorCycleDepartureCallback()；
}
```

4.  超循环中调用`pulseSensorMain()`

```c
while(1)
{
    pulseSensorMain();
}
```