/*	Author: amuru005
 *  Partner(s) Name: Anto Murugan
 *	Lab Section: 022
 *	Assignment: Lab 2  Exercise 4
 *	Exercise Description: Amusement park passenger weight sensor
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    	DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
	DDRB = 0x00; PORTB = 0xFF; // Configure port B's 8 pins as inputs
	DDRC = 0x00; PORTC = 0xFF; // Configure port C's 8 pins as inputs
	DDRD = 0xFF; PORTD = 0x00; // Configure port D's 8 pins as outputs, initialize to 0s
	unsigned char tmpA = 0x00; // Temporary variable to hold the value of A
	unsigned char tmpB = 0x00; // Temporary variable to hold the value of B
	unsigned char tmpC = 0x00; // Temporary variable to hold the value of C
	unsigned char tmpD = 0x00; // Temporary variable to hold the value of D
	
	while(1) {
		// 1) Read input
		tmpA = PINA & 0xFF; //Check the weight in seat A
		tmpB = PINB & 0xFF; //Check the weight in seat B
		tmpC = PINC & 0xFF; //Check the weight in seat C
		// 2) Perform computation
		tmpD = ((tmpA + tmpB + tmpC) >> 4) & 0xFC;
		if((tmpA + tmpB + tmpC) > 0x8C){ tmpD = tmpD & 0xF1;}
		else if((tmpA - tmpC) > 0x50 | (tmpC - tmpA) > 0x50) { tmpD = tmpD & 0xF2;} 
	// 3) Write output
	PORTD = tmpD;	
	}
	return 0;

}
