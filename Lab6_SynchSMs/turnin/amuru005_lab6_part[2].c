/*      Author: gowthamanto
 *  Partner(s) Name: Anto Murugan
 *      Lab Section: 022
 *      Assignment: Lab 6  Exercise 2
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

enum States {Start, pB0, pB1, pB2, pA0, Wait}state;

void Tick()
{
	switch(state){ // Transitions
	case Start:
		state = pB0;
		break;
	case pB0:
		if((~PINA & 0x01) == 0x01) {
			state = pA0;   
			break;
		} else {
			state = pB1;  
			break;
		}
	case pB1:
		if((~PINA & 0x01) == 0x01) {
			state = pA0;   
			break;
		} else {	
			state = pB2;  
			break;
		}
	case pB2:
		if((~PINA & 0x01) == 0x01) {
			state = pA0;   
			break;
		} else {
			state = pB0;  
			break;
		}
	case pA0:
		if((~PINA & 0x01) == 0x00) {
			state = Wait;   
			break;
		} else {
			state = pA0;  
			break;
		}

	case Wait:
		if((~PINA & 0x01) == 0x01) {
			if(tmpB == 0x00) {	
				state = pB0;  
				break;
			} else if(tmpB == 0x01) {	
				state = pB0;  break;
			} else if(tmp == 0x02) {	
				state = pB0;  break;
			}
		} else {
			state = Wait;  break;
		}
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
			tmp = 0x00;
			break;
		case pB1:
			PORTB = 0x02;
			tmp = 0x01;
			break;
		case pB2:
			PORTB = 0x04;
			tmp = 0x02;
			break;
		case pA0:
  			break;
		case Wait:
			if((PINA & 0x01) == 0x01) {
				break;
			} else {
				if(tmpB == 0x00) {	
					PORTB = 0x01;  
					break;
				} else if(tmpB == 0x01) {	
					PORTB = 0x02;  
					break;
				} else if(tmpB == 0x02) {	
					PORTB = 0x04;  
					break;
				}
	
			}
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
	TimerSet(300);
	TimerOn();
	while(1) {
		Tick();
		while (!TimerFlag);
		TimerFlag = 0;
	}
}
	


