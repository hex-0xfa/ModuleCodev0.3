
//这个头文件存放了实现与 Tx Driver 芯片通信的函数的声明

#ifndef MODULE_MASTER_DRIVER_I2C
#define MODULE_MASTER_DRIVER_I2C

#include "stm32l0xx_hal.h"


//一些与tx-driver相关的常量
#define GN1185_ADDRESS               0xA6            //地址
#define I_Mod                        0               //调制电流
#define I_Bias                       1               //偏置电流
#define Mon_Disable                  2               //禁止Monitor
#define Channel_0                    0               //tx0
#define Channel_1                    1               //tx1
#define Channel_2                    2               //tx2
#define Channel_3                    3               //tx3
#define Channel_All                  4               //所有通道
#define MAX_IBIAS_CUR                70.0            //最大偏置电流
#define MAX_IMOD_CUR                 55.0            //最大调制电流
#define MAX_CRO_POI                  65.0            //最大交叉点
#define MIN_CRO_POI                  35.0            //最小交叉点

void SetTxModulationCurrent(double modulationCurrent, I2C_HandleTypeDef *hi2c, uint8_t channel);   //设置调制电流

void SetTxBiasSinkCurrent(double biasSinkCurrent, I2C_HandleTypeDef *hi2c, uint8_t channel);       //设置偏置电流

void TxEnable(I2C_HandleTypeDef *hi2c, uint8_t channel);                                           //失能Tx_Dis

void TxDisable(I2C_HandleTypeDef *hi2c, uint8_t channel);                                          //使能Tx_Dis

uint8_t GetTxStatus(I2C_HandleTypeDef *hi2c, uint8_t channel);                                     //获取Tx状态

void SetCurrentMonitor(I2C_HandleTypeDef *hi2c,uint8_t currentType, uint8_t channel);              //设置电流监视器

void SetLDD_EYE_OPT(uint8_t value, I2C_HandleTypeDef *hi2c, uint8_t channel);                      //设置眼图优化

void SetEqulizationMag(uint8_t value, I2C_HandleTypeDef *hi2c, uint8_t channel);                   //设置平衡大小
	
void SetEqulizationPhase(uint8_t phase, I2C_HandleTypeDef *hi2c, uint8_t channel);                 //设置平衡角度
	
void EnableEqulizer(I2C_HandleTypeDef *hi2c, uint8_t channel);                                     //使能平衡
	
void DisableEqulizer(I2C_HandleTypeDef *hi2c, uint8_t channel);                                    //失能平衡

void SetCrossingPointAdj(uint8_t value, I2C_HandleTypeDef *hi2c, uint8_t channel);                 //设置交叉点

void EnableCrossingPointAdj(I2C_HandleTypeDef *hi2c, uint8_t channel);                             //使能交叉点
	
void DisableCrossingPointAdj(I2C_HandleTypeDef *hi2c, uint8_t channel);                            //失能交叉点

#endif
