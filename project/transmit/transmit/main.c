/*
 * transmit.c
 *
 * Created: 23-07-2018 04:06:31 PM
 * Author : Prakash Saini
 */ 

#define F_CPU 16000000UL
#define BAUD 9600
#define BRC ((F_CPU/16/BAUD) - 1)

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    UBRRH = (BRC>>8);
	UBRRL = BRC;
	
	UCSRB = (1<<TXEN);
	UCSRC = (1<<UCSZ0) | (1<<UCSZ1);
	
    while (1) 
    {
		UDR ='8';
		_delay_ms(1000);
    }
}

