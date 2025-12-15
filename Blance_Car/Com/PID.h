#ifndef __PID_H
#define __PID_H
#include "main.h"
#include <math.h>


//直立环(角度环)
int PID_Blance(float Angle,float Blance_Angle,short gy);

//速度环
int PID_Speed(int EncoderA,int EncoderB);

//转向环
int PID_Turn(short gz);
#endif
