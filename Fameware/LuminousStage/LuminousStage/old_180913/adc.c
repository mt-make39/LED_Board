#include <avr/io.h>
#include "adc.h"
#include "common.h"

void adcInit(void)
{
	//外部基準電圧,左揃え,ADC0(PC0)
	ADMUX = 0x20;
	//A/D許可,割り込み禁止,CLK/2
	ADCSRA = 0x80;
}

uint8_t adcStart(void)
{
	ADCSRA |= _BV(ADSC);
	while(ADSC & _BV(ADSC));

	return ADCH;
}

uint16_t adcAverage(uint8_t cnt)
{
	if(cnt < 3) cnt = 3;
	uint8_t max = 0;
	uint8_t min = 0xFF;
	uint8_t tmp = 0;
	uint16_t sum = 0;

	for(int i=0; i<cnt; i++){
		tmp = adcStart();
		if(tmp > max) max = tmp;
		if(tmp < min) min = tmp;
		sum += tmp;
	}
	sum -= max;
	sum -= min;
	sum /= cnt;

	return sum << 2;
}