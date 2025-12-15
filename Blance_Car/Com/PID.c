#include "PID.h"

#define P_Blance    0    //直立环的P系数
#define D_Blance    0    //直立环的D系数

#define P_Speed     0   //直立环的P系数
#define I_Speed     0   //直立环的I系数

#define P_turn      0   //转向环的P系数

//PID算法，P系数*误差值+I系数*误差积分+D系数*误差微分 



//直立环(角度环)
int PID_Blance(float Angle,float Blance_Angle,short gy)
{
    
    return P_Blance*(Angle-Blance_Angle)+D_Blance *gy;
}

//速度环
int PID_Speed(int EncoderA,int EncoderB)
{

    static int Sum_Speed=0;
    static int Last_Speed=0;
	//计算速度偏差
	int Speed=(EncoderA+EncoderB)/2-0;
    //对速度偏差做一个滤波（一阶低通滤波）
    //系数*上次的值+（1-k）*这次的值
    Speed=Speed*0.2+0.8*Last_Speed;
    Last_Speed=Speed;

    //计算积分
    Sum_Speed=Speed+Sum_Speed;

    //65535/2=32767;
    //积分操作一般都要进行限幅
    if(Sum_Speed>10000)
        Sum_Speed=10000;
    else if(Sum_Speed<-10000)
        Sum_Speed=-10000;

    //计算PID
    return P_Speed*Speed+I_Speed*Sum_Speed;

}

//转向环
int PID_Turn(short gz)
{
    return P_turn*(gz-0);
}