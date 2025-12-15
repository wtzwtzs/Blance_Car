#include "Encoder.h"
//获取电机转速
int Get_Encoder(uint8_t timx)
{
  int Encoder_Value=0;

  switch(timx)
  {
    case 2:
       Encoder_Value=(short)__HAL_TIM_GetCounter(&htim2);
       __HAL_TIM_SetCounter(&htim2,0);
        break;
    case 3:
       Encoder_Value=__HAL_TIM_GetCounter(&htim3);
       __HAL_TIM_SetCounter(&htim3,0);
        break; 
    defaule:
        break;
  }
  return Encoder_Value;
}