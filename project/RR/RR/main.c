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
#include "rr.c"
#include "ultrasonic.c"


int main(void)
{
	
	DDRB |= 0x0F;
	TCCR1A |= (1<<WGM11) | (1<<COM1A1);
	TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS10);
	TIMSK |= 1<<OCIE1A;
	
	TCCR1A = 0;
	
	int16_t COUNTA = 0;
	
	ICR1=19999;
	
	
	double a2,a1,tc1,tc2;
	
	sei();
	while (1)
	{
		//PORTD|=(1<<PIND0);
		//_delay_us(15);
		//PORTD &=~(1<<PIND0);
		
		//COUNTA = pulse/58;
		COUNTA =ultrasonic();
		if (COUNTA <=30)
		{
			a2=t2_rr(COUNTA);
			a1=t1_rr(COUNTA,a2);
			
			if (TCNT1>=590 && TCNT1<=2600)
			{
				if(TCNT1 >=(int)a1  && bit_is_set(PORTB,PINB0))
				{   
					PORTB &=~(1<<PINB0);
				}
				if(TCNT1 >=(int)a2 && bit_is_set(PORTB,PINB1)) 
				{
					   PORTB &=~(1<<PINB1);
				}
				if(TCNT1 >=(int)2500 && bit_is_set(PORTB,PINB2))
				{ 
					   PORTB &=~(1<<PINB2);
				}
			}
			if (TCNT1<590 || TCNT1>2600)
			{
			}
		}
		
		
	}
}


ISR(TIMER1_COMPA_vect)
{
	PORTB=0x0f;
}
/*
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
*/