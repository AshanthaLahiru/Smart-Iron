
void EEPROMSET(void);
void EEPROMGET(void);
unsigned char readEEPROM(unsigned char address);
void writeEEPROM(unsigned char address, unsigned char datas);


unsigned char readEEPROM(unsigned char address)
{
  EEADR = address; //Address to be read
  EEPGD = 0;//Selecting EEPROM Data Memory
  RD = 1; //Initialise read cycle
  return EEDATA; //Returning data
}

void writeEEPROM(unsigned char address, unsigned char datas)
{
  unsigned char INTCON_SAVE;//To save INTCON register value
  EEADR = address; //Address to write
  EEDATA = datas; //Data to write
  EEPGD = 0; //Selecting EEPROM Data Memory
  WREN = 1; //Enable writing of EEPROM
  INTCON_SAVE=INTCON;//Backup INCON interupt register
  INTCON=0; //Diables the interrupt
  EECON2=0x55; //Required sequence for write to internal EEPROM
  EECON2=0xAA; //Required sequence for write to internal EEPROM
  WR = 1; //Initialise write cycle
  INTCON = INTCON_SAVE;//Enables Interrupt
  WREN = 0; //To disable write
  while(EEIF == 0)//Checking for complition of write operation
  {
    //asm nop; //do nothing
  }
  EEIF = 0; //Clearing EEIF bit
}