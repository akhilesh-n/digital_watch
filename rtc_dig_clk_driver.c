#include "header.h"
#include <reg51.h>
sbit SW1=P1^0;//increment
sbit SW2=P1^1;//next
sbit SW3=P3^3;//save n exit
sbit SW4=P3^2;//menu
u8 SNE=0;
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

//ext int0 isr

void interrupt_handler_0(void) interrupt 0 
{
RTC_SET=1;	
}

void enable_ext_int1(void) 
{
	EA=EX1=1;
	IT1=1;//edge triggered
}

//ext int1 isr

void interrupt_handler_1(void) interrupt 2 
{
SNE=1;	
}
u8 hex_to_int(u8 num)// 0x24--->24 ; not equqlent of 0x24
{
	u8 n;
	n=(num/16)*10 +(num%16);
	return n;
}

u8 int_to_hex(u8 num)
{
	return num;
}
void time_setting()
{
	u8 i_hr,i_min,i_sec;
	i_hr=hex_to_int(hr);
	i_min=hex_to_int(min);
	i_sec=hex_to_int(sec);
	
	while((SW2==1) && (SNE==0))//SNE save and exit flag will set by ext intr 1
	{
		lcd_cmd(0x1);
	lcd_string("set hour");
	lcd_cmd(0xc0);
		lcd_data((hr/16)+48);
	lcd_data((hr%16)+48);
		if(SW1==0)
		{
			i_hr++;
		hr=int_to_hex(i_hr);
		}
	}
	if(SNE==1)
	{
		SNE=0;
		goto set;
	}
	
	while((SW2==1) && (SNE==0))//SNE save and exit flag will set by ext intr 1
	{
		lcd_cmd(0x1);
	lcd_string("set min");
	lcd_cmd(0xc0);
		lcd_data((min/16)+48);
		lcd_data((min%16)+48);
		if(SW1==0)
		{
			i_min++;
		min=int_to_hex(i_min);
		}
	}
	if(SNE==1)
	{
		SNE=0;
		goto set;
	}
	
	while((SW2==1) && (SNE==0))//SNE save and exit flag will set by ext intr 1
	{
		lcd_cmd(0x1);
	lcd_string("set sec");
	lcd_cmd(0xc0);
		lcd_data((sec/16)+48);
		lcd_data((sec%16)+48);
		if(SW1==0)
		{
			i_sec++;
		sec=int_to_hex(i_sec);
		}
	}
	set:
	i2c_byte_write_frame(0xd0,0x2,i_hr);
	delay_ms(10);
	i2c_byte_write_frame(0xd0,0x1,i_min);
	delay_ms(10);
	i2c_byte_write_frame(0xd0,0x0,i_sec);
	delay_ms(10);
SNE=0;
}