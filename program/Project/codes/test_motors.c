#include "REG_89C51.h"
#include "general.h"
#include "lcdp2.h"
void forward()
{
	P1_4=1;	P1_6=0;
	P1_5=0; P1_7=1;
}
void backward() {
	P1_4=0;	P1_6=1;
	P1_5=1; P1_7=0;
}
int  ultra (void) {
	uint time_us,dist;
	TL0=0x00; TH0=0x00;
	usec(2.7);
	TR0=1;
//	P3_2=1;
		//while(P3_2);
	msec(10);
	TR0=0;
	time_us=TH0;
	time_us=(time_us<<8)+TL0;
//	 dist=(time_us/58+66);
	return time_us;
}
void main()
{
//	byte x;
	TMOD=0x9;
	
//	IT0=1; EX0=1; EA=1;
	init_lcd();
	while(1) {
		usec(5);
	P3_4=1;
	usec(1.2);
	P3_4=0;
	usec(1.2);
		if(ultra>=0.020) {
			lcd_puts(0x87,"no");
		}
		else {
			lcd_puts(0x87,"Yes");
	}
		
	}
}