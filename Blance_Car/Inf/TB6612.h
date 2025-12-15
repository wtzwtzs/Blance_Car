#ifndef __TB6612_H
#define __TB6612_H
#include "stm32f1xx_hal.h";
#include "tim.h"
#include <stdio.h>
#include <stdlib.h>

//设置PWM(既要设置转速还要设置方向，传入的CCR的值带有符号 符号代表方向)
void TB6612_SetPWM(int PWMA,int PWMB);


#endif
