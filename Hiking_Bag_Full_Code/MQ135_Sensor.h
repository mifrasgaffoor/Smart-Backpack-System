

#ifndef MQ135_SENSOR_H_
#define MQ135_SENSOR_H_

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <avr/interrupt.h>
#include	<avr/interrupt.h>
#include 	<avr/pgmspace.h>
#include 	<avr/eeprom.h>
#include 	<avr/sleep.h>
#include 	<string.h>
#include	<math.h>

#define MQ135_PULLDOWNRES 22000

#define MQ135_DEFAULTPPM 392 //default ppm of CO2 for calibration
#define MQ135_DEFAULTRO 41763 //default Ro for MQ135_DEFAULTPPM ppm of CO2
#define MQ135_SCALINGFACTOR 116.6020682 //CO2 gas value
#define MQ135_EXPONENT -2.769034857 //CO2 gas value
#define MQ135_MAXRSRO 2.428 //for CO2
#define MQ135_MINRSRO 0.358 //for CO2

#define AREF 0					//adc_init(parameters) (INTERNAL) or (AREF) or (AVCC)
#define AVCC 1
#define INTERNAL 2

#define ADC0 0
#define ADC1 1
#define ADC2 2
#define ADC3 3
#define ADC4 4
#define ADC5 5
#define ADC6 6
#define ADC7 7
#define RIGHT 0
#define LEFT 1

typedef unsigned   char  int8u;
typedef unsigned   short   int16u;

#define	buzon()			BUZ_PORT |= _BV(BUZ_PIN)
#define	buzoff()		BUZ_PORT &= ~_BV(BUZ_PIN)

#define	BUZ_DDR						DDRD
#define	BUZ_PORT					PORTD
#define	BUZ_PIN						PD2
#define OFF_TIME					100



//functions
void Air_Composition();


extern long mq135_getro(long resvalue, double ppm);
extern double mq135_getppm(long resvalue, long ro);
void adc_init(unsigned char prescaler, unsigned char vref, unsigned char location);
void adc_clkPrescaler(unsigned char prescaler);
void adc_voltageReference(unsigned char Vref);
void adc_inputChannel(unsigned char input_channel);
unsigned int adc_read(unsigned char input_channel);
long adc_getresistence(uint16_t adcread, uint16_t adcbalanceresistor);
void beep		(int8u nbeep, int16u ontime);
void buzinit	(void);
void dlyms(unsigned int x);

#endif /* MQ135_SENSOR_H_ */





