## 移植

> [!NOTE]  
> 在advenced选项中选择为每个外设生成头文件。

### 软件I2C

在CubemMX中把软件I2C的两个引脚对应的User Label修改成`OLEDSDA`和`OLEDSCL`，配置GPIO口为高速输出模式，

### 硬件I2C

在CubemMX中配置硬件I2C，文件中以I2C1为例，需要请自行修改。

## 初始化

```c
OLED_Init();
```

## 换行打印

```c
OLED_Print("Hello,world!");
```
