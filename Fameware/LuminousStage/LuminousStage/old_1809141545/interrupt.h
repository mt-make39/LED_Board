#ifndef INTERRUPT_H
#define INTERRUPT_H
#include "common.h" //LEDNUMを参照する為
#include "ws2813.h"

extern volatile uint8_t pwrFlg;
extern volatile LedParam led[LEDNUM];
extern volatile uint8_t ptnMode;
extern volatile uint8_t firstColor;
extern volatile uint8_t secondColor;
extern volatile uint8_t rRed, rGreen, rBlue;
extern volatile uint8_t rainbowStep;

void tmr0Init(void);
//ISR(TIMER0_COMPA_vect);

#endif