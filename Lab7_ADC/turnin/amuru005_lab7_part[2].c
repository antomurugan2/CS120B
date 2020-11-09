/*	Author: gowthamanto
 *  Partner(s) Name: Anto Murugan
 *	Lab Section: 022
 *	Assignment: Lab 7  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void ADC_init() {
	ADCSRA |= (1<<ADEN) | (1<<ADSC) | (1<<ADATE);
}

int main(void) {
    /* Insert DDR and PORT initializations */
    	DDRA = 0x00; PORTA = 0xFF; 
	DDRB = 0xFF; PORTB = 0x00; 
	DDRD = 0xFF; PORTD = 0x00; 
	ADC_init();

    /* Insert your solution below */
    unsigned short adc_var = ADC;
    unsigned char tmp1 = (char)adc_var;
    unsigned char tmp2 = (char)(adc_var>>8);
    
    while (1) {
		adc_var = ADC;
		tmp1 = (char)adc_var;
		tmp2 = (char)(adc_var>>8);
		PORTB = tmp1;
		PORTD = tmp2;
    }
    return 0;
}
