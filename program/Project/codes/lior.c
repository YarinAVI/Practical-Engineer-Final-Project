#include "REG_89C51.h"
#include "general.h"
#include "lcdp2.h"

void servo_init() {
	CCAP2H=244;
	CCAP3H=244;
	CCAP4H=244;
}


void main() { 
		  TMOD=0x12;
	TH0=0xB8;
	TL0=0xB8;
	TR0=1;
	CCAPM2=0x42;
	CCAPM3=0x42;
	CCAPM4=0x42;
  CMOD=4;
	CCON=0x40;
	servo_init();
	
	while(1) {

	CCAP4H=230;
	msec(1000);
	CCAP4H=244;
	msec(1000);
	}
	}