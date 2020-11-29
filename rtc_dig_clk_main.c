#include"header.h"
#include<reg51.h>
u8 RTC_SET=0;
u8 hr,min,sec;

void main()
{

	lcd_init();
	enable_ext_int0();
	i2c_byte_write_frame(0xd0,0x2,0x23);
	delay_ms(10);
	i2c_byte_write_frame(0xd0,0x1,0x59);
	delay_ms(10);
	i2c_byte_write_frame(0xd0,0x0,0x59);
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
	lcd_cmd(0x80);
	lcd_cmd(0xc);
	lcd_data((hr/16)+48);
	lcd_data((hr%16)+48);
		lcd_data(':');
		lcd_data((min/16)+48);
		lcd_data((min%16)+48);
		lcd_data(':');
		lcd_data((sec/16)+48);
		lcd_data((sec%16)+48);
}
}