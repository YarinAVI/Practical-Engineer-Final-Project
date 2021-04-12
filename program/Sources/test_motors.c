#include "REG_89C51.h"
#include "general.h"
#include "lcdp2.h"


void main()
{
//	byte x;
	init_lcd();
	while(1) {
	lcd_puts(0x83,"Forward");
	forward();
	msec(6000);
		lcd_puts(0x83,"Backward");
	backward();
		msec(6000);
	}

//	{
//		x=getkey();
//		switch (x)
//		{
//		 	case '2': forward();break;
//			case '8': backward();break;
//			case '5': stop();break;
//			case '1': forw_l();break;
//			case '3': forw_r();break;
//			case '4': spin_l();break;
//			case '6': spin_r();break;
//		}
//	 	
//	}
}