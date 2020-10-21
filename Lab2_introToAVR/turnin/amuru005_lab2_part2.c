/*	Author: amuru005
 *  Partner(s) Name: Anto Murugan
 *	Lab Section: 022
 *	Assignment: Lab 2  Exercise 2
 *	Exercise Description: Parking space availability
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
	DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs, initialize to 0s
	unsigned char tmpA = 0x00; // Temporary variable to hold the value of A
	unsigned char cntavail = 0x00; // Temporary variable to hold the value of C
	while(1) {
		// 1) Read input
		tmpA = PINA & 0x0F; //Check how many parking space is occupied
		// 2) Perform computation
		if (tmpA == 0x01 | tmpA == 0x02 | tmpA == 0x04 | tmpA == 0x08) { 
			cntavail = 0x03; // if any one of the parking space is occupied then cntvail = 3
							 
		} else if (tmpA == 0x03 | tmpA == 0x06 | tmpA == 0x0C | tmpA == 0x09 | tmpA == 0x0A | tmpA == 0x05) {
			 cntavail = 0x02; // if any two of the parking spaces are occupied then cntvail = 2
							
		} else if (tmpA == 0x07 | tmpA == 0x0D | tmpA == 0x0B | tmpA == 0x0E) {
                         cntavail = 0x01; // if any three of the parking spaces are occupied then cntvail = 1

                } else if (tmpA == 0x0F) {
                         cntavail = 0x00; // if the lot is full then cntvail = 0

                } else {cntavail = 0x04;}
	// 3) Write output
	PORTC = cntavail;	
	}
	return 0;

}
