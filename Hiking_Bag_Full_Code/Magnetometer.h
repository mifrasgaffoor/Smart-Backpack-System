


#ifndef MAGNETOMETER_H_
#define MAGNETOMETER_H_


#include <avr/io.h>										/* Include AVR std. library file */
#include <stdlib.h>										/* Include std. library file */
#include <math.h>										/* Include math header file */
#include <stdio.h>
#include <string.h>
#include <util/delay.h>					/* Include Delay header file */
#include "Magnetometer_LCDDisplay.h"

#define LCD_Data_Dir DDRB				/* Define LCD data port direction */
#define LCD_Command_Dir DDRC			/* Define LCD command port direction register */
#define LCD_Data_Port PORTB				/* Define LCD data port */
#define LCD_Command_Port PORTC			/* Define LCD data port */
#define EN PC2							/* Define Enable signal pin */
#define RW PC3							/* Define Read/Write signal pin */
#define RS PC4							/* Define Register Select (data reg./command reg.) signal pin */
#define SCL_CLK 100000L							/* Define SCL clock frequency */
#define BITRATE(TWSR)	((F_CPU/SCL_CLK)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1))))) /* Define bit rate */
#define PI	3.14159265359								/* Define Pi value */
#define Declination	-0.00669							/* Define declination of location from where measurement going to be done.*/

void Direction();

void Magneto_init();
int Magneto_GetHeading();

void I2C_Init();								/* I2C initialize function */
uint8_t  I2C_Start(char slave_write_address);	/* I2C start function */
uint8_t  I2C_Repeated_Start(char slave_read_address);	/* I2C repeated start function */
void I2C_Stop();								/* I2C stop function */
void I2C_Start_Wait(char slave_write_address);		/* I2C start wait function */
uint8_t  I2C_Write(char data);					/* I2C write function */
char I2C_Read_Ack();							/* I2C read ack function */
char I2C_Read_Nack();							/* I2C read nack function */




#endif /* MAGNETOMETER_H_ */