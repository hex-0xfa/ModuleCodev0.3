
//这个c文件存放了虚拟寄存器的数据，内部常量以及各种函数的具体实现

#include "Module_MemMap.h"
#include "main.h"
#include "constant.h"
#include "stdlib.h"
#include "Module_Master_CDR.h"
#include "utilities.h"
#include "Module_Master_Driver_I2C.h"

//v0.3 版 只支持 SFF8636中 定义的最简功能，Memory Map共有256个字节。
//只读区域
#define RO_START_ADDRESS_1    0
#define RO_STOP_ADDRESS_1    85
#define RO_START_ADDRESS_2  108
#define RO_STOP_ADDRESS_2   111
#define RO_START_ADDRESS_3  128
#define RO_STOP_ADDRESS_3   223
//如以后增加只读区域的话按需添加

//内部数据结构
static uint8_t status_code = 0;                                       //错误代码
static uint8_t MemMap_Array[MEMORY_MAP_SIZE] = {0};                   //内部内存地址
extern I2C_HandleTypeDef hi2c2;                                       //外部上位机联络I2C结构地址

//内部函数
//static int Address_Redirection(int Memory_Address);                 //可以实现多页的MemMap（未完成）

uint8_t Read_MemMap(int Memory_Address)                               //外部读虚拟寄存器
{
	if( Memory_Address >= MEMORY_MAP_SIZE)                              //超出范围
	{
		status_code = 1;                                                  //设置错误代码
		return READ_ERR;                                                  //如果读出来的结果是FF，则检查错误。
	}
	
	if(Memory_Address == STATUS+1)                                      //读到了IntL和Data_Not_Ready寄存器
	{
		if((*(MemMap_Array + Memory_Address) & 0x01) == 0)                //如果Data_Ready
		{
			Deassert_IntL();                                                //反断言 IntL
		}
	}
	else if (Memory_Address == (INTERRUPT_FLAG + 1))                    //读到了Tx_Fault的寄存器
	{
		*(MemMap_Array + Memory_Address) = GetLatchTxFault();             //获取 Tx_Fault
		 ClearLatchTxfault();                                             //清除 Tx_Fault
		 Deassert_IntL();                                                 //反断言 IntL
	}
	else if(Memory_Address == (INTERRUPT_FLAG + 3))                     //读到了High_Temperature_Alarm
	{
	   *(MemMap_Array + Memory_Address) = GetLatchTempHighAlarm();      //获取 High_Temperature_Alarm
		 ClearLatchTempHighAlarm();                                       //清除 High_Temperature_Alarm
		 Deassert_IntL();                                                 //反断言 High_Temperature_Alarm
	}
  return *(MemMap_Array + Memory_Address);                            //返回值
}

uint8_t Write_MemMap(int Memory_Address, uint8_t value)               //外部写虚拟寄存器
{
	if(( Memory_Address >= MEMORY_MAP_SIZE)                                              ||    //超出范围  
		 ((Memory_Address >= RO_START_ADDRESS_1) && (Memory_Address <= RO_STOP_ADDRESS_1)) ||
		 ((Memory_Address >= RO_START_ADDRESS_2) && (Memory_Address <= RO_STOP_ADDRESS_2)) ||
	   ((Memory_Address >= RO_START_ADDRESS_3) && (Memory_Address <= RO_STOP_ADDRESS_3)))        
	   //如增加只读区域的话按需添加
	{
		status_code = 1;                                                  //设置错误代码
		return WRITE_ERR;                                                 //如果读出来的结果是FF，则检查错误。
	}
	else
	{
    *(MemMap_Array + Memory_Address) = value;                         //写值
		
		if(Memory_Address == CONTROL)                                     //写Control位后的一些操作（未完成）
		{
			/*
		  if((value &  0x08) != 0)                                        //禁用/启用Tx3
			{
			  TxDisable(&hi2c2,Channel_3);
			}
			else
			{
				TxEnable(&hi2c2,Channel_3);
			}
		  if((value &  0x04) != 0)                                        //禁用/启用Tx2
			{
			  TxDisable(&hi2c2,Channel_2);			  
			}
			else
			{
				TxEnable(&hi2c2,Channel_2);
			}
		  if((value &  0x02) != 0)                                        //禁用/启用Tx1
			{
			  TxDisable(&hi2c2,Channel_1);			  
			}
			else
			{
				TxEnable(&hi2c2,Channel_1);
			}
      if((value &  0x01) != 0)                                        //禁用/启用Tx0
			{
			  TxDisable(&hi2c2,Channel_0);			  
		  }
			else
			{
				TxEnable(&hi2c2,Channel_0);
			}
			*/
		}
		else if(Memory_Address == CONTROL + 7)                         //写功率控制位
		{
			if((value & 0x01) == 0)                                      //如果未覆盖
			{
				 if(IsLPMode() == 0)                                       //如果为0
	       {
		       NormalPowerMode();                                      //正常模式
		     }
	       else                                                      //如果为1
	       {
		       LowPowerMode();                                         //低功率模式
		     }
	    }
			else                                                         //如果已覆盖
			{
				if((value & 0x02) == 0)                                    //如果软件LPMode位为0
				{
					NormalPowerMode();                                       //正常模式
				}
				else                                                       //如果软件LPMode位为1
				{
					LowPowerMode();                                          //低功率模式
				}
			}
		}
	}
	return WRITE_NORMAL;                                               //写正常 0
}

uint8_t Internal_Write_MemMap(int Memory_Address, uint8_t value)     //内部写虚拟寄存器
{
	if(Memory_Address >= MEMORY_MAP_SIZE)                              //超出范围
	{
		status_code = 1;                                                 //设置错误代码
		return WRITE_ERR;                                                //如果读出来的结果是FF，则检查错误。
	}
  *(MemMap_Array + Memory_Address) = value;                          //写值
	return WRITE_NORMAL;                                               //写正常 0
}

uint8_t Internal_Read_MemMap(int Memory_Address)                     //内部读虚拟寄存器
{
	if( Memory_Address >= MEMORY_MAP_SIZE)                             //超出范围
	{
		status_code = 1;                                                 //设置错误代码
		return READ_ERR;                                                 //如果读出来的结果是FF，则检查错误。
	}
  return *(MemMap_Array + Memory_Address);                           //读值
}

uint8_t Is_MemMap_Error(void)                                        //返回错误代码
{ 
	uint8_t s = status_code;
	status_code = 0;                                                   //清空错误代码
	return s;                                       
}
