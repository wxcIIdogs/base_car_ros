#ifndef __ROSMAIAN_H
#define __ROSMAIAN_H
#include "define.h"


#ifdef __cplusplus
extern "C" {
#endif



extern void initRosNode(void);
extern void rosSpinOnce(void);
extern void getHandShankData(float *linex,float *angular);
extern void rosSendPushData(char *buff);
#ifdef __cplusplus
}
#endif




#endif
