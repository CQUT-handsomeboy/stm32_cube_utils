## 移植

1.  在Cube中进行GPIO引脚配置，参考代码。

```c
GPIO_InitTypeDef GPIO_InitStructure;

RCC_I2C_SDA_ENABLE();
RCC_I2C_SCL_ENABLE();

GPIO_InitStructure.Pin = MPU6050_I2C_SCL_PIN;
GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH; /* Maximum output speed */
GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD; /* GPIO mode */
HAL_GPIO_Init(MPU6050_I2C_SCL_PORT, &GPIO_InitStructure);


GPIO_InitStructure.Pin = MPU6050_I2C_SDA_PIN;
GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH; /* Maximum output speed */
GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD; /* GPIO mode */
HAL_GPIO_Init(MPU6050_I2C_SDA_PORT, &GPIO_InitStructure);
```

2.  在`mpu6050_i2c.c`中根据实际引脚情况修改软件I2C引脚。

```c
/* 以下内容移植时需要修改 */
#define RCC_I2C_SDA_ENABLE()    __HAL_RCC_GPIOB_CLK_ENABLE()
#define RCC_I2C_SCL_ENABLE()    __HAL_RCC_GPIOB_CLK_ENABLE()

#define MPU6050_I2C_SCL_PORT 	MPU6050_I2C_SCL_GPIO_Port
#define MPU6050_I2C_SCL_PIN       MPU6050_I2C_SCL_Pin
#define MPU6050_I2C_SDA_PORT 	MPU6050_I2C_SDA_GPIO_Port
#define MPU6050_I2C_SDA_PIN       MPU6050_I2C_SDA_Pin
/* 以上内容移植时需要修改 */
```

3.  在`mpu6050.h`中根据实际引脚情况修改地址地址宏定义

```c
/* 以下移植时需要修改 */
/* AD0脚(9脚)接地,I2C地址为0X68(不包含最低位) */
/* AD0脚(9脚)接V3.3,I2C地址为0X69(不包含最低位) */
#define MPU_ADDR					0X68
/* 以上移植时需要修改 */
```

4.  在`mpu6050.h`中，有对延时的宏定义如下。

```c
#define delay_ms				HAL_Delay
```
根据实际情况进行修改。

## 初始化

```c
if( MPU_Init() || mpu_dmp_init() )
{
    /* 初始化失败 */
} else {
    /* 初始化成功 */
}
```

## 获取欧拉角

```c
float pitch,roll,yaw;
while(mpu_dmp_get_data(&pitch, &roll, &yaw)); /* 特别注意 */
/* 此时才能正常使用DMP获取到的数据 */
```
