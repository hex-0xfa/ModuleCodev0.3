
//这个c文件存放了关于模块初始化的具体实现

#include "Module_MemMap.h"
#include "Module_Initialization.h"
#include "utilities.h"
#include "constant.h"
#include "Module_Master_CDR.h"

void Module_Init_Hardware(void)                             //初始化板载硬件
{
	//打开并调试 Tx Driver，检查是否运行正常
	
  //打开并调试 Tx CDR，检查是否运行正常
	
  //打开并调试 Rx CDR，检查是否运行正常
}


void Module_Init_Register(void)                             //初始化模块

{
	extern ADC_HandleTypeDef hadc;                  //获取外部定义的hadc1

	Data_Not_Ready();                                //数据未准备好
	
//00h 上半区	
	Internal_Write_MemMap(0,0x11);                   //识别码   QSFP28
	Internal_Write_MemMap(1,0x00);                   //版本未注明，（应为2.9最新版）
	Internal_Write_MemMap(2,0x07);                   //无多 Page，IntL 高， Data Not Ready 高
	//在MASTERI2C或者MASTERMONITER中需要这些函数：
	//3       LOS Flag                          （可选）
	SetLatchTxfault();                               //4 TX Fault Flag                     
  //5       LOL Flag                          （可选）
  //6       温度预警（可选）
	//7       电压预警（可选）
	//8       随意
	//9-10    功率预警 （可选）
	//11-12   TX偏置电流预警 （可选） 
	//13-14   TX PWR 预警 （可选） 
	//15-18   保留位
	//19-21   随意
	//在utilities中需要这些函数
	uint16_t temperature = GetTemperature(&hadc);
	Internal_Write_MemMap(22,((uint8_t)(temperature/256)));
	Internal_Write_MemMap(23,((uint8_t)(temperature & CLEAR_HIGHER_BIT)));
  //22-23   获取温度警告
	//24-25   保留位
	//26-27   获取提供电压（可选）
	//28-29   保留位
	//30-33   随意 
	//34-41   获取接收端功率  （可选）
	//42-49   获取偏置电流    （可选）
	//50-57   获取发送端功率  （可选）
	//58-65   保留位
	//66-81   随意
	//82-85   保留位
	Internal_Write_MemMap(86,0x00);     //86 Tx失能
  //87      选择 Rx 的速率 （可选）
  //88      选择 Tx 的速率 （可选）
  //89-92 Rx Software Application 选择 （可选） 
	Internal_Write_MemMap(93,0x00);     //93 低功耗模式,  软件LPMode无， 失能LPMode覆盖
	//94-97 Tx Software Application 选择 （可选）
	//98      CDR控制  （可选）
	//99      保留位
	//100     LOS 掩码
	Internal_Write_MemMap(101,0x00);    //101 Tx失能掩码
	//102     LOL 掩码
	//103     温度掩码
	//104     提供电压掩码
	//105-106 随意
	//107     保留位
	//108-109 传输延迟 （可选）
	//110     高级低功率模式/远处为相同/最小工作电压 （可选）
	//111     保留位
	//112-118  保留位
	//119-126 密码位  （可选）
	//127     页数选择     （可选）
	
//00h 下半区
  //128-191 硬件数据（1）
	//192 延长的以太网标准吗
	//193 是否支持一些硬件功能（1）
	//194 是否支持一些硬件功能（2）
	//195 是否支持一些硬件功能（3）
	//196-220 硬件数据（2）
	//221 是否支持一些硬件功能（4）
	//222 比特率
	//223 检查码
	//224-255 随意
	Data_Ready();                                  //数据已准备好
	Assert_IntL();                                 //断言IntL
}

