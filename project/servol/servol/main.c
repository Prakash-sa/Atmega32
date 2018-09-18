/*
 * servol.c
 *
 * Created: 10-08-2018 11:26:25 PM
 * Author : Prakash Saini
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>	// include interrupt support

#include "global.h"
#include "servoconf.h"
#include "uart.h"		// include uart function library
#include "uart.c"
#include "a2d.h"		// include A/D converter function library
#include "a2d.c"
#include "timer.h"		// include timer function library (timing, PWM, etc)
#include "timer.c"
#include "servo.h"		// include RC servo driver library
#include "servo.c"
// global AVRLIB defines
#include "avrlibdefs.h"
// global AVRLIB types definitions
#include "avrlibtypes.h"

void servoTest(void);



int main(void)
{
   uartInit();
   // set the baud rate of the UART for our debug/reporting output
   uartSetBaudRate(9600);
   // initialize the timer system
   timerInit();

   // begin servo test
   servoTest();

   return 0;
    while (1) 
    {
    }
}

void servoTest(void)
{
	u08 pos;
	u08 channel;

	// do some examples
	// initialize RC servo system
	servoInit();
	// setup servo output channel-to-I/Opin mapping
	// format is servoSetChannelIO( CHANNEL#, PORT, PIN );
	servoSetChannelIO(0, _SFR_IO_ADDR(PORTC), PC0);
	servoSetChannelIO(1, _SFR_IO_ADDR(PORTC), PC1);
	servoSetChannelIO(2, _SFR_IO_ADDR(PORTC), PC2);
	servoSetChannelIO(3, _SFR_IO_ADDR(PORTC), PC3);

	// set port pins to output
	outb(DDRC, 0x0F);

	pos = 0;

	#define SPEED_SERVO	1

	// spin servos sequentially back and forth between their limits
	while(1)
	{
		for(channel=0; channel<SERVO_NUM_CHANNELS; channel++)
		{
			for(pos=0; pos<SERVO_POSITION_MAX; pos++)
			{
				servoSetPosition(channel,pos);
				timerPause(SPEED_SERVO);
			}
		}

		for(channel=0; channel<SERVO_NUM_CHANNELS; channel++)
		{
			for(pos=SERVO_POSITION_MAX; pos>=1; pos--)
			{
				servoSetPosition(channel,pos);
				timerPause(SPEED_SERVO);
			}
		}
	}
}

