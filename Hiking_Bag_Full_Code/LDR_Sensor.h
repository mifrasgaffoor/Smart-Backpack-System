

#ifndef LDR_SENSOR_H_
#define LDR_SENSOR_H_

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void initialize_LDR();
void LDR_Output();


#endif /* LDR_SENSOR_H_ */