#ifndef __STM32HARDWARE_H__
#define __STM32HARDWARE_H__

#include "define.h"
#include <stdint.h>
class Stm32Hardware
{
	public:
		Stm32Hardware(){};
		void init(void)
        {
        }
        
        int getBaud(){return baud_;}
        
        void setBaud(long baud)
        {
            //this->baud_= baud;
        }
        
		int read(void)
        {
			return getWifiData();
        }
		void write(uint8_t* data, int length)
        {
			setWifiData(data, length);
//			if(Wifi_TcpIp_SendDataTcp(0,length,data) == 0)
//				printf("send data false\r\n");
        }
		unsigned long time(void){return HAL_GetTick();}
        
    protected:        
        long baud_;
};



#endif
