#include "stm32f1xx_hal.h"
#include "mpu6050.h"
uint8_t MPU_Init(void)
{
    uint8_t res;

    MPU_I2CInit();
    MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X80);	
    delay_ms(100);
    MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X00);	
    MPU_Set_Gyro_Fsr(3);					
    MPU_Set_Accel_Fsr(0);					
    MPU_Set_Rate(50);						
    MPU_Write_Byte(MPU_INT_EN_REG,0X00);	
    MPU_Write_Byte(MPU_USER_CTRL_REG,0X00);	
    MPU_Write_Byte(MPU_FIFO_EN_REG,0X00);	
    MPU_Write_Byte(MPU_INTBP_CFG_REG,0X80);	
    res=MPU_Read_Byte(MPU_DEVICE_ID_REG);
    if(res==MPU_ADDR)
    {
        MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X01);	
        MPU_Write_Byte(MPU_PWR_MGMT2_REG,0X00);	
        MPU_Set_Rate(50);						
    } else return 1;
    return 0;
}

uint8_t MPU_Set_Gyro_Fsr(uint8_t fsr)
{
    return MPU_Write_Byte(MPU_GYRO_CFG_REG,fsr<<3);
}

uint8_t MPU_Set_Accel_Fsr(uint8_t fsr)
{
    return MPU_Write_Byte(MPU_ACCEL_CFG_REG,fsr<<3);
}

uint8_t MPU_Set_LPF(uint16_t lpf)
{
    uint8_t data=0;
    if(lpf>=188)data=1;
    else if(lpf>=98)data=2;
    else if(lpf>=42)data=3;
    else if(lpf>=20)data=4;
    else if(lpf>=10)data=5;
    else data=6;
    return MPU_Write_Byte(MPU_CFG_REG,data);
}

uint8_t MPU_Set_Rate(uint16_t rate)
{
    uint8_t data;
    if(rate>1000)rate=1000;
    if(rate<4)rate=4;
    data=1000/rate-1;
    data=MPU_Write_Byte(MPU_SAMPLE_RATE_REG,data);	
    return MPU_Set_LPF(rate/2);	
}

short MPU_Get_Temperature(void)
{
    uint8_t buf[2];
    short raw;
    float temp;
    MPU_Read_Len(MPU_ADDR,MPU_TEMP_OUTH_REG,2,buf);
    raw=((uint16_t)buf[0]<<8)|buf[1];
    temp=36.53+((double)raw)/340;
    return temp * 100;
}

uint8_t MPU_Get_Gyroscope(short *gx,short *gy,short *gz)
{
    uint8_t buf[6],res;
    res=MPU_Read_Len(MPU_ADDR,MPU_GYRO_XOUTH_REG,6,buf);
    if(res==0)
    {
        *gx=((uint16_t)buf[0]<<8)|buf[1];
        *gy=((uint16_t)buf[2]<<8)|buf[3];
        *gz=((uint16_t)buf[4]<<8)|buf[5];
    }
    return res;;
}

uint8_t MPU_Get_Accelerometer(short *ax,short *ay,short *az)
{
    uint8_t buf[6],res;
    res=MPU_Read_Len(MPU_ADDR,MPU_ACCEL_XOUTH_REG,6,buf);
    if(res==0)
    {
        *ax=((uint16_t)buf[0]<<8)|buf[1];
        *ay=((uint16_t)buf[2]<<8)|buf[3];
        *az=((uint16_t)buf[4]<<8)|buf[5];
    }
    return res;;
}

uint8_t MPU_Write_Len(uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf)
{
    uint8_t i;
    MPU_I2CStart();
    MPU_I2CSend_Byte((addr<<1)|0);
    if(MPU_I2CWait_Ack())	
    {
        MPU_I2CStop();
        return 1;
    }
    MPU_I2CSend_Byte(reg);	
    MPU_I2CWait_Ack();		
    for(i=0; i<len; i++)
    {
        MPU_I2CSend_Byte(buf[i]);	
        if(MPU_I2CWait_Ack())		
        {
            MPU_I2CStop();
            return 1;
        }
    }
    MPU_I2CStop();
    return 0;
}

uint8_t MPU_Read_Len(uint8_t addr,uint8_t reg,uint8_t len,uint8_t *buf)
{
    MPU_I2CStart();
    MPU_I2CSend_Byte((addr<<1)|0);
    if(MPU_I2CWait_Ack())	
    {
        MPU_I2CStop();
        return 1;
    }
    MPU_I2CSend_Byte(reg);	
    MPU_I2CWait_Ack();		
    MPU_I2CStart();
    MPU_I2CSend_Byte((addr<<1)|1);
    MPU_I2CWait_Ack();		
    while(len)
    {
        if(len==1)*buf=MPU_I2CRead_Byte(0);
        else *buf=MPU_I2CRead_Byte(1);		
        len--;
        buf++;
    }
    MPU_I2CStop();	
    return 0;
}

uint8_t MPU_Write_Byte(uint8_t reg,uint8_t data)
{
    MPU_I2CStart();
    MPU_I2CSend_Byte((MPU_ADDR<<1)|0);
    if(MPU_I2CWait_Ack())	
    {
        MPU_I2CStop();
        return 1;
    }
    MPU_I2CSend_Byte(reg);	
    MPU_I2CWait_Ack();		
    MPU_I2CSend_Byte(data);
    if(MPU_I2CWait_Ack())	
    {
        MPU_I2CStop();
        return 1;
    }
    MPU_I2CStop();
    return 0;
}

uint8_t MPU_Read_Byte(uint8_t reg)
{
    uint8_t res;
    MPU_I2CStart();
    MPU_I2CSend_Byte((MPU_ADDR<<1)|0);
    MPU_I2CWait_Ack();		
    MPU_I2CSend_Byte(reg);	
    MPU_I2CWait_Ack();		
    MPU_I2CStart();
    MPU_I2CSend_Byte((MPU_ADDR<<1)|1);
    MPU_I2CWait_Ack();		
    res=MPU_I2CRead_Byte(0);
    MPU_I2CStop();			
    return res;
}
