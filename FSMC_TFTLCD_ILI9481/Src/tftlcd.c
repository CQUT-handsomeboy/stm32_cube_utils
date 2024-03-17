#include "tftlcd.h"
#include "stdint.h"
#include "main.h"
#include "stdio.h"
#include "tftlcd_fonts.h"

void TFT_WriteCmd(uint16_t cmd)
{
    *(__IO uint16_t *)(0x6C000000) = cmd;
}

void TFT_WriteData(uint16_t dat)
{
    *(__IO uint16_t *)(0x6C000080) = dat;
}

uint16_t TFT_ReadData()
{
	return *(__IO uint16_t *)(0x6C000800);
}	

uint16_t TFT_ReadID(void)
{
		uint16_t id;
		HAL_Delay(20);
		TFT_WriteCmd(0Xd3);	
		id = TFT_ReadData();
		id = TFT_ReadData();
		id = TFT_ReadData();
		id <<= 8;
		id |= TFT_ReadData();
		return id;
}

void TFT_Init()
{
	TFT_WriteCmd(0xFF);
	TFT_WriteCmd(0xFF);
	HAL_Delay(5);

	TFT_WriteCmd(0xFF);
	TFT_WriteCmd(0xFF);
	TFT_WriteCmd(0xFF);
	TFT_WriteCmd(0xFF);
	HAL_Delay(10);
	
	TFT_WriteCmd(0xB0);
	TFT_WriteData(0x00);
	
	TFT_WriteCmd(0xB3);
	TFT_WriteData(0x02);
	TFT_WriteData(0x00);
	TFT_WriteData(0x00);
	TFT_WriteData(0x00);
	
	TFT_WriteCmd(0xC0);
	TFT_WriteData(0x13);
	TFT_WriteData(0x3B);//480
	TFT_WriteData(0x00);
	TFT_WriteData(0x00);
	TFT_WriteData(0x00);
	TFT_WriteData(0x01);
	TFT_WriteData(0x00);//NW
	TFT_WriteData(0x43);
	
	TFT_WriteCmd(0xC1);
	TFT_WriteData(0x08);
	TFT_WriteData(0x1B);//CLOCK
	TFT_WriteData(0x08);
	TFT_WriteData(0x08);
	
	TFT_WriteCmd(0xC4);
	TFT_WriteData(0x11);
	TFT_WriteData(0x01);
	TFT_WriteData(0x73);
	TFT_WriteData(0x01);
	
	TFT_WriteCmd(0xC6);
	TFT_WriteData(0x00);
	
	TFT_WriteCmd(0xC8);
	TFT_WriteData(0x0F);
	TFT_WriteData(0x05);
	TFT_WriteData(0x14);
	TFT_WriteData(0x5C);
	TFT_WriteData(0x03);
	TFT_WriteData(0x07);
	TFT_WriteData(0x07);
	TFT_WriteData(0x10);
	TFT_WriteData(0x00);
	TFT_WriteData(0x23);
	
	TFT_WriteData(0x10);
	TFT_WriteData(0x07);
	TFT_WriteData(0x07);
	TFT_WriteData(0x53);
	TFT_WriteData(0x0C);
	TFT_WriteData(0x14);
	TFT_WriteData(0x05);
	TFT_WriteData(0x0F);
	TFT_WriteData(0x23);
	TFT_WriteData(0x00);
	
	TFT_WriteCmd(0x35);
	TFT_WriteData(0x00);
	
	TFT_WriteCmd(0x44);
	TFT_WriteData(0x00);
	TFT_WriteData(0x01);
	
	TFT_WriteCmd(0xD0);
	TFT_WriteData(0x07);
	TFT_WriteData(0x07);//VCI1
	TFT_WriteData(0x1D);//VRH
	TFT_WriteData(0x03);//BT
	
	TFT_WriteCmd(0xD1);
	TFT_WriteData(0x03);
	TFT_WriteData(0x5B);//VCM
	TFT_WriteData(0x10);//VDV
	
	TFT_WriteCmd(0xD2);
	TFT_WriteData(0x03);
	TFT_WriteData(0x24);
	TFT_WriteData(0x04);

	TFT_WriteCmd(0x2A);
	TFT_WriteData(0x00);
	TFT_WriteData(0x00);
	TFT_WriteData(0x01);
	TFT_WriteData(0x3F);//320
	
	TFT_WriteCmd(0x2B);
	TFT_WriteData(0x00);
	TFT_WriteData(0x00);
	TFT_WriteData(0x01);
	TFT_WriteData(0xDF);//480

	TFT_WriteCmd(0x36);
	TFT_WriteData(0x00);

	TFT_WriteCmd(0xC0);
	TFT_WriteData(0x13);

	TFT_WriteCmd(0x3A);
	TFT_WriteData(0x55);

	TFT_WriteCmd(0x11);
	HAL_Delay(150);
	
	TFT_WriteCmd(0x29);
	HAL_Delay(30);
		
	TFT_WriteCmd(0x2C);
}

void TFT_WriteCmdData(uint16_t cmd,uint16_t data)
{
	TFT_WriteCmd(cmd);
	TFT_WriteData(data);
}

void TFT_WriteData_Color(uint16_t color)
{
	TFT_WriteData(color);
}

void TFT_Clear(uint16_t color)
{
	uint16_t i, j ;

	TFT_Set_Window(0, 0, WIDTH-1,HEIGHT-1);	 //作用区域
  	for(i=0; i<WIDTH; i++)
	{
		for (j=0; j<HEIGHT; j++)
		{
			TFT_WriteData_Color(color);
		}
	} 
}

//设置窗口,并自动设置画点坐标到窗口左上角(sx,sy).
//sx,sy:窗口起始坐标(左上角)
//width,height:窗口宽度和高度,必须大于0!!
//窗体大小:width*height. 
void TFT_Set_Window(uint16_t sx,uint16_t sy,uint16_t width,uint16_t height)
{
	TFT_WriteCmd(0x2A);
	TFT_WriteData(sx/256);   
	TFT_WriteData(sx%256); 	 
	TFT_WriteData(width/256); 
	TFT_WriteData(width%256);
	
	TFT_WriteCmd(0x2B);
	TFT_WriteData(sy/256);  
	TFT_WriteData(sy%256);
	TFT_WriteData(height/256); 
	TFT_WriteData(height%256); 	

	TFT_WriteCmd(0x2C);
}

void TFT_DrawFRONT_COLOR(uint16_t x,uint16_t y,uint16_t color)
{	   
	TFT_Set_Window(x, y, x, y);
	TFT_WriteData_Color(color);	
}

//在指定位置显示一个字符
//x,y:起始坐标
//num:要显示的字符:" "--->"~"
//size:字体大小 12/16/24
//mode:叠加方式(1)还是非叠加方式(0)
void TFT_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint8_t size,uint8_t mode)
{  							  
    uint8_t temp,t1,t;
	uint16_t y0=y;
	uint8_t csize=(size/8+((size%8)?1:0))*(size/2);		//得到字体一个字符对应点阵集所占的字节数	
 	num=num-' ';//得到偏移后的值（ASCII字库是从空格开始取模，所以-' '就是对应字符的字库）
	for(t=0;t<csize;t++)
	{   
		if(size==12)temp=ascii_1206[num][t]; 	 	//调用1206字体
		else if(size==16)temp=ascii_1608[num][t];	//调用1608字体
		else if(size==24)temp=ascii_2412[num][t];	//调用2412字体
		else return;								//没有的字库
		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)TFT_DrawFRONT_COLOR(x,y,FRONT_COLOR);
			else if(mode==0)TFT_DrawFRONT_COLOR(x,y,BACK_COLOR);
			temp<<=1;
			y++;
			if(y>=HEIGHT)return;		//超区域了
			if((y-y0)==size)
			{
				y=y0;
				x++;
				if(x>=HEIGHT)return;	//超区域了
				break;
			}
		}  	 
	}  	    	   	 	  
}

//显示字符串
//x,y:起点坐标
//width,height:区域大小  
//size:字体大小
//*p:字符串起始地址		  
void TFT_ShowString(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t size,uint8_t *p)
{         
	uint8_t x0=x;
	width+=x;
	height+=y;
    while((*p<='~')&&(*p>=' '))//判断是不是非法字符!
    {       
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;//退出
        TFT_ShowChar(x,y,*p,size,0);
        x+=size/2;
        p++;
    }  
}