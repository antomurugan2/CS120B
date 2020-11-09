/*      Author: gowthamanto
 *  Partner(s) Name: Anto Murugan
 *      Lab Section: 022
 *      Assignment: Lab 6  Exercise 3
 *      Exercise Description: [optional - include for your own benefit]
 *
 *      I acknowledge all content contained herein, excluding template or example
 *      code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

unsigned char tmpB = 0x03;

void TimerOn()
{       
        TCCR1B = 0x0B;
        OCR1A = 125;
        TIMSK1 = 0x02;
        TCNT1=0;
        _avr_timer_cntcurr = _avr_timer_M;
        SREG |= 0x80;
}

void TimerOff()
{       
        TCCR1B = 0x00;
}

void TimerISR()
{       
        TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect)
{       
        _avr_timer_cntcurr--;
        if (_avr_timer_cntcurr == 0)
        {       
                TimerISR();
                _avr_timer_cntcurr = _avr_timer_M;
        }
}

void TimerSet(unsigned long M)
{
        _avr_timer_M = M;
        _avr_timer_cntcurr = _avr_timer_M;
}

enum States {Start, Init, Increment, Decrement, Reset, Increase, Decrease}state;

void Tick() {
	switch(state) { // Transitions
		case Start:
			PORTB = 0x07;
			tmpB = 0x00;
			state = Init;
			break;

		case Init:
			if ((~PINA & 0x03) == 0x01) {
				state = Increment;
			} else if ((~PINA & 0x03) == 0x02) {
				state = Decrement;
			} else if ((~PINA & 0x03) == 0x03) {
				state = Reset;
			} else if ((~PINA & 0x03) == 0x00) {
				state = Init;
			}
			break;

		case Increment: 
			if ((~PINA & 0x03) == 0x01) {
				state = Increase;
			} else if ((~PINA & 0x03) == 0x02) {
				state = Decrement;
			} else if ((~PINA & 0x03) == 0x03) {
				state =  Reset;
			} else if ((~PINA & 0x03) == 0x00) {
				state = Init;
			}
			break;

		case Decrement: 
			if ((~PINA & 0x03) == 0x01) {
				state = Increment;
			} else if ((~PINA & 0x03) == 0x02) {
				state = Decrease;
			} else if ((~PINA & 0x03) == 0x03) {
				state =  Reset;
			} else if ((~PINA & 0x03) == 0x00) {
				state = Init;
			}
			break;

		case Reset:
			if ((~PINA & 0x03) == 0x01) {
				state = Increment;
			} else if ((~PINA & 0x03) == 0x02) {
				state = Decrement;
			} else if ((~PINA & 0x03) == 0x03) {
				state =  Reset;
			} else if ((~PINA & 0x03) == 0x00) {
				state = Init;
			}
			break;
			
		case Increase: 
			if ((~PINA & 0x03) == 0x01) {
				state = Increase;
			} else if ((~PINA & 0x03) == 0x02) {
				state = Decrement;
			} else if ((~PINA & 0x03) == 0x03) {
				state =  Reset;
			} else if ((~PINA & 0x03) == 0x00) {
				state = Init;
			}
			break;
		
		case Decrease: 
			if ((~PINA & 0x03) == 0x01) {
				state = Increment;
			} else if ((~PINA & 0x03) == 0x02) {
				state = Decrease;
			} else if ((~PINA & 0x03) == 0x03) {
				state =  Reset;
			} else if ((~PINA & 0x03) == 0x00) {
				state = Init;
			}
			break;
		default:
			state = Start;
			break;
	}
		
	switch(state){ // State actions
		case Start:
			PORTB = 0x07;
			tmpB = 0x00;
			break;

		case Init:
			tmpB = 0x00;
			break;

		case Increment: 
			tmpB = 0x00;
			if (PORTB < 0x09) {
				PORTB = PORTB + 0x01;
			}
			break;

		case Decrement: 
			tmpB = 0x00;
			if (PORTB > 0x00) {
				PORTB = PORTB - 0x01;
			}
			break;

		case Reset:
			PORTB = 0x00;
			tmpB = 0x00;
			break;
			
		case Increase: 
			if ((PORTB < 0x09) && (tmpB >= 0x0A)) {
				PORTB = PORTB + 0x01;
				tmpB = 0x00;
			}
			tmpB = tmpB + 0x01;
			break;
		
		case Decrease: 
			if ((PORTB > 0x00) && (tmpB >= 0x0A)) {
				PORTB = PORTB - 0x01;
				tmpB = 0x00;
			}
			tmpB = tmpB + 0x01;
			break;
		default:
			PORTB = 0x00;
			break;
	}
}

int main(void)
{
	DDRA = 0x00;
	PORTA = 0xFF;
	DDRB = 0xFF;
	PORTB = 0x00;

	state = Start;
	TimerSet(100);
	TimerOn();
	while(1) {
		Tick();
		while (!TimerFlag);
		TimerFlag = 0;
	}
}

