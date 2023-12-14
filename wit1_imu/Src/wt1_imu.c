#include "wt1_imu.h"

float process_num = 0;

uint16_t AxL;
uint16_t AxH;
uint16_t AyL;
uint16_t AyH;
uint16_t AzL;
uint16_t AzH;

uint16_t WxL;
uint16_t WxH;
uint16_t WyL;
uint16_t WyH;
uint16_t WzL;
uint16_t WzH;

uint16_t RollL;
uint16_t RollH;
uint16_t PitchL;
uint16_t PitchH;
uint16_t YawL;
uint16_t YawH;

int WT_Solve(uint8_t * wit_data,float* Acc,float* AngleSpeed,float* Angle)
{
	if(wit_data[0] != 0x55)
		return 1;
	switch(wit_data[1])
	{
		case 0x51:// 加速度
			// x(short)
			AxL=wit_data[2];
			AxH=wit_data[3];
			process_num=(short)(((short)AxH<<8)|AxL);
			Acc[0]=process_num/32768*16*9.8;
			// y
			AyL=wit_data[4];
			AyH=wit_data[5];
			process_num=(short)(((short)AyH<<8)|AyL);
			Acc[1]=process_num/32768*16*9.8;
			// z
			AzL=wit_data[6];
			AzH=wit_data[7];
			process_num=(short)(((short)AzH<<8)|AzL);
			Acc[2]=process_num/32768*16*9.8;
			break;
		case 0x52:// 角速度
			// x
			WxL=wit_data[2];
			WxH=wit_data[3];
			process_num=(short)(((short)WxH<<8)|WxL);
			AngleSpeed[0]= process_num/32768*2000;
			// y
			WyL=wit_data[4];
			WyH=wit_data[5];
			process_num=(short)(((short)WyH<<8)|WyL);
			AngleSpeed[1]=process_num/32768*2000;
			// z
			WzL=wit_data[6];
			WzH=wit_data[7];
			process_num=(short)(((short)WzH<<8)|WzL);
			AngleSpeed[2]=process_num/32768*2000;
			break;
		case 0x53:// 角度
			// x
			RollL=wit_data[2];
			RollH=wit_data[3];
			process_num=(short)(((short)RollH<<8)|RollL);
			Angle[0]= process_num/32768*180;
			// y
			PitchL=wit_data[4];
			PitchH=wit_data[5];
			process_num=(short)(((short)PitchH<<8)|PitchL);
			Angle[1]=process_num/32768*180;
			// z
			YawL=wit_data[6];
			YawH=wit_data[7];
			process_num=(short)(((short)YawH<<8)|YawL);
			Angle[2]=process_num/32768*180;
			break;
	}
	return 0;
}

