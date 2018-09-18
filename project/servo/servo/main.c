/*
 * servo.c

 * Created: 08-07-2018 17:59:20
 * Author : Prakash Saini
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/*
//Inverting mode

int main(void)
{
	DDRD |=0x20;
	TCCR1A |=(1<<WGM11) | (1<<COM1A0) | (1<<COM1A1);
	TCCR1B |=(1<<WGM13) | (1<<WGM12) | (1<<CS10);
	ICR1=19999;
	
    while (1) 
    {
		OCR1A=ICR1 - 800;
		_delay_ms(100);
		OCR1A=ICR1 - 2000;
		_delay_ms(100);
    }
}

*/


//NON Inverting Mode

int main()
{
	DDRD |=0xFF;
	//DDRB |=0x08;
	//TCCR0 |=(1<<WGM00)|(1<<COM01)|(1<<CS01);
	//TCCR2 |=(1<<WGM20)|(1<<COM21)|(1<<CS21);
	TCCR1A |=(1<<WGM10) | (1<<COM1A1) | (1<<COM1B1) ;
	TCCR1B |=(1<<WGM12) | (1<<CS10);
	ICR1=19999;
	
	while (1)
	{
		OCR1A=388;
		_delay_ms(100);
		//OCR0=500;
		//_delay_ms(100);
		//OCR2=2000;
		//_delay_ms(100);
		OCR1B=388;
		_delay_ms(100);
	}
	
}

/*

//multiple servo ,interrupt

int main()
{
	DDRD |=0xFF;
	TCCR1A |=(1<<WGM11) ;
	TCCR1B |=(1<<WGM13) | (1<<WGM12) | (1<<CS10);
	TIMSK |=1<<OCIE1A;
	ICR1=19999;
	
	sei();	
	
	while (1)
	{
		if (TCNT1>800 && TCNT1<2400)
		{
			if (TCNT1 == 2000) PORTD &=~(1<<PINB0);
		} 
				
	}
	
}

ISR(TIMER1_COMPA_vect)
{
	PORTD=0xff;

}

*/
