#include"header.h"
#include<reg51.h>
u8 RTC_SET=0,IS_AM=1,IS_24=1;
u8 hr,min,sec,dd,mm,yy,day;

void main()
{

	lcd_init();
	enable_ext_int0();
	enable_ext_int1();
	i2c_byte_write_frame(0xd0,0x2,0x20);
	delay_ms(10);
	i2c_byte_write_frame(0xd0,0x1,0x10);
	delay_ms(10);
	i2c_byte_write_frame(0xd0,0x0,0x10);
	delay_ms(10);
	i2c_byte_write_frame(0xd0,0x3,0x5);//day
	delay_ms(10);
	i2c_byte_write_frame(0xd0,0x4,0x17);//date dd
	delay_ms(10);
		i2c_byte_write_frame(0xd0,0x5,0x12);//month mm
	delay_ms(10);
		i2c_byte_write_frame(0xd0,0x6,0x20);//year yy
	delay_ms(10);
	while(1)
	{
		if(RTC_SET==1)
		{
			//timer setting
			RTC_SET=0;
			time_setting();
	
		}
	hr=i2c_byte_read_frame(0xd0,0x2);
	min=i2c_byte_read_frame(0xd0,0x1);
	sec=i2c_byte_read_frame(0xd0,0x0);
	day=i2c_byte_read_frame(0xd0,0x3);
	dd=i2c_byte_read_frame(0xd0,0x4);
	mm=i2c_byte_read_frame(0xd0,0x5);
	yy=i2c_byte_read_frame(0xd0,0x6);
	lcd_cmd(0x80);
	lcd_cmd(0xc);
		if(IS_24==1)
		{
			lcd_data((hr/16)+48);
			lcd_data((hr%16)+48);
		}
		else
		{
			lcd_data(((hr&(~(0x60)))/16)+48);
			lcd_data(((hr&(~(0x60)))%16)+48);
		}
	lcd_data(':');
	lcd_data((min/16)+48);
	lcd_data((min%16)+48);
	lcd_data(':');
	lcd_data((sec/16)+48);
	lcd_data((sec%16)+48);
	if(IS_24==0)
	{
		lcd_cmd(0x80+14);
		if(IS_AM==1)
		{
			lcd_data('A');
			lcd_data('M');
		}
		else
		{
			lcd_data('P');
			lcd_data('M');
		}
	}
	lcd_cmd(0xc0);
	lcd_data((dd/16)+48);
	lcd_data((dd%16)+48);
	lcd_data('/');
	lcd_data((mm/16)+48);
	lcd_data((mm%16)+48);
	lcd_data('/');
	lcd_data((yy/16)+48);
	lcd_data((yy%16)+48);
	lcd_cmd(0xc0+13);
	lcd_week(day);
}
}