/*	Author: gowthamanto
 *  Partner(s) Name: Anto Murugan
 *	Lab Section: 022
 *	Assignment: Lab 7  Exercise 4
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
    
    while (1) {

		if (adc_var >= 0x0F) {
			PORTB = 0x01;
		} else if (adc_var >= 0x0F * 2) {
			PORTB = 0x03;
		} else if (adc_var >= 0x0F * 3) {
			PORTB = 0x07;
		} else if (adc_var >= 0x0F * 4) {
			PORTB = 0x0F;
		} else if (adc_var >= 0x0F * 5) {
			PORTB = 0x1F;
		} else if (adc_var >= 0x0F * 6) {
			PORTB = 0x3F;
		} else if (adc_var >= 0x0F * 7) {
			PORTB = 0x7F;
		} else if (adc_var >= 0x0F * 8) {
			PORTB = 0xFF;
		} 
    }
    return 0;
}
