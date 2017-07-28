
//���c�ļ�������� Tx/Rx CDR оƬͨ�ŵĺ����ľ���ʵ��

#include "Module_Master_CDR.h"
#include "stm32l0xx_hal.h"
#include "utilities.h"
#include "constant.h"
#include "Module_MemMap.h"

static uint8_t Latch_Tx1_Fault = 0;
static uint8_t Latch_Tx2_Fault = 0;
static uint8_t Latch_Tx3_Fault = 0;
static uint8_t Latch_Tx4_Fault = 0;

extern I2C_HandleTypeDef hi2c2;

void SetLatchTxfault(void)         //���� Tx Fault
{
	//��⵽������Ͱ����������ŵ�һ��
	if(0)              //Tx4 Fault ����
	{
		Latch_Tx4_Fault = 1;
		if((Internal_Read_MemMap(MODULE_AND_CHANNEL_MASKES+1) & 0x08) == 0)
		{
		  Assert_IntL();
		}
	}
	if(0)              //Tx3 Fault ����
	{
		Latch_Tx3_Fault = 1;
		if((Internal_Read_MemMap(MODULE_AND_CHANNEL_MASKES+1) & 0x04) == 0)
		{
		  Assert_IntL();
		}
	}
	if(0)              //Tx2 Fault ����
	{
		Latch_Tx2_Fault = 1;
		if((Internal_Read_MemMap(MODULE_AND_CHANNEL_MASKES+1) & 0x02) == 0)
		{
		  Assert_IntL();
		}
	}
	if(0)              //Tx1 Fault ����
	{
	  Latch_Tx1_Fault = 1;
		if((Internal_Read_MemMap(MODULE_AND_CHANNEL_MASKES+1) & 0x01) == 0)
		{
		  Assert_IntL();
		}
	}
}

uint8_t GetLatchTxFault(void)     //��ȡ Tx Fault
{
  return 0x00 | (Latch_Tx4_Fault << 3) | (Latch_Tx3_Fault << 2) | (Latch_Tx2_Fault << 1) | (Latch_Tx1_Fault);   //����һ������sff-8636Э��İ�λ�ַ�
}

void ClearLatchTxfault(void)                         //��� Tx Fault
{
  Latch_Tx1_Fault = 0;
  Latch_Tx2_Fault = 0;
  Latch_Tx3_Fault = 0;
  Latch_Tx4_Fault = 0;
}