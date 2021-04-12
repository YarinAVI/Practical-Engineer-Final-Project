#include "REG_89C51.h"
#include "general.h"
#include "lcdp2.h"

#define bit_IR P3_7

byte data arr_remote[4];

bit remote()
{
 	byte data num,num_bit,len_arr;
	uint data time_units;
	//=========== 16T =============//
	TL0=TH0=0;
	TR0=1;	
	while(!bit_IR);//bit_IR up
    TR0=0; //stop timer
	time_units =TH0;
	time_units =time_units <<8;//shift left 8
    time_units =time_units |TL0; //
    if(time_units <11060 && time_units >6248)// check 16T
	{
	   //============= 8T =============//	
		TL0=TH0=0;
	    // TMOD=1;
		 TR0=1;	
		while(bit_IR);//bit_IR down
   		TR0=0; //stop timer
		time_units =TH0;
		time_units =time_units <<8;
 		time_units =time_units |TL0;  
		if(time_units <6248 && time_units >3124)
		{ 
		 //========= start of Tishdoret =========//
			for(len_arr=0;len_arr<4;len_arr++)	
	      	{
			 	num=0;	
		        for(num_bit=0;num_bit<8;num_bit++)
		     	{//==== 1T =======//	
	                while(!bit_IR);//bit_IR up  	            
					//===== 3T ======//
					  //TMOD=1;
					  TL0=TH0=0;
					  TR0=1;
					   while(bit_IR); //bit_IR down
    				  TR0=0; //stop timer
					  time_units =TH0;
				      time_units =time_units <<8;
    				  time_units =time_units |TL0;
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
}//end of remote

void main()
{ 
    init_lcd();
    TMOD=1;//timer 0 mode 1
	lcd_puts(0x80,"address  ");
	lcd_puts(0xC0,"data     ");
 // ==========================================//
	   while(1)
		 { 
			while(bit_IR);//bit_IR down
 			if(remote())
			{
 			  set_lcd(0,0x88);
			  set_lcd(1,arr_remote[0]/10+0x30);
	      set_lcd(1,arr_remote[0]%10+0x30);
			  set_lcd(0,0xC8);
		    set_lcd(1,arr_remote[2]/10+0x30);
	      set_lcd(1,arr_remote[2]%10+0x30);  
		 	}
	  }
}