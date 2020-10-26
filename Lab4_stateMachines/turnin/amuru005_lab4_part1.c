/*	Author: amuru005
 *  Partner(s) Name: Anto Murugan
 *	Lab Section: 022
 *	Assignment: Lab 4  Exercise 1
 *	Exercise Description: LED button simulator
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
 B = 0x01;
 break;
 case OffR:
 if (PINA == 0x01){state = OnP; PORTB = 0x02;}
 else if (PINA != 0x01){state = OffR;}
 break;
 case OnP:
 if (PINA != 0x01) {state = OnR;}
 else if (PINA == 0x01) {state = OnP;}
 break;
 case OnR:
 if (PINA == 0x01){state = OffP; PORTB = 0x01;}
 else if (PINA != 0x01){state = OnR;}
 break;
 case OffP:
 if (PINA != 0x01) {state = OffR;}
 else if (PINA == 0x01) {state = OffP;}
 break;
 default:
 state = Start;
 break;
 } // Transitions
}

int main(void) {
	state = start;
 // Initialize ports
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

	while(1) {
		Tick_OffOnRP();
	}
    return 0;
}
