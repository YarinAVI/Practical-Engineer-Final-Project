#include "REG_89C51.h"
#include "general.h"


//#define motor P2
sbit motor= P1^1;  //


int motor_pos = 0 ;

void servo_on(byte angle)
{
	byte i;
 			for(i=0;i<50;i++)				//0,60  P0_0
			{
			 	motor = 1;//0xA5;
//				msec(1);
				usec(angle);
//				usec(0);
				motor = 0;
				msec(22);
			//	motor_pos+=2;
			}	
}

void main()
{
//	byte i;
	motor=0;
	msec(1000);
//	while(1){
//		for(i=0;i<50;i++)				//0,60  P0_0
//			{
//			 	motor = 1;//0xA5;
////				msec(1);
//				usec(40);
//				usec(0);
//				motor = 0;
//				msec(22);
//			//	motor_pos+=2;
//			}
//				msec(3000);
//		 		for(i=0;i<50;i++)				//0,60  P0_0
//			{
//			 	motor = 1;//0xA5;
//				msec(1);
//				usec(95);
//				motor = 0;
//				msec(22);
//			//	motor_pos+=2;
//			}
//			msec(3000); 
//			}

while(1)
{
	 servo_on(45);
	 msec(2000);
	 servo_on(100);
	 msec(2000);
	 servo_on(150);
	 msec(2000);
	 servo_on(180);
	 msec(2000);
}
//	while(1)
//	{	
//	while(motor_pos<60)	
//	{	for(i=0;i<20;i++)				//0,60  P0_0
//			{
//			 	motor = 1;//0xA5;
//				msec(1);
//				usec(motor_pos);
//				motor = 0;
//				msec(22);
//				motor_pos+=2;
//			} }
//			  			msec(1000);
//		while(motor_pos>0)
//		 {for(i=0;i<20;i++)
//			{
//			 	motor = 1;//0xA5;
//				msec(1);
//				usec(motor_pos);
//				motor = 0;
//				msec(22);
//				motor_pos-=2;
//			} }
//			msec(1000);
//	}
}
