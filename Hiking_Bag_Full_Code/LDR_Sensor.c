

#include "LDR_Sensor.h"

volatile unsigned char lux=0;

void LDR_Output()
{
	DDRA = 0x00;											//Configuring Port A as input
	DDRC = 0xFF;											//Configuring Port C as output
	PORTC = 0x00;
	initialize_LDR();
	while (1)
	{
		if (lux > 150 ) //please choose an appropriate value.
		{ PORTC |= (1<<5); }
		else
		{ PORTC=0x00; }
	}
}

void initialize_LDR()
{
	ADMUX |= (1 << REFS0);									//Setting Reference voltage as AVcc with external capacitor at AREF
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);	//Setting Pre scalar division factor as 128
	ADMUX  |= (1<<ADLAR);
	ADCSRA |= (1 << ADIE);									//Enable Interrupt
	ADCSRA |= (1 << ADEN);									//Turn on ADC feature

	sei();													//Enable global interrupts

	ADCSRA |= (1 << ADSC);									//Start conversion

}

ISR (ADC_vect)
{
	lux = ADCH;
	ADCSRA |= 1<<ADSC;
}
