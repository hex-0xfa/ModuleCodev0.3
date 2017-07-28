
//这个c文件存放了关于与上位机沟通的I2C的初始化中断，关闭中断和中断函数的具体实现和一些内部函数以及内部数据结构。

#include "Module_Slave_I2C.h"
#include "main.h"
#include "constant.h"
#include "Module_MemMap.h"
#include "utilities.h"

#define TXRXBUFFER_SIZE     RW_CHUNK_SIZE+1                            //缓冲区大小
#define USER_I2C_NO_OPTION_FRAME     (0xFFFF0000U)                     //无FRAME

//内部数据结构
static uint8_t TxRxBuffer[TXRXBUFFER_SIZE] = {0};                      //数据发送接收缓冲区
static uint8_t Buffer_Internal_Address = 0;                            //缓冲区地址

//内部函数
static HAL_StatusTypeDef User_I2C_Slave_ISR_IT(I2C_HandleTypeDef *hi2c, uint32_t ITFlags, uint32_t ITSources);    //事件中断处理

void I2C_Slave_Transreceiver_IT_Initialize(I2C_HandleTypeDef *hi2c)    //初始化中断
{ 
	  //将丛机，繁忙状态读入I2C结构
    hi2c->State = HAL_I2C_STATE_BUSY;
    hi2c->Mode = HAL_I2C_MODE_SLAVE;
    hi2c->ErrorCode = HAL_I2C_ERROR_NONE;
 
    //使能响应
    hi2c->Instance->CR2 &= ~I2C_CR2_NACK;

	  //将缓冲区和缓冲大小读入I2C结构
    hi2c->pBuffPtr = TxRxBuffer;
    hi2c->XferSize = TXRXBUFFER_SIZE;
    hi2c->XferCount = TXRXBUFFER_SIZE;
    hi2c->XferOptions = USER_I2C_NO_OPTION_FRAME;
    hi2c->XferISR     = User_I2C_Slave_ISR_IT;

    //使能中断
    __HAL_I2C_ENABLE_IT(hi2c, I2C_IT_ERRI|I2C_IT_TCI|
	                            I2C_IT_STOPI|I2C_IT_NACKI|I2C_IT_ADDRI|
	                            I2C_IT_RXI|I2C_IT_TXI);
}

void I2C_Slave_Transreceiver_IT_Deinitialize(I2C_HandleTypeDef *hi2c)   //关闭中断
{
	 //清空缓存区
	  EmptyBuffer(TxRxBuffer);
	 
	  //失能中断
    __HAL_I2C_DISABLE_IT(hi2c, I2C_IT_ERRI|I2C_IT_TCI|
	                            I2C_IT_STOPI|I2C_IT_NACKI|I2C_IT_ADDRI|
	                            I2C_IT_RXI|I2C_IT_TXI);
	  
	  //失能相应
	  hi2c->Instance->CR2 |= I2C_CR2_NACK;
	
	  //状态为待命
	  hi2c->State = HAL_I2C_STATE_READY;
	  
	  //模式为没有
    hi2c->Mode = HAL_I2C_MODE_NONE;
}

void User_Slave_I2C_EV_IRQHandler(I2C_HandleTypeDef *hi2c)      //事件中断处理
{
  //获取中断标识和终端缘由
  uint32_t itflags   = READ_REG(hi2c->Instance->ISR);
  uint32_t itsources = READ_REG(hi2c->Instance->CR1);

  //I2C中断处理
  if(hi2c->XferISR != NULL)
  {
    hi2c->XferISR(hi2c, itflags, itsources);
  }
}

static HAL_StatusTypeDef User_I2C_Slave_ISR_IT(struct __I2C_HandleTypeDef *hi2c, uint32_t ITFlags, uint32_t ITSources)    //事件中断处理
{
  if(((ITFlags & I2C_FLAG_AF) != RESET) && ((ITSources & I2C_IT_NACKI) != RESET))       //无响应Flag
  {
     __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_AF);                                           //清空 AF Flag
     EmptyBuffer(TxRxBuffer);                                                           //清空缓冲区
     hi2c->pBuffPtr = TxRxBuffer;                                                       //设置缓冲区指针
     hi2c->XferCount = TXRXBUFFER_SIZE;                                                 //设置缓冲区大小
  }
  else if(((ITFlags & I2C_FLAG_RXNE) != RESET) && ((ITSources & I2C_IT_RXI) != RESET))  //接收数据已空Flag
  {
		 if(hi2c->XferCount != 0)
     {
       (*hi2c->pBuffPtr++) = hi2c->Instance->RXDR;                                      //从接受存储器写入数据
       hi2c->XferCount--;
     }
  }
  else if(((ITFlags & I2C_FLAG_ADDR) != RESET) && ((ITSources & I2C_IT_ADDRI) != RESET))//地址匹配Flag
  {
	  if(((ITFlags & I2C_FLAG_DIR) != RESET) && (hi2c->XferCount < hi2c->XferSize))       //是否为接受了地址的发送模式
	  {
		  int i = 0;
		  Buffer_Internal_Address = (*((hi2c->pBuffPtr)-1));                                 //设置地址
	    for(i = 0; i < RW_CHUNK_SIZE; i++)                                                 //将数据写入缓冲区
	    {
		    *((hi2c->pBuffPtr)+i) = Read_MemMap(Buffer_Internal_Address + i); 
	    }
    }
    else if (((ITFlags & I2C_FLAG_DIR) != RESET) && (hi2c->XferCount == hi2c->XferSize)) //是否为未接收地址的发送模式
	  {
		  int j = 0;
		  for(j = 0; j < RW_CHUNK_SIZE; j++)                                                 //将数据写入缓冲区
	    {
		    *((hi2c->pBuffPtr)+j) = Read_MemMap(Buffer_Internal_Address + j); 
	    }
	  }
      __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_ADDR);                                         //清空ADDR Flag
  }
  else if(((ITFlags & I2C_FLAG_TXIS) != RESET) && ((ITSources & I2C_IT_TXI) != RESET))   //传输数据未空Flag
  {
	  if(hi2c->XferCount != 0)
    {
      hi2c->Instance->TXDR = (*hi2c->pBuffPtr++);                                        //将数据写入接受存储器
      hi2c->XferCount--;
    }
  }
  if(((ITFlags & I2C_FLAG_STOPF) != RESET) && ((ITSources & I2C_IT_STOPI) != RESET))     //停止Flag
  {
     __HAL_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_STOPF);                                         //清空 STOPF Flag      
     int m = 0;
     int n = TXRXBUFFER_SIZE - hi2c->XferCount;        
	   if(n >0)                                                                            //如果接受到了数据
	   {
       Buffer_Internal_Address = TxRxBuffer[0];                                          //设置地址
	   }
	   while(m+1<n)                                                                        //当除了地址还有数据时
	   {
		   Write_MemMap(Buffer_Internal_Address+m, TxRxBuffer[m+1]);                         //将缓冲区数据写入虚拟寄存器
		   m++;
	   }
	   EmptyBuffer(TxRxBuffer);                                                            //清空缓冲区
	   hi2c->pBuffPtr = TxRxBuffer;                                                        //设置缓冲区指针
     hi2c->XferCount = TXRXBUFFER_SIZE;                                                  //设置缓冲区大小
  }
	return HAL_OK;
}
