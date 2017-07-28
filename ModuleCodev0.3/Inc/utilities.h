
//这个头文件存放了一些公用函数和GPIO函数的定义

#ifndef UTILITIES
#define UTILITIES

#include "stdint.h"
#include "stm32l0xx_hal.h"

//清空数组
void EmptyBuffer(uint8_t* a);

//关于温度的函数
uint16_t GetTemperature (ADC_HandleTypeDef *hadc);      //获取温度
void    SetLatchTempHighAlarm(ADC_HandleTypeDef *hadc); //设置高温警告
uint8_t GetLatchTempHighAlarm(void);                    //获取高温警告
void    ClearLatchTempHighAlarm(void);                  //清空高温警告

//关于ModselL的函数
uint8_t IsModSelL(void);                                //检测ModSelL

//关于IntL的函数
void Assert_IntL(void);                                 //断言IntL
void Deassert_IntL(void);                               //反断言IntL
void GetIntL(void);                                     //检测IntL

//关于Data_Not_Ready的函数
void Data_Ready(void);                                  //数据准备完成
void Data_Not_Ready(void);                              //数据未准备完成

//关于LPMode的函数
uint8_t IsLPMode(void);                                 //是否低功耗模式
void LowPowerMode(void);                                //进入低功耗模式
void NormalPowerMode(void);                             //进入正常功耗模式
uint8_t IsLPMode_Overriade(void);                       //LPMode是否被覆盖

//关于pin TX-DISABLE 的函数
void Tx_Pin_Disable(void);                              //失能Tx-dis pin
void Tx_Pin_Enable(void);                               //使能Tx-dis pin
uint8_t GetTx_Pin_DIS(I2C_HandleTypeDef *hi2c);         //检测Tx-dis pin

#endif
