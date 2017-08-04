
//这个c文件存放了与 Tx/Rx CDR 芯片通信的函数的具体实现

#include "Module_Master_CDR.h"
#include "stm32l0xx_hal.h"
#include "Module_MCU.h"
#include "constant.h"
#include "Module_MemMap.h"

static uint8_t Latch_Tx1_Fault = 0;
static uint8_t Latch_Tx2_Fault = 0;
static uint8_t Latch_Tx3_Fault = 0;
static uint8_t Latch_Tx4_Fault = 0;
static uint8_t temp_reg = 0x00;

extern I2C_HandleTypeDef hi2c2;

void SetLatchTxfault(void)         //设置 Tx Fault
{
	//检测到有问题就把有问题的针脚调一。
	if(0)              //Tx4 Fault 条件
	{
		Latch_Tx4_Fault = 1;
		if((Internal_Read_MemMap(MODULE_AND_CHANNEL_MASKES+1) & 0x08) == 0)
		{
		  Assert_IntL();
		}
	}
	if(0)              //Tx3 Fault 条件
	{
		Latch_Tx3_Fault = 1;
		if((Internal_Read_MemMap(MODULE_AND_CHANNEL_MASKES+1) & 0x04) == 0)
		{
		  Assert_IntL();
		}
	}
	if(0)              //Tx2 Fault 条件
	{
		Latch_Tx2_Fault = 1;
		if((Internal_Read_MemMap(MODULE_AND_CHANNEL_MASKES+1) & 0x02) == 0)
		{
		  Assert_IntL();
		}
	}
	if(0)              //Tx1 Fault 条件
	{
	  Latch_Tx1_Fault = 1;
		if((Internal_Read_MemMap(MODULE_AND_CHANNEL_MASKES+1) & 0x01) == 0)
		{
		  Assert_IntL();
		}
	}
}

uint8_t GetLatchTxFault(void)     //获取 Tx Fault
{
  return 0x00 | (Latch_Tx4_Fault << 3) | (Latch_Tx3_Fault << 2) | (Latch_Tx2_Fault << 1) | (Latch_Tx1_Fault);   //返回一个符合sff-8636协议的八位字符
}

void ClearLatchTxfault(void)                         //清空 Tx Fault
{
  Latch_Tx1_Fault = 0;
  Latch_Tx2_Fault = 0;
  Latch_Tx3_Fault = 0;
  Latch_Tx4_Fault = 0;
}

void WakeUpTxCDR_DRIVER(void)                                                             //使TxCDR和Driver从reset模式变为正常工作模式
{
	HAL_GPIO_WritePin(Tx_Reset_GPIO_Port, Tx_Reset_Pin, GPIO_PIN_SET);
}

void WakeUpRxCDR(void)                                                                    //使RxCDR从reset模式变为正常工作模式
{
	HAL_GPIO_WritePin(Rx_Reset_GPIO_Port, Rx_Reset_Pin, GPIO_PIN_SET);
}

void DisableTxCDR_DRIVER(void)                                                            //让TxCDR和Driver进入reset模式
{
	HAL_GPIO_WritePin(Tx_Reset_GPIO_Port, Tx_Reset_Pin, GPIO_PIN_RESET);
}
	
void DisableRxCDR(void)                                                                   //让RxCDR进入reset模式
{
	HAL_GPIO_WritePin(Rx_Reset_GPIO_Port, Rx_Reset_Pin, GPIO_PIN_RESET);
}

uint8_t GetRxLOLPin(void)                                                                 //读取RxLOL Pin
{
	return HAL_GPIO_ReadPin(Rx_LOL_GPIO_Port,Rx_LOL_Pin);
}

uint8_t GetRxLOSPin(void)                                                                 //读取RxLOS Pin
{
	return HAL_GPIO_ReadPin(Rx_LOS_GPIO_Port,Rx_LOS_Pin);
}

uint8_t GetTxLOSLOLPin(void)                                                              //读取TxLOSLOL Pin
{
	return HAL_GPIO_ReadPin(Tx_LOS_LOL_GPIO_Port,Tx_LOS_LOL_Pin);
}

void AssertRxLOL(void)                                                                    //调查具体是哪一条线失去时钟（Rx）
{
	
}

void AssertRxLOS(void)                                                                    //调查具体是那一条线失去信号（Rx）
{
	
} 

void AssertTxLOSLOL(void)                                                                 //调查具体是那一条线失去信号或时钟（Tx）
{
	
}

void PowerUp(I2C_HandleTypeDef *hi2c, uint8_t channel)                                    //打开总线和模拟电路电源
{
	temp_reg = 0x00;
	HAL_I2C_Mem_Write(hi2c, GN2104_TX_I2C_ADDRESS, 1142, GN2104_ADDRESS_SIZE, &temp_reg,1,I2C_WAIT_TIME);
	HAL_I2C_Mem_Write(hi2c, GN2104_RX_I2C_ADDRESS, 1142, GN2104_ADDRESS_SIZE, &temp_reg,1,I2C_WAIT_TIME);
	temp_reg = 0x00;
}

void LOSPowerUp(I2C_HandleTypeDef *hi2c, uint8_t channel)                                 //打开 LOS 检测
{
	temp_reg = 0x01;
	HAL_I2C_Mem_Write(hi2c, GN2104_TX_I2C_ADDRESS, 1028, GN2104_ADDRESS_SIZE, &temp_reg,1,I2C_WAIT_TIME);
	HAL_I2C_Mem_Write(hi2c, GN2104_RX_I2C_ADDRESS, 1028, GN2104_ADDRESS_SIZE, &temp_reg,1,I2C_WAIT_TIME);
	temp_reg = 0x00;
}
