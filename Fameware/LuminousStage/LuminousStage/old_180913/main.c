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
#include "adc.h"
#include "interrupt.h"
#include "ws2813.h"

//PWR_HOLD完了フラグ
volatile uint8_t pwrFlg = 0;

//各LEDの点灯色管理用変数
volatile LedParam led[LEDNUM];
//カラープリセット
volatile const LedParam presetColor[PRESET_MAX] = {
											{0,255,0},
											{0,0,255},
											{255,0,0},
											{255,255,0},
											{127,255,255},
											{255,0,255},
											{255,127,127},
											{127,255,0},
											{255,255,255},
											{0,255,255}};
//各LEDの輝度管理用変数
volatile uint8_t brightness[LEDNUM] = {BRIGHTNESS_MAX};
//1色目,2色目のプリセットナンバー
volatile uint8_t firstColor = 0;
volatile uint8_t secondColor = 1;
//現在の点灯パターン管理用変数
volatile uint8_t ptnMode = 0;
//RainbowモードのRGB値
volatile uint8_t rRed = 0, rGreen = 0, rBlue = 0;
//Rainbowモードの増減方向 0bit=rRed, 1bit=rGreen, 2bit=rBlue 1なら増加 0なら減少
volatile uint8_t rainbowUpFlg;
//音声レベル
volatile uint16_t audioLevel=0;

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
	sei();			//全体割り込み許可
	
	while (1){
		switch(ptnMode){
			case SINGLE:
				singleColor();
				break;
			case DOUBLE_A:
				doubleColor_A();
				break;
			case DOUBLE_B:
				break;
			default:
				break;
		}
		_delay_ms(10);
	}
}

