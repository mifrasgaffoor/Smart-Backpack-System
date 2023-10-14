

#include "MQ135_Sensor.h"
#include "MQ135_Sensor_LCDDisplay.h"

char RoStr[10];
int gas_presentage=0;
char gas_presentage_str[10];

void Air_Composition()
{
	DDRA |= (1<<0);
	DDRD |= (1<<2);
	
	char printbuff[100];
	double d = 0;
	uint16_t adc = 0;
	//long mq135_ro = 0;
	
	adc_init(1, AVCC, 0);
	lcd_init(LCD_DISP_ON);
	
	while (1)
	{
		adc = adc_read(0);
		long res = adc_getresistence(adc, MQ135_PULLDOWNRES);
		//mq135_ro = mq135_getro(res, MQ135_DEFAULTPPM);
		d = mq135_getppm(res, MQ135_DEFAULTRO);
		
		dtostrf(d, 3, 5, printbuff);
		lcd_gotoxy(0, 0);
		lcd_puts("CO2: ");
		lcd_gotoxy(6, 0);
		lcd_puts(printbuff);
		lcd_gotoxy(15, 0);
		lcd_puts("ppm");
		
		if (d>100){
			lcd_gotoxy(0, 1);
			lcd_puts("Buzzer ON");
			PORTD |= (1<<2);
		}
		else{
			PORTD &= ~(1<<2);
			lcd_gotoxy(0, 1);
			lcd_puts("Buzzer OFF");
		}
	}
	
}


long mq135_getro(long resvalue, double ppm) {
	return (long)(resvalue * exp( log(MQ135_SCALINGFACTOR/ppm) / MQ135_EXPONENT ));
}

double mq135_getppm(long resvalue, long ro) {
	double ret = 0;
	//double validinterval = 0;
	//validinterval = resvalue/(double)ro;
	
	ret = (double)MQ135_SCALINGFACTOR * pow( ((double)resvalue/ro), MQ135_EXPONENT);
	
	return ret;
	
}



void adc_init(unsigned char prescaler, unsigned char vref, unsigned char location)
{
	ADCSRA |= (1<<ADEN);
	ADCSRA |= (1<<ADATE);
	adc_clkPrescaler(prescaler);
	adc_voltageReference(vref);
	location ? (ADMUX |= (1<<ADLAR)) : (ADMUX &= ~(1<<ADLAR));
	
	
	sei();
	return;
}


void adc_clkPrescaler(unsigned char prescaler)
{
	ADCSRA &= (~(1<<ADPS0)) & (~(1<<ADPS1)) & (~(1<<ADPS2)); 
	switch(prescaler){
		case 2:
			ADCSRA |= (1<<ADPS0);							
			break;
		case 4:
			ADCSRA |= (1<<ADPS1);							
			break;
		case 8:
			ADCSRA |= (1<<ADPS0) | (1<<ADPS1);				
			break;
		case 16:
			ADCSRA |= (1<<ADPS2);							
			break;
		case 32:
			ADCSRA |= (1<<ADPS0) | (1<<ADPS2);				
			break;
		case 64:
			ADCSRA |= (1<<ADPS1) | (1<<ADPS2);				
			break;
		case 128:
			ADCSRA |= (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2);	
			break;
		default:
			ADCSRA |= 0x00;			
	}
	return;
}

void adc_voltageReference(unsigned char Vref){
	ADMUX &= (~(1<<REFS0)) & (~(1<<REFS1));

	switch(Vref){
		case AREF:
			ADMUX |= 0x00;						
			break;
		case AVCC:
			ADMUX |= (1<<REFS0);				
			break;
		case INTERNAL:
			ADMUX |= (1<<REFS0) | (1<<REFS1);	
			break;
		default:
			ADMUX |= 0x00;
	}
	return;
}

void adc_inputChannel(unsigned char input_channel){
	ADMUX &= 0xC0; 
	
	

	switch(input_channel)
	{
		case ADC0:
			ADMUX |= 0x00;							
			break;
		case ADC1:
			ADMUX |= (1<<MUX0);						
			break;
		case ADC2:
			ADMUX |= (1<<MUX1);						
			break;
		case ADC3:
			ADMUX |= (1<<MUX0) | (1<<MUX1);			
			break;
		case ADC4:
			ADMUX |= (1<<MUX2);						
			break;
		case ADC5:
			ADMUX |= (1<<MUX0) | (1<<MUX2);			
			break;
		case ADC6:
			ADMUX |= (1<<MUX1) | (1<<MUX2);			
			break;
		case ADC7:
			//ADMUX |= 0x07;
			ADMUX |= (1<<MUX0) | (1<<MUX1) | (1<<MUX2);
			break;
		default:
			ADMUX |= (0x1F & input_channel);
	}
	return;
}
//****************************************************************************
unsigned int adc_read(unsigned char input_channel){
	int analogReading = 0;
	unsigned char LSB;
	unsigned char MSB;
	adc_inputChannel(input_channel);
	ADCSRA |= (1<<ADSC);    
	while((ADCSRA & (1<<ADIF)) == 0); 
	LSB = ADCL;
	MSB = ADCH;
	analogReading |= MSB;
	analogReading <<= 8;
	analogReading |= LSB;
	return analogReading;
}

long adc_getresistence(uint16_t adcread, uint16_t adcbalanceresistor)
{
	if(adcread == 0)
	return 0;
	else
	return (long)((long)(1024*(long)adcbalanceresistor)/adcread-(long)adcbalanceresistor);
}


void buzinit(void)
{
	BUZ_DDR 		|= _BV(BUZ_PIN);
	BUZ_PORT 		&= ~_BV(BUZ_PIN);
}
void beep(int8u nbeep, int16u ontime)
{
	while(nbeep--)	{
		buzon();
		dlyms(ontime);
		buzoff();
		dlyms(100);
	}
}

void dlyms(unsigned int x)
{
	unsigned int i;
	for (i = 0; i < x; i++)
	_delay_ms(1);
}

void dlyus(unsigned int x)
{
	unsigned int i;
	for (i = 0; i < x; i++)
	_delay_us(1);
	
}