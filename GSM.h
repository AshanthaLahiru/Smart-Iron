/* 
 * File:   GSM.h
 * Author: Lahiru
 *
 * Created on January 22, 2016, 9:24 PM
 */

void SendMsg_Inti();
void Msg_Setup();
void InitUART(int BAUDRATE);
char BusyUART(void);
void SendByteSerially(unsigned char Byte);
void SendStringSerially(const unsigned char* st);
void GSM_Send(void);

void SendMsg_Inti()
{
  SendStringSerially("AT+CMGF=1");
  SendByteSerially((char)13);
  __delay_ms(1000);
}
 

char txt[20];
void Msg_Setup()
{  
    sprintf(txt,"AT+CMGS=\"%s\"\r",number);
    SendStringSerially(txt);
    __delay_ms(1000);
    SendStringSerially("I'm your safety iron unit. Unexpected situation has occurred. Check it ASAP!");
    SendByteSerially((char)26);
    __delay_ms(1000);
}

void InitUART(int BAUDRATE)
{
	TRISC6 = 0;   					// TX Pin
	TRISC7 = 1;   					// RX Pin

	SPBRG = ((_XTAL_FREQ/16)/BAUDRATE) - 1;
	BRGH  = 1;                   	// Fast baudrate
	SYNC  = 0;						// Asynchronous
	SPEN  = 1;						// Enable serial port pins
	CREN  = 1;						// Enable reception
	SREN  = 0;						// No effect
	TXIE  = 0;						// Disable tx interrupts
	RCIE  = 1;						// Enable rx interrupts
	TX9   = 0;						// 8-bit transmission
	RX9   = 0;						// 8-bit reception
	TXEN  = 0;						// Reset transmitter
	TXEN  = 1;						// Enable the transmitter
}

char BusyUART(void)
{
    if (!TXIF)
        return 1;
    else
    {
        TXIF = 0; //Clear busy flag
        return 0;
    }
}

void SendByteSerially(unsigned char Byte)  // Writes a character to the serial port
{
	while(!TXIF);  // wait for previous transmission to finish
	TXREG = Byte;
}

void SendStringSerially(const unsigned char* st)
{
	while(*st)
		SendByteSerially(*st++);
}

void GSM_Send(void)
{
    InitUART(9600);
    __delay_ms(1000);
    SendMsg_Inti();
    __delay_ms(1000);
    Msg_Setup();    
    __delay_ms(1000); 
}

    




