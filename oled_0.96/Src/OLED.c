#include "gpio.h"
#include "main.h"

#include "OLED_Font.h"
#include "OLED.h"
#include "i2c.h"

#define OLED_SCL_PORT OLEDSCL_GPIO_Port
#define OLED_SCL_PIN	OLEDSCL_Pin
#define OLED_SDA_PORT OLEDSDA_GPIO_Port
#define OLED_SDA_PIN	OLEDSDA_Pin

#define OLED_W_SCL(x) 	HAL_GPIO_WritePin(OLED_SCL_PORT, OLED_SCL_PIN, (GPIO_PinState)(x))
#define OLED_W_SDA(x)	HAL_GPIO_WritePin(OLED_SDA_PORT, OLED_SDA_PIN, (GPIO_PinState)(x))

uint8_t OLED_GRAM[128][8];

/* OLEDI2C开始 */
void OLED_I2C_Start(void)
{
	OLED_W_SDA(1);
	OLED_W_SCL(1);
	OLED_W_SDA(0);
	OLED_W_SCL(0);
}

/* OLEDI2C结束 */
void OLED_I2C_Stop(void)
{
	OLED_W_SDA(0);
	OLED_W_SCL(1);
	OLED_W_SDA(1);
}

/* OLEDI2C发送字节 */
void OLED_I2C_SendByte(uint8_t Byte)
{
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		OLED_W_SDA(Byte & (0x80 >> i));
		OLED_W_SCL(1);
		OLED_W_SCL(0);
	}
	OLED_W_SCL(1);	//额外的一个时钟，不处理应答信号
	OLED_W_SCL(0);
}

#ifdef OLED_SOFTWARE_I2C
/* 软件I2C */

/* OLEDI2C发送命令 */
void OLED_WriteCommand(uint8_t Command)
{
	OLED_I2C_Start();
	OLED_I2C_SendByte(0x78);		//从机地址
	OLED_I2C_SendByte(0x00);		//写命令
	OLED_I2C_SendByte(Command); 
	OLED_I2C_Stop();
}

/* OLEDI2C写数据 */
void OLED_WriteData(uint8_t Data)
{
	OLED_I2C_Start();
	OLED_I2C_SendByte(0x78);		//从机地址
	OLED_I2C_SendByte(0x40);		//写数据
	OLED_I2C_SendByte(Data);
	OLED_I2C_Stop();
}

#endif

#ifdef OLED_HARDWARE_I2C
/* 硬件I2C */

/* OLEDI2C发送命令 */
void OLED_WriteCommand(uint8_t cmd)
{
	uint8_t sendBuffer[2] = {0x00,cmd};
	HAL_I2C_Master_Transmit(&hi2c1,OLED_ADDRESS,sendBuffer,2,HAL_MAX_DELAY);
}

/* OLEDI2C写数据 */
void OLED_WriteData(uint8_t data)
{
	uint8_t sendBuffer[2] = {0x40,data};
	HAL_I2C_Master_Transmit(&hi2c1,OLED_ADDRESS,sendBuffer,2,HAL_MAX_DELAY);
}

#endif

/* OLEDI2C刷新屏幕 */
void OLED_Refresh(void)
{
	uint8_t i,n;
	for( i=0 ; i<8 ; i++ )
	{
		OLED_WriteCommand(0xB0 + i);
		OLED_WriteCommand(0x00);
		OLED_WriteCommand(0x10);
		OLED_I2C_Start();
		OLED_I2C_SendByte(0x78);
		OLED_I2C_SendByte(0x40);
		for(n=0;n<128;n++)
		{
			OLED_I2C_SendByte(OLED_GRAM[n][i]);
		}
		OLED_I2C_Stop();
  }
}

/* OLEDI2C设置光标位置 */
void OLED_SetCursor(uint8_t Y, uint8_t X)
// Y 页地址
// X 列地址
{
	OLED_WriteCommand(0xB0 | Y);					//设置Y
	OLED_WriteCommand(0x10 | ((X & 0xF0) >> 4));	//设置X高4位
	OLED_WriteCommand(0x00 | (X & 0x0F));			//设置X低4位
}

/* OLEDI2C清屏 */
void OLED_Clear(void)
{  
	uint8_t i, j;
	for (j = 0; j < 8; j++)
	{
		OLED_SetCursor(j, 0);
		for(i = 0; i < 128; i++)
		{
			OLED_WriteData(0x00);
		}
	}
}

/* OLEDI2C显示字符 */
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char)
// line 1->4
// column 1->16
{
	uint8_t i;
	OLED_SetCursor((Line - 1) * 2, (Column - 1) * 8);		//设置光标位置在上半部分
	for (i = 0; i < 8; i++)
	{
		OLED_WriteData(OLED_F8x16[Char - ' '][i]);			//显示上半部分内容
	}
	OLED_SetCursor((Line - 1) * 2 + 1, (Column - 1) * 8);	//设置光标位置在下半部分
	for (i = 0; i < 8; i++)
	{
		OLED_WriteData(OLED_F8x16[Char - ' '][i + 8]);		//显示下半部分内容
	}
}

/* OLEDI2C打印 */
void OLED_Print(char * String)
{
	uint8_t i = 0,line,column;
	for( i = 0 ;(String[i] != '\0') && ( i < 64); i++ )
	{
		line = i / 16 + 1;
		column = i % 16 + 1;
		OLED_ShowChar(line, column, String[i]);
	}
}

/* OLEDI2C初始化 */
void OLED_Init(void)
{
	uint32_t i, j;
	
	for (i = 0; i < 1000; i++)			//上电延时
	{
		for (j = 0; j < 1000; j++);
	}

	OLED_WriteCommand(0xAE);	//关闭显示
	
	OLED_WriteCommand(0xD5);	//设置显示时钟分频比/振荡器频率
	OLED_WriteCommand(0x80);
	
	OLED_WriteCommand(0xA8);	//设置多路复用率
	OLED_WriteCommand(0x3F);
	
	OLED_WriteCommand(0xD3);	//设置显示偏移
	OLED_WriteCommand(0x00);
	
	OLED_WriteCommand(0x40);	//设置显示开始行
	
	OLED_WriteCommand(0xA1);	//设置左右方向，0xA1正常 0xA0左右反置
	
	OLED_WriteCommand(0xC8);	//设置上下方向，0xC8正常 0xC0上下反置

	OLED_WriteCommand(0xDA);	//设置COM引脚硬件配置
	OLED_WriteCommand(0x12);
	
	OLED_WriteCommand(0x81);	//设置对比度控制
	OLED_WriteCommand(0xCF);

	OLED_WriteCommand(0xD9);	//设置预充电周期
	OLED_WriteCommand(0xF1);

	OLED_WriteCommand(0xDB);	//设置VCOMH取消选择级别
	OLED_WriteCommand(0x30);

	OLED_WriteCommand(0xA4);	//设置整个显示打开/关闭

	OLED_WriteCommand(0xA6);	//设置正常/倒转显示

	OLED_WriteCommand(0x8D);	//设置充电泵
	OLED_WriteCommand(0x14);

	OLED_WriteCommand(0xAF);	//开启显示
		
	OLED_Clear();				//OLED清屏
}
