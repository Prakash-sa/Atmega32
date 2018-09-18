#ifndef  F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/twi.h>
#include <util/delay.h>
#include "PCA9685.h"

#define F_SCL 100000UL // SCL frequency
#define Prescaler 1
#define TWBR_val ((((F_CPU / F_SCL) / Prescaler) - 16 ) / 2)

#define lowByte(w) ((uint8_t) ((w) & 0xff))
#define highByte(w) ((uint8_t) ((w) >> 8))

#define PCA9685_LED0 0x06

/*
void PCA9685_init()
{
	unsigned char MSB = 0x00;
	
	i2c_start(0x40);
	_delay_ms(10000);
	
	PCA9685_soft_reset();
	_delay_ms(1000);
	
	PCA9685_write_byte(PCA9685_MODE1_reg, 0x01);
	
	MSB = PCA9685_read_byte(PCA9685_MODE1_reg);
	
	PCA9685_write_byte(PCA9685_MODE1_reg, (0x10 | MSB));
	PCA9685_write_byte(PCA9685_MODE2_reg, 0x04);
	PCA9685_write_byte(PCA9685_PRE_SCALE_reg, 0x06);
	_delay_ms(1000);
	PCA9685_write_byte(PCA9685_MODE1_reg, MSB);
}


void PCA9685_soft_reset()
{
	i2c_start(PCA9685_write_cmd);
	i2c_write(PCA9685_software_reset);
	i2c_stop();
}


unsigned char PCA9685_read_byte(unsigned char address)
{
	unsigned char temp = 0x00;
	
	i2c_start(PCA9685_write_cmd);
	i2c_write(address);
	i2c_write(PCA9685_read_cmd);
	temp = i2c_read_ack();
	i2c_stop();
	
	return temp;
}


void PCA9685_write_byte(unsigned char address, unsigned char value)
{
	i2c_start(PCA9685_write_cmd);
	i2c_write(address);
	i2c_write(value);
	i2c_stop();
}


void PCA9685_write_word(unsigned char address, unsigned int word_value)
{
	unsigned char hb = 0x00;
	unsigned char lb = 0x00;
	
	lb = (word_value & 0x00FF);
	hb = ((word_value & 0xFF00) >> 0x08);
	
	PCA9685_write_byte(address, lb);
	PCA9685_write_byte((address + 1), hb);
}


void PCA9685_set_PWM_duty(unsigned char ch, unsigned int duty, unsigned int dead_time)
{
	unsigned int off_time = 0x0000;

	off_time = (duty + dead_time);

	if(off_time >= MAX_count)
	{
		off_time = (off_time - MAX_count);
	}

	PCA9685_write_word((PCA9685_CH0_ON_L_reg + (ch << 2)), (dead_time & 0x0FFF));
	PCA9685_write_word((PCA9685_CH0_OFF_L_reg + (ch << 2)), (off_time & 0x0FFF));
}

*/

    void PCA9685_init() {
		
    i2c_start(0x40);
    _delay_ms(100);
	
	PCA9685writeRegister(PCA9685_MODE1_reg, 0x01);	// reset the device
	_delay_ms(100);
	PCA9685writeRegister(PCA9685_MODE1_reg, 0xa1);	// set up for auto increment
	PCA9685writeRegister(PCA9685_MODE2_reg, 0x10);	// set to output
	}

	void PCA9685setLEDOn(int ledNumber) {
	PCA9685writeLED(ledNumber, 0x1000, 0);
	}

	void PCA9685setLEDOff(int ledNumber) {
	PCA9685writeLED(ledNumber, 0, 0x1000);
	}

	void PCA9685setLEDDimmed(int ledNumber, uint8_t amount) {		// Amount from 0-100 (off-on)
	if (amount==0)	{
	PCA9685setLEDOff(ledNumber);
	} else if (amount>=100) {
	PCA9685setLEDOn(ledNumber);
	} else {
	srand(4096);
	int randNumber = (int)rand();	// Randomize the phaseshift to distribute load. Good idea? Hope so.
	PCA9685writeLED(ledNumber, randNumber, (int)(amount*41+randNumber) & 0xFFF);
	}
	}

	void PCA9685writeLED(int ledNumber, uint16_t LED_ON, uint16_t LED_OFF) {	// LED_ON and LED_OFF are 12bit values (0-4095); ledNumber is 0-15
	if (ledNumber >=0 && ledNumber <= 15)	{
	i2c_start(PCA9685_write_cmd);
	i2c_write(PCA9685_LED0 + 4*ledNumber);
	i2c_write(lowByte(LED_ON));
	i2c_write(highByte(LED_ON));
	i2c_write(lowByte(LED_OFF));
	i2c_write(highByte(LED_OFF));
	i2c_stop();
	}
	}

	void PCA9685writeRegister(int regAddress, uint8_t data) {
	i2c_start(PCA9685_write_cmd);
	i2c_write(regAddress);
	i2c_write(data);
	i2c_stop();
	}
	
void i2c_init(void)
{
	DDRC &= 0xff; /* make SDA and SCL outout */
	TWBR = (uint8_t)TWBR_val;
}

uint8_t i2c_start(uint8_t address)
{
	// reset TWI control register
	TWCR = 0;
	// transmit START condition
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	// wait for end of transmission
	while( !(TWCR & (1<<TWINT)) );
	
	// check if the start condition was successfully transmitted
	if((TWSR & 0xF8) != TW_START){ return 1; }
	
	// load slave address into data register
	TWDR = address;
	// start transmission of address
	TWCR = (1<<TWINT) | (1<<TWEN);
	// wait for end of transmission
	while( !(TWCR & (1<<TWINT)) );
	
	// check if the device has acknowledged the READ / WRITE mode
	uint8_t twst = TW_STATUS & 0xF8;
	if ( (twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK) ) return 1;
	
	return 0;
}

uint8_t i2c_write(uint8_t data)
{
	// load data into data register
	TWDR = data;
	// start transmission of data
	TWCR = (1<<TWINT) | (1<<TWEN);
	// wait for end of transmission
	while( !(TWCR & (1<<TWINT)) );
	
	if( (TWSR & 0xF8) != TW_MT_DATA_ACK ){ return 1; }
	
	return 0;
}

uint8_t i2c_read_ack(void)
{
	
	// start TWI module and acknowledge data after reception
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	// wait for end of transmission
	while( !(TWCR & (1<<TWINT)) );
	// return received data from TWDR
	return TWDR;
}

uint8_t i2c_read_nack(void)
{
	
	// start receiving without acknowledging reception
	TWCR = (1<<TWINT) | (1<<TWEN);
	// wait for end of transmission
	while( !(TWCR & (1<<TWINT)) );
	// return received data from TWDR
	return TWDR;
}

uint8_t i2c_transmit(uint8_t address, uint8_t* data, uint16_t length)
{
	if (i2c_start(address | I2C_WRITE)) return 1;
	
	for (uint16_t i = 0; i < length; i++)
	{
		if (i2c_write(data[i])) return 1;
	}
	
	i2c_stop();
	
	return 0;
}

uint8_t i2c_receive(uint8_t address, uint8_t* data, uint16_t length)
{
	if (i2c_start(address | I2C_READ)) return 1;
	
	for (uint16_t i = 0; i < (length-1); i++)
	{
		data[i] = i2c_read_ack();
	}
	data[(length-1)] = i2c_read_nack();
	
	i2c_stop();
	
	return 0;
}

uint8_t i2c_writeReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length)
{
	if (i2c_start(devaddr | 0x00)) return 1;

	i2c_write(regaddr);

	for (uint16_t i = 0; i < length; i++)
	{
		if (i2c_write(data[i])) return 1;
	}

	i2c_stop();

	return 0;
}

uint8_t i2c_readReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length)
{
	if (i2c_start(devaddr)) return 1;

	i2c_write(regaddr);

	if (i2c_start(devaddr | 0x01)) return 1;

	for (uint16_t i = 0; i < (length-1); i++)
	{
		data[i] = i2c_read_ack();
	}
	data[(length-1)] = i2c_read_nack();

	i2c_stop();

	return 0;
}

void i2c_stop(void)
{
	// transmit STOP condition
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	
}
