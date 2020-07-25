#ifndef __ROSMAIAN_H
#define __ROSMAIAN_H
#include "define.h"


#ifdef __cplusplus
extern "C" {
#endif



void initRosNode(void);
void rosSpinOnce(void);

void getHandShankData(float *linex,float *angular);
#ifdef __cplusplus
}
#endif




#endif
