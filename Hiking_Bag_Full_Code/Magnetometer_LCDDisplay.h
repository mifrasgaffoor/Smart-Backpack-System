

#ifndef MAGNETOMETER_LCDDISPLAY_H_
#define MAGNETOMETER_LCDDISPLAY_H_


#include <avr/io.h>						/* Include AVR std. library file */
#include <util/delay.h>					/* Include Delay header file */

#define LCD_Data_Dir DDRB				/* Define LCD data port direction */
#define LCD_Command_Dir DDRC			/* Define LCD command port direction register */
#define LCD_Data_Port PORTB				/* Define LCD data port */
#define LCD_Command_Port PORTC			/* Define LCD data port */
#define EN PC2							/* Define Enable signal pin */
#define RW PC3							/* Define Read/Write signal pin */
#define RS PC4							/* Define Register Select (data reg./command reg.) signal pin */

void LCD_Display_Command (char);				/* LCD command write function */
void LCD_Display_Char (char);					/* LCD data write function */
void LCD_Display_Init (void);					/* LCD Initialize function */
void LCD_Display_String (char*);				/* Send string to LCD function */
void LCD_Display_String_xy (char,char,char*);	/* Send row, position and string to LCD function */



#endif /* MAGNETOMETER_LCDDISPLAY_H_ */