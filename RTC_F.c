
#include <htc.h>
#include <string.h>
#define _XTAL_FREQ 20000000
#include <stdio.h>
#include <xc.h>
#include "lcd.h"
#include "keypad.h"
#include "configuration.h"
#include "GSM.h"
#include "UART1.h"
#include "Includes.h"
#include "ADC.h"
#include "DateTimeDisplay.h"
#include "EEPROM.h"
#include <stdlib.h>
#include "math.h"

void CSFSensors(void);
void Settings(void); 
float CLeakage(void);
void avgpow();

int x,mins,secs,ihh,imm,iss,iap,iDD,iMM,iYY,iDAY;
int avgpower=0,count=0;
//unsigned int a,b,c,dif,current_bits;
float current;
char text[16];

void EEPROMSET(void)
{   
    int x;
    for(x=0;x<12;x++)
    writeEEPROM(x,number[x]);
    __delay_ms(50);        
}

void EEPROMGET(void)
{
    int x;
    for(x=0;x<12;x++)
    number[x]=readEEPROM(x);
    __delay_ms(50);
}

void InitUnit(void)
{   char Key = 'n';
    EEPROMGET();
    TRISA = 0xFF;  // Make A port as a Input
    TRISD = 0x00;  // Make D port as a Output (dedicated for LCD)
    PORTD = 0X00;
    ADC_Init(); 
    TRISE=0x04;
    RE0=0;
    RE1=1;
    TRISC=0XFF;   // Make C port as a Input
    RD0=0;    //Power off the unit(relay)
    InitKeypad();		 // Initialize Keypad pins
    InitI2C();
    RE0=0;
    RE1=1;
    Lcd_Init();
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("    WELCOME");
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String("****************");
    RD1=1;
    __delay_ms(1500);
    RD1=0;
    __delay_ms(1500);
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String(" Initializing.!");
    __delay_ms(2000);
    Lcd_Clear();
    __delay_ms(300);
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String(" Initializing.!");
    __delay_ms(2000);
    Lcd_Clear();
    __delay_ms(300);
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String(" Initializing.!");
    __delay_ms(2000);
    Lcd_Clear();
    __delay_ms(300);
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("Press");
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String("F1 for Settings");
    Key = GetKeySettings();
    if(Key=='/')
        Settings();
    Lcd_Clear();
    __delay_ms(300);
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("    Switch ON");
    
    RD0=1;   //Switch on the unit. 
    RE0=1;
    RE1=0;
    __delay_ms(2000);

}

void Settings(void)
{
while(1)
	{   
        char Key = 'n';		 // Variable to store pressed key value
        char nkey='n';
        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("1:Numb 2:Time ");
        Lcd_Set_Cursor(2,1);
        Lcd_Write_String("3:Date 4:ShowInf");        
		Key = GetKey();		 // Get pressed key from keypad
		switch(Key)
        {
            case '1':   Lcd_Clear();
                        Lcd_Set_Cursor(1,1);
                        Lcd_Write_String("Enter number");
                        __delay_ms(1000);
                        Lcd_Clear();
                        while(1)
                        {
                        
                        nkey=GetKeyNumber();
                        Lcd_Clear();
                        Lcd_Set_Cursor(1,8);
                        Lcd_Write_Char(nkey);
                        Lcd_Set_Cursor(2,1);
                        Lcd_Write_String(number);
        
                        if(x==12)
                        {
                        Lcd_Clear();
                        Lcd_Set_Cursor(1,1);
                        Lcd_Write_String(" Entered Number");
                        Lcd_Set_Cursor(2,2);
                        Lcd_Write_String(number);
                        EEPROMSET();
                        __delay_ms(2000);
                        break;
                        }
                        }
                        break;
                        
            case '2':   Lcd_Clear();
                        Lcd_Set_Cursor(1,1);
                        Lcd_Write_String("HH:MM:SS:AM/PM");
                        Lcd_Set_Cursor(2,1);
                        Lcd_Write_String("AM - 1    PM-2");
                        while(1)
                        {
                        nkey=GetKeyTime();
                        Lcd_Clear();
                        Lcd_Set_Cursor(1,8);
                        Lcd_Write_Char(nkey);
                        Lcd_Set_Cursor(2,1);
                        sprintf(txt,"%s:%s:%s:%s",hh,mm,ss,ap);
                        Lcd_Write_String(txt);
        
                        if(c==3)
                        {
                        Lcd_Clear();
                        Lcd_Set_Cursor(1,1);
                        Lcd_Write_String(" Entered Time");
                        Lcd_Set_Cursor(2,2);
                        Lcd_Write_String(txt);
                        // Set initial time
                        __delay_ms(2000);
                        ihh = atoi(hh);
                        imm = atoi(mm);
                        iss = atoi(ss);
                        iss = atoi(nkey);
                        Set_DS1307_RTC_Time(iap, ihh, imm, iss);	// Set time 08:32:59 AM

                        Lcd_Clear();
                        break;
                        }
                        }
                        break;
                        
            case '3':   Lcd_Clear();
                        Lcd_Set_Cursor(1,1);
                        Lcd_Write_String("DD:MM:YY:DAY");
                        while(1)
                        {
                        nkey=GetKeyDate();
                        Lcd_Clear();
                        Lcd_Set_Cursor(1,8);
                        Lcd_Write_Char(nkey);
                        Lcd_Set_Cursor(2,1);
                        sprintf(txt,"%s:%s:%s %s",DD,MM,YY,DAY);
                        Lcd_Write_String(txt);
        
                        if(h==1)
                        {
                        Lcd_Clear();
                        Lcd_Set_Cursor(1,1);
                        Lcd_Write_String(" Entered Date");
                        Lcd_Set_Cursor(2,2);
                        Lcd_Write_String(txt);
                        __delay_ms(2000);
                        iDD = atoi(DD);
                        iMM = atoi(MM);
                        iYY = atoi(YY);
                        iDAY= atoi(cDAY);
                        // Set initial date

                        Set_DS1307_RTC_Date(iDD, iMM, iYY, iDAY); 	// Set 15-12-2012 @ Saturday

                        __delay_ms(2000);
                        break;
                        }
                        }
                        break;
                        
            case '4':   Lcd_Clear();
                        Lcd_Set_Cursor(1,1);
                        int x=0;
                        while(1)
                        {
                        Lcd_Clear();
                        Lcd_Set_Cursor(1,1);
                        // Display RTC time on first line of LCD
                        DisplayTimeToLCD(Get_DS1307_RTC_Time());

                        // Display RTC date on second line of LCD
                        DisplayDateOnLCD(Get_DS1307_RTC_Date());

                        __delay_ms(1500);	// 1 second delay
                        
                        Lcd_Clear();
                        Lcd_Set_Cursor(1,1);
                        Lcd_Write_String("Phone Number :");
                        Lcd_Set_Cursor(2,1);
                        Lcd_Write_String(number);
                        __delay_ms(1500);
                        x++;
                        if(x==3)
                        {
                        Lcd_Clear();
                        break;
                        }
                        }
                        break;
                       
            default :   continue;
                        
        }  
        
        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("F1:Edit ");
        Lcd_Set_Cursor(2,1);
        Lcd_Write_String("F2:Exit");        
		Key = GetKey();		 // Get pressed key from keypad
        if(Key=='x')
            break;
        else
            continue;

	}
}

float CLeakage(void)
{    unsigned int a,b,c,dif,current_bits;
     
 ADC_Init();                   //Initialize ADC
 a = ADC_Read(0);            //Read Analog Channel 0 (Current in)
 ADC_Init();                      
 b = ADC_Read(1);                 //Volatage in                  
 ADC_Init();                      
 c = ADC_Read(2);                  //reference
 
            
                
                    if(a>(c/2))
                        current_bits=a-(c/2);
                    else
                       current_bits=(c/2)-a;
                float power;
                if(current_bits>=5)
                current=(current_bits*0.0488);
                else
                current=0;
                float voltage=(230.0/330.0)*b;
                power=current*voltage*0.8;
                sprintf(text,"    %d W",(int)power);
                
                Lcd_Set_Cursor(2,1);
                Lcd_Write_String(text);
                
                avgpower=(avgpower+(int)power);
                
                count++;

}

void CheckSensors(void)
{
            if(RC1==0 || RC2==0) //Smoke and Fire Sensors
            {
                RD0=0;       //Relay
                RE0=0;
    RE1=1;
                //RD1=1;       //Speaker
                Lcd_Clear();
                Lcd_Set_Cursor(1,1);
                Lcd_Write_String("     DANGER");
                __delay_ms(2000);
                GSM_Send();
                Lcd_Clear();
                Lcd_Set_Cursor(1,1);
                Lcd_Write_String("Message Sent!");
                __delay_ms(2000);
                Lcd_Clear();
                Lcd_Set_Cursor(1,1);
                Lcd_Write_String("     DANGER");
                while(1)
                {}
            }
}

void main(void)
{  
  InitUnit();
  
  while(1)
  {
     if(RC0==0)          //if the iron isn't being moved
        {
            for(x=1;x<120;x++)      //Counting 2mins
            {
                mins=x/60;
                secs=x%60;
                sprintf(text,"      0%d:%d",mins,secs);
                Lcd_Clear();
                Lcd_Set_Cursor(1,1);
                Lcd_Write_String(text);
                __delay_ms(800);
                         
                CheckSensors(); //Checking Sensor status
                //CLeakage(); //Checking current leakage
                
                if(RC0==1)
                    break;
                 
            if(x==119 || RE2==0)
            {
                RD0=0;
                Lcd_Clear();
                Lcd_Set_Cursor(1,1);
                Lcd_Write_String("   Switched OFF");
                RE0=0;
                RE1=1;
                
                __delay_ms(20000);
                while(1)
                {}
                
            }
            }
            
        }
        
     else
     {
         
                CheckSensors(); //Checking Sensor status
                      
        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("    Switch ON");
        CLeakage(); //Checking current leakage
        __delay_ms(1000);
        
        if(RE2==0)
            {
                RD0=0;
                Lcd_Clear();
                Lcd_Set_Cursor(1,1);
                Lcd_Write_String("   Switched OFF");
                RE0=0;
                RE1=1;
                __delay_ms(1000);
                avgpow();
                while(1)
                {}
                
            }
        
        
     }
   
  }
       
}

void avgpow()
{
                Lcd_Clear();
                Lcd_Set_Cursor(1,1);
                sprintf(text,"AVGPOWER = %d W",(avgpower/count));
                Lcd_Write_String(text);
}

