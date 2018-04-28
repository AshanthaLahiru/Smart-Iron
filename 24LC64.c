#include "Includes.h"




// Function Purpose: Write_Byte_To_24LC64_EEPROM writes a single byte on given address
// Address can have any value fromm 0 to 0x1FFF, and DataByte can have a value of 0 to 0xFF.
void Write_Byte_To_24LC64_EEPROM(unsigned int Address, unsigned char DataByte)
{
	I2C_Start();										// Start i2c communication

	// Send i2c address of 24LC64 with write command
	while(I2C_Write_Byte(Device_Address_24LC64_EEPROM + 0) == 1)// Wait until device is free
	{	I2C_ReStart();	}		

	I2C_Write_Byte(Address>>8);							// Write Address upper byte
	I2C_Write_Byte((unsigned char)Address);				// Write Address lower byte
	I2C_Write_Byte(DataByte);							// Write data byte
	I2C_Stop();											// Stop i2c communication
}



// Function Purpose: Read_Byte_From_24LC64_EEPROM reads a single byte from given address
// Address can have any value fromm 0 to 0x1FFF.
unsigned char Read_Byte_From_24LC64_EEPROM(unsigned int Address)
{
	unsigned char Byte = 0;								// Variable to store Received byte

	I2C_Start();										// Start i2c communication

	// Send i2c address of 24LC64 with write command
	while(I2C_Write_Byte(Device_Address_24LC64_EEPROM + 0) == 1)// Wait until device is free
	{	I2C_ReStart();	}		

	I2C_Write_Byte(Address>>8);							// Write Address upper byte
	I2C_Write_Byte((unsigned char)Address);				// Write Address lower byte
	I2C_ReStart();										// Restart i2c

	// Send i2c address of 24LC64 EEPROM with read command	
	I2C_Write_Byte(Device_Address_24LC64_EEPROM + 1);		

	Byte = I2C_Read_Byte();								// Read byte from EEPROM

	I2C_Send_NACK();									// Give NACK to stop reading
	I2C_Stop();											// Stop i2c communication

	return Byte;				// Return the byte received from 24LC64 EEPROM
}



// Function Purpose: Write_Page_To_24LC64_EEPROM writes a page on given address
// Address can have value 0, 32, 64, .... only and pData is pointer to the array
// containing NoOfBytes bytes in it. NoOfBytes can have a value from 1 to 32 only.
void Write_Page_To_24LC64_EEPROM(unsigned int Address,unsigned char* pData,unsigned char NoOfBytes)
{
	unsigned int i;

	I2C_Start();										// Start i2c communication

	// Send i2c address of 24LC64 with write command
	while(I2C_Write_Byte(Device_Address_24LC64_EEPROM + 0) == 1)// Wait until device is free
	{	I2C_ReStart();	}	

	I2C_Write_Byte(Address>>8);							// Write Address upper byte
	I2C_Write_Byte((unsigned char)Address);				// Write Address lower byte

	for(i=0;i<NoOfBytes;i++)							// Write NoOfBytes
		I2C_Write_Byte(pData[i]);						// Write data byte

	I2C_Stop();											// Stop i2c communication
}




// Function Purpose: Read_Bytes_From_24LC64_EEPROM reads a NoOfBytes bytes from given starting address.
// Address can have any value fromm 0 to 0x1FFF. Also, NoOfBytes can have any value 0 to 0x1FFF.
// Read bytes are returned in pData array.
void Read_Bytes_From_24LC64_EEPROM(unsigned int Address, unsigned char* pData, unsigned int NoOfBytes)
{
	unsigned int i;

	I2C_Start();										// Start i2c communication

	// Send i2c address of 24LC64 with write command
	while(I2C_Write_Byte(Device_Address_24LC64_EEPROM + 0) == 1)// Wait until device is free
	{	I2C_ReStart();	}		

	I2C_Write_Byte(Address>>8);							// Write Address upper byte
	I2C_Write_Byte((unsigned char)Address);				// Write Address lower byte
	I2C_ReStart();										// Restart i2c

	// Send i2c address of 24LC64 EEPROM with read command	
	I2C_Write_Byte(Device_Address_24LC64_EEPROM + 1);		

	pData[0] = I2C_Read_Byte();							// Read First byte from EEPROM

	for(i=1;i<NoOfBytes;i++)							// Read NoOfBytes
	{		
		I2C_Send_ACK();					// Give Ack to slave to start receiving next byte
		pData[i] = I2C_Read_Byte();		// Read next byte from EEPROM
	}

	I2C_Send_NACK();									// Give NACK to stop reading
	I2C_Stop();											// Stop i2c communication
}