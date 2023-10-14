

#ifndef LCD_KEYPAD_H_
#define LCD_KEYPAD_H_

#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <util/delay.h>

#define LCD_Dir  DDRC			/* Define LCD data port direction */
#define LCD_Port PORTC			/* Define LCD data port */
#define RS PC0				/* Define Register Select pin */
#define EN PC2 				/* Define Enable signal pin */

#define KEY_PRT 	PORTB
#define KEY_DDR		DDRB
#define KEY_PIN		PINB

void LCD_Command( unsigned char cmnd );
void LCD_Char( unsigned char data );
void LCD_Init (void);
void LCD_String (char *str)	;
void LCD_String_xy (char row, char pos, char str);
void LCD_Clear();
char keyfind();

#endif /* LCD_KEYPAD_H_ */