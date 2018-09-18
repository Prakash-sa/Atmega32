/*
 * multipleservo.c
 *
 * Created: 22-07-2018 11:08:48 AM
 * Author : Prakash Saini
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>

int main(void)
{
	DDRB |= 0x0F;
	TCCR1A |= (1<<WGM11) | (1<<COM1A1);
	TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS10);
	TIMSK |= 1<<OCIE1A;
	
	ICR1=19999;
	
	
	double tc1,tc2,tc3,tc4,a[4]={0,90,180,45} ;
	
	
	
	tc1=(float)10.5556*(0)+600;
	tc2=(float)10.5556*(90)+600;
	tc3=(float)10.5556*(180)+600;
	
	sei();
	while (1)
	{
		if (TCNT1>=590 && TCNT1<=2600)
		{
			if(TCNT1 >=(int)600  && bit_is_set(PORTB,PINB0))   PORTB &=~(1<<PINB0);
			if(TCNT1 >=(int)600 && bit_is_set(PORTB,PINB1))    PORTB &=~(1<<PINB1);
			if(TCNT1 >=(int)600 && bit_is_set(PORTB,PINB2))    PORTB &=~(1<<PINB2);  
			   
		}
		if (TCNT1<590 || TCNT1>2600)
		{
		}
	}
}


ISR(TIMER1_COMPA_vect)
{
	PORTB=0x0f;
}