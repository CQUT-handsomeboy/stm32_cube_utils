#ifndef WT1_IMU_H
#define WT1_IMU_H

#include "stdint.h"

int WT_Solve(uint8_t * wit_data,float* Acc,float* AngleSpeed,float* Angle);

#endif