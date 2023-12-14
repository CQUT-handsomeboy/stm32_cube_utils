#ifndef _I2CH
#define _I2CH

#include <inttypes.h>
#include "gpio.h"

#define I2CWR	0
#define I2CRD	1

void I2CStart(void);
void I2CStop(void);
void I2CSend_Byte(uint8_t _ucByte);
uint8_t I2CRead_Byte(uint8_t ack);
uint8_t I2CWait_Ack(void);
void I2CAck(void);
void I2CNAck(void);
uint8_t I2CCheckDevice(uint8_t _Address);
void I2CGPIO_Init(void);

#endif
