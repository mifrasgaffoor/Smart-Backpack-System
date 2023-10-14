
#include "Pressure.h"

void Atmospheric_Pressure()
{
	float adc_result;
	char net[10];
	DDRB = 0xFF;
	//Initialize ADC
	InitADC();
	//Initialize LCD
	Lcd8_Init ();
	_delay_ms(50); //giving delay of 50ms
	

	while(1)
	{
		
		Lcd8_Clear ();
		Lcd8_Set_Cursor(1,0);
		Lcd8_Write_String("Pressure ");
		_delay_ms(1000);
		Lcd8_Set_Cursor(2,0);
		Lcd8_Write_String("monitor ");
		_delay_ms(1000);
		Lcd8_Clear ();
		Lcd8_Cmd(0x38); //telling LCD we are using 8bit command /data mode
		_delay_ms(300);
		Lcd8_Set_Cursor(0,0);		/* Enter column and row position */
		Lcd8_Write_String("Pressure = ");
		Lcd8_Set_Cursor(2,0);
		_delay_ms(300);

		adc_result= (5.0/1023.0)*ReadADC(0);           // Read Analog value from channel-0
		adc_result=((adc_result/5.0)+0.095)/0.009-1;
		sprintf(net,"%d",(int)adc_result);
		Lcd8_Write_String(net);
		_delay_ms(2000);
		Lcd8_Clear ();
		_delay_ms(1000);

		Lcd8_Set_Cursor(0,1);		/* Enter column and row position */
		Lcd8_Clear ();
		_delay_ms(1000);

		Lcd8_Set_Cursor(12,1);		/* Enter column and row position */
		Lcd8_Write_String("Kpa");

		_delay_ms(10000);
	}
}

void InitADC()
{
	DDRA = 0x00;	        /* Make ADC port as input */
	ADCSRA = 0x87;          /* Enable ADC, with freq/128  */
	ADMUX = 0x40;           /* V ref: Avcc, ADC channel: 0 */
}

int ReadADC(char ch)
{
	ADMUX = 0x40 | (ch & 0x07);   /* set input channel to read */
	ADCSRA |= (1<<ADSC);               /* Start ADC conversion */
	while (!(ADCSRA & (1<<ADIF)));     /* Wait until end of conversion by polling ADC interrupt flag */
	ADCSRA |= (1<<ADIF);               /* Clear interrupt flag */
	_delay_ms(1);                      /* Wait a little bit */
	return ADCW;                       /* Return ADC word */
}

void Lcd8_Cmd(unsigned char cmnd)
{
	LCD_Data_Port= cmnd;
	LCD_Command_Port &= ~(1<<RS);	/* RS=0 command reg. */
	LCD_Command_Port |= (1<<EN);	/* Enable pulse */
	_delay_us(1);
	LCD_Command_Port &= ~(1<<EN);
	_delay_ms(3);
}

char Lcd8_Write_Char (unsigned char char_data)	/* LCD data write function */
{
	LCD_Data_Port= char_data;
	LCD_Command_Port |= (1<<RS);	/* RS=1 Data reg. */
	LCD_Command_Port |= (1<<EN);	/* Enable Pulse */
	_delay_us(1);
	LCD_Command_Port &= ~(1<<EN);
	_delay_ms(1);
	return char_data;
}

void Lcd8_Init (void)			/* LCD Initialize function */
{
	LCD_Command_Dir = 0xFF;		/* Make LCD command port direction as o/p */
	LCD_Data_Dir = 0xFF;		/* Make LCD data port direction as o/p */
	_delay_ms(20);			/* LCD Power ON delay always >15ms */
	
	Lcd8_Cmd (0x38);		/* Initialization of 16X2 LCD in 8bit mode */
	Lcd8_Cmd (0x0C);		/* Display ON Cursor OFF */
	Lcd8_Cmd (0x06);		/* Auto Increment cursor */
	Lcd8_Cmd (0x01);		/* Clear display */
	Lcd8_Cmd (0x80);		/* Cursor at home position */
}

char Lcd8_Write_String (char *str)		/* Send string to LCD function */
{
	int i;
	for(i=0;str[i]!=0;i++)		/* Send each char of string till the NULL */
	{
		Lcd8_Write_Char (str[i]);
	}
	return *str;
}

void Lcd8_Clear()
{
	Lcd8_Cmd (0x01);		/* clear display */
	Lcd8_Cmd (0x80);		/* cursor at home position */
}

void Lcd8_Set_Cursor(char row, char pos)
{
	if(row == 1)
	Lcd8_Cmd(0x80 + pos);
	else if(row == 2)
	Lcd8_Cmd(0xC0 + pos);
}
