#ifndef __SHELLUSART__H
#define __SHELLUSART__H

#include "define.h"

extern SHELL_TypeDef shell;






extern 	void initShellusart(void);
extern 	void shellWriteDebug(char data);
extern  void shellRevData(uint8_t *buff,int32_t len);







#endif
