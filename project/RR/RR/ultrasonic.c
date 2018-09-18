#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 1000000UL
#include <util/delay.h>

static volatile int pulse = 0;
static volatile int i = 0;

int ultrasonic(void)
{
	
	DDRD = 0b11111011;
	_delay_ms(50);
	
	GICR|=(1<<INT0);
	MCUCR|=(1<<ISC00);
	
	TCCR1A = 0;
	  
	int16_t COUNTA = 0;
		
	sei();
	
	
	PORTD|=(1<<PIND0);
	_delay_us(15);
	PORTD &=~(1<<PIND0);
			
	COUNTA = pulse/58;
	return COUNTA;
		
		
	
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