/*
 */

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "lcd.h"
#include "lcd.c"

int main(void)
{
    lcd_init();

    while(1)
    {
           for (int x=15;x>=1;x--)
           {
              gotoxy(x,1);
			  string("Surat to Kanpur");
			  _delay_ms(1000);
			  gotoxy(x,1);
			  string("               ");
			  
			  
           }
    }
    return 0;
}