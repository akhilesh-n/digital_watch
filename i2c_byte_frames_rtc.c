//i2c byte frame
#include"header.h"
#include<reg51.h>

void i2c_byte_write_frame(u8 sa,u8 ma,u8 d)
{
	bit res;
	i2c_start();
	
	i2c_write(sa);//sa(7bit) with write(1bit) option
	res=i2c_ack();
/*	if(res==1)
	{
		//uart_string("sa+w error in write\n");
		goto out;
	}*/
	
	i2c_write(ma);//write 8 bit ma
	res=i2c_ack();
	if(res==1)
	{
		//uart_string("ma+w error in write\n");
		goto out;
	}
	
	i2c_write(d);//write 8 bit data
	res=i2c_ack();
	if(res==1)
	{
		//uart_string("d+w error in write\n");
		goto out;
	}
	out:
	i2c_stop();
}
	
	
u8 i2c_byte_read_frame(u8 sa,u8 ma)
{
	bit res;
	u8 temp;
	i2c_start();
	
	i2c_write(sa);//sa with write option
	res=i2c_ack();
	if(res==1)
	{
		//uart_string("sa+w write error in read\n");
		goto out;
	}
	
	i2c_write(ma);//ma with write option
	res=i2c_ack();
	if(res==1)
	{
		//uart_string("ma+w write error in read\n");
		goto out;
	}
	
	//i2c_restart();
	i2c_start();
	
	i2c_write(sa|1);
	res=i2c_ack();
	if(res==1)
	{
		//uart_string("sa+r write error in read\n");
		goto out;
	}
	
	temp=i2c_read();
	i2c_no_ack();
	
	out:
		i2c_stop();
	return temp;
}