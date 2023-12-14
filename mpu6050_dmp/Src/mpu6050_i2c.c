#include <mpu6050_i2c.h>
#include "stm32f1xx_hal.h"

/* 以下内容移植时需要修改 */
#define RCC_I2C_SDA_ENABLE()    __HAL_RCC_GPIOB_CLK_ENABLE()
#define RCC_I2C_SCL_ENABLE()    __HAL_RCC_GPIOB_CLK_ENABLE()

#define MPU6050_I2C_SCL_PORT 	MPU6050_I2C_SCL_GPIO_Port
#define MPU6050_I2C_SCL_PIN       MPU6050_I2C_SCL_Pin
#define MPU6050_I2C_SDA_PORT 	MPU6050_I2C_SDA_GPIO_Port
#define MPU6050_I2C_SDA_PIN       MPU6050_I2C_SDA_Pin

/* 以上内容移植时需要修改 */

#define I2C_SCL_1()  HAL_GPIO_WritePin(MPU6050_I2C_SCL_PORT, MPU6050_I2C_SCL_PIN, GPIO_PIN_SET)		
#define I2C_SCL_0()  HAL_GPIO_WritePin(MPU6050_I2C_SCL_PORT, MPU6050_I2C_SCL_PIN, GPIO_PIN_RESET)		
#define I2C_SDA_1()  HAL_GPIO_WritePin(MPU6050_I2C_SDA_PORT, MPU6050_I2C_SDA_PIN, GPIO_PIN_SET)		
#define I2C_SDA_0()  HAL_GPIO_WritePin(MPU6050_I2C_SDA_PORT, MPU6050_I2C_SDA_PIN, GPIO_PIN_RESET)		
#define I2C_SDA_READ()  HAL_GPIO_ReadPin(MPU6050_I2C_SDA_PORT, MPU6050_I2C_SDA_PIN)	

void I2CGPIO_Init(void);

static void I2CDelay(void)
{
    uint8_t i;
    
    for (i = 0; i < 10; i++);
}

void I2CStart(void)
{
    I2C_SDA_1();
    I2C_SCL_1();
    I2CDelay();
    I2C_SDA_0();
    I2CDelay();
    I2C_SCL_0();
    I2CDelay();
}

void I2CStop(void)
{
    I2C_SDA_0();
    I2C_SCL_1();
    I2CDelay();
    I2C_SDA_1();
}

void I2CSend_Byte(uint8_t _ucByte)
{
    uint8_t i;

    
    for (i = 0; i < 8; i++)
    {
        if (_ucByte & 0x80)
        {
            I2C_SDA_1();
        }
        else
        {
            I2C_SDA_0();
        }
        I2CDelay();
        I2C_SCL_1();
        I2CDelay();
        I2C_SCL_0();
        if (i == 7)
        {
            I2C_SDA_1(); 
        }
        _ucByte <<= 1;	
        I2CDelay();
    }
}

uint8_t I2CRead_Byte(uint8_t ack)
{
    uint8_t i;
    uint8_t value;
    
    value = 0;
    for (i = 0; i < 8; i++)
    {
        value <<= 1;
        I2C_SCL_1();
        I2CDelay();
        if (I2C_SDA_READ())
        {
            value++;
        }
        I2C_SCL_0();
        I2CDelay();
    }
    if(ack==0)
        I2CNAck();
    else
        I2CAck();
    return value;
}

uint8_t I2CWait_Ack(void)
{
    uint8_t re;

    I2C_SDA_1();	
    I2CDelay();
    I2C_SCL_1();	
    I2CDelay();
    if (I2C_SDA_READ())	
    {
        re = 1;
    }
    else
    {
        re = 0;
    }
    I2C_SCL_0();
    I2CDelay();
    return re;
}

void I2CAck(void)
{
    I2C_SDA_0();	
    I2CDelay();
    I2C_SCL_1();	
    I2CDelay();
    I2C_SCL_0();
    I2CDelay();
    I2C_SDA_1();	
}

void I2CNAck(void)
{
    I2C_SDA_1();	
    I2CDelay();
    I2C_SCL_1();	
    I2CDelay();
    I2C_SCL_0();
    I2CDelay();
}

void I2CGPIO_Init(void)
{

    /* 使用代码初始化 */
    
    /*
        GPIO_InitTypeDef GPIO_InitStructure;

        RCC_I2C_SDA_ENABLE();
        RCC_I2C_SCL_ENABLE();
        
        GPIO_InitStructure.Pin = MPU6050_I2C_SCL_PIN;
        GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD;
        GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(MPU6050_I2C_SCL_PORT, &GPIO_InitStructure);

        
        GPIO_InitStructure.Pin = MPU6050_I2C_SDA_PIN;
        GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD;
        GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(MPU6050_I2C_SDA_PORT, &GPIO_InitStructure);
    */
    I2CStop();
}

uint8_t I2CCheckDevice(uint8_t _Address)
{
    uint8_t ucAck;

    I2CGPIO_Init();		

    I2CStart();		

    
    I2CSend_Byte(_Address|I2CWR);
    ucAck = I2CWait_Ack();	

    I2CStop();			

    return ucAck;
}
