

#include "define.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <std_msgs/UInt8.h>
#include <std_msgs/UInt8MultiArray.h>
#include "ros.h"
#include "shellUsart.h"

void msgCallBack(const geometry_msgs::Twist& msg);
void subShellCallBack(const std_msgs::UInt8MultiArray& msg);
void subUpdataCallBack(const std_msgs::UInt8MultiArray& msg);

std_msgs::UInt8 msg1;
std_msgs::UInt8 msg2;

ros::NodeHandle nh;
//-------------ROS����----------------
ros::Subscriber<geometry_msgs::Twist> cmd_vel("cmd_vel", msgCallBack);
ros::Subscriber<std_msgs::UInt8MultiArray> subShell("shell", subShellCallBack);
ros::Subscriber<std_msgs::UInt8MultiArray> subUpdata("subUpdate", subUpdataCallBack);


ros::Publisher pubUpdate("pubUpdate",&msg2);
ros::Publisher pubShell("pubShell",&msg1);
int i = 0;
static float sg_linex = 0;
static float sg_angularZ = 0;

void getHandShankData(float *linex,float *angular)
{
	*linex = sg_linex;
	*angular = sg_angularZ;	
}

void msgCallBack(const geometry_msgs::Twist& msg)
{   
	sg_linex = msg.linear.x;
	sg_angularZ = msg.angular.z;
	printf("%.3f,%.3f",sg_linex,sg_angularZ);
	
}

void subShellCallBack(const std_msgs::UInt8MultiArray& msg)
{   
	shellRevData(msg.data,msg.data_length);
}
void subUpdataCallBack(const std_msgs::UInt8MultiArray& msg)
{   

}
void rosSendUpdataData(uint8_t buff)
{
	if(nh.connected())
	{
		msg2.data = buff;
	    pubUpdate.publish(&msg2);	
	}
}

void rosSendPushData(uint8_t buff)
{
	if(nh.connected())
	{
		msg1.data = buff;
	    pubShell.publish(&msg1);	
	}
}
void initRosNode()
{
	nh.initNode();
	nh.advertise(pubUpdate);
	nh.advertise(pubShell);
	
    nh.subscribe(cmd_vel);
    nh.subscribe(subShell);
	nh.subscribe(subUpdata);
}
void rosSpinOnce()
{
	nh.spinOnce();
}
