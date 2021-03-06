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
	static uint8_t intCnt=0;
	static uint16_t pwrSwCheckCnt=0, ptnSwCheckCnt=0;

	intCnt++;
	if(intCnt>250)intCnt=0;

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
			if(pwrSwCheckCnt == LONG_PRESS){
				//長押しでPWR_OFF
				if(pwrFlg){
					for(int i=0; i<LEDNUM; i++) brightness[i] = BRIGHTNESS_MIN;
					updateLed();
					PWR_OFF();
				}else{
					pwrFlg = 1;
				}
			}else if(pwrSwCheckCnt > SHORT_PRESS){
				//短押しでfirstColor変更
				//if(ptmMode == SINGLE){									//単色モード
				if(1){														//単色モード
					firstColor++;
					updateLedFlg = 1;
					if(firstColor == RAINBOW){								//Rainbow用の変数を初期化
						rRed = 0xFF;
						rGreen = 0x00;
						rBlue = 0x00;
						rainbowStep = 0;
					}else if(firstColor > RAINBOW) firstColor = 0;
				}
			}
			pwrSwCheckCnt = 0;												//ON時間監視リセット
		}

		//PATTERN_SWの監視
		if(PTN_SW == ON){
			if(ptnSwCheckCnt < LONG_PRESS) ptnSwCheckCnt++;					//ON時間監視
		}else{
			if(ptnSwCheckCnt == LONG_PRESS){
				//長押しで点灯パターン切り替え
				ptnMode++;
				if(ptnMode >= PTATTEN_TYPE) ptnMode = 0;
			}else if(ptnSwCheckCnt > SHORT_PRESS){
				//短押しでカラー変更
				if(ptnMode == SINGLE){										//単色モード:前の色に戻す
					if(firstColor == 0) firstColor = RAINBOW;
					else firstColor--;
					updateLedFlg = 1;
				}else if((ptnMode == DOUBLE_A) || (ptnMode == DOUBLE_B)){	//2色モード:secondColorの変更
					secondColor++;
					updateLedFlg = 1;
					if(secondColor ==RAINBOW){								//Rainbow用の変数を初期化
						rRed = 0xFF;
						rGreen = 0x00;
						rBlue = 0x00;
						rainbowStep = 0; //rRedのみ増加
					}else if(secondColor > RAINBOW) secondColor = 0;
				}
			}
			ptnSwCheckCnt = 0;												//ON時間監視リセット
		}

		//ADC処理
		//音声レベルによってLEDの輝度を変更
		//audioLevel = adcAverage(10);
	}

	//50ms毎の処理
	if(!(intCnt % 50)){
		if((firstColor == RAINBOW) || (secondColor == RAINBOW)){
			switch(rainbowStep){
				case 0:
					//Red減少,Green増加
					rRed--;
					rGreen++;
					if(rGreen == 0xFF) rainbowStep = 1;
					break;
				case 1:
					//Green減少,Blue増加
					rGreen--;
					rBlue++;
					if(rBlue == 0xFF) rainbowStep = 2;
					break;
				case 2:
					//Blue減少,Red増加
					rBlue--;
					rRed++;
					if(rRed == 0xFF) rainbowStep =0;
					break;
			}
			updateLedFlg = 1;
		}
	}
}