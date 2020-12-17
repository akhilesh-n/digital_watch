#include "header.h"
#include <reg51.h>
sbit NXT=P1^1;//next 
sbit INC=P3^3;//increment intrr
sbit MENU=P3^2;//menu intrrr
u8 INCR=0;
void delay_ms(unsigned int ms)
{
unsigned char ch;
while(--ms)
{
ch=250;
while(--ch);
ch=247;
while(--ch);
}
}

//ext int0 enable
void enable_ext_int0(void) 
{
	EA=EX0=1;
	IT0=1;//edge triggered
}



void interrupt_handler_0(void) interrupt 0 //ext int0 isr
{
RTC_SET=1;	
}

void enable_ext_int1(void) 
{
	EA=EX1=1;
	IT1=1;//edge triggered
}



void interrupt_handler_1(void) interrupt 2 //ext int1 isr
{
	INCR=1;
}
void time_setting()
{
	
		lcd_cmd(0x1);
	lcd_string("set hour");

	while(NXT==1)//SNE save and exit flag will set by ext intr 1
	{
		
	lcd_cmd(0xc0);
	lcd_data((hr/16)+48);
	lcd_data((hr%16)+48);
		
		if(INCR==1)
		{
			INCR=0;
			hr++;
			if(hr>0x23)
				hr=0;
			
			if((hr%16)>9)
				hr+=6;
		}
		if(RTC_SET==1)
	{
		RTC_SET=0;
		goto set;
	}
	}
	
	while(NXT==0);

	lcd_cmd(0x1);
	lcd_string("set min");	
	while(NXT==1)//SNE save and exit flag will set by ext intr 1
	{
	lcd_cmd(0xc0);
		lcd_data((min/16)+48);
		lcd_data((min%16)+48);
		
		if(INCR==1)
		{
			INCR=0;
			min++;
			if(min>0x59)
				min=0;
			if((min%16)>9)
			min+=6;
		}
			if(RTC_SET==1)
	{
		RTC_SET=0;
		goto set;
	}
	}

	while(NXT==0);

	lcd_cmd(0x1);
	lcd_string("set sec");
	while(NXT==1)//SNE save and exit flag will set by ext intr 1
	{
		lcd_cmd(0xc0);
		lcd_data((sec/16)+48);
		lcd_data((sec%16)+48);
		if(INCR==1)
		{
			INCR=0;
			sec++;
			if(sec>0x59)
				sec=0;
			if((sec%16)>9)
			sec+=6;
		}
		if(RTC_SET==1)
		{
			RTC_SET=0;
			goto set;
		}
	}

	while(NXT==0);

	lcd_cmd(0x1);
	lcd_string("set date");
	while(NXT==1)//
	{
		lcd_cmd(0xc0);
		lcd_data((dd/16)+48);
		lcd_data((dd%16)+48);
		if(INCR==1)
		{
			INCR=0;
			dd++;
			if(dd>0x31)
				dd=1;
			if((dd%16)>9)
			dd+=6;
		}
		if(RTC_SET==1)
		{
			RTC_SET=0;
			goto set;
		}
	}

	while(NXT==0);

	lcd_cmd(0x1);
	lcd_string("set month");
	while(NXT==1)//SNE save and exit flag will set by ext intr 1
	{
		lcd_cmd(0xc0);
		lcd_data((mm/16)+48);
		lcd_data((mm%16)+48);
		if(INCR==1)
		{
			INCR=0;
			mm++;
			if(mm>0x12)
				mm=1;
			if((mm%16)>9)
			mm+=6;
		}
		if(RTC_SET==1)
		{
			RTC_SET=0;
			goto set;
		}
	}

	while(NXT==0);

	lcd_cmd(0x1);
	lcd_string("set year");
	while(NXT==1)//SNE save and exit flag will set by ext intr 1
	{
		lcd_cmd(0xc0);
		lcd_data(2+48);
		lcd_data(0+48);
		lcd_data((yy/16)+48);
		lcd_data((yy%16)+48);
		if(INCR==1)
		{
			INCR=0;
			yy++;
			if(yy>0x99)
				yy=1;
			if((yy%16)>9)
			yy+=6;
		}
		if(RTC_SET==1)
		{
			RTC_SET=0;
			goto set;
		}
	}
	
	while(NXT==0);

	lcd_cmd(0x1);
	lcd_string("set week");
	while(NXT==1)//SNE save and exit flag will set by ext intr 1
	{
		lcd_cmd(0xc0);
		lcd_week(day);
		if(INCR==1)
		{
			INCR=0;
			day++;
			if(day>7)
				day=1;
		}
		if(RTC_SET==1)
		{
			RTC_SET=0;
			goto set;
		}
	}


	
	set:
	i2c_byte_write_frame(0xd0,0x2,hr);
	delay_ms(10);
	i2c_byte_write_frame(0xd0,0x1,min);
	delay_ms(10);
	i2c_byte_write_frame(0xd0,0x0,sec);
	delay_ms(10);
	i2c_byte_write_frame(0xd0,0x3,day);
	delay_ms(10);
	i2c_byte_write_frame(0xd0,0x4,dd);
	delay_ms(10);
	i2c_byte_write_frame(0xd0,0x5,mm);
	delay_ms(10);
	i2c_byte_write_frame(0xd0,0x6,yy);
	delay_ms(10);
lcd_cmd(0x01);
}
