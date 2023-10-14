

#ifndef DHT11_LCDDISPLAY_H_
#define DHT11_LCDDISPLAY_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

#define DHT11_PIN 6
#define LCD_DPRT PORTB
#define LCD_DDDR DDRB
#define LCD_RS 0
#define LCD_EN 1

void Request();
void Response();
uint8_t Receive_data();
void Temperature_and_Humidity();

void lcdcommand(unsigned char cmnd);
void lcddata(unsigned char data);
void lcdinit();
void lcd_gotoxy(unsigned char x, unsigned char y);
void lcd_print(char *str);
void lcd_clear();

#endif /* DHT11_LCDDISPLAY_H_ */