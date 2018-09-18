/*
 * ultrasonicsensor.c
 *
 * Created: 18-08-2018 04:09:39 PM
 * Author : Prakash Saini
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 1000000UL
#include <util/delay.h>
#include <stdlib.h>
#include "lcd.h"
#include "lcd.c"
#include "rr.c"

static volatile int pulse = 0;
static volatile int i = 0;

int main(void)
{
	
	DDRD = 0b11111011;
	_delay_ms(50);
	lcd_init();
	
	GICR|=(1<<INT0);
	MCUCR|=(1<<ISC00);
	
	TCCR1A = 0;
	  
	int16_t COUNTA = 0;
	char SHOWA [16];
	char SHOWA2 [16];
	char SHOWA3 [16];
	double a2,a1;
	
	sei();
	
	while(1)
	{
		PORTD|=(1<<PIND0);
		_delay_us(15);
		PORTD &=~(1<<PIND0);
		
		COUNTA = pulse/58;
		if (COUNTA<=32)
		{
			a2=t2_rr(COUNTA);
			a1=t1_rr(COUNTA,a2);
			itoa(a2,SHOWA,10);
			gotoxy(1,1);
			string(" ");
			string(SHOWA);
			string(" ");
			itoa(a2,SHOWA3,10);
			//gotoxy(70,2);
			//string(SHOWA3);
			gotoxy(5,1);
			itoa(COUNTA,SHOWA2,10);
			string(" ");
			string(SHOWA2);
			string("    ");
		}
		
		
		//string(SHOWA);
		//string ("cm    ");
		
	}
}

ISR(INT0_vect)
{
	if (i==1)
	{
		TCCR1B=0;
		pulse=TCNT1;
		TCNT1=0;
		i=0;
	}
	if (i==0)
	{
		TCCR1B|=(1<<CS10);
		i=1;
	}
}




