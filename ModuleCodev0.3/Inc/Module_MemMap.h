
//这个头文件存放了关于虚拟寄存器的函数和常量的定义。

#ifndef MODULE_MEMMAP_H
#define MODULE_MEMMAP_H

#include "main.h"
#include "stdint.h"

#define WRITE_ERR     0xFF                    //返回值，写出现错误
#define WRITE_NORMAL  0x00                    //返回值，写正常
#define READ_ERR      0xFF                    //返回值，读出现错误

uint8_t Read_MemMap(int internal_address);                                              //外部读虚拟寄存器

uint8_t Write_MemMap(int internal_address, uint8_t value);                              //外部写虚拟寄存器

uint8_t Internal_Write_MemMap(int internal_address, uint8_t value);                     //内部读虚拟寄存器

uint8_t Internal_Read_MemMap(int Memory_Address);                                       //内部写虚拟寄存器

uint8_t Is_MemMap_Error(void);                                                                 //检查错误

#endif
