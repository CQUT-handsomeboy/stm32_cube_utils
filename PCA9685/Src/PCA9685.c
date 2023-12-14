#include "PCA9685.h"

/* PCA9685复位函数 */
void PCA9685_Reset()
{
    PCA9685_Write(PCA9685_MODE1,0x00);
}

/*  PCA9685启动函数 */
void PCA9685_Init()
{
    PCA9685_Reset();
}

/* 设置PWM信号的频率 */
void PCA9685_SetPWMFreq(float freq)
{
    uint32_t prescale,oldmode,newmode;
    float prescaleval;
    
    freq *= 0.92;  // 修正频率设置中的过冲
    
    prescaleval = 25000000;
    prescaleval /= 4096;
    prescaleval /= freq;
    prescaleval -= 1;
    
    prescale = floor(prescaleval + 0.5);
    
    oldmode = PCA9685_Read(PCA9685_MODE1);
    newmode = (oldmode&0x7F) | 0x10; // 进入睡眠模式
    PCA9685_Write(PCA9685_MODE1, newmode); // 进入睡眠模式
    PCA9685_Write(PCA9685_PRESCALE, prescale); // 设置预分频器
    PCA9685_Write(PCA9685_MODE1, oldmode);
    PCA9685_Write(PCA9685_MODE1, oldmode | 0xa1);
}

/* 设置指定通道的PWM信号的占空比 */
void PCA9685_SetPWM(uint32_t num,uint32_t on,uint32_t off)
{
    PCA9685_Write(LED0_ON_L+4*num,on);
    PCA9685_Write(LED0_ON_H+4*num,on>>8);
    PCA9685_Write(LED0_OFF_L+4*num,off);
    PCA9685_Write(LED0_OFF_H+4*num,off>>8);
}

/* 从指定地址读取一个字节的数据 */
uint8_t PCA9685_Read(uint8_t startAddress) 
{
	I2C_Start();
	I2C_SendByte(W_ADDRESS);	//从机地址 写控制码
	I2C_SendByte(startAddress); //寄存器地址
	I2C_Start();
	I2C_SendByte(R_ADDRESS); 	//从机地址 读控制码

	uint8_t data = 0x00;
	short i = 7;
	for(i = 7;i >= 0;i--)
	{
		W_SCL(1);
		data |= ((R_SDA()) << i);
		W_SCL(0);
	}
	return data;
}

/* 向指定地址写入一个字节的数据 */
void PCA9685_Write(uint8_t startAddress, uint8_t buffer) 
{
	I2C_Start();
	I2C_SendByte(W_ADDRESS);	//从机地址 写控制码
	I2C_SendByte(startAddress);	//寄存器地址
	I2C_SendByte(buffer);		//写入数据
	I2C_Stop();
}

void I2C_Start()
{
	W_SDA(1);
	W_SCL(1);
	W_SDA(0);
	W_SCL(0);
}

void I2C_Stop()
{
	W_SDA(0);
	W_SCL(1);
	W_SDA(1);
}

void I2C_SendByte(uint8_t Byte)
{
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		W_SDA(Byte & (0x80 >> i));
		W_SCL(1);
		W_SCL(0);
	}
	W_SCL(1);
	W_SCL(0);
}
