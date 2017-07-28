
//这个头文件存放了实现与 Tx/Rx CDR 芯片通信的函数的声明

#ifndef MODULE_MASTER_CDR
#define MODULE_MASTER_CDR

#include "stdint.h"
#include "stm32l0xx_hal.h"

//各路编号
#define Tx0   0
#define Tx1   1
#define Tx2   2
#define Tx3   3
#define Rx0   4
#define Rx1   5
#define Rx2   6
#define Rx3   7
#define ChAll 8

//使能，失能
#define Value_Reset 0
#define Value_Set   1

//调试控制
#define Precursor  0
#define Postcurosr 1

//芯片常量
#define GN2104_TX_I2C_ADDRESS                 0x24                                  //Tx CDR 地址
#define GN2104_RX_I2C_ADDRESS                 0x2C                                  //Rx CDR 地址
#define GN2104_ADDRESS_SIZE                   I2C_MEMADD_SIZE_16BIT                 //数据大小


void SetLatchTxfault(void);                             //设置 Tx Fault

uint8_t GetLatchTxFault(void);                          //获取 Tx Fault

void ClearLatchTxfault(void);                           //清空 Tx Fault

//以下函数还未实现，将会在调试的时候（v0.3）进行处理

void PowerUp(I2C_HandleTypeDef *hi2c, uint8_t channel);                                    //打开总线和模拟电路电源

void PowerDown(I2C_HandleTypeDef *hi2c, uint8_t channel);                                  //关闭总线和模拟电路电源

void LOSPowerUp(I2C_HandleTypeDef *hi2c, uint8_t channel);                                 //打开 LOS 检测

void LOSPowerDown(I2C_HandleTypeDef *hi2c, uint8_t channel);                               //关闭 LOS 检测

void CDRPowerUp(I2C_HandleTypeDef *hi2c, uint8_t channel);                                 //打开CDR
 
void CDRPowerDown(I2C_HandleTypeDef *hi2c, uint8_t channel);                               //关闭CDR

void SetLosThres(I2C_HandleTypeDef *hi2c, uint8_t channel, uint8_t value);                 //设置LOS门槛

void SetLosHyst(I2C_HandleTypeDef *hi2c, uint8_t channel, uint8_t value);                  //设置LOS滞后

void CDRBypass(I2C_HandleTypeDef *hi2c, uint8_t channel, uint8_t state);                   //跳过CDR

void SetEqulizer(I2C_HandleTypeDef *hi2c, uint8_t channel, uint8_t value);                 //设置补偿器

void SetDriverMute(I2C_HandleTypeDef *hi2c, uint8_t channel, uint8_t state);               //设置Driver沉默

void SetDriverDeemp(I2C_HandleTypeDef *hi2c, uint8_t channel, uint8_t value);              //设置去加重

void SetDeempPrePostCursor(I2C_HandleTypeDef *hi2c, uint8_t channel, uint8_t PreorPost);   //设置去加重前后

uint8_t GetTxLOSCDR(I2C_HandleTypeDef *hi2c, uint8_t channel);                             //读取TxLOS

uint8_t GetRxLOSCDR(I2C_HandleTypeDef *hi2c, uint8_t channel);                             //读取RxLOS

uint8_t GetTxLOLCDR(I2C_HandleTypeDef *hi2c, uint8_t channel);                             //读取TxLOL

uint8_t GetRxLOLCDR(I2C_HandleTypeDef *hi2c, uint8_t channel);                             //读取RxLOL

#endif
