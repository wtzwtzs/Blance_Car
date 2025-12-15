#ifndef __MPU6050_H
#define __MPU6050_H
#include "main.h"
#include "i2c.h"
#include "usart.h"

void MPU6050_Init(void);
void MPU6050_Sample_Rate(uint8_t Sample_Rate);
void Get_Gyroscope(short *gx,short *gy,short *gz);
void Get_Accelerometer (short *ax,short *ay,short *az);


#endif
