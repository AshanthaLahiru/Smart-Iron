/* 
 * File:   UART1.h
 * Author: Lahiru
 *
 * Created on January 22, 2016, 9:25 PM
 */

#ifndef __UART1_H
#define __UART1_H

// Comm Setup
//#define BAUDRATE 9600  //bps
// 8 bit data mode with one stop bit
// No flow control, no parity bit

//Function Prototypes
void InitUART(int);
char BusyUART(void);
void SendByteSerially(unsigned char Byte);
void SendStringSerially(const unsigned char* st);



#endif


