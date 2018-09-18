/*
 * pca9685.c
 *
 * Created: 09-08-2018 05:11:00 PM
 * Author : Prakash Saini
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "PCA9685.c"
#include "PCA9685.h"


int main(void)
{
	
    signed char j = 0;
    signed int i = 0;
    unsigned int v = 0;
    
	i2c_init();
	PCA9685_init();
	

    
    while(1)
    {
		

			for(int i=0; i<6; i++)  {
				PCA9685setLEDDimmed(i,50);
				_delay_ms(10000);
			}
			
			for(int i=0; i<6; i++)  {
				PCA9685setLEDDimmed(i,70);
				_delay_ms(1000);
			}
			for(int i=0; i<6; i++)  {
				PCA9685writeLED(i,2000,4096);
				_delay_ms(1000);
			}
			for(int i=0; i<6; i++)  {
				PCA9685writeLED(i,2500,4096);
				_delay_ms(1000);
			}
			for(int i=0; i<6; i++)  {
				PCA9685writeLED(i,3000,4096);
				_delay_ms(1000);
			}
			for(int i=0; i<6; i++)  {
				PCA9685writeLED(i,4000,4096);
				_delay_ms(1000);
			}
		/*
	    for(j = 0; j < 5; j ++)
	    {
		    for(i = 0; i <= 228; i++)
		    {
			    PCA9685_set_PWM_duty(j,0,4096);
			    _delay_ms(1000);
		    }
	    }
	    
	    for(j = 5; j > 0; j --)
	    {
		    for(i = 0; i <= 180; i++)
		    {
			    PCA9685_set_PWM_duty(j, 0,4096);
				_delay_ms(20000);
		    }
	    }
	    
	    
	    for(j = 0; j < 5; j ++)
	    {
		    for(i = 0; i <= 180; i++)
		    {
			    v = (MAX_count * cos(0.0174 * i));
			    PCA9685_set_PWM_duty(j, v, (j * 256));
			    _delay_ms(1000);
		    }
	    }

	    for(j = 5; j > 0; j --)
	    {
		    for(i = 0; i < 180; i++)
		    {
			    v = (MAX_count * cos(0.0174 * i));
			    PCA9685_set_PWM_duty(j, v, (j * 256));
			    _delay_ms(1000);
		    }
	    }
		
		*/
		
	}
}

