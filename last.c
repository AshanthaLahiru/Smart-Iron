/* 
 * File:   last.c
 * Author: Lahiru
 *
 * Created on April 26, 2016, 5:20 PM
 */
#define _XTAL_FREQ 8000000
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "lcd.h"

#define RS RD2
#define EN RD3
#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7

// BEGIN CONFIG
#pragma config FOSC = HS // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF // Flash Program Memory Code Protection bit (Code protection off)
//END CONFIG

char findKey(unsigned short a, unsigned short b);
char readKeyboard();
void display(char x);
char readKeyboard()
{
 unsigned int i = 0;
 for(i=0;i<4;i++)
 {
  if(i == 0)
  PORTB = 1;
  else if(i == 1)
  PORTB = 2;
  else if(i == 2)
  PORTB = 4;
  else if(i == 3)
  PORTB = 8;

  if(PORTBbits.RB4)
    return findKey(i,0);
  if(PORTBbits.RB5)
   return findKey(i,1);
  if(PORTBbits.RB6)
   return findKey(i,2);
  if(PORTBbits.RB7)
   return findKey(i,3);
 }
 return 'n';
}

char findKey(unsigned short a, unsigned short b)
{
 if(b == 0)
 {
   if(a == 3)
    return '0';
   else if(a == 2)
    return '1';
   else if(a == 1)
    return '2';
   else if(a == 0)
    return '3';
 }
 else if(b == 1)
 {
   if(a == 3)
    return '4';
   else if(a == 2)
    return '5';
   else if(a == 1)
    return '6';
   else if(a == 0)
    return '7';
 }
 else if(b == 2)
 {
   if(a == 3)
    return '8';
   else if(a == 2)
    return '9';
   else if(a == 1)
    return 'A';
   else if(a == 0)
    return '-';
 }
 else if(b == 3)
 {
   if(a == 3)
    return 'C';
   else if(a == 2)
    return 'U';
   else if(a == 1)
    return 'E';
   else if(a == 0)
    return 'F';
 }
}

void display(char x)
{
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String(x);
}

/*void main()
{
    TRISD=0x00;
    TRISB=0xF0;
    
    Lcd_Init();
    Lcd_Clear();
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("    WELCOME");
    __delay_ms(1000);
    Lcd_Clear();
    while(1)
    {   char x='n';
        x=readKeyboard();
        if(x!='n')
        {
            display(x);
        }
                
    }

}*/