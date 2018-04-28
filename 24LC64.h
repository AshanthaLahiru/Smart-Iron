
#ifndef __24LC64_H
#define __24LC64_H


// Define 24LC64 i2c device address0xA0
#define Device_Address_24LC64_EEPROM	0xA0


// Function Declarations
void Write_Byte_To_24LC64_EEPROM(unsigned int, unsigned char);
unsigned char Read_Byte_From_24LC64_EEPROM(unsigned int);
void Write_Page_To_24LC64_EEPROM(unsigned int, unsigned char*, unsigned char);
void Read_Bytes_From_24LC64_EEPROM(unsigned int, unsigned char*, unsigned int);

#endif