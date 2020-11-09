/*	Author: gowthamanto
 *  Partner(s) Name: Anto Murugan
 *	Lab Section: 022
 *	Assignment: Lab 6  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
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

enum States {Start, pB0, pB1, pB2}state;

void Tick()
{
	switch(state){ // Transitions
		case Start:
			state = pB0;
			break;
		case pB0:
			state = pB1;
			break;
		case pB1:
			state = pB2;
			break;
		case pB2:
			state = pB0;
			break;
		default:
			state = Start;
			break;
	}

	switch(state){ // State actions
		case Start:
			PORTB = 0x00;
			break;
		case pB0:
			PORTB = 0x01;
			break;
		case pB1:
			PORTB = 0x02;
			break;
		case pB2:
			PORTB = 0x04;
			break;
	        default:
                        PORTB = 0x00;
                        break;
	}
}

int main(void)
{
	DDRB = 0xFF;
	PORTB = 0x00;

	state = Start;
	TimerSet(1000);
	TimerOn();
	while(1) {
		Tick();
		while (!TimerFlag);
		TimerFlag = 0;
	}
}
