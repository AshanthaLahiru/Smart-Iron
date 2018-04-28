/* 
 * File:   DateTimeDisplay.h
 * Author: Lahiru
 *
 * Created on May 5, 2016, 7:41 AM
 */
void DisplayTimeToLCD( unsigned char* pTimeArray );
void DisplayDateOnLCD( unsigned char* pDateArray );


void DisplayTimeToLCD( unsigned char* pTimeArray )   // Displays time in HH:MM:SS AM/PM format
{
	//ClearLCDScreen();      // Move cursor to zero location and clear screen
    Lcd_Clear();
	// Display Hour
    Lcd_Set_Cursor(1,1);
	Lcd_Write_Char((pTimeArray[2]/10)+0x30 );
    Lcd_Set_Cursor(1,2);
	Lcd_Write_Char((pTimeArray[2]%10)+0x30 );
    Lcd_Set_Cursor(1,3);
	//Display ':'
	Lcd_Write_Char(':');

	//Display Minutes
    Lcd_Set_Cursor(1,4);
	Lcd_Write_Char((pTimeArray[1]/10)+0x30 );
    Lcd_Set_Cursor(1,5);
	Lcd_Write_Char((pTimeArray[1]%10)+0x30 );
    
    Lcd_Set_Cursor(1,6);
	//Display ':'
	Lcd_Write_Char(':');
    Lcd_Set_Cursor(1,7);
	//Display Seconds
	Lcd_Write_Char((pTimeArray[0]/10)+0x30 );
    Lcd_Set_Cursor(1,8);
	Lcd_Write_Char((pTimeArray[0]%10)+0x30 );
    
    Lcd_Set_Cursor(1,9);
	//Display Space
	Lcd_Write_Char(' ');
    Lcd_Set_Cursor(1,10);
	// Display mode
	switch(pTimeArray[3])
	{
	case AM_Time:	Lcd_Write_String("AM");	break;
	case PM_Time:	Lcd_Write_String("PM");	break;

	default: //Lcd_Write_Char('H');	
            break;
	}
}




void DisplayDateOnLCD( unsigned char* pDateArray )   // Displays Date in DD:MM:YY @ Day format
{
	Lcd_Set_Cursor(2,1);      // Move cursor to second line
	// Display Date
	Lcd_Write_Char( (pDateArray[1]/10)+0x30 );
    Lcd_Set_Cursor(2,2);
	Lcd_Write_Char( (pDateArray[1]%10)+0x30 );
    Lcd_Set_Cursor(2,3);
	//Display '/'
	Lcd_Write_Char('/');
    Lcd_Set_Cursor(2,4);
	//Display Month
	Lcd_Write_Char( (pDateArray[2]/10)+0x30 );
    Lcd_Set_Cursor(2,5);
	Lcd_Write_Char( (pDateArray[2]%10)+0x30 );
    Lcd_Set_Cursor(2,6);
	//Display '/'
	Lcd_Write_Char('/');
    Lcd_Set_Cursor(2,7);
	//Display Year
	Lcd_Write_Char( (pDateArray[3]/10)+0x30 );
    Lcd_Set_Cursor(2,8);
	Lcd_Write_Char( (pDateArray[3]%10)+0x30 );
    Lcd_Set_Cursor(2,9);
	//Display Space
	Lcd_Write_Char(' ');
    Lcd_Set_Cursor(2,10);
	// Display Day
	switch(pDateArray[0])
	{
	case Monday:	Lcd_Write_String("MON");	break;
	case Tuesday:	Lcd_Write_String("TUE");	break;
	case Wednesday:	Lcd_Write_String("WED");	break;
	case Thursday:	Lcd_Write_String("THU");	break;
	case Friday:	Lcd_Write_String("FRI");	break;
	case Saturday:	Lcd_Write_String("SAT");	break;
	case Sunday:	Lcd_Write_String("SUN");	break;

	default: Lcd_Write_String("???");	break;
	}
}

