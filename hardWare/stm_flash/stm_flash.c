/* ����ͷ�ļ� ----------------------------------------------------------------*/
#include "stm_flash.h"

/* ˽�����Ͷ��� --------------------------------------------------------------*/
/* ˽�к궨�� ----------------------------------------------------------------*/
#if STM32_FLASH_SIZE < 256
  #define STM_SECTOR_SIZE  1024 //�ֽ�
#else 
  #define STM_SECTOR_SIZE	 2048
#endif


/* ˽�б��� ------------------------------------------------------------------*/
#if STM32_FLASH_WREN	//���ʹ����д 
static uint16_t STMFLASH_BUF [ STM_SECTOR_SIZE / 2 ];//�����2K�ֽ�
static FLASH_EraseInitTypeDef EraseInitStruct;
#endif

/* ��չ���� ------------------------------------------------------------------*/
/* ˽�к���ԭ�� --------------------------------------------------------------*/
/* ������ --------------------------------------------------------------------*/
/**
  * ��������: ��ȡָ����ַ�İ���(16λ����)
  * �������: faddr:����ַ(�˵�ַ����Ϊ2�ı���!!)
  * �� �� ֵ: ����ֵ:��Ӧ����.
  * ˵    ������
  */
uint16_t STMFLASH_ReadHalfWord ( uint32_t faddr )
{
	return *(__IO uint16_t*)faddr; 
}

#if STM32_FLASH_WREN	//���ʹ����д   
/**
  * ��������: ������д��
  * �������: WriteAddr:��ʼ��ַ
  *           pBuffer:����ָ��
  *           NumToWrite:����(16λ)��
  * �� �� ֵ: ��
  * ˵    ������
  */
void STMFLASH_Write_NoCheck ( uint32_t WriteAddr, uint16_t * pBuffer, uint16_t NumToWrite )   
{ 			 		 
	uint16_t i;	
	
	for(i=0;i<NumToWrite;i++)
	{
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,WriteAddr,pBuffer[i]);
		WriteAddr+=2;                                    //��ַ����2.
	}  
} 


void STMFLASH_WriteStruct(uint32_t WriteAddr,void * pBuffer,uint16_t NumToWrite)
{
	int wCount = NumToWrite % 2 + NumToWrite;
	uint16_t wBuff[wCount];
	uint8_t *pdata = pBuffer;
	int oriIndex = 0;
	for(int i = 0; i < wCount ; i ++)
	{
		wBuff[i] = pdata[oriIndex + 1] << 8 | pdata[oriIndex];
		oriIndex += 2;
	}
	STMFLASH_Write(WriteAddr,wBuff,wCount);
	
}


/**
  * ��������: ��ָ����ַ��ʼд��ָ�����ȵ�����
  * �������: WriteAddr:��ʼ��ַ(�˵�ַ����Ϊ2�ı���!!)
  *           pBuffer:����ָ��
  *           NumToWrite:����(16λ)��(����Ҫд���16λ���ݵĸ���.)
  * �� �� ֵ: ��
  * ˵    ������
  */
void STMFLASH_Write ( uint32_t WriteAddr, uint16_t * pBuffer, uint16_t NumToWrite )	
{
	uint32_t SECTORError = 0;
	uint16_t secoff;	   //������ƫ�Ƶ�ַ(16λ�ּ���)
	uint16_t secremain; //������ʣ���ַ(16λ�ּ���)	   
 	uint16_t i;    
	uint32_t secpos;	   //������ַ
	uint32_t offaddr;   //ȥ��0X08000000��ĵ�ַ
	
	if(WriteAddr<FLASH_BASE||(WriteAddr>=(FLASH_BASE+1024*STM32_FLASH_SIZE)))return;//�Ƿ���ַ
	
	HAL_FLASH_Unlock();						//����
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
					 FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);
	offaddr=WriteAddr-FLASH_BASE;		//ʵ��ƫ�Ƶ�ַ.
	secpos=offaddr/STM_SECTOR_SIZE;			//������ַ  0~127 for STM32F103RBT6
	secoff=(offaddr%STM_SECTOR_SIZE)/2;		//�������ڵ�ƫ��(2���ֽ�Ϊ������λ.)
	secremain=STM_SECTOR_SIZE/2-secoff;		//����ʣ��ռ��С   
	if(NumToWrite<=secremain)secremain=NumToWrite;//�����ڸ�������Χ
	
	while(1) 
	{	
		STMFLASH_Read(secpos*STM_SECTOR_SIZE+FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);//������������������
		for(i=0;i<secremain;i++)//У������
		{
			if(STMFLASH_BUF[secoff+i]!=0XFFFF)break;//��Ҫ����  	  
		}
		if(i<secremain)//��Ҫ����
		{
			//�����������
			/* Fill EraseInit structure*/
//			EraseInitStruct.TypeErase     = FLASH_TYPEERASE_PAGES;
//			EraseInitStruct.PageAddress   = secpos*STM_SECTOR_SIZE+FLASH_BASE;
//			EraseInitStruct.NbPages       = 1;
			//HAL_FLASHEx_Erase(&EraseInitStruct, &SECTORError);
			FLASH_Erase_Sector(GetSector(secpos*STM_SECTOR_SIZE+FLASH_BASE), FLASH_VOLTAGE_RANGE_3);

			for(i=0;i<secremain;i++)//����
			{
				STMFLASH_BUF[i+secoff]=pBuffer[i];	  
			}
			STMFLASH_Write_NoCheck(secpos*STM_SECTOR_SIZE+FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);//д����������  
		}
    else
    {
      STMFLASH_Write_NoCheck(WriteAddr,pBuffer,secremain);//д�Ѿ������˵�,ֱ��д������ʣ������. 				   
		}
    if(NumToWrite==secremain)break;//д�������
		else//д��δ����
		{
			secpos++;				//������ַ��1
			secoff=0;				//ƫ��λ��Ϊ0 	 
		   	pBuffer+=secremain;  	//ָ��ƫ��
			WriteAddr+=secremain;	//д��ַƫ��	   
		   	NumToWrite-=secremain;	//�ֽ�(16λ)���ݼ�
			if(NumToWrite>(STM_SECTOR_SIZE/2))secremain=STM_SECTOR_SIZE/2;//��һ����������д����
			else secremain=NumToWrite;//��һ����������д����
		}	 
	};	
	HAL_FLASH_Lock();//����
}
#endif

/**
  * ��������: ��ָ����ַ��ʼ����ָ�����ȵ�����
  * �������: ReadAddr:��ʼ��ַ
  *           pBuffer:����ָ��
  *           NumToRead:����(16λ)��
  * �� �� ֵ: ��
  * ˵    ������
  */
void STMFLASH_Read ( uint32_t ReadAddr, uint16_t *pBuffer, uint16_t NumToRead )   	
{
	uint16_t i;
	
	for(i=0;i<NumToRead;i++)
	{
		pBuffer[i]=STMFLASH_ReadHalfWord(ReadAddr);//��ȡ2���ֽ�.
		ReadAddr+=2;//ƫ��2���ֽ�.	
	}
}
uint32_t GetSector(uint32_t Address)
{
  uint32_t sector = 0;
  
  if((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
  {
    sector = FLASH_SECTOR_0;  
  }
  else if((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
  {
    sector = FLASH_SECTOR_1;  
  }
  else if((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
  {
    sector = FLASH_SECTOR_2;  
  }
  else if((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
  {
    sector = FLASH_SECTOR_3;  
  }
  else if((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4))
  {
    sector = FLASH_SECTOR_4;  
  }
  else if((Address < ADDR_FLASH_SECTOR_6) && (Address >= ADDR_FLASH_SECTOR_5))
  {
    sector = FLASH_SECTOR_5;  
  }
  else if((Address < ADDR_FLASH_SECTOR_7) && (Address >= ADDR_FLASH_SECTOR_6))
  {
    sector = FLASH_SECTOR_6;  
  }
  else if((Address < ADDR_FLASH_SECTOR_8) && (Address >= ADDR_FLASH_SECTOR_7))
  {
    sector = FLASH_SECTOR_7;  
  }
  else if((Address < ADDR_FLASH_SECTOR_9) && (Address >= ADDR_FLASH_SECTOR_8))
  {
    sector = FLASH_SECTOR_8;  
  }
  else if((Address < ADDR_FLASH_SECTOR_10) && (Address >= ADDR_FLASH_SECTOR_9))
  {
    sector = FLASH_SECTOR_9;  
  }
  else if((Address < ADDR_FLASH_SECTOR_11) && (Address >= ADDR_FLASH_SECTOR_10))
  {
    sector = FLASH_SECTOR_10;  
  }
  else/*(Address < FLASH_END_ADDR) && (Address >= ADDR_FLASH_SECTOR_11))*/
  {
    sector = FLASH_SECTOR_11;  
  }
  return sector;
}

/******************* (C) COPYRIGHT 2015-2020 ӲʯǶ��ʽ�����Ŷ� *****END OF FILE****/
