
/* 
 *  Created by: Unique Circuits
 *  Title: Rain sensing module
 *  Controller used: PIC16F877A
 *  Compiler used: XC8
 *  Date: 14/04/2019
 */

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
 
#define RAIN RD0                  //Rain sensor Output is connected at PORTD.0
 
#define rs RC0
#define rw RC1
#define en RC2
#define delay for(i=0;i<1000;i++)
 
int i;
 
void lcd_init();
void cmd(unsigned char a);
void dat(unsigned char b);
void show(unsigned char *s);
 
 
void main()
{
    /* PORT direction configuration */
    TRISB = 0x0;
    TRISC = 0x0;
    TRISD = 0x01;    
            
            
    lcd_init();
    cmd(0x80);
    show("Unique Circuits");
    cmd(0xc0);
    while(1) {
        if(RAIN == 0) {
            cmd(0xc0);
            show("Rain Detected");
            delay;delay;
        } else {
            cmd(0xc0);
            show("                ");
        }
    }
}
 
void lcd_init()
{
    cmd(0x38);
    cmd(0x0c);
    cmd(0x06);
    cmd(0x80);
}
 
void cmd(unsigned char a)
{
    PORTB=a;
    rs=0;
    rw=0;
    en=1;
    delay;
    en=0;
}
 
void dat(unsigned char b)
{
    PORTB=b;
    rs=1;
    rw=0;
    en=1;
    delay;
    en=0;
}
 /* Write string to LCD */
void show(unsigned char *s)
{
    while(*s)
    {
        dat(*s++);
    }
}
