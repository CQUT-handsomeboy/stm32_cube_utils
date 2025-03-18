## 移植

在CubemMX中把软件I2C的两个引脚对应的User Label修改成`OLEDSDA`和`OLEDSCL`，配置GPIO口为高速输出模式，在advenced选项中选择为每个外设生成头文件。

**注意不要设置硬件I2C，而是直接设置GPIO_OUTPUT**。

## 初始化

```c
OLED_Init();
```

## 换行打印

```c
OLED_Print("Hello,world!");
```
