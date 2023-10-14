

#include <avr/io.h>
#include <util/delay.h>

#include "LCD_KeyPad.h"
#include "DHT11_LCDDisplay.h"
#include "Pressure.h"
#include "Magnetometer.h"
#include "Magnetometer_LCDDisplay.h"
#include "MQ135_Sensor.h"
#include "MQ135_Sensor_LCDDisplay.h"
#include "LDR_Sensor.h"



#ifndef F_CPU
#define F_CPU 16000000UL
#endif

void LCD_Initial_Code(); //prototypes

char t;//variables

int main(void)
{
	LCD_Initial_Code();
	
	switch(t)
	{
		case '1':
		LCD_Command(0xC0);
		LCD_String("Temperature and Humidity: ");
		Temperature_and_Humidity();
		_delay_ms(200);
		break;
		
		case '2':
		LCD_Command(0xC0);
		LCD_String("Direction: ");
		Direction();
		_delay_ms(200);
		break;
		
		case '3':
		LCD_Command(0xC0);
		LCD_String("Atmospheric Pressure:");
		Atmospheric_Pressure();
		_delay_ms(200);
		break;
		
		
		case '4':
		LCD_Command(0xC0);
		LCD_String("Air Composition: ");
		Air_Composition();
		_delay_ms(200);
		break;
		
		default:
		LCD_Command(0xC0);
		LCD_String("Wrong input");
		_delay_ms(200);
		break;
	}
	LDR_Output();

	
}

void LCD_Initial_Code()
{
	LCD_Init();			/* Initialization of LCD*/
	LCD_Clear(); // clear LCD Display
	LCD_Command(0x0C);
	LCD_String("WELCOME");
	_delay_ms(50);
	LCD_String(" TO");
	_delay_ms(50);
	LCD_Command(0xC0);
	LCD_String("   OUR PROJECT");
	_delay_ms(200);
	LCD_Clear(); // clear LCD Display
	LCD_String("Enter");
	_delay_ms(50);
	LCD_String(" the buttons");
	_delay_ms(50);
	LCD_Command(0xC0);
	LCD_String(" to get Output");
	_delay_ms(200);
	LCD_Clear(); // clear LCD Display
	LCD_String("Temperature and Humidity: ");
	_delay_ms(50);
	LCD_Command(0xC0);
	LCD_String("Enter 1");
	_delay_ms(200);
	LCD_Clear(); // clear LCD Display
	LCD_String("Direction: ");
	_delay_ms(50);
	LCD_Command(0xC0);
	LCD_String("Enter 2");
	_delay_ms(200);
	LCD_Clear(); // clear LCD Display
	LCD_String("Atmospheric Pressure: ");
	_delay_ms(50);
	LCD_Command(0xC0);
	LCD_String("Enter 3");
	_delay_ms(200);
	LCD_Clear(); // clear LCD Display
	LCD_String("Air Composition: ");
	_delay_ms(50);
	LCD_Command(0xC0);
	LCD_String("Enter 4");
	_delay_ms(200);
	LCD_Clear(); // clear LCD Display
	LCD_String_xy(0,0,"Enter a key: ");
	t = keyfind();
	LCD_Char(t);
	_delay_ms(200);
}
