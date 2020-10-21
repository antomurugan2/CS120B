/*	Author: amuru005
 *  Partner(s) Name: Anto Murugan
 *	Lab Section: 022
 *	Assignment: Lab 3  Exercise 3
 *	Exercise Description: Car seatbelt warning system
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
	DDRC = 0xFF; PORTC = 0x00; // Configure port C's 8 pins as outputs, initialize to 0s
	unsigned char tmpA = 0x00; // Temporary variable to hold the value of A
	unsigned char tmpC = 0x00; // Temporary variable to hold the value of C
    /* Insert your solution below */
    while (1) {
	tmpA = PINA & 0xFF; // Set tmpA to values of PINA
	switch(tmpA){		// Use switch case to identify the different levels of fuel
	case 0x00: tmpC = 0x40; break;
	case 0x01: case 0x02: tmpC = 0x60; break;
	case 0x03: case 0x04: tmpC = 0x70; break;
	case 0x05: case 0x06: tmpC = 0x38; break;
	case 0x07: case 0x08: case 0x09: tmpC = 0x3C; break;
	case 0x0A: case 0x0B: case 0x0C: tmpC = 0x3E; break;
	case 0x0D: case 0x0E: case 0x0F: tmpC = 0x3F; break;
  	case 0x30: tmpC = 0xC0; break;
	case 0x31: case 0x32: tmpC = 0x70; break;
	case 0x33: case 0x34: tmpC = 0xF0; break;
	case 0x35: case 0x36: tmpC = 0xB8; break;
	case 0x37: case 0x38: case 0x39: tmpC = 0xBC; break;
	case 0x3A: case 0x3B: case 0x3C: tmpC = 0xBE; break;
	case 0x3D: case 0x3E: case 0x3F: tmpC = 0xBF; break;
	default: tmpC = 0x40; break;
	}
	PORTC = tmpC;
    }
    return 0;
}
