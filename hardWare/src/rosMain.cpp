

#include "define.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <std_msgs/UInt8.h>
#include "ros.h"


void msgCallBack(const geometry_msgs::Twist& msg);

std_msgs::String msg1;
ros::NodeHandle nh;
//-------------ROS±‰¡ø----------------
ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", msgCallBack);
ros::Publisher pub("stm_publish",&msg1);
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
void rosSendPushData(char *buff)
{
	if(nh.connected())
	{
		msg1.data = buff;		
	    pub.publish(&msg1);	
	}
}
void initRosNode()
{
	nh.initNode();
	nh.advertise(pub);
    nh.subscribe(sub);
}
void rosSpinOnce()
{
	nh.spinOnce();
}
