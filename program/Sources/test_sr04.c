#include "REG_89C51.h"
#include "general.h"
#include "lcd_4.h"
#include "keyb.h"
#include "dist.h"


uint dist;//k=0,j=0,m=0,n=0,i=0;

void reverse(void)
{
 	while(1) us_sr04(B);	 // back
	
}

void distance_forw(void)
{	uint time_us,i;
   TL0=0x00; TH0=0x00;
	trig1=1;
    i=1;i=2;i=3;i=4;i=5;i=6;i=7;i=8; i=9;	  //10usec
	trig1=0;

	 usec(1);//20 usec ;  
	 usec(1);//20 usec ;

	 TR0=1; 
	 if(echo1){
	 while(echo1);
	 TR0=0;

	time_us=TH0;
	time_us=(time_us<<8)+TL0;
	dist=(time_us/58+66) ; //K=58
	set_lcd(0,0x80);
	display(dist);}
}
void distance_backw(void)
{		uint time_us,i;

   TL0=0x00; TH0=0x00;
	 trig2=1;
    i=1;i=2;i=3;i=4;i=5;i=6;i=7;i=8; i=9;	  //10usec
	trig2=0;

	 usec(1);//20 usec ;  
	 usec(1);//20 usec ;

	TR0=1; 
	if(echo2){
	while(echo2);
	TR0=0;

	time_us=TH0;
	time_us=(time_us<<8)+TL0;
	dist=(time_us/58+66) ; //K=58
	set_lcd(0,0xc0);
	display(dist);
	if (dist<250) {	//lcd_puts(0x86,"STOP");
										 
				lcd_puts(0xc7,"Stay away"); }

	else {      lcd_puts(0xc7,"         "); }
	}	 
}


void main()
{

	trig1=0;
	trig2=0;
	init_lcd();

	set_lcd(0,0x85);
		while(1)
		 {
			distance_backw();	 // back
			distance_forw();	 // forward	
		}
	  

}