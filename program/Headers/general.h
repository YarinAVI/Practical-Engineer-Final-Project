//	for P89V51RD2  
#ifndef __general_h__
#define __general_h__

typedef unsigned char  byte;
typedef unsigned int   uint;

#define ACK 0
#define NACK 1
#define TRUE 1
#define FALSE 0
//================= IR CODES DEFINED =============================
#define _0 22
#define _1 12
#define _2 24
#define _3 94
#define _4 8
#define _5 28
#define _6 90
#define _7 66
#define _8 82
#define _9 74
#define _plus 64
#define _minus 25
#define _play 21
#define _right 9
#define _left 7
#define _test 68
#define _spin 67
#define _menu 71
#define _shutdown 69
//=============================== end ir codes define===============================


void msec(uint ms);
void nop(void);


void nop(void){ } // delay 5usec


void msec(uint ms)
{
	uint n;
	uint i;
	//ms=ms*4.11;

	for (n=0; n<ms; n++)
	{
		for (i=0; i<112; i++); 
	} 
}

void usec(uint us)
{ 
    while(us--) nop();
}
#endif