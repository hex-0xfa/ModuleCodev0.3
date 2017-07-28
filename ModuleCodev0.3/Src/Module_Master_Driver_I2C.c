
//这个c文件存放了与 Tx Driver 芯片通信的函数的具体实现

#include "Module_Master_Driver_I2C.h"
#include "utilities.h"

//一些内部变量
static uint8_t Bits_On = 0x01;                   //位为1
static uint8_t Bits_Off = 0x00;                  //位为0
static uint8_t Buffer = 0x00;                    //缓冲位

void SetTxModulationCurrent(double modulationCurrent, I2C_HandleTypeDef *hi2c, uint8_t channel)      //设置调制电流
{
	uint16_t current = (uint16_t)(1023.0*(modulationCurrent/MAX_IMOD_CUR));
	uint8_t currentUp = (current/256) & (0x03);
  uint8_t currentDown = current & (0xFF);
	if(current <= 1023)
	{
		if(channel == Channel_0)
		{
		  HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x03, I2C_MEMADD_SIZE_8BIT, &currentUp,1,20);
		  HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x04, I2C_MEMADD_SIZE_8BIT, &currentDown,1,20);
		}
		else if(channel == Channel_1)
		{
		  HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x13, I2C_MEMADD_SIZE_8BIT, &currentUp,1,20);
		  HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x14, I2C_MEMADD_SIZE_8BIT, &currentDown,1,20);
		}
		else if(channel == Channel_2)
		{
		  HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x23, I2C_MEMADD_SIZE_8BIT, &currentUp,1,20);
		  HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x24, I2C_MEMADD_SIZE_8BIT, &currentDown,1,20);
		}
		else if(channel == Channel_3)
		{
		  HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x33, I2C_MEMADD_SIZE_8BIT, &currentUp,1,20);
		  HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x34, I2C_MEMADD_SIZE_8BIT, &currentDown,1,20);
		}
		else if(channel == Channel_All)
		{
		  HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x03, I2C_MEMADD_SIZE_8BIT, &currentUp,1,20);
		  HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x04, I2C_MEMADD_SIZE_8BIT, &currentDown,1,20);
		  HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x13, I2C_MEMADD_SIZE_8BIT, &currentUp,1,20);
		  HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x14, I2C_MEMADD_SIZE_8BIT, &currentDown,1,20);
		  HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x23, I2C_MEMADD_SIZE_8BIT, &currentUp,1,20);
		  HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x24, I2C_MEMADD_SIZE_8BIT, &currentDown,1,20);
		  HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x33, I2C_MEMADD_SIZE_8BIT, &currentUp,1,20);
		  HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x34, I2C_MEMADD_SIZE_8BIT, &currentDown,1,20);
		}
	}
	return;
}

void SetTxBiasSinkCurrent(double biasSinkCurrent, I2C_HandleTypeDef *hi2c, uint8_t channel)          //设置偏置电流
{
	uint16_t current = (uint16_t)(1023.0*(biasSinkCurrent/MAX_IBIAS_CUR));
	uint8_t currentUp = (current/256) & (0x03);
  uint8_t currentDown = current & (0xFF);
	if(current <= 1023)
	{
		if(channel == Channel_0)
		{
		  HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x05, I2C_MEMADD_SIZE_8BIT, &currentUp,1,20);
		  HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x06, I2C_MEMADD_SIZE_8BIT, &currentDown,1,20);
		}
		else if(channel == Channel_1)
		{
		  HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x15, I2C_MEMADD_SIZE_8BIT, &currentUp,1,20);
		  HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x16, I2C_MEMADD_SIZE_8BIT, &currentDown,1,20);
		}
		else if(channel == Channel_2)
		{
		  HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x25, I2C_MEMADD_SIZE_8BIT, &currentUp,1,20);
		  HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x26, I2C_MEMADD_SIZE_8BIT, &currentDown,1,20);
		}
		else if(channel == Channel_3)
		{
		  HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x35, I2C_MEMADD_SIZE_8BIT, &currentUp,1,20);
		  HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x36, I2C_MEMADD_SIZE_8BIT, &currentDown,1,20);
		}
		else if(channel == Channel_All)
		{
		  HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x05, I2C_MEMADD_SIZE_8BIT, &currentUp,1,20);
		  HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x06, I2C_MEMADD_SIZE_8BIT, &currentDown,1,20);
		  HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x15, I2C_MEMADD_SIZE_8BIT, &currentUp,1,20);
		  HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x16, I2C_MEMADD_SIZE_8BIT, &currentDown,1,20);
		  HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x25, I2C_MEMADD_SIZE_8BIT, &currentUp,1,20);
		  HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x26, I2C_MEMADD_SIZE_8BIT, &currentDown,1,20);
		  HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x35, I2C_MEMADD_SIZE_8BIT, &currentUp,1,20);
		  HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x36, I2C_MEMADD_SIZE_8BIT, &currentDown,1,20);
		}
	}
	return;
}

void TxEnable(I2C_HandleTypeDef *hi2c, uint8_t channel)	                                           //失能Tx_Dis
{
	  Tx_Pin_Enable();
		if(channel == Channel_0)
		{
      HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x09, I2C_MEMADD_SIZE_8BIT, &Bits_Off, 1, 20);
		}
		else if(channel == Channel_1)
		{
      HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x19, I2C_MEMADD_SIZE_8BIT, &Bits_Off, 1, 20);
		}
		else if(channel == Channel_2)
		{
      HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x29, I2C_MEMADD_SIZE_8BIT, &Bits_Off, 1, 20);
		}
		else if(channel == Channel_3)
		{
      HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x39, I2C_MEMADD_SIZE_8BIT, &Bits_Off, 1, 20);
		}
		else if(channel == Channel_All)
		{
      HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x09, I2C_MEMADD_SIZE_8BIT, &Bits_Off, 1, 20);
			HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x19, I2C_MEMADD_SIZE_8BIT, &Bits_Off, 1, 20);
			HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x29, I2C_MEMADD_SIZE_8BIT, &Bits_Off, 1, 20);
			HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x39, I2C_MEMADD_SIZE_8BIT, &Bits_Off, 1, 20);
		}
	return;
}

void TxDisable(I2C_HandleTypeDef *hi2c, uint8_t channel)	                                        //使能Tx_Dis
{
		if(channel == Channel_0)
		{
      HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x09, I2C_MEMADD_SIZE_8BIT, &Bits_On, 1, 20);
		}
		else if(channel == Channel_1)
		{
      HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x19, I2C_MEMADD_SIZE_8BIT, &Bits_On, 1, 20);
		}
		else if(channel == Channel_2)
		{
      HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x29, I2C_MEMADD_SIZE_8BIT, &Bits_On, 1, 20);
		}
		else if(channel == Channel_3)
		{
      HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x39, I2C_MEMADD_SIZE_8BIT, &Bits_On, 1, 20);
		}
		else if(channel == Channel_All)
		{
			Tx_Pin_Disable();
      HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x09, I2C_MEMADD_SIZE_8BIT, &Bits_On, 1, 20);
			HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x19, I2C_MEMADD_SIZE_8BIT, &Bits_On, 1, 20);
			HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x29, I2C_MEMADD_SIZE_8BIT, &Bits_On, 1, 20);
			HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x39, I2C_MEMADD_SIZE_8BIT, &Bits_On, 1, 20);
		}
	return;
}

uint8_t GetTxStatus(I2C_HandleTypeDef *hi2c, uint8_t channel)                                     //获取Tx状态
{
	  HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x0C, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
	  if(channel == Channel_0)
		{
       return ((Buffer & 0x02)!=0);
		}
		else if(channel == Channel_1)
		{
       return ((Buffer & 0x04)!=0);
		}
		else if(channel == Channel_2)
		{
       return ((Buffer & 0x08)!=0);
		}
		else if(channel == Channel_3)
		{
       return ((Buffer & 0x10)!=0);
		}
		return 1;
}


void SetCurrentMonitor(I2C_HandleTypeDef *hi2c,uint8_t currentType, uint8_t channel)               //设置电流监视器
{
	if(currentType == I_Mod)
	{
		if(channel == Channel_0)
		{
       Buffer = 0x01;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x0A, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
		else if(channel == Channel_1)
		{
       Buffer = 0x05;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x0A, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
		else if(channel == Channel_2)
		{ 
       Buffer = 0x09;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x0A, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
		else if(channel == Channel_3)
		{
       Buffer = 0x0D;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x0A, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
	}
	else if(currentType == I_Bias)
	{
	  if(channel == Channel_0)
		{
       Buffer = 0x02;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x0A, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
		else if(channel == Channel_1)
		{
       Buffer = 0x06;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x0A, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
		else if(channel == Channel_2)
		{
       Buffer = 0x0A;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x0A, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
		else if(channel == Channel_3)
		{
       Buffer = 0x0E;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x0A, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
	}
	else if(currentType == Mon_Disable)
	{
	     Buffer = 0x00;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x0A, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
	}
	return;
}

void SetLDD_EYE_OPT(uint8_t value, I2C_HandleTypeDef *hi2c, uint8_t channel)                          //设置眼图优化
{
		if(channel == Channel_0)
		{
       HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x07, I2C_MEMADD_SIZE_8BIT, &value, 1, 20);
		}
		else if(channel == Channel_1)
		{
       HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x17, I2C_MEMADD_SIZE_8BIT, &value, 1, 20);
		}
		else if(channel == Channel_2)
		{
       HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x27, I2C_MEMADD_SIZE_8BIT, &value, 1, 20);
		}
		else if(channel == Channel_3)
		{
       HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x37, I2C_MEMADD_SIZE_8BIT, &value, 1, 20);
		}
		else if(channel == Channel_All)
		{
       HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x07, I2C_MEMADD_SIZE_8BIT, &value, 1, 20);
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x17, I2C_MEMADD_SIZE_8BIT, &value, 1, 20);
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x27, I2C_MEMADD_SIZE_8BIT, &value, 1, 20);
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x37, I2C_MEMADD_SIZE_8BIT, &value, 1, 20);
		}
	return;
}

void SetEqulizationMag(uint8_t value, I2C_HandleTypeDef *hi2c, uint8_t channel)                       //设置平衡大小
{
		if(channel == Channel_0)
		{
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x01, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0x03) | ((value & 0x1F) << 3);
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x01, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
		else if(channel == Channel_1)
		{
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x11, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0x03) | ((value & 0x1F) << 3);
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x11, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
		else if(channel == Channel_2)
		{
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x21, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0x03) | ((value & 0x1F) << 3);
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x21, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
		else if(channel == Channel_3)
		{
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x31, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0x03) | ((value & 0x1F) << 3);
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x31, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
		else if(channel == Channel_All)
		{
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x01, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0x03) | ((value & 0x1F) << 3);
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x01, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x11, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0x03) | ((value & 0x1F) << 3);
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x11, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x21, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0x03) | ((value & 0x1F) << 3);
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x21, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x31, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0x03) | ((value & 0x1F) << 3);
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x31, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
	return;
}
	
void SetEqulizationPhase(uint8_t phase, I2C_HandleTypeDef *hi2c, uint8_t channel)                     //设置平衡角度
{
		if(channel == Channel_0)
		{
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x01, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFD) | ((phase & 0x01) << 1);
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x01, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
		else if(channel == Channel_1)
		{
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x11, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFD) | ((phase & 0x01) << 1);
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x11, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
		else if(channel == Channel_2)
		{
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x21, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFD) | ((phase & 0x01) << 1);
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x21, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
		else if(channel == Channel_3)
		{
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x31, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFD) | ((phase & 0x01) << 1);
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x31, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
		else if(channel == Channel_All)
		{
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x01, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFD) | ((phase & 0x01) << 1);
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x01, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x11, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFD) | ((phase & 0x01) << 1);
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x11, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x21, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFD) | ((phase & 0x01) << 1);
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x21, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x31, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFD) | ((phase & 0x01) << 1);
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x31, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
	return;
}
	
void EnableEqulizer(I2C_HandleTypeDef *hi2c, uint8_t channel)                                        //使能平衡
{
		if(channel == Channel_0)
		{
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x01, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFE) | 0x01;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x01, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
		else if(channel == Channel_1)
		{
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x11, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFE) | 0x01;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x11, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
		else if(channel == Channel_2)
		{
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x21, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFE) | 0x01;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x21, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
		else if(channel == Channel_3)
		{
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x31, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFE) | 0x01;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x31, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
		else if(channel == Channel_All)
		{
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x01, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFE) | 0x01;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x01, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x11, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFE) | 0x01;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x11, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x21, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFE) | 0x01;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x21, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x31, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFE) | 0x01;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x31, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
	return;
}
	
void DisableEqulizer(I2C_HandleTypeDef *hi2c, uint8_t channel)                                      //失能平衡
{
		if(channel == Channel_0)
		{
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x01, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFE) | 0x00;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x01, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
		else if(channel == Channel_1)
		{
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x11, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFE) | 0x00;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x11, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
		else if(channel == Channel_2)
		{
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x21, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFE) | 0x00;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x21, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
		else if(channel == Channel_3)
		{
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x31, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFE) | 0x00;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x31, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
		else if(channel == Channel_All)
		{
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x01, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFE) | 0x00;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x01, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x11, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFE) | 0x00;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x11, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x21, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFE) | 0x00;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x21, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x31, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFE) | 0x00;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x31, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
	return;
}

void SetCrossingPointAdj(uint8_t value, I2C_HandleTypeDef *hi2c, uint8_t channel)                   //设置交叉点
{
		if(channel == Channel_0)
		{
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x00, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0x01) | ((value & 0x3F) << 2);
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x00, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
		else if(channel == Channel_1)
		{
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x10, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0x01) | ((value & 0x3F) << 2);
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x10, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
		else if(channel == Channel_2)
		{
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x20, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0x01) | ((value & 0x3F) << 2);
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x20, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
		else if(channel == Channel_3)
		{
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x30, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0x01) | ((value & 0x3F) << 2);
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x30, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
		else if(channel == Channel_All)
		{
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x00, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0x01) | ((value & 0x3F) << 2);
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x00, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x10, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0x01) | ((value & 0x3F) << 2);
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x10, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x20, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0x01) | ((value & 0x3F) << 2);
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x20, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x30, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0x01) | ((value & 0x3F) << 2);
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x30, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
	return;
}
	
void EnableCrossingPointAdj(I2C_HandleTypeDef *hi2c, uint8_t channel)                             //使能交叉点
{
		if(channel == Channel_0)
		{
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x00, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFE) | 0x01;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x00, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
		else if(channel == Channel_1)
		{
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x10, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFE) | 0x01;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x10, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
		else if(channel == Channel_2)
		{
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x20, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFE) | 0x01;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x20, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
		else if(channel == Channel_3)
		{
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x30, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFE) | 0x01;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x30, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
		else if(channel == Channel_All)
		{
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x00, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFE) | 0x01;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x00, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x10, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFE) | 0x01;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x10, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x20, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFE) | 0x01;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x20, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x30, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFE) | 0x01;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x30, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
	return;
}
	
void DisableCrossingPointAdj(I2C_HandleTypeDef *hi2c, uint8_t channel)                                //失能交叉点
{
		if(channel == Channel_0)
		{
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x00, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFE) | 0x00;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x00, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
		else if(channel == Channel_1)
		{
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x10, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFE) | 0x00;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x10, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
		else if(channel == Channel_2)
		{
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x20, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFE) | 0x00;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x20, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
		else if(channel == Channel_3)
		{
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x30, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFE) | 0x00;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x30, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
		else if(channel == Channel_All)
		{
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x00, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFE) | 0x00;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x00, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x10, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFE) | 0x00;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x10, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x20, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFE) | 0x00;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x20, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
       HAL_I2C_Mem_Read(hi2c, GN1185_ADDRESS, 0x30, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
			 Buffer = (Buffer & 0xFE) | 0x00;
			 HAL_I2C_Mem_Write(hi2c, GN1185_ADDRESS, 0x30, I2C_MEMADD_SIZE_8BIT, &Buffer, 1, 20);
		}
	return;
}
