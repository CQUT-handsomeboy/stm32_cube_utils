#ifndef PCA9685_H
#define PCA9685_H

#include <stdint.h>
#include <gpio.h>

#define PCA9685_MODE1 0x0
#define PCA9685_PRESCALE 0xFE
#define PCA9685_adrr 0x40

#define LED0_ON_L 0x6
#define LED0_ON_H 0x7
#define LED0_OFF_L 0x8
#define LED0_OFF_H 0x9

#define ALLLED_ON_L 0xFA
#define ALLLED_ON_H 0xFB
#define ALLLED_OFF_L 0xFC
#define ALLLED_OFF_H 0xFD

#define W_SCL(x)	HAL_GPIO_WritePin(PCA9685_SCL_GPIO_Port,PCA9685_SCL_Pin,x)
#define W_SDA(x)	HAL_GPIO_WritePin(PCA9685_SDA_GPIO_Port,PCA9685_SDA_Pin,x)
#define R_SCL()		HAL_GPIO_ReadPin(PCA9685_SCL_GPIO_Port,PCA9685_SCL_Pin)
#define R_SDA()		HAL_GPIO_ReadPin(PCA9685_SDA_GPIO_Port,PCA9685_SDA_Pin)

/*
 * 关于读地址和写地址的区分
 * 请参考：https://blog.csdn.net/weixin_43242118/article/details/124487590
 * */

#define W_ADDRESS 0x80 // 写地址（八位包含读写位）
#define R_ADDRESS 0x81 // 读地址（八位包含读写位）

void PCA9685_Reset();
void PCA9685_Init();
void PCA9685_SetPWMFreq(float freq);
void PCA9685_SetPWM(uint32_t num,uint32_t on,uint32_t off);
uint8_t PCA9685_Read(uint8_t startAddress);
void PCA9685_Write(uint8_t startAddress, uint8_t buffer);
void I2C_Start();
void I2C_Stop();

#endif
