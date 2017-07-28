
//这个头文件存放了一些全局常量

#ifndef CONSTANT
#define CONSTANT

#define PAGE_SIZE                             128                         //页大小
#define PAGE_NUMBER                           2                           //页数量
#define MEMORY_MAP_SIZE                       PAGE_SIZE*PAGE_NUMBER       //虚拟寄存器大小
#define RW_CHUNK_SIZE                         PAGE_SIZE * 2               //一次性读取/写入大小

#define QSFP28_IDENTIFIER                     0X11                        //QSFP28识别码
#define IS_PAGED                              0x00<<2U                    //是否分页

//各寄存器地址，详情请参考 SFF 8636
#define IDENTIFIER_ADDRESS                    0
#define STATUS                                1
#define INTERRUPT_FLAG                        3
#define FREE_SIDE_MONITORS                    22
#define CHANNEL_MONITORS                      34
#define CONTROL                               86
#define MODULE_AND_CHANNEL_MASKES             100
#define FREE_SIDE_DEVICE_PROPERTIES           108
#define PASSWORD_CHANGE_ENTRY_AREA            119
#define PASSWORD_ENTRY_AREA                   123
#define PAGE_SELECT_BYTE                      127

#define CLEAR_HIGHER_BIT                      0x00FF                      //清楚十六位的上面八位

#endif
