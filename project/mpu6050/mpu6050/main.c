/*
 * mpu6050.c
 *
 * Created: 05-08-2018 09:59:21 PM
 * Author : Prakash Saini
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "lcd.c"
#include <inttypes.h>									/* Include integer type header file */
#include <stdlib.h>										/* Include standard library file */
#include <stdio.h>										/* Include standard library file */
#include "MPU6050_res_define.h"
#include "i2c_master.c"
#include "i2c_master.h"


float Acc_x,Acc_y,Acc_z,Temperature,Gyro_x,Gyro_y,Gyro_z;

void MPU6050_Init()										/* Gyro initialization function */
{
	_delay_ms(150);										/* Power up time >100ms */
	i2c_start(0xD0);								/* Start with device write address */
	i2c_write(SMPLRT_DIV);								/* Write to sample rate register */
	i2c_write(0x07);									/* 1KHz sample rate */
	i2c_stop();

	i2c_start(0xD0);
	i2c_write(PWR_MGMT_1);								/* Write to power management register */
	i2c_write(0x01);									/* X axis gyroscope reference frequency */
	i2c_stop();

	i2c_start(0xD0);
	i2c_write(CONFIG);									/* Write to Configuration register */
	i2c_write(0x00);									/* Fs = 8KHz */
	i2c_stop();

	i2c_start(0xD0);
	i2c_write(GYRO_CONFIG);								/* Write to Gyro configuration register */
	i2c_write(0x18);									/* Full scale range +/- 2000 degree/C */
	i2c_stop();

	i2c_start(0xD0);
	i2c_write(INT_ENABLE);								/* Write to interrupt enable register */
	i2c_write(0x01);
	i2c_stop();
}

void MPU_Start_Loc()
{
	i2c_start(0xD0);								/* I2C start with device write address */
	i2c_write(ACCEL_XOUT_H);							/* Write start location address from where to read */
	i2c_start(0xD1);							/* I2C start with device read address */
}

void Read_RawValue()
{
	MPU_Start_Loc();									/* Read Gyro values */
	Acc_x = (((int)i2c_read_ack()<<8) | (int)i2c_read_ack());
	Acc_y = (((int)i2c_read_ack()<<8) | (int)i2c_read_ack());
	Acc_z = (((int)i2c_read_ack()<<8) | (int)i2c_read_ack());
	Temperature = (((int)i2c_read_ack()<<8) | (int)i2c_read_ack());
	Gyro_x = (((int)i2c_read_ack()<<8) | (int)i2c_read_ack());
	Gyro_y = (((int)i2c_read_ack()<<8) | (int)i2c_read_ack());
	Gyro_z = (((int)i2c_read_ack()<<8) | (int)i2c_read_nack());
	i2c_stop();
}

int main()
{
	lcd_init();
	
	char buffer[20], float_[10];
	float Xa,Ya,Za,t;
	float Xg=0,Yg=0,Zg=0;
	i2c_init();											/* Initialize I2C */
	MPU6050_Init();	
	
	
	while(1)
	{
		Read_RawValue();

		Xa = Acc_x/16384.0;								/* Divide raw value by sensitivity scale factor to get real values */
		Ya = Acc_y/16384.0;
		Za = Acc_z/16384.0;
	
		Xg = Gyro_x/16.4;
		Yg = Gyro_y/16.4;
		Zg = Gyro_z/16.4;

		t = (Temperature/340.00)+36.53;					/* Convert temperature in °/c using formula */
		
	
		dtostrf( Xa, 3, 2, float_ );					
		sprintf(buffer,"x=%s g\t",float_);
		gotoxy(65,1);
		string(buffer);

		
	
		dtostrf( Ya, 3, 2, float_ );
		sprintf(buffer,"y=%s g\t",float_);
		gotoxy(72,1);
		string(buffer);
	
		

		dtostrf( t, 3, 2, float_ );
		sprintf(buffer," T = %s%cC\t",float_,0xF8);           /* 0xF8 Ascii value of degree '°' on serial */
		gotoxy(1,1);
		string(buffer);									/* Initialize USART with 9600 baud rate */
		
		

		
	}
}

