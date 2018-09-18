#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"


void lcd_cmd(unsigned char cmd)
{
    lcdgpio=cmd;
    controllcd &=~(1<<twomood | 1<<readwrite);
    controllcd |=1<<enable;
    _delay_ms(10);
    controllcd &=~(1<<enable);

}

void lcd_data(unsigned char data)
{
    lcdgpio=data;
    controllcd &=~(1<<readwrite);
    controllcd |=(1<<twomood | 1<<enable);
    _delay_ms(10);
    controllcd &=~(1<<enable);
}

void lcd_init()
{
    datacontrollcd |=(1<<twomood) | (1<<readwrite) | (1<<enable);
    _delay_ms(10);

    datalcdgpio |=0xff;
    _delay_ms(10);

    lcd_cmd(0x01);
    _delay_ms(2);

    lcd_cmd(0x38);
    _delay_ms(50);

    lcd_cmd(0x0e);
    _delay_ms(50);

}

void string(char *line)
{
	while(*line>0)
	{
		lcd_data(*line);
		*line++;
	}
}

void gotoxy(uint8_t x,uint8_t y)
{
    lcd_cmd(0x80+colpos[y-1]+x);
}
