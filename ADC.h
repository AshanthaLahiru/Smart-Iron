/* 
 * File:   ADC.h
 * Author: Lahiru
 *
 * Created on May 5, 2016, 7:35 AM
 */

void ADC_Init()
{
 ADCON0 = 0x81;               //Turn ON ADC and Clock Selection
 ADCON1 = 0x82;               //All pins as Analog Input and setting Reference Voltages
}

unsigned int ADC_Read(unsigned char channel)
{
  if(channel > 7)              //Channel range is 0 ~ 7
    return 0;

  ADCON0 &= 0xC5;              //Clearing channel selection bits
  ADCON0 |= channel<<3;        //Setting channel selection bits
  __delay_ms(2);               //Acquisition time to charge hold capacitor
  GO_nDONE = 1;                //Initializes A/D conversion
  while(GO_nDONE);             //Waiting for conversion to complete
  return ((ADRESH<<8)+ADRESL); //Return result
}