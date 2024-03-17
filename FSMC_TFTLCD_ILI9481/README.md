# 移植指南

适用于光电系发给同学们的STM32普中天马F407开发板。

[普中官方给出的资料链接](https://pan.baidu.com/s/18CDb67p1YA4mzYdj1k-V_w?pwd=1234)

CubeMX上配置FSMC。

根据原理图选中`NE4`和`A6`，数据宽度选择`16bits`。

![](../.resoures/fsmc_cubemx_config.png)

生成代码。

将驱动添加到工程中，即可使用。