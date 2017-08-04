
//这个头文件存放了一些公用函数和GPIO函数的定义

#ifndef UTILITIES
#define UTILITIES

#include "stdint.h"
#include "stm32l0xx_hal.h"

//清空数组
void EmptyBuffer(uint8_t* a);

//关于温度的函数
uint16_t GetTemperature(void);                                //获取温度          （未完成，要按照8636里的要求返回值）
void    SetLatchTempHighAlarm(ADC_HandleTypeDef *hadc);       //设置高温警告      （未完成，要自定义一个高温）
uint8_t GetLatchTempHighAlarm(void);                          //获取高温警告
void    ClearLatchTempHighAlarm(void);                        //清空高温警告

//获取RSSI电压的函数（未完成，需要和参考电压做对比）
uint16_t  GetRSSI1(void);                                     //获取RSSI1         
uint16_t  GetRSSI2(void);                                     //获取RSSI2
uint16_t  GetRSSI3(void);                                     //获取RSSI3
uint16_t  GetRSSI4(void);                                     //获取RSSI4

//获取IBias电压的函数（未完成，需要和参考电压做对比）
uint16_t  GetIBias(void);

//关于ModselL的函数
uint8_t   IsModSelL(void);                              //检测ModSelL

//关于IntL的函数
void Assert_IntL(void);                                 //断言IntL
void Deassert_IntL(void);                               //反断言IntL
void GetIntL(void);                                     //检测IntL
uint8_t WhetherIntL(void);                              //是否反断言IntL    （未完成）

//关于Data_Not_Ready的函数
void Data_Ready(void);                                  //数据准备完成
void Data_Not_Ready(void);                              //数据未准备完成

//关于LPMode的函数
uint8_t IsLPMode(void);                                 //是否低功耗模式
void LowPowerMode(void);                                //进入低功耗模式    （未完成）
void NormalPowerMode(void);                             //进入正常功耗模式  （未完成）
uint8_t IsLPMode_Overriade(void);                       //LPMode是否被覆盖

//关于pin TX-DISABLE 的函数
void Tx_Pin_Disable(void);                              //失能Tx-dis pin
void Tx_Pin_Enable(void);                               //使能Tx-dis pin
uint8_t GetTx_Pin_DIS(I2C_HandleTypeDef *hi2c);         //检测Tx-dis pin

//关于ADC的函数
void ADC_Update(void);                                  //更新所有ADC的值

//关于EEPROM的函数
void Save_Data(uint8_t address, uint8_t word);          //将一个八位的数值写入自带的EEPROM（断电不会丢失）
uint8_t Load_Data(uint8_t address);                     //从EEPROM读一个八位的数值
#endif
