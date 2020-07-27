#include "define.h"
#include "math.h"
/*
*author:Wxc
*info:
*data: 2020-05-07
*/

static pid_ctrl_t l_pid;
static pid_ctrl_t r_pid;


/***********************************
*func:
*parm:
*return:
*info:
***********************************/
int16_t ZqAbs(int16_t speed)
{
	if(speed>=0)
	{
		return speed;
	}
	else
	{
		return speed*(-1);
	}
}
/***********************************
*func:
*parm:
*return:
*info:
***********************************/
int8_t S16Symbol(int16_t x)
{
	if(x >= 0)
		return 1;
	else
		return -1;
}
static int LunW = 54;    //cm
static double WHEEL = 3.14159*30.4/32;     //pai  lun tai zhi jing     jian shu bi
void getCanMotorCalcSpeed(int16_t aimSpeed,int16_t swerveValue,int16_t *lSpeed,int16_t *rSpeed,int16_t MaxSpeed)
{
	double V1,V2,Vin,Vout;
	int8_t direct = S16Symbol(swerveValue);
	//get swerve value for aimSpeed and swerveValue
	//float swerveR = 400 - (ZqAbs(swerveValue) - 1)*3.10;						//aimspeed >0   <4000
//	printf("swereR = %f\r\n",swerveR);
	// swerve is zero don`t calc
	if(aimSpeed == 0)
	{
		//is only swerve
		*lSpeed = (swerveValue * MaxSpeed/128);
		*rSpeed = (swerveValue * MaxSpeed/128) * -1;
		return;
	}
	//R= L*Vin/(Vout-Vin)
	//Vin = 2*V - Vout
	//Vin = (swerveR*Vout)/(swerveR + LunW);
	double data = (LunW/2)*(tan((50 * ZqAbs(swerveValue)/128)*3.14159/180))*60/WHEEL;
	Vout = aimSpeed + data;
	Vin = aimSpeed - data;
	//Vout = (2*LunW*aimSpeed + 2*aimSpeed*swerveR)/(2*swerveR + LunW);
	//Vin = 2*aimSpeed - Vout;
	if(direct > 0)
	{
		//right
		V1 = Vout;
		V2 = Vin;
	}
	else
	{
		//left
		V1 = Vin;
		V2 = Vout;
		
	}
	*lSpeed = (int16_t)V1;
	*rSpeed = (int16_t)V2;	
	return;	
}

void setPidGains(float p,float i,float d)
{
	pid_set_gains(&l_pid,p,i,d);
	pid_set_gains(&r_pid,p,i,d);
}
SHELL_EXPORT_CMD(setpid,setPidGains,set pid pid value);
/***********************************
*func:
*parm:
*return:
*info:
***********************************/
void initPidTask()
{
	pid_init(&l_pid);
	pid_init(&r_pid);
	pid_set_gains(&l_pid,10,0,4);
	pid_set_gains(&r_pid,10,0,4);
}
/***********************************
*func:
*parm:
*return:
*info:
***********************************/
//10ms
void pidTask()
{
	static int timeCount = 0;
	if(timeCount ++ == 5)
	{
		//50ms
		
		float linex;
		float argular;
		// aim speed
		int16_t l_speed;
		int16_t r_speed;
		getHandShankData(&linex,&argular);
		getCanMotorCalcSpeed(linex,argular,&l_speed,&r_speed,100);		
		//get curSpeed
		stuEncodeData temp = getEncodeData();
		
		//calc
		
		//motor_pwm = pid_process(&pid, error);
		
		//set motor
		
	}
}

