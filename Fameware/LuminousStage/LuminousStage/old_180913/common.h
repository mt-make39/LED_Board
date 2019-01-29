#ifndef COMMON_H
#define COMMON_H

#define PWR_SW_PORT PIND
#define PWR_SW_PIN PD2

#define PTN_SW_PORT PIND
#define PTN_SW_PIN PD3

#define PWR_HOLD_PORT PORTD
#define PWR_HOLD_PIN PD7

#define LED_PORT PORTD
#define LED_PIN PD4

#define LEDNUM 25

#define BRIGHTNESS_MAX 10
#define BRIGHTNESS_MIN 1

#define ON 0
#define OFF 1

#define DEBUG_PIN_ON()	(PORTD |= _BV(PD5))
#define DEBUG_PIN_OFF() (PORTD &= ~_BV(PD5))

#define PWR_SW	(PWR_SW_PORT & _BV(PWR_SW_PIN))
#define PTN_SW	(PTN_SW_PORT & _BV(PTN_SW_PIN))

#define LONG_PRESS 200										//長押し時間しきい値 300*10ms=3s
#define SHORT_PRESS 3										//短押し時間しきい値 3*10ms=30ms

#define PWR_HOLD() (PWR_HOLD_PORT |= _BV(PWR_HOLD_PIN))
#define PWR_OFF() (PWR_HOLD_PORT &= ~_BV(PWR_HOLD_PIN))

#define PRESET_MAX 10										//プリセットの要素数
#define RAINBOW PRESET_MAX									//プリセットの要素番号が0～9までなのでPRESET_MAXと同じ値になる

#define PTATTEN_TYPE 3										//点灯パターンの種類
#define SINGLE 0
#define DOUBLE_A 1
#define DOUBLE_B 2

#endif