/* 
 * File:   keypad.h
 * Author: Lahiru
 *
 * Created on April 27, 2016, 9:28 AM
 */

#define RowA		RB0
#define RowB		RB1
#define RowC		RB2
#define RowD		RB3
#define C1			RB4
#define C2			RB5
#define C3			RB6
#define C4			RB7

#define Keypad_PORT			PORTB
#define Keypad_PORT_Dir		TRISB	


// Function declarations
void InitKeypad(void);
char GetKey(void);

char number[15]; //User entered number
int x=0,a=0,b=0,c=0,d=0,e=0,f=0,g=0,h=0;         //Global counter for number array
unsigned char hh[5],mm[5],ss[5],ap[5],DD[5],MM[5],YY[5],DAY[10],cDAY[5];
// Function name: InitKeypad
void InitKeypad(void)
{
	Keypad_PORT	    = 0x00;	// Set Keypad port pin values zero
	Keypad_PORT_Dir = 0xF0;	// Last 4 pins input, First 4 pins output

	// Enable weak internal pull up on input pins
	OPTION_REG &= 0x7F;
}



// Function name: READ_SWITCHES
// Scan all the keypad keys to detect any pressed key.
char READ_SWITCHES(void)	
{	
	RowA = 0; RowB = 1; RowC = 1; RowD = 1; 	//Test Row A

	if (C1 == 0) { __delay_ms(250); while (C1==0); return '1'; }
	if (C2 == 0) { __delay_ms(250); while (C2==0); return '2'; }
	if (C3 == 0) { __delay_ms(250); while (C3==0); return '3'; }
	if (C4 == 0) { __delay_ms(250); while (C4==0); return '/'; }

	RowA = 1; RowB = 0; RowC = 1; RowD = 1; 	//Test Row B

	if (C1 == 0) { __delay_ms(250); while (C1==0); return '4'; }
	if (C2 == 0) { __delay_ms(250); while (C2==0); return '5'; }
	if (C3 == 0) { __delay_ms(250); while (C3==0); return '6'; }
	if (C4 == 0) { __delay_ms(250); while (C4==0); return 'x'; }
	
	RowA = 1; RowB = 1; RowC = 0; RowD = 1; 	//Test Row C

	if (C1 == 0) { __delay_ms(250); while (C1==0); return '7'; }
	if (C2 == 0) { __delay_ms(250); while (C2==0); return '8'; }
	if (C3 == 0) { __delay_ms(250); while (C3==0); return '9'; }
	if (C4 == 0) { __delay_ms(250); while (C4==0); return '-'; }
	
	RowA = 1; RowB = 1; RowC = 1; RowD = 0; 	//Test Row D

	if (C1 == 0) { __delay_ms(250); while (C1==0); return 'C'; }
	if (C2 == 0) { __delay_ms(250); while (C2==0); return '0'; }
	if (C3 == 0) { __delay_ms(250); while (C3==0); return '='; }
	if (C4 == 0) { __delay_ms(250); while (C4==0); return '+'; }

	return 'n';           	// Means no key has been pressed
}

// Function name: GetKey
// Read pressed key value from keypad and return its value
char GetKey(void)           	 // Get key from user
{
	char key = 'n';              // Assume no key pressed
    
	while(key=='n')              // Wait untill a key is pressed
        key = READ_SWITCHES();   // Scan the keys again and again
                
	return key;                  //when key pressed then return its value
}

char GetKeyNumber(void)           	 // Get key from user
{
	char key = 'n';              // Assume no key pressed
    
	while(key=='n')              // Wait untill a key is pressed
        key = READ_SWITCHES();   // Scan the keys again and again
        
    number[x]=key;
    x++;
   
	return key;                  //when key pressed then return its value
}

char GetKeyTime(void)           	 // Get key from user
{
	char key = 'n';              // Assume no key pressed
    
	while(key=='n')              // Wait untill a key is pressed
        key = READ_SWITCHES();   // Scan the keys again and again
    if(a<2)    
    {
    hh[a]=key;
    a++;
    }
    else if(b<2)
    {
    mm[b]=key;
    b++;
    }
    else if(c<2)
    {
    ss[c]=key;
    c++;
    }
    else if(c<3)
        {
        if(key=='1')
        {strcpy(ap,"AM");
        c++;}
        else if(key=='2')
        {strcpy(ap,"PM");
        c++;}
        }
	return key;                  //when key pressed then return its value
}

char GetKeyDate(void)           	 // Get key from user
{
	char key = 'n';              // Assume no key pressed
    
	while(key=='n')              // Wait untill a key is pressed
        key = READ_SWITCHES();   // Scan the keys again and again
    if(e<2)    
    {
    DD[e]=key;
    e++;
    }
    else if(f<2)
    {
    MM[f]=key;
    f++;
    }
    else if(g<2)
    {
    YY[g]=key;
    g++;
    }
    else if(h<1)
    {switch(key)
	{
	case '1':	strcpy(DAY,"MON");	break;
	case '2':	strcpy(DAY,"TUE");	break;
	case '3':	strcpy(DAY,"WED");	break;
	case '4':	strcpy(DAY,"THU");	break;
	case '5':	strcpy(DAY,"FRI");	break;
	case '6':	strcpy(DAY,"SAT");	break;
	case '7':	strcpy(DAY,"SUN");	break;

	default: Lcd_Write_String("???");	break;
	}
    h++;
    cDAY[0]=key;
    }
    

	return key;                  //when key pressed then return its value
}

char GetKeySettings(void)           	 // Get key from user
{
	char key = 'n';              // Assume no key pressed
    int set=0;
	while(key=='n')              // Wait untill a key is pressed
    {
        key = READ_SWITCHES();   // Scan the keys again and again
        __delay_ms(70);
        set++;
        if(set==20)
        {   
            key = 'n';
            break;
        }
    }         
	return key;                  //when key pressed then return its value
}