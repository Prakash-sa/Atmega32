/*
 * led.c
 *
 * Created: 21-06-2018 23:18:49
 * Author : Prakash Saini
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

void Delay(void){
   while(TCNT1<15625);
   TCNT1 -=15625;

}




int main(void)
{
	DDRB |=(1<<PINB0);
	TCCR1B=(1<<CS10)|(1<<CS11);
    /* Replace with your application code */
    while (1) 
    {
		PORTB &=0xFE;
		Delay();
		PORTB |=0x01;
		Delay();
    }
}



