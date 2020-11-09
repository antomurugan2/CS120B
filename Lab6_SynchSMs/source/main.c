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

enum States {Start, Init, Add, Sub, R, ADDING, MINUSING}state;

void Tick() {
	switch(state) { //transitions
		case Start:
			PORTB = 0x07;
			temp = 0x00;
			state = INIT;
			break;

		case INIT:
			if ((~PINA & 0x03) == 0x01) {
				state = ADD;
			} else if ((~PINA & 0x03) == 0x02) {
				state = MINUS;
			} else if ((~PINA & 0x03) == 0x03) {
				state = RESET;
			} else if ((~PINA & 0x03) == 0x00) {
				state = INIT;
			}
			break;

		case ADD: 
			if ((~PINA & 0x03) == 0x01) {
				state = ADDING;
			} else if ((~PINA & 0x03) == 0x02) {
				state = MINUS;
			} else if ((~PINA & 0x03) == 0x03) {
				state =  RESET;
			} else if ((~PINA & 0x03) == 0x00) {
				state = INIT;
			}
			break;

		case MINUS: 
			if ((~PINA & 0x03) == 0x01) {
				state = ADD;
			} else if ((~PINA & 0x03) == 0x02) {
				state = MINUSING;
			} else if ((~PINA & 0x03) == 0x03) {
				state =  RESET;
			} else if ((~PINA & 0x03) == 0x00) {
				state = INIT;
			}
			break;

		case RESET:
			if ((~PINA & 0x03) == 0x01) {
				state = ADD;
			} else if ((~PINA & 0x03) == 0x02) {
				state = MINUS;
			} else if ((~PINA & 0x03) == 0x03) {
				state =  RESET;
			} else if ((~PINA & 0x03) == 0x00) {
				state = INIT;
			}
			break;
			
		case ADDING: 
			if ((~PINA & 0x03) == 0x01) {
				state = ADDING;
			} else if ((~PINA & 0x03) == 0x02) {
				state = MINUS;
			} else if ((~PINA & 0x03) == 0x03) {
				state =  RESET;
			} else if ((~PINA & 0x03) == 0x00) {
				state = INIT;
			}
			break;
		
		case MINUSING: 
			if ((~PINA & 0x03) == 0x01) {
				state = ADD;
			} else if ((~PINA & 0x03) == 0x02) {
				state = MINUSING;
			} else if ((~PINA & 0x03) == 0x03) {
				state =  RESET;
			} else if ((~PINA & 0x03) == 0x00) {
				state = INIT;
			}
			break;
	}
		
	switch(state){ //actions
		case Start:
			PORTB = 0x07;
			temp = 0x00;
			break;

		case INIT:
			temp = 0x00;
			break;

		case ADD: 
			temp = 0x00;
			if (PORTB < 0x09) {
				PORTB = PORTB + 0x01;
			}
			break;

		case MINUS: 
			temp = 0x00;
			if (PORTB > 0x00) {
				PORTB = PORTB - 0x01;
			}
			break;

		case RESET:
			PORTB = 0x00;
			temp = 0x00;
			break;
			
		case ADDING: 
			if ((PORTB < 0x09) && (temp >= 0x0A)) {
				PORTB = PORTB + 0x01;
				temp = 0x00;
			}
			temp = temp + 0x01;
			break;
		
		case MINUSING: 
			if ((PORTB > 0x00) && (temp >= 0x0A)) {
				PORTB = PORTB - 0x01;
				temp = 0x00;
			}
			temp = temp + 0x01;
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

