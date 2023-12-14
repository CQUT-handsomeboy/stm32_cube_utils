在使用CubeMX生成代码的时候，将软件I2C的相应引脚的`User Label`设为`OLEDSCL`和`OLEDSDA`，并将其`Maximum output speed`设置为`Very High`。

在`Project Manager`的`Code Generator`中勾选`Generate peripheral initialization as a pair of '.c/.h' files per peripheral`。

```c
OLED_Init();
OLED_Clear();
OLED_ShowString(0,0,"Hello world",12);
```