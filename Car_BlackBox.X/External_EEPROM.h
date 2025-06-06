#ifndef EXTERNAL_EEPROM_H
#define EXTERNAL_EEPROM_H

#define EE_SLAVE_READ		0xA1
#define EE_SLAVE_WRITE		0xA0


void write_external_eeprom(unsigned char address1,  unsigned char data);
unsigned char read_external_eeprom(unsigned char address1);

#endif