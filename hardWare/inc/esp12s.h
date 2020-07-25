#ifndef _ESP12S_H
#define _ESP12S_H
#include "define.h"

#ifdef __cplusplus
extern "C" {
#endif

/********************begin define  *****************************************/

/**********************end define *****************************************/



/********************begin  type *****************************************/


/**********************end  type *****************************************/



/********************begin parm *****************************************/




/**********************end  parm *****************************************/






/********************begin func *****************************************/

extern void initEspWifi(void);

extern int getWifiData(void);

extern void setWifiData(uint8_t *buff,int len);
/**********************end func *****************************************/


#ifdef __cplusplus
}
#endif


#endif
