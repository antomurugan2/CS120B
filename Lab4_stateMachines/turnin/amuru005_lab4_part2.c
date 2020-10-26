/*	Author: amuru005
 *  Partner(s) Name: Anto Murugan
 *	Lab Section: 022
 *	Assignment: Lab 4  Exercise 2
 *	Exercise Description: Button simulator to increment/decrement value in PORTC
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


enum States { Start, OffR, OnR, OffP, OnP} state;
void Tick_OffOnRP()
{
 switch(state) { // Transitions
 case Start: // Initial transition
 state = OffR;
 PORTC = 7;
 break;
 case OffR:
 if (PINA == 0x01 && PORTC <= 9){state = OnP; ++PORTC;}
 else if (PINA == 0x02 && PORTC >= 0){state = OnP; --PORTC;}
 else {state = OffR;}
 break;
 case OnP:
 if (!(PINA == 0x01 && PORTC <= 9)) {state = OnR;}
 else if (!(PINA == 0x02 && PORTC >= 0)){state = OnR;}
 else {state = OnP;}
 break;
 case OnR:
 if (PINA == 0x01 && PORTC <= 9){state = OffP; ++PORTC;}
 else if (PINA == 0x02 && PORTC >= 0){state = OffP; --PORTC;}
 else {state = OnR;}
 break;
 case OffP:
 if (!(PINA == 0x01 && PORTC <= 9)) {state = OffR;}
 else if (!(PINA == 0x02 && PORTC >= 0)){state = OffR;}
 else {state = OffP;}
 break;
 default:
 state = Start;
 break;
 } // Transitions
}

int main(void) {
	state = Start;
 // Initialize ports
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;

	while(1) {
		Tick_OffOnRP();
	}
    return 0;
}
