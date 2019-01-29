/*
 * LuminousStage.c
 *
 * Created: 2018/09/09 20:24:11
 * Author : KOKORO
 */
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
//#include <avr/wdt.h>
#include "common.h"

//PWR_HOLD完了フラグ
volatile uint8_t pwrFlg = 0;

//PWR_SWステータス
volatile uint8_t pwrSwState = OFF;
volatile uint8_t ptnSwState = OFF;

//各LEDの点灯色管理用変数
volatile LedParam led[LEDNUM];
//カラープリセット
volatile const LedParam presetColor[PRESET_MAX] = {
											{0,240,0},
											{0,0,240},
											{240,0,0},
											{255,255,0},
											{100,255,100},
											{255,0,255},
											{255,0,64},
											{64,255,0},
											{255,255,255},
											{0,255,255}};
//各LEDの輝度管理用変数
volatile uint8_t brightness[LEDNUM] = {BRIGHTNESS_MAX};
//LED更新フラグ
volatile uint8_t updateLedFlg = 0;
//1色目,2色目のプリセットナンバー
volatile uint8_t firstColor = 0;
volatile uint8_t secondColor = 1;
//現在の点灯パターン管理用変数
volatile uint8_t ptnMode = 0;
//Rainbow更新フラグ
volatile uint8_t rainbowUpdateFlg = 0;
//Rainbowモードのステップ管理 0~2
volatile uint8_t rainbowStep = 0;
//RainbowモードのRGB値
volatile uint8_t rRed = 0, rGreen = 0, rBlue = 0;
//ADC更新フラグ
volatile uint8_t adcEnFlg = 0;
//音声レベル
volatile uint16_t audioLevel = 0;

/************************************************************
	各種ポートの入出力設定
************************************************************/
void avrInit(void)
{
	DDRB = _BV(PB3) | _BV(PB5);
	DDRC = 0x00;
	DDRD = _BV(PD1) | _BV(LED_PIN) | _BV(PWR_HOLD_PIN) | _BV(PD5); //PD5 is Debug Pin

	/*//MCUSR &= ~_BV(WDRF);
	MCUSR = 0x00;
	WDTCSR |= _BV(WDCE) | _BV(WDE);
	WDTCSR = 0x00;*/
}

/************************************************************
	メイン関数
************************************************************/
int main(void)
{
	avrInit();		//AVR初期化
	tmr0Init();		//TMR0割り込み初期化
	adcInit();		//ADC初期化
	uartInit();		//UART初期化
	sei();			//全体割り込み許可

	while (1){
		/******************************
		  PWR_SW押下処理
		******************************/
		switch(pwrSwState){
			//OFF時
			case OFF:
				break;
			//長押し時 電源ON/OFF処理
			case ON_LONG:
				if(pwrFlg){
					//輝度を最小にしてから電源OFF
					for(int i=0; i<LEDNUM; i++) brightness[i] = BRIGHTNESS_MIN;
					updateLed();
					PWR_OFF();
				}else{
					//PWR_HOLD完了
					pwrFlg = 1;
					updateLedFlg = 1;
				}
				pwrSwState = OFF;
				break;
			case ON_SHORT:
				//短押しでfirstColor変更
				firstColor++;
				if((firstColor == secondColor) && (ptnMode != SINGLE)) firstColor++;
				updateLedFlg = 1;
				if(firstColor == RAINBOW){								//Rainbow用の変数を初期化
					if(ptnMode == GRADATION) firstColor = 0;
					else{
						rRed = 0xFF;
						rGreen = 0x00;
						rBlue = 0x00;
						rainbowStep = 0;
					}
				}else if(firstColor > RAINBOW) firstColor = 0;
				pwrSwState = OFF;
				break;
		}
		/******************************
		  PTN_SW押下処理
		******************************/
		switch(ptnSwState){
			//OFF時
			case OFF:
				break;
			//長押し時 点灯パターン切替
			case ON_LONG:
				ptnMode++;
				if(ptnMode >= PTATTEN_TYPE) ptnMode = 0;
				ptnSwState = OFF;
				if(firstColor == secondColor) secondColor++;			//2色が同じ色にならないように処理
				updateLedFlg = 1;
				if(secondColor ==RAINBOW){								//Rainbow用の変数を初期化
					rRed = 0xFF;
					rGreen = 0x00;
					rBlue = 0x00;
					rainbowStep = 0; //rRedのみ増加
				}else if(secondColor > RAINBOW) secondColor = 0;
				break;
			//短押し時 カラー変更
			case ON_SHORT:
				if(ptnMode == SINGLE){										//単色モード:前の色に戻す
					if(firstColor == 0) firstColor = RAINBOW;
					else firstColor--;
					updateLedFlg = 1;
					if(firstColor ==RAINBOW){								//Rainbow用の変数を初期化
						rRed = 0xFF;
						rGreen = 0x00;
						rBlue = 0x00;
						rainbowStep = 0; //rRedのみ増加
					}
				}else if((ptnMode == DOUBLE_A) || (ptnMode == DOUBLE_B) || (ptnMode ==GRADATION)){	//2色モード:secondColorの変更
					secondColor++;
					if(firstColor == secondColor) secondColor++;
					updateLedFlg = 1;
					if(secondColor ==RAINBOW){								//Rainbow用の変数を初期化
						if(ptnMode == GRADATION) secondColor = 0;
						else{
							rRed = 0xFF;
							rGreen = 0x00;
							rBlue = 0x00;
							rainbowStep = 0; //rRedのみ増加
						}
					}else if(secondColor > RAINBOW) secondColor = 0;
				}
				ptnSwState = OFF;
				break;
		}
		/******************************
		  Rainbow計算処理
		******************************/
		if(rainbowUpdateFlg){
			rainbowUpdateFlg = 0;
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

		/******************************
		  オーディオレベル更新処理
		******************************/
		if(adcEnFlg){
			adcEnFlg = 0;
			audioLevel = adcAverage(10);
			//if(UCSR0A & _BV(UDRE0)) send1byte((uint8_t)(audioLevel>>8));
			//if(UCSR0A & _BV(UDRE0)) send1byte((uint8_t)audioLevel);
			updateLedFlg = 1;
		}

		/******************************
		  LED更新処理
		******************************/
		if(updateLedFlg && pwrFlg){
			updateLedFlg = 0;
			switch(ptnMode){
				case SINGLE:
					singleColor();
					break;
				case DOUBLE_A:
					doubleColor_A();
					break;
				case DOUBLE_B:
					doubleColor_B();
					break;
				case GRADATION:
					gradation_LB_RT();
					break;
				case SINGLE_All:
					singleColor();
					brightnessAudioAll();
					break;
				case DOUBLE_A_All:
					doubleColor_A();
					brightnessAudioAll();
					break;
				case DOUBLE_B_All:
					doubleColor_B();
					brightnessAudioAll();
					break;
				case GRADATION_All:
					gradation_LB_RT();
					brightnessAudioAll();
					break;
				case SINGLE_Meter:
					singleColor();
					brightnessAudioMeter();
					break;
				case GRADATION_Meter:
					gradation_LB_RT();
					brightnessAudioMeter();
					break;
			}
			//LED更新
			updateLed();
		}
	}
}

