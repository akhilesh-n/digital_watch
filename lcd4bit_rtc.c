#include<reg51.h>
#include"header.h"
//#include <string.h>

sbit RS=P3^4;
sbit RW=P3^5;
sbit EN=P3^6;

void lcd_init()
{
	lcd_cmd(0x2);//compulsory in hw curser set to home not clr
	lcd_cmd(0x28);//init into 8 bitmode
	lcd_cmd(0xe);//cursor on
	lcd_cmd(0x1);//clr scr n set cursor to home
}
void lcd_data(u8 ch)
{
	P0=ch>>4;
	RS=1;
	RW=0;
	EN=1;
	delay_ms(2);
	EN=0;
	
	P0=ch&0x0f;
	RS=1;
	RW=0;
	EN=1;
	delay_ms(2);
	EN=0;
}

void lcd_cmd(u8 cmd)
{
	P0=cmd>>4;
	RS=0;
	RW=0;
	EN=1;
	delay_ms(2);
	EN=0;
	P0=cmd&0x0f;
	RS=0;
	RW=0;
	EN=1;
	delay_ms(2);
	EN=0;
}


void lcd_string(u8 *str)
{
	while(*str)
	{
		lcd_data(*str);
		str++;	
	}
}
void lcd_week(u8 day)
{
	switch(day)
	{
		case 1: lcd_string("SUN");
						break;
		case 2: lcd_string("MON");
						break;
		case 3: lcd_string("TUE");
						break;
		case 4: lcd_string("WED");
						break;
		case 5: lcd_string("THU");
						break;
		case 6: lcd_string("FRI");
						break;
		case 7: lcd_string("SAT");
						break;
	}
}

