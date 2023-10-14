

#ifndef PRESSURE_H_
#define PRESSURE_H_


#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define LCD_Data_Dir DDRD		/* Define LCD data port direction */
#define LCD_Command_Dir DDRC		/* Define LCD command port direction register */
#define LCD_Data_Port PORTD		/* Define LCD data port */
#define LCD_Command_Port PORTC		/* Define LCD data port */

#ifndef RS
#define RS PC6				/* Define Register Select (data/command reg.)pin */
#endif

#ifndef EN
#define EN PC7				/* Define Enable signal pin */
#endif


void Atmospheric_Pressure();

void InitADC();
int ReadADC(char ch);
void Lcd8_Cmd(unsigned char cmnd);
char Lcd8_Write_Char (unsigned char char_data);
void Lcd8_Init (void);
char Lcd8_Write_String (char *str);
void Lcd8_Clear();
void Lcd8_Set_Cursor(char row, char pos);

#endif /* PRESSURE_H_ */