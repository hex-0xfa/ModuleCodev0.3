
//这个头文件存放了关于与上位机沟通的I2C的初始化中断，关闭中断和中断函数的定义

#ifndef MODULE_SLAVE_I2C
#define MODULE_SLAVE_I2C

#include "stm32l0xx_hal.h"

void I2C_Slave_Transreceiver_IT_Initialize(I2C_HandleTypeDef *hi2c);            //初始化中断

void I2C_Slave_Transreceiver_IT_Deinitialize(I2C_HandleTypeDef *hi2c);          //关闭中断

void User_Slave_I2C_EV_IRQHandler(I2C_HandleTypeDef *hi2c);                     //处理事件中断


#endif
