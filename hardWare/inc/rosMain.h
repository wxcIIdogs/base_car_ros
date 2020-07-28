#ifndef __ROSMAIAN_H
#define __ROSMAIAN_H
#include "define.h"


#ifdef __cplusplus
extern "C" {
#endif



extern void initRosNode(void);
extern void rosSpinOnce(void);
extern void getHandShankData(float *linex,float *angular);
extern void rosSendPushData(uint8_t buff);

#ifdef __cplusplus
}
#endif




#endif
