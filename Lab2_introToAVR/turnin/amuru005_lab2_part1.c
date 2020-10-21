/*	Author: amuru005
 *  Partner(s) Name: Anto Murugan
 *	Lab Section: 022
 *	Assignment: Lab 2  Exercise 1
 *	Exercise Description: Garage door status indicator
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
	DDRB = 0xFF; PORTB = 0x00; // Configure port B's 8 pins as outputs, initialize to 0s
	unsigned char tmpB = 0x00; // Temporary variable to hold the value of B
	unsigned char tmpA = 0x00; // Temporary variable to hold the value of A
	while(1) {
		// 1) Read input
		tmpA = PINA & 0x03; //Check if Garage door(PA0) is open and light sensor(PA1) detects light
		// 2) Perform computation
		if (tmpA == 0x01) { // True if PA0 is 1 and PA1 is 0
			tmpB = 0x01; // Sets tmpB to 00000001, illuminate LED connected to PB0
							 
		} else {
			tmpB = 0x00; // Sets tmpB to 00000000, turn off LED connected to PB0
							
		}	
	// 3) Write output
	PORTB = tmpB;	
	}
	return 0;

}
