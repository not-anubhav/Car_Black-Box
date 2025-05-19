#include "black_box.h"

void write_external_eeprom(unsigned char address1,  unsigned char data)
{
	i2c_start();
	i2c_write(EE_SLAVE_WRITE);
	i2c_write(address1);
	i2c_write(data);
	i2c_stop();
    for(unsigned int wait = 3000; wait--; );
}

unsigned char read_external_eeprom(unsigned char address1)
{
	unsigned char data;

	i2c_start();
	i2c_write(EE_SLAVE_WRITE);
	i2c_write(address1);
	i2c_rep_start();
	i2c_write(EE_SLAVE_READ);
	data = i2c_read();
	i2c_stop();

	return data;
}