#ifndef COMMON_H
#define COMMON_H

/************************************************************
	マクロ定義
************************************************************/
#define PWR_SW_PORT PIND
#define PWR_SW_PIN PD2

#define PTN_SW_PORT PIND
#define PTN_SW_PIN PD3

#define PWR_HOLD_PORT PORTD
#define PWR_HOLD_PIN PD7

#define LED_PORT PORTD
#define LED_PIN PD4

#define LEDNUM 25

#define BRIGHTNESS_MAX 100
#define BRIGHTNESS_MIN 1

#define ON 0												//SW入力ピンの状態

#define OFF 1												//SWのstate管理用
#define ON_LONG 2
#define ON_SHORT 3

#define LONG_PRESS 100										//長押し時間しきい値 300*10ms=3s
#define SHORT_PRESS 3										//短押し時間しきい値 3*10ms=30ms

#define PRESET_MAX 10										//プリセットの要素数
#define RAINBOW PRESET_MAX									//プリセットの要素番号が0～9までなのでPRESET_MAXと同じ値になる

#define PTATTEN_TYPE 10										//点灯パターンの種類
#define SINGLE 0
#define DOUBLE_A 1
#define DOUBLE_B 2
#define GRADATION 3
#define SINGLE_All 4
#define DOUBLE_A_All 5
#define DOUBLE_B_All 6
#define GRADATION_All 7
#define SINGLE_Meter 8
#define GRADATION_Meter 9

#define AUDIO_LEVEL_MAX 1020								//ADC読み取り値の最大(0,1bit切り捨て)
#define AUDIO_LEVEL_OFFSET 220								//ADCオフセット(500mV)

#define DEBUG_PIN_ON()	(PORTD |= _BV(PD5))
#define DEBUG_PIN_OFF() (PORTD &= ~_BV(PD5))

#define PWR_SW	(PWR_SW_PORT & _BV(PWR_SW_PIN))
#define PTN_SW	(PTN_SW_PORT & _BV(PTN_SW_PIN))

#define PWR_HOLD() (PWR_HOLD_PORT |= _BV(PWR_HOLD_PIN))
#define PWR_OFF() (PWR_HOLD_PORT &= ~_BV(PWR_HOLD_PIN))

/************************************************************
	構造体定義
************************************************************/
typedef struct {
	volatile uint8_t green;
	volatile uint8_t red;
	volatile uint8_t blue;
} LedParam;

/************************************************************
	グローバル変数宣言(main.c)
************************************************************/
//PWR_HOLD完了フラグ
extern volatile uint8_t pwrFlg;

//PWR_SWステータス
extern volatile uint8_t pwrSwState;
extern volatile uint8_t ptnSwState;

//各LEDの点灯色管理用変数
extern volatile LedParam led[LEDNUM];
//カラープリセット
extern volatile const LedParam presetColor[PRESET_MAX];
//各LEDの輝度管理用変数
extern volatile uint8_t brightness[LEDNUM];
//LED更新フラグ
extern volatile uint8_t updateLedFlg;
//1色目,2色目のプリセットナンバー
extern volatile uint8_t firstColor;
extern volatile uint8_t secondColor;
//現在の点灯パターン管理用変数
extern volatile uint8_t ptnMode;
//Rainbow更新フラグ
volatile uint8_t rainbowUpdateFlg;
//Rainbowモードのステップ管理 0~2
extern volatile uint8_t rainbowStep;
//RainbowモードのRGB値
extern volatile uint8_t rRed, rGreen, rBlue;
//ADC更新フラグ
extern volatile uint8_t adcEnFlg;
//音声レベル
extern volatile uint16_t audioLevel;

/************************************************************
	関数プロトタイプ宣言(ws2813.c)
************************************************************/
void singleColor(void);
void doubleColor_A(void);
void doubleColor_B(void);
void gradation_LB_RT(void);
void setColor(uint8_t, uint8_t);
void brightnessAudioAll(void);
void brightnessAudioMeter(void);
void updateLed(void);

/************************************************************
	関数プロトタイプ宣言(interrupt.c)
************************************************************/
void tmr0Init(void);

/************************************************************
	関数プロトタイプ宣言(adc.c)
************************************************************/
void adcInit(void);
uint8_t adcStart(void);
uint16_t adcAverage(uint8_t);

/************************************************************
	関数プロトタイプ宣言(uart.c)
************************************************************/
void uartInit(void);
uint8_t receive1byte(void);
void send1byte(uint8_t data);

/************************************************************
	関数プロトタイプ宣言(eeprom.c)
************************************************************/
void EEPROM_write(uint16_t, uint8_t);
uint8_t EEPROM_read(uint16_t);

#endif