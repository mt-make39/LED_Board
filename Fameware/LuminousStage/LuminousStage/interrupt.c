#include <avr/io.h>
#include <avr/interrupt.h>
#include "common.h"

/************************************************************
	タイマー初期設定
************************************************************/
void tmr0Init(void)
{
	//CTCモード,clk/64
	TCCR0A = 0x02;
	TCCR0B = 0x03;
	//比較A割り込み許可
	TIMSK0 =0x02;
	//1/16MHz*64*250=1ms
	OCR0A = 0xFA;
}

/************************************************************
	比較A一致割り込み
************************************************************/
ISR(TIMER0_COMPA_vect)
{
	//タイマ割り込み1ms周期
	static uint16_t intCnt=0;
	static uint16_t pwrSwCheckCnt=0, ptnSwCheckCnt=0;

	intCnt++;
	if(intCnt  > 1000) intCnt=0;

	//10ms毎の処理
	if(!(intCnt % 10)){
		//PWR_SWの監視
		if(PWR_SW == ON){
			//長押しでPWR_HOLD
			if(pwrSwCheckCnt < LONG_PRESS){
				pwrSwCheckCnt++;
			}else{
				if(!pwrFlg) PWR_HOLD();
			}
		}else{
			if(pwrSwCheckCnt == LONG_PRESS) pwrSwState = ON_LONG;
			else if(pwrSwCheckCnt > SHORT_PRESS) pwrSwState = ON_SHORT;
			pwrSwCheckCnt = 0;												//ON時間監視リセット
		}

		//PATTERN_SWの監視
		if(PTN_SW == ON){
			if(ptnSwCheckCnt < LONG_PRESS) ptnSwCheckCnt++;					//ON時間監視
		}else{
			if(ptnSwCheckCnt == LONG_PRESS){
				ptnSwState = ON_LONG;
			}else if(ptnSwCheckCnt > SHORT_PRESS){
				ptnSwState = ON_SHORT;
			}
			ptnSwCheckCnt = 0;												//ON時間監視リセット
		}
		//ADC更新
		if(!adcEnFlg) adcEnFlg = 1;
	}

	//30ms毎の処理
	if(!(intCnt % 30)){
		//rainbow更新
		if((firstColor == RAINBOW) || (secondColor == RAINBOW))
			if(!rainbowUpdateFlg) rainbowUpdateFlg = 1;
	}
}