#ifndef REVDATAINFO
#define REVDATAINFO
#include "define.h"




/********************begin define  *****************************************/
#define UART_REV_NULL			0x00
#define UART_REV_DMA			0x01
#define UART_REV_INT			0x02
#define UART_REV_POLL			0x03

#define UART_SEND_IO			0x04
#define UART_SEND_ANSY			0x05

#define UARTINFO_COUNT       	0x05
#define UARTINFO_SIZE			256
#define UARTINFO_SEND_SIZE		64
/**********************end define *****************************************/



/********************begin  type *****************************************/
typedef void (*revFunc)(uint8_t *buff,int32_t len);



typedef struct uartrevfifo
{
	UART_HandleTypeDef *uart;
	revFunc revFunc;
	uint8_t revBuff[UARTINFO_SIZE];
	uint8_t sendBuff[UARTINFO_SEND_SIZE];	
	uint8_t sendLen;
	uint8_t revCmd;	
}stuUartRevFifo;




/**********************end  type *****************************************/



/********************begin parm *****************************************/




/**********************end  parm *****************************************/






/********************begin func *****************************************/
extern int32_t 		createFifoRev(UART_HandleTypeDef *uart , revFunc revDataFunc,uint32_t revMode);

extern void 		delFifoRev(int32_t index);

extern void 		sendBuffFifo(int32_t index , uint8_t *buff,int32_t len,int32_t sendMode);

extern void 		UsartReceive_IDLE(UART_HandleTypeDef *huart);

extern void 		setUartIntRev(stuUartRevFifo *revinfo);

extern void 		setUartDmaIdleRev(stuUartRevFifo *revinfo);


/**********************end func *****************************************/






#endif



