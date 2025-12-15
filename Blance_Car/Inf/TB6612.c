#include "TB6612.H"
#define     Go      0
#define     Back    1
#define     Stop    2


//控制电机A的方向
void Set_MotorA_Dri(uint8_t Driection)
{
    switch(Driection)
    {
        
        case 0:
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);
            break;

        case 1:
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
            break;
        
        case 2:
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
            break;

        default:
            break;
    }
}

//控制电机A的方向
void Set_MotorB_Dri(uint8_t Driection)
{
    switch(Driection)
    {
        
        case 0:
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET);
            break;

        case 1:
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_RESET);
            break;
        
        case 2:
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_RESET);
            break;

        default:
            break;
    }
}

//设置PWM的转速 符号代表方向
void TB6612_SetPWM(int PWMA,int PWMB)
{
    /*----------电机A的方向和转速-----------*/
    //判断电机A的方向
    if(PWMA > 0)
    {
        //前进
        Set_MotorA_Dri(Go);
    }
    else if(PWMA < 0)
    {
        //后退
        Set_MotorA_Dri(Back);
    }
    else
    {
        //停止
        Set_MotorA_Dri(Stop);
    }

    //设置PWM的值(转速)
    __HAL_TIM_SetCompare(&htim4,TIM_CHANNEL_4,abs(PWMA));



    /*----------电机B的方向和转速-----------*/
    //鎺у埗鏂瑰悜
    if(PWMB > 0)
    {
        //瑕佹?ｈ浆
        Set_MotorB_Dri(Go);
    }
    else if(PWMB < 0)
    {
        //瑕佺炕杞?
        Set_MotorB_Dri(Back);
    }
    else
    {
        //鍋滄??
        Set_MotorB_Dri(Stop);
    }

    //璁剧疆PWM鐨勫�?
    __HAL_TIM_SetCompare(&htim4,TIM_CHANNEL_3,abs(PWMB));

}


