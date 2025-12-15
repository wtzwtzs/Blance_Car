#include "App_Car.h"

short ax=0,ay=0,az=0,gx=0,gy=0,gz=0;
float angle;
float Accele_Angle=0;
float actual_gy=0;
int Encoder_A,Encoder_B;
void Get_Kalman_Angle()
{
    
    //通过加速度获取当前的角度
    Get_Accelerometer(&ax,&ay,&az);
    Accele_Angle=atan2(ax,az)*180/PI;

    //获取当前y轴的角速度
    Get_Gyroscope(&gx,&gy,&gz);
    printf("gy=%d\n",gy);
    actual_gy=-gy/16.4;

    //卡曼滤波后的角度
    Com_Filter_Kalman(Accele_Angle,actual_gy);

   //在计算角度的时候 加速度计算的角度符号和角速度的符号是否一致
}



void Show_Informain(void)
{ 
    /*--------------------数据获取--------------------*/
    //获取电压
    float V_St;
    char V_Buff[5];
    float V;
    V_St=Get_V();
    printf("%f",V_St);
    sprintf(V_Buff,"%.1f",V_St);

    //获取电机转速
    char EncoderA_Buff[10],EncoderB_Buff[10];
    Encoder_A=Get_Encoder(2);
    Encoder_B=Get_Encoder(3);
    sprintf(EncoderA_Buff,"%d",Encoder_A);
    sprintf(EncoderB_Buff,"%d",Encoder_B);
   
    //获取滤波后的倾斜角度
    char Angle_Buff[5];
    sprintf(Angle_Buff,"%.1f",angle);

    /*--------------------数据显示--------------------*/
    //显示当前电压
    OLED_ShowString(0,0,"V:    V",16,1);
    OLED_ShowString(16,0,V_Buff,16,1);
   
    //显示电机速度
    OLED_ShowString(0,16,"EA:",16,1);
    OLED_ShowString(0,32,"EB:",16,1);
    OLED_ShowString(24,16,EncoderA_Buff,16,1);
    OLED_ShowString(24,32,EncoderB_Buff,16,1);

    //显示当前的倾斜角度
    OLED_ShowString(0,48,"Angle:",16,1);
    OLED_ShowString(48,48,Angle_Buff,16,1);
    OLED_Refresh();
}


void Car_PID()
{
    int Blance_Out=0;
    int Speed_Out=0;
    int Turn_Out=0;
    int PWMA=0,PWMB=0;
    //直立环的控制
    Blance_Out=PID_Blance(angle,0,gy);
    //速度环的控制
    Speed_Out=PID_Speed(Encoder_A,Encoder_B);
    //转向环的控制
    Turn_Out=PID_Turn(gz);
    
    //叠加PID的结果，作用到电机中
    PWMA=Blance_Out+Speed_Out+Turn_Out;
    PWMB=Blance_Out+Speed_Out-Turn_Out;
    TB6612_SetPWM(PWMA,PWMB);
}


// 为什么选择蓝牙 功耗 距离 速率