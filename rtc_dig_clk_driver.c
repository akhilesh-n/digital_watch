#include "header.h"
#include <reg51.h>


void delay_ms(unsigned int ms)
{
unsigned char ch;
while(--ms)
{
ch=250;
while(--ch);
ch=247;
while(--ch);
	/*if(~(sw1)||~(sw2)||~(sw3)||~(sw4))
	{
		flag=1;
		return;
	}*/
}
}
