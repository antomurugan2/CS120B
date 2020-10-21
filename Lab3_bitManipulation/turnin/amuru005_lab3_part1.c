/*	Author: amuru005
 *  Partner(s) Name: Anto Murugan
 *	Lab Section: 022
 *	Assignment: Lab 3  Exercise 1
 *	Exercise Description: Count number of 1's in PORTA and PORTB
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0x00; PORTB = 0xFF; // Configure port B's 8 pins as inputs
	DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs, initialize to 0s
	unsigned char tmpA = 0x00; // Temporary variable to hold the value of A
	unsigned char tmpB = 0x00; // Temporary variable to hold the value of B
	unsigned char tmpC = 0x00; // Temporary variable to hold the value of C
	unsigned char i = 0;
    /* Insert your solution below */
    while (1) {
	tmpA = PINA & 0xFF; // Set tmpA to values of PINA
	tmpB = PINB & 0xFF; // Set tmpB to values of PINB
	for (; i < 8; ++i) {
		if(((tmpA & (0x01 << i)) != 0)) {
			++tmpC;
		}
	}
	for (; i < 8; ++i) {
		if(((tmpB & (0x01 << i)) != 0)) {
			++tmpC;
		}
	}
	PORTC = tmpC;
    }
    return 0;
}
