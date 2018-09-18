#ifndef lcd
#define lcd


#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#define lcdgpio PORTB
#define datalcdgpio DDRB
#define controllcd PORTD
#define datacontrollcd DDRD
#define twomood 3
#define readwrite 7
#define enable 5



void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_init(void);
void string(char *line);
void gotoxy(uint8_t x,uint8_t y);

char colpos[2]={0,65};
char positionstring[2];


#endif // LCD_H_INCLUDED
