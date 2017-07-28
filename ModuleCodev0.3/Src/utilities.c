
//这个c文件存放了常规函数的具体实现

#include "utilities.h"
#include "constant.h"
#include "stdint.h"
#include "stm32l0xx_hal.h"
#include "main.h"
#include "Module_MemMap.h"

//关于温度转换的常数
#define Vadc          3.3                
#define V25           1774.0
#define AVG_SLOPE     0.0043
#define TEMP_ALARM_VALUE 0xFFFF                         //警告温度

//高温预警位
static uint8_t latch_temp_high_alarm = 0;

//清空缓冲区
void EmptyBuffer(uint8_t* a)
{
	int i = 0;
	for(i =0; i<= PAGE_SIZE+1;i++)
	{
		a[i] = 0;
  }
}

//获取温度
uint16_t GetTemperature (ADC_HandleTypeDef *hadc)
{
	uint32_t TemBuffer = 0x00000000;
	HAL_ADC_Start(hadc);
	HAL_Delay(500);
	TemBuffer = HAL_ADC_GetValue(hadc);
	HAL_ADC_Stop(hadc);
  return ((uint16_t)(TemBuffer & 0x0000FFFF));
	//温度转换（未校准）
	//double Measured_Temperature = ((V25 - (double)TemBuffer)*(Vadc/4095.0))/(AVG_SLOPE)-25.0;
	//uint16_t temp = ((uint16_t)(Measured_Temperature*256.0));
	//return temp;
}

//设置高温警告
void SetLatchTempHighAlarm(ADC_HandleTypeDef *hadc)
{
	/*if(GetTemperature(hadc) > TEMP_ALARM_VALUE )
	{
	   latch_temp_high_alarm = 0x80;
	}*/
	return;
}

//获取高温警告
uint8_t GetLatchTempHighAlarm(void)
{
  return latch_temp_high_alarm;
}

//清空高温警告
void    ClearLatchTempHighAlarm(void)
{
	latch_temp_high_alarm = 0;
}

//检测ModSelL
uint8_t IsModSelL(void)                //1不接受数据，0接收数据
{
	return HAL_GPIO_ReadPin(ModSelL_GPIO_Port, ModSelL_Pin);
}

//断言IntL
void Assert_IntL(void)                 //低电平
{
	HAL_GPIO_WritePin(IntL_GPIO_Port, IntL_Pin, GPIO_PIN_RESET);
	uint8_t u = Internal_Read_MemMap(2);
	u = u & 0xFD;
	Internal_Write_MemMap(2,u);
}

//反断言IntL
void Deassert_IntL(void)               //高电平
{
	HAL_GPIO_WritePin(IntL_GPIO_Port, IntL_Pin, GPIO_PIN_SET);
	uint8_t u = Internal_Read_MemMap(2);
	u = u | 0x02;
	Internal_Write_MemMap(2,u);
}

//检测IntL
void GetIntL(void)
{
	HAL_GPIO_ReadPin(IntL_GPIO_Port, IntL_Pin);
}

//数据准备完成
void Data_Ready(void)
{
	uint8_t u = Internal_Read_MemMap(2);
	u = u & 0xFE;
	Internal_Write_MemMap(2,u);
}

//数据未准备完成
void Data_Not_Ready(void)
{
	uint8_t u = Internal_Read_MemMap(2);
	u = u | 0x01;
	Internal_Write_MemMap(2,u);
}

//是否低功耗模式pin为高
uint8_t IsLPMode(void)
{
	return HAL_GPIO_ReadPin(LPMode_GPIO_Port, LPMode_Pin);
}

//进入低功耗模式
void LowPowerMode(void)
{
	//（未完成）
}

//进入正常功耗模式
void NormalPowerMode(void)
{
	//（未完成）
}

//LPMode是否被覆盖
uint8_t IsLPMode_Overriade(void)
{
	return (Internal_Read_MemMap(93) & 0x01);
}

//失能Tx-dis pin
void Tx_Pin_Disable(void)
{
   HAL_GPIO_WritePin(TxDSBL_GPIO_Port, TxDSBL_Pin, GPIO_PIN_SET);
}

//使能Tx-dis pin
void Tx_Pin_Enable(void)
{
   HAL_GPIO_WritePin(TxDSBL_GPIO_Port, TxDSBL_Pin, GPIO_PIN_RESET);
}

//检测Tx-dis pin
uint8_t GetTx_Pin_DIS(I2C_HandleTypeDef *hi2c)
{
  return HAL_GPIO_ReadPin(TxDSBL_GPIO_Port, TxDSBL_Pin);
}
