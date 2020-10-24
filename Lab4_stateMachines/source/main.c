/*	Author: amuru005
 *  Partner(s) Name: Anto Murugan
 *	Lab Section: 022
 *	Assignment: Lab 4  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include "RIMS.h"

enum SM3_STATES { SM3_SMStart, SM3_OffR, SM3_OnR, SM3_OffP, SM3_OnP} SM3_STATE;

void Tick_OffOnRP() {
 switch(SM3_STATE) { // Transitions
    case SM3_SMStart: // Initial transition
                    SM2_STATE = SM3_OffR;
                    B = 0;
                    break;
    case SM3_OffR:
                    if (A0){SM3_STATE = SM3_OnP; B = 0x1;}
                    else if (!A0){SM3_STATE = SM3_OffR;}
                    else {SM3_STATE = SM3_OffR;}
                    break;
    case SM3_OnP:
                    if (!A0) {SM3_STATE = SM3_OnR;}
                    else if (A0) {SM3_STATE = SM3_OnP;}
                    else {SM3_STATE = SM3_OnP;}
                    break;
    case SM3_OnR:
                    if (A0){SM3_STATE = SM3_OffP; B = 0;}
                    else if (!A0){SM3_STATE = SM3_OnR;}
                    else {SM3_STATE = SM3_OnR;}
                    break;
    case SM3_OffP:
                    if (!A0) {SM3_STATE = SM3_OffR;}
                    else if (A0) {SM3_STATE = SM3_OffP;}
                    else {SM3_STATE = SM3_OffP;}
                    break;
    default:
                    SM3_STATE = SM3_OffR;
                    break;
   } // Transitions
}

void main() {
 B = 0x00; // Initialize outputs
 SM3_STATE = SM3_SMStart; // Indicates initial call
 while(1) {Tick_OffOnRP();}
}
