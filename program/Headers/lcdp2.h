//===========================================================================
//                         "lcdp2.h"        
//===========================================================================
#ifndef __lcd_4_h__
#define __lcd_4_h__

#define RS_lcd     P2_0
#define RW_lcd     P2_1
#define E_lcd      P2_2
#define DATA_lcd   P2

//===========================================================================
void set_lcd1(bit char_command,byte lcd_d) 
{ 
   RW_lcd = 0 ; 		
   E_lcd = 0 ;
   RS_lcd = char_command ;
   DATA_lcd &= 0x87; 
   DATA_lcd |= ((lcd_d &0xf0 )>>1);
   E_lcd = 1 ;
   nop();
   E_lcd = 0 ;
   msec(3);
}

void set_lcd(bit char_command,byte lcd_d) 
{ 
   RW_lcd = 0 ; 		
   E_lcd = 1 ;
   RS_lcd =char_command ;
   DATA_lcd &= 0x87;
   DATA_lcd |= ((lcd_d &0xf0 )>>1);//write 4bit High
   E_lcd = 1 ;
   nop();
   E_lcd = 0 ;
 

   RW_lcd = 0 ; 		
   E_lcd = 1 ;
   RS_lcd = char_command ;
   DATA_lcd &= 0x87;
   DATA_lcd |= ((lcd_d &0x0f )<<3);//write 4bit Low
    E_lcd = 1 ;
   nop();
   E_lcd = 0 ;
   msec(3);
	
	
}


//===========================================================================
/*
 I/D - when high, cursor moves right DDRAM addr. inc. by 1
     - when low,  cursor moves left  DDRAM addr. dec. by 1
 SH  - Shift of entire display
 D   - Display on/off (high = on; low = off; Data stored)
 C   - Cursor  on/off (high = on; low = off; ID   stored)
 B   - Cursor blink on/off (high = blink on; low = blink off)
 S/C - 1 - display; 0 - cursor;
 R/L - 1 - right;   0 - left;
 DL  - Interface data length  ( 1 - 8 bit; 0 - 4 bit;)
 N   - Display line number (1 - two lines; 0 - one line;)
 F   - Display font type (1 - 5x11; 0 - 5x8;)
*/
//===========================================================================
void init_lcd() 
{

	msec(50);  // Recovery time after power on
  
   set_lcd1(0,0x30);//  0 0 1 DL N F 0 0    - FUNCTION SET - 8bit interface
   set_lcd1(0,0x30);//  0 0 1 DL N F 0 0    - FUNCTION SET - 8bit interface
   set_lcd1(0,0x30);//  0 0 1 DL N F 0 0    - FUNCTION SET - 8bit interface
   set_lcd1(0,0x2C);//  0 0 1 DL N F 0 0    - FUNCTION SET - 4bit interface

   set_lcd(0,0x2C);//  0 0 1 DL N F 0 0    - FUNCTION SET - 4bit interface

   set_lcd(0,0x0c);//  0 0 0 0 1 D C B     - DISPLAY ON/OFF CONTROL

   set_lcd(0,0x06);//  0 0 0 0 0 1 I/D SH  - ENTRY MODE SET

   set_lcd(0,0x14);//  0 0 0 1 S/C R/L 0 0 - CURSOR OR DISPLAY SHIFT

   set_lcd(0,0x01);//  0 0 0 0 0 0 0 1     - DISPLAY CLEAR

}//init_lcd()

void lcd_puts(byte location,const byte *str)
{
	set_lcd(0,location);
 	while(*str) set_lcd(1,*str++);
} //lcd_put_str(byte location,const byte *str)
void lcd_clr() {
	set_lcd(0,0x01);
}
#endif


//===========================================================================
//                   End Of File "lcd_p2.h"        
//===========================================================================

