#include "MPU6050.h"

//写入单个数据
HAL_StatusTypeDef Write_MPU6050(uint8_t Addr,uint8_t Data)
{
    return HAL_I2C_Mem_Write(&hi2c2,0xD0,Addr,I2C_MEMADD_SIZE_8BIT,&Data,1,2000);
}

//写入多个数据
HAL_StatusTypeDef Writes_MPU6050(uint8_t Addr,uint8_t Data,uint8_t size)
{
    return HAL_I2C_Mem_Write(&hi2c2,0xD0,Addr,I2C_MEMADD_SIZE_8BIT,&Data,size,2000);
}

//读取单个数据
HAL_StatusTypeDef Read_MPU6050(uint8_t Addr,uint8_t *Data)
{
    return HAL_I2C_Mem_Read(&hi2c2,0xD0,Addr,I2C_MEMADD_SIZE_8BIT,Data,1,2000);
}

//读取多个数据
HAL_StatusTypeDef Reads_MPU6050(uint8_t Addr,uint8_t *Data,uint8_t size)
{
    return HAL_I2C_Mem_Read(&hi2c2,0xD0,Addr,I2C_MEMADD_SIZE_8BIT,Data,size,2000);
}

void MPU6050_Init(void)
{
    //MPU6050复位
    Write_MPU6050(0x6B,0x80);
    HAL_Delay(300);
    //唤醒MPU6050
    Write_MPU6050(0x6B,0x00);

    //设置MPU6050的角速度量程
    Write_MPU6050(0x1B,0x18);

    //设置MPU6050加速度的量程
    Write_MPU6050(0x1C,0x00);

    //关闭中断
    Write_MPU6050(0x38,0x00);

    //关闭FIFO
    Write_MPU6050(0x23,0x00);

    //关闭第二IIC
    Write_MPU6050(0x6A,0x00);
    
    //读取MPU6050的地址
    uint8_t ID;
    Read_MPU6050(0x75,&ID);
    printf("ID=0x%x",ID);

    //设置MPU6050的时钟源
    Write_MPU6050(0x6B,0x01);

}
void Set_DLPF(uint8_t Rate)
{
  
    Write_MPU6050(0x1A,3);
}

void MPU6050_Sample_Rate(uint8_t Sample_Rate)
{
    uint8_t SMPLRT_DIV=0;
    //MPU6050的采样频率=陀螺仪的输出速率/(1+ SMPLRT_DIV)
    //所以 SMPLRT_DIV=陀螺仪的输出速率/MPU6050的采样频率-1
    SMPLRT_DIV=1000/Sample_Rate-1;
    Write_MPU6050(0x19,SMPLRT_DIV);

    //设置数字的低通滤波
    Set_DLPF(Sample_Rate);

    //使能角速度寄存器和加速度寄存器
     Write_MPU6050(0x6C,0x00);
}

void Get_Gyroscope(short *gx,short *gy,short *gz)
{
    uint8_t Buff[6];
    Reads_MPU6050(0x43,Buff,6);
    *gx=((short)Buff[0]<<8)|Buff[1];
    *gy=((short)Buff[2]<<8)|Buff[3];
    *gz=((short)Buff[4]<<8)|Buff[5];
  
}
void Get_Accelerometer (short *ax,short *ay,short *az)
{
    uint8_t Buff[6];
    Reads_MPU6050(0x3B,Buff,6);
    *ax=((short)Buff[0]<<8)|Buff[1];
    *ay=((short)Buff[2]<<8)|Buff[3];
    *az=((short)Buff[4]<<8)|Buff[5];
  
}



/*卡尔曼滤波进行角度测量 
*输入用加速度计算出来的角度和MPU6050测量出来的y轴角速度给卡尔曼滤波进行测算
*输出一个预测的角度值
*/
void KalMan()
{

}

