#include <avr/io.h>
#include "common.h"

void adcInit(void)
{
	//外部基準電圧,左揃え,ADC0(PC0)
	ADMUX = 0x20;
	//A/D許可,割り込み禁止,CLK/8
	ADCSRA = 0x83;
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
	uint16_t max = 0x0000;
	uint16_t min = 0xFFFF;
	uint16_t tmp = 0;
	uint32_t sum = 0;

	for(int i=0; i<cnt; i++){
		tmp = adcStart() << 2;
		if(tmp > AUDIO_LEVEL_MAX) tmp = AUDIO_LEVEL_MAX;
		if(tmp > AUDIO_LEVEL_OFFSET) tmp -= AUDIO_LEVEL_OFFSET;
		else tmp = 0;
		if(tmp > max) max = tmp;
		if(tmp < min) min = tmp;
		sum += tmp;
	}
	//トリム平均
	sum -= max;
	sum -= min;
	sum =  (float)sum / (cnt - 2) + 0.5;
	return (uint16_t)sum;
}