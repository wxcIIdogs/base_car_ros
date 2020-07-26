
#include "Wifi.h"

//#######################################################################################
void	Wifi_UserInit(void)
{
	Wifi_SetMode(WifiMode_Station);
  //Wifi_SetMode(WifiMode_SoftAp); 
  int count = 10;
  while (Wifi_Station_ConnectToAp("wxc","853976858",NULL) == false)
  {
	  printf("ssid = wxc,passwd = 853976858 connect false\r\n");	
	  if(count -- == 0)
	  	return;
  }
  printf("ssid = wxc,passwd = 853976858 connect success\r\n");
}
//#######################################################################################
void  Wifi_UserProcess(void)
{
	static int s_scanTime = 300;
	//Wifi.MyGateWay
  if(Wifi.TcpIpConnections[0].status != WifiConnectionStatus_Connected)
  {
	  if(Wifi_TcpIp_StartTcpConnection(0,"192.168.0.106",11411,10))
	  {
		  printf("tcp connect success\r\n");
		  Wifi.TcpIpConnections[0].status = WifiConnectionStatus_Connected;
	  }
	  else
	  {
		  printf("tcp connect false\r\n");
		  if(Wifi_TcpIp_Ping("192.168.0.106"))
			  printf("ip %s to ping 192.168.0.106 success\r\n",Wifi.MyIP);
		  else
			  printf("ip %s to ping 192.168.0.106 false\r\n",Wifi.MyIP);
	  }
  }
  else
  {
	  if(s_scanTime -- == 0)
	  {
		  Wifi_TcpIp_GetConnectionStatus();
		  s_scanTime = 300;
	  }
	  led_setStatus(1,LED_OPT_NORMAL,500);
  }
//  if(Wifi.TcpIpConnections[0].status == WifiConnectionStatus_Connected)
//	Wifi_TcpIp_SendDataTcp(0,8,"hello");
}
//#######################################################################################
void  Wifi_UserGetUdpData(uint8_t LinkId,uint16_t DataLen,uint8_t *Data)
{
	Wifi_TcpIp_SendDataUdp(LinkId,2,(uint8_t*)"OK");
}

static uint8_t  wifiBuff[1024];
static int readIndex = 0;
static int writeIndex = 0;

int getWifiData()
{
	int rpy = -1;
	if(readIndex == writeIndex)
		return rpy;
	rpy = wifiBuff[readIndex];
	readIndex++;
	if(readIndex == 1024)
	{
		readIndex = 0;
	}
	return rpy;
}

//#######################################################################################
void  Wifi_UserGetTcpData(uint8_t LinkId,uint16_t DataLen,uint8_t *Data)
{
	
	for(int i = 0; i < DataLen ; i++)
	{
		wifiBuff[writeIndex] = Data[i];
		writeIndex ++;
		if(writeIndex == 1024)
			writeIndex = 0;
	}
	//Wifi_TcpIp_SendDataTcp(LinkId,0,(uint8_t*)"OK");
}
//#######################################################################################

static uint8_t  wifiwBuff[1024];
static int readwIndex = 0;
static int writewIndex = 0;


void setWifiData(uint8_t *buff,int len)
{
	for(int i = 0; i < len ; i++)
	{
		wifiwBuff[writewIndex] = buff[i];
		writewIndex ++;
		if(writewIndex == 1024)
			writewIndex = 0;
	}
}

void loopWifiSendData()
{
	uint8_t  temp[1024];
	int count = 0;
	while(writewIndex != readwIndex)
	{
		temp[count ++] = wifiwBuff[readwIndex];
		readwIndex ++;
		if(readwIndex == 1024)
			readwIndex = 0;
	}
	if(count != 0)
		Wifi_TcpIp_SendDataTcp(0,count,temp);
}
