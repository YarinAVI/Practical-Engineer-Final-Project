#include "REG_89C51.h"
#include "general.h"



void main()
{
	while(1){
		P3_4=1;
		usec(1);
		P3_4=0;
		usec(1);
}
	}