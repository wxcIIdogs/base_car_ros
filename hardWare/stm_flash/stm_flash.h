#ifndef __STMFLASH_H__
#define __STMFLASH_H__

/* 包含头文件 ----------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* 类型定义 ------------------------------------------------------------------*/
#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbytes */
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbytes */
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbytes */
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbytes */
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbytes */
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbytes */
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) /* Base @ of Sector 6, 128 Kbytes */
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) /* Base @ of Sector 7, 128 Kbytes */
#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000) /* Base @ of Sector 8, 128 Kbytes */
#define ADDR_FLASH_SECTOR_9     ((uint32_t)0x080A0000) /* Base @ of Sector 9, 128 Kbytes */
#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x080C0000) /* Base @ of Sector 10, 128 Kbytes */
#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbytes */

/* 宏定义 --------------------------------------------------------------------*/
/************************** STM32 内部 FLASH 配置 *****************************/
#define STM32_FLASH_SIZE        512  // 所选STM32的FLASH容量大小(单位为K)
#define STM32_FLASH_WREN        1    // stm32芯片内容FLASH 写入使能(0，禁用;1，使能)

/* 扩展变量 ------------------------------------------------------------------*/
/* 函数声明 ------------------------------------------------------------------*/
uint16_t STMFLASH_ReadHalfWord(uint32_t faddr);		  //读出半字
extern uint32_t GetSector(uint32_t Address);

void STMFLASH_WriteLenByte(uint32_t WriteAddr, uint32_t DataToWrite, uint16_t Len );	      //指定地址开始写入指定长度的数据
uint32_t STMFLASH_ReadLenByte(uint32_t ReadAddr, uint16_t Len );					                    	//指定地址开始读取指定长度数据
void STMFLASH_Write( uint32_t WriteAddr, uint16_t * pBuffer, uint16_t NumToWrite );		//从指定地址开始写入指定长度的数据
void STMFLASH_Read( uint32_t ReadAddr, uint16_t * pBuffer, uint16_t NumToRead );   	//从指定地址开始读出指定长度的数据
void STMFLASH_WriteStruct(uint32_t WriteAddr,void * pBuffer,uint16_t NumToWrite);	//write buff to flash
#endif /* __STMFLASH_H__ */

/******************* (C) COPYRIGHT 2015-2020 硬石嵌入式开发团队 *****END OF FILE****/
