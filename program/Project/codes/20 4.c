// wirtten by Yarin Avisidris & Idan Lisha and guided by Ludmila koz
#include "REG_89C51.h"
#include "general.h"
#include "lcdp2.h"
#define bit_IR P3_7
bit flag=0;
sbit trig=P3^6;
sbit echo=P3^3; // echo=gate=p3.3
byte data arr_remote[4];
uint time,dist;
//=================== ULTRASONIC SENSOR INTERRUPTS AND FUNTIONS================
void us_trig() {// trigger function for ultrasonic sensor
	 trig=1;
	 nop();nop();nop();// delay of  14us requirements are atleast 10us for sr_04 Trigger
	 trig=0;
	msec(50);
}// end trigger
void distance() interrupt 2 { // interrupt function (echo falls int1 interrupt)
	time =TH1;
	time =time<<8;//shift left 8
  time =time|TL1; //
	dist=time/58;
	TH1=TL1=0;
	flag=1;
}
//======================END OF ULTRASONIC SENSOR INTERRUPTS AND FUNCTIONS======
//====================================REMOTE IR FUNCTION=============================

bit remote()
{
 	byte data num,num_bit,len_arr;
	uint data time_units;
	//=========== 16T =============//

	TL1=TH1=0;
	TR1=1;	
	while(!bit_IR);//bit_IR up
    TR1=0; //stop timer
	time_units =TH1;
	time_units =time_units <<8;//shift left 8
    time_units =time_units |TL1; //
    if(time_units <11060 && time_units >6248)// check 16T
	{
	   //============= 8T =============//	
		TL1=TH1=0;
		 TR1=1;	
		while(bit_IR);//bit_IR down
   		TR1=0; //stop timer
		time_units =TH1;
		time_units =time_units <<8;
 		time_units =time_units |TL1;  
		if(time_units <6248 && time_units >3124)
		{ 
		 //========= start of transmitting(DATA) =========//
			for(len_arr=0;len_arr<4;len_arr++)	
	      	{
			 	num=0;	
		        for(num_bit=0;num_bit<8;num_bit++)
		     	{//==== 1T =======//	
	                while(!bit_IR);//bit_IR up  	            
					//===== 3T ======//
					  TL1=TH1=0;
					  TR1=1;
					   while(bit_IR); //bit_IR down
    				  TR1=0; //stop timer
					  time_units =TH1;
				      time_units =time_units <<8;
    				  time_units =time_units |TL1;
   				       if(time_units <1823 && time_units >1041)//3t
			     			 num|=1<<num_bit;		
				}//for8       	 	        	  
	            arr_remote[len_arr]=num;
		 	}//for4		
		if(arr_remote[0]==~arr_remote[1]) //address && !address
					if(arr_remote[2]==~arr_remote[3])
						return 1;
		return 0;	 
		 } // 8t
    	return 0 ;
       }//16t check
     return 0;
}
//====================================== END OF REMOTE FUNCTION================
//============================== Start of DC motors functions=====================
void forward()
{
	P1_0=0;	P1_2=1;
	P1_1=1; P1_3=0;

}
void backward() {
	P1_0=1;	P1_2=0;
	P1_1=0; P1_3=1;

}
void left() {
	P1_0=1;	P1_2=1;
	P1_1=0; P1_3=0;

}
void right() {
	P1_0=0;	P1_2=0;
	P1_1=1; P1_3=1;

	
}
void motorstop() {
	P1_0=0;	P1_2=0;
	P1_1=0; P1_3=0;
	
}
void servo_x(bit control) {
	if(control==1 & CCAP2H>230 ) CCAP2H--; // 1 LOGIC AT CONTROL IS ADDIN ANGLE
  if(control==0 & CCAP2H<244 ) CCAP2H++; // 0 LOGIC AT CONTROL IS SUB ANGLE
	}	
void servo_y(bit control) {
	if(control==1 & CCAP3H>230 ) CCAP3H--; // 1 LOGIC AT CONTROL IS ADDIN ANGLE
  if(control==0 & CCAP3H<244 ) CCAP3H++; // 0 LOGIC AT CONTROL IS SUB ANGLE
	}
void servo_init() {
	CCAP1H=244;
	CCAP2H=238;
	CCAP3H=244;
	CCAP4H=244;
}
//============================= end of DC Motors functions==========================
void main()
{ 

  bit A=0;
	byte f;
	byte prev=10000;
  init_lcd();
	servo_init();
	start:
  TMOD=0x12;//timer 0 8 bit auto reload pwm for servo motor, timer1 mode1(ir config)
		TH0=0xB8;
	TL0=0xB8;
	TR0=1;
	CCAPM1=0x42;
	CCAPM2=0x42;
	CCAPM3=0x42;
	CCAPM4=0x42;
	CMOD=4;
	CCON=0x40;
	while(bit_IR) lcd_puts(0x84,"IR wait");//waiting for steady mode to fall (start of comm) 
		lcd_clr();
	   while(1)
		 {
			 if(remote()){
				switch(arr_remote[2]) {
					case _plus: lcd_clr();forward(); break;
					case _minus: lcd_clr(); backward();break;
					case _play: lcd_clr(); motorstop();break;
					case _left: lcd_clr(); left();break;
					case _right: lcd_clr(); right();break;
					case _6:  lcd_clr();  servo_x(1); break;
					case _4: lcd_clr(); servo_x(0); break;
					case _5: lcd_clr(); 
					          if(CCAP4H==244) CCAP4H=230; else CCAP4H=244; break; // open/close 
					case _2: lcd_clr(); servo_y(0); break;
          case _8: lcd_clr(); servo_y(1);	break;		
          case _spin: if(CCAP1H==244) CCAP1H=234; else CCAP1H=244; break;					
					case _test: lcd_clr();   TMOD=0x92;//timer 1 int1 interrupt for ultrasonic timer0 8bit autoreload for pwm
						EX1=1; //enabling interrupt 1
					  TR1=1; // running timer 1, timer runs when gate is 1.
						IT1=1; // falling edge interrupt 1
						EA=1; // enabling all interrupts
						TL1=TH1=0;
					  CCAP2H=238; // arm in middle
//					forward();
//					control();
//					while(1) {
//						
//												us_trig();
//						while(!flag);
//						flag=0;
//	set_lcd(0,0x85);
//	set_lcd(1,dist/100+0x30);
//	dist=dist%100;
//	set_lcd(1,dist/10+0x30);
//	set_lcd(1,dist%10+0x30);
//					}

												while(1) {
													A=0;
													while(A==0) { 
						if(dist<=20) {
						A=1;
						motorstop();
						}
            if(A==0) {						
            forward();
						msec(400);
						motorstop();
						}
						us_trig();
						while(!flag);
						flag=0;
						if(dist<=20 & A==0) {
							lcd_puts(0x84,"B");
						A=1;
						}
						
		
							 if(A==0) {
							CCAP1H=234;
						msec(400);
						us_trig();
						while(!flag);
						flag=0;
						if(dist>40) {
							//FINDING EXIT AT LEFT
							//AND EXITING THE ROOM 
							//FROM THE LEFT
							forward();
							msec(600);
							left();
							msec(1000);
							motorstop();
							forward();
							msec(2200);
							motorstop();
							lcd_puts(0x84,"I exited the room !");
							goto start;
						}
						///////
						///////           MOVING STRAIGHT CONTROL 
					  ///////
						///////
						if(dist<=15) {
							right();
								while(dist<=prev) {
							us_trig();
						while(!flag);
						flag=0;
							prev=dist;
						us_trig();
						while(!flag);
						flag=0;
							}
							
						}
						if(dist>=13) {
             left();							
							while(dist>=prev) {
							us_trig();
						while(!flag);
						flag=0;
							prev=dist;
						us_trig();
						while(!flag);
						flag=0;
							}
						
						}
					}
						//msec(500);
						CCAP1H=244;
					msec(100);
					
				}
						
					
						
						///// this is for EDGE solving when the car needs to rotate right with controll
				    /////
					
					  if(A==1) {
						CCAP1H=234;
					  msec(250);
						}
						while(A==1 ) {
							f=0;
							right();
							lcd_puts(0x84,"C");
							
							while(f<2) {
							us_trig();
						while(!flag);
						flag=0;
							prev=dist;
							
						us_trig();
						while(!flag);
						flag=0;
								if(dist>prev) f++;
							}
							CCAP1H=244;
							A=0;
							motorstop();
						}
					}// end while(1) automatic
					}
						
						
						
	
							
							
							

				}
			}
		}