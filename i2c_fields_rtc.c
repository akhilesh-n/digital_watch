//i2c_fields
#include"header.h"
#include<reg51.h>
#include<intrins.h>

sbit SDA=P2^0;
sbit SCL=P2^1;

//i2c fields.c

void i2c_start(void)
{
	SCL=1;
	SDA=1;
//	delay_ms(1); no need in 8051
	SDA=0;
}

void i2c_stop(void)
{
	SCL=0;
	SDA=0;
	SCL=1;
	SDA=1;
}

void i2c_write(u8 d)
{
	s8 i;
	for(i=7;i>=0;i--)
	{
		SCL=0;
		SDA=((d>>i)&1)?1:0;
		SCL=1;
	}
}

u8 i2c_read(void)
{
	s8 i;
	u8 temp=0;
	for(i=7;i>=0;i--)
	{
		SCL=1;
		if(SDA==1)
			temp|=(1<<i);
		else
			temp&=~(1<<i);
		SCL=0;//as per notes
	}
	return temp;
}

bit i2c_ack(void)
{
	SCL=0;
	SDA=1;
	SCL=1;
	
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	
	if(SDA==0)
	{
		SCL=0;//added line after each ack SCL must be zero not explained in class,refer data sheet m24c08
		return 0;
	}
	else
		{
		SCL=0;//added line
		return 1;
	}
	
}
void i2c_no_ack(void)
{
	//SCL=0; no need 
	SDA=1;
	SCL=1;
}