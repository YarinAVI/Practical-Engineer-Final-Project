#include "REG_89C51.h"
#include "general.h"
#include "lcdp2.h"
//#include "keyb.h"
//#include "uart.h"

//void test_keyb(void)
//{
//	byte x;
//	set_lcd(0,0xC0);
//	while(1){
//			 x=getkey(); 
//			 set_lcd(1,x);
//			 
//			}
//}

void main()
{
//	byte x;
	init_lcd();
//	init_uart();
//	transmit_string("TEST uart");
//	transmit_byte(0x0d);transmit_byte(0x0a);  //enter
   	lcd_puts(0x83,"My Project");
	while(1);
//	lcd_puts(0xC0,"TEST KEYB");
//	set_lcd(0,0xc0);
//	test_keyb();
/*	while(1){
	x=recieve_byte();
	 transmit_byte(x);
	 set_lcd(1,x);
*/
//	P2 = 0;
////	transmit_string("TEST uart");
//	while(1){
//	x=recieve_byte();
//	set_lcd(1,x);
//	if(x == 'q')
//		while(x!='*') {x=getkey();transmit_byte(x);}
//
//}
}//main






 
