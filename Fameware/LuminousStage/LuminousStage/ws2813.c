#include <avr/io.h>
#include <avr/interrupt.h>
//#include <math.h>
#include "common.h"

/************************************************************
	単色モードの点灯色制御
************************************************************/
void singleColor(void)
{
	if(firstColor == RAINBOW){
		for(int i=0; i<LEDNUM; i++){
			led[i].red = rRed;
			led[i].green = rGreen;
			led[i].blue = rBlue;
		}
	}else{
		for(int i=0; i<LEDNUM; i++) setColor(i,firstColor);
	}
}

/************************************************************
	2色モードの点灯色制御 市松模様
************************************************************/
void doubleColor_A(void)
{
	for(int i=0; i<LEDNUM; i++){
		if(i % 2){							//偶数番firstColor
			if(firstColor == RAINBOW){
				led[i].red = rRed;
				led[i].green = rGreen;
				led[i].blue = rBlue;
			}else{
				setColor(i,firstColor);
			}
		}else{								//奇数番secondColor
			if(secondColor == RAINBOW){
				led[i].red = rRed;
				led[i].green = rGreen;
				led[i].blue = rBlue;
			}else{
				setColor(i,secondColor);
			}
		}
	}
}

/************************************************************
	2色モードの点灯色制御 回の字
************************************************************/
void doubleColor_B(void)
{
	for(int i=0; i<LEDNUM; i++){
		if((i == 6) || (i == 7) || (i == 8) || (i == 11) || (i == 13) || (i == 16) || (i == 17) || (i == 18)){
			if(secondColor == RAINBOW){
				led[i].red = rRed;
				led[i].green = rGreen;
				led[i].blue = rBlue;
				}else{
				setColor(i,secondColor);
			}
		}else{
			if(firstColor == RAINBOW){
				led[i].red = rRed;
				led[i].green = rGreen;
				led[i].blue = rBlue;
				}else{
				setColor(i,firstColor);
			}
		}
	}
}

/************************************************************
	2色モードの点灯色制御 左下から右上へグラデーション
************************************************************/
void gradation_LB_RT(void)
{
	LedParam first = {presetColor[firstColor].green, presetColor[firstColor].red, presetColor[firstColor].blue};
	LedParam second = {presetColor[secondColor].green, presetColor[secondColor].red, presetColor[secondColor].blue};
	LedParam defColor;
	uint8_t incOrDec = 0;
	
	//firstとsecondの色の差分をdefColorにセット
	//オーバーフロー処理が面倒な為、四捨五入はしない
	if(first.green > second.green){
		defColor.green = (first.green - second.green) / 8;
		incOrDec |= 0x01; //デクリメント
	}else{
		 defColor.green = (second.green - first.green) / 8;
	}
	if(first.red > second.red){
		defColor.red = (first.red - second.red) / 8;
		incOrDec |= 0x02; //デクリメント
	}else{
		defColor.red = (second.red - first.red) / 8;
	}
	if(first.blue > second.blue){
		defColor.blue = (second.blue - first.blue) / 8;
		incOrDec |= 0x04; //デクリメント
	}else{
		defColor.blue = (second.blue - first.blue) / 8;
	}
	
	for(int i=0; i<LEDNUM; i++){
		setColor(i,firstColor);
		switch(i){
			case 20:
				break;
			case 19:
			case 21:
				if(incOrDec & 0x01) led[i].green -= defColor.green;
				else led[i].green += defColor.green;
				if(incOrDec & 0x02) led[i].red -= defColor.red;
				else led[i].red += defColor.red;
				if(incOrDec & 0x04) led[i].blue -= defColor.blue;
				else led[i].blue += defColor.blue;
				break;
			case 10:
			case 18:
			case 22:
				if(incOrDec & 0x01) led[i].green -= defColor.green * 2;
				else led[i].green += defColor.green * 2;
				if(incOrDec & 0x02) led[i].red -= defColor.red * 2;
				else led[i].red += defColor.red * 2;
				if(incOrDec & 0x04) led[i].blue -= defColor.blue * 2;
				else led[i].blue += defColor.blue * 2;
				break;
			case 9:
			case 11:
			case 17:
			case 23:
				if(incOrDec & 0x01) led[i].green -= defColor.green * 3;
				else led[i].green += defColor.green * 3;
				if(incOrDec & 0x02) led[i].red -= defColor.red * 3;
				else led[i].red += defColor.red * 3;
				if(incOrDec & 0x04) led[i].blue -= defColor.blue * 3;
				else led[i].blue += defColor.blue * 3;
				break;
			case 0:
			case 8:
			case 12:
			case 16:
			case 24:
				if(incOrDec & 0x01) led[i].green -= defColor.green * 4;
				else led[i].green += defColor.green * 4;
				if(incOrDec & 0x02) led[i].red -= defColor.red * 4;
				else led[i].red += defColor.red * 4;
				if(incOrDec & 0x04) led[i].blue -= defColor.blue * 4;
				else led[i].blue += defColor.blue * 4;
				break;
			case 1:
			case 7:
			case 13:
			case 15:
				if(incOrDec & 0x01) led[i].green -= defColor.green * 5;
				else led[i].green += defColor.green * 5;
				if(incOrDec & 0x02) led[i].red -= defColor.red * 5;
				else led[i].red += defColor.red * 5;
				if(incOrDec & 0x04) led[i].blue -= defColor.blue * 5;
				else led[i].blue += defColor.blue * 5;
				break;
			case 2:
			case 6:
			case 14:
				if(incOrDec & 0x01) led[i].green -= defColor.green * 6;
				else led[i].green += defColor.green * 6;
				if(incOrDec & 0x02) led[i].red -= defColor.red * 6;
				else led[i].red += defColor.red * 6;
				if(incOrDec & 0x04) led[i].blue -= defColor.blue * 6;
				else led[i].blue += defColor.blue * 6;
				break;
			case 3:
			case 5:
				if(incOrDec & 0x01) led[i].green -= defColor.green * 7;
				else led[i].green += defColor.green * 7;
				if(incOrDec & 0x02) led[i].red -= defColor.red * 7;
				else led[i].red += defColor.red * 7;
				if(incOrDec & 0x04) led[i].blue -= defColor.blue * 7;
				else led[i].blue += defColor.blue * 7;
				break;
			case 4:
				if(incOrDec & 0x01) led[i].green -= defColor.green * 8;
				else led[i].green += defColor.green * 8;
				if(incOrDec & 0x02) led[i].red -= defColor.red * 8;
				else led[i].red += defColor.red * 8;
				if(incOrDec & 0x04) led[i].blue -= defColor.blue * 8;
				else led[i].blue += defColor.blue * 8;
				break;
		}
	}
	
	
	
}

/************************************************************
	各LEDの点灯色設定値変更
		adr:LED番号 0からLEDNUM-1まで
		presetNum:プリセットナンバー 0からPRESET_MAX-1まで
************************************************************/
void setColor(uint8_t  adr, uint8_t  presetNum)
{
	if(adr >= LEDNUM) adr = 0;
	if(presetNum >= PRESET_MAX) presetNum = 0;

	led[adr].green = presetColor[presetNum].green;
	led[adr].red = presetColor[presetNum].red;
	led[adr].blue = presetColor[presetNum].blue;
}

/************************************************************
	オーディオレベルを元に輝度を反映
		全LED同じ割合
************************************************************/
void brightnessAudioAll(void)
{
	/*if(audioLevel == 0){
		for(int i=0; i<LEDNUM; i++){
			led[i].red = 0;
			led[i].green = 0;
			led[i].blue = 0;
		}
	}else{
		double tmp;
		tmp = audioLevel * (20 * log((double)audioLevel) / 60.0);
		if(tmp > 1.0) tmp = 1.0;
		for(int i=0; i<LEDNUM; i++){
			led[i].red = led[i].red * tmp + 0.5;
			led[i].green = led[i].green * tmp + 0.5;
			led[i].blue = led[i].blue * tmp + 0.5;
		}		
	}*/
	
	float tmp = (float)audioLevel / (AUDIO_LEVEL_MAX - AUDIO_LEVEL_OFFSET);
	
	for(int i=0; i<LEDNUM; i++){
		led[i].red = led[i].red * tmp + 0.5;
		led[i].green = led[i].green * tmp + 0.5;
		led[i].blue = led[i].blue * tmp + 0.5;
	}
}

/************************************************************
	オーディオレベルを元に輝度を反映
		斜め方向に輝度を変更
************************************************************/
void brightnessAudioMeter(void)
{	
	float tmp[9];
	float ref;
	
	ref = (AUDIO_LEVEL_MAX - AUDIO_LEVEL_OFFSET) / 9.0;
	
	for(int i=0; i<9; i++){
		if(0.0 < (audioLevel - ref * (i + 1))){
			tmp[i] = 1.0;
		}else{
			tmp[i] = 0.5;
			for(int j=i; j<9; j++) tmp[j] = 0.0;
			break;
		}
	}
	
	for(int i=0; i<LEDNUM; i++){
		switch(i){
			case 20:
				led[i].red = led[i].red * tmp[0] + 0.5;
				led[i].green = led[i].green * tmp[0] + 0.5;
				led[i].blue = led[i].blue * tmp[0] + 0.5;
				break;
			case 19:
			case 21:
				led[i].red = led[i].red * tmp[1] + 0.5;
				led[i].green = led[i].green * tmp[1] + 0.5;
				led[i].blue = led[i].blue * tmp[1] + 0.5;
				break;
			case 10:
			case 18:
			case 22:
				led[i].red = led[i].red * tmp[2] + 0.5;
				led[i].green = led[i].green * tmp[2] + 0.5;
				led[i].blue = led[i].blue * tmp[2] + 0.5;
				break;
			case 9:
			case 11:
			case 17:
			case 23:
				led[i].red = led[i].red * tmp[3] + 0.5;
				led[i].green = led[i].green * tmp[3] + 0.5;
				led[i].blue = led[i].blue * tmp[3] + 0.5;
				break;
			case 0:
			case 8:
			case 12:
			case 16:
			case 24:
				led[i].red = led[i].red * tmp[4] + 0.5;
				led[i].green = led[i].green * tmp[4] + 0.5;
				led[i].blue = led[i].blue * tmp[4] + 0.5;
				break;
			case 1:
			case 7:
			case 13:
			case 15:
				led[i].red = led[i].red * tmp[5] + 0.5;
				led[i].green = led[i].green * tmp[5] + 0.5;
				led[i].blue = led[i].blue * tmp[5] + 0.5;
				break;
			case 2:
			case 6:
			case 14:
				led[i].red = led[i].red * tmp[6] + 0.5;
				led[i].green = led[i].green * tmp[6] + 0.5;
				led[i].blue = led[i].blue * tmp[6] + 0.5;
				break;
			case 3:
			case 5:
				led[i].red = led[i].red * tmp[7] + 0.5;
				led[i].green = led[i].green * tmp[7] + 0.5;
				led[i].blue = led[i].blue * tmp[7] + 0.5;
				break;
			case 4:
				led[i].red = led[i].red * tmp[8] + 0.5;
				led[i].green = led[i].green * tmp[8] + 0.5;
				led[i].blue = led[i].blue * tmp[8] + 0.5;
				break;
		}
	}
}

/************************************************************
	全LEDの点灯色の更新
************************************************************/
void updateLed(void)
{
	volatile uint8_t *port = &LED_PORT;			//LEDが接続されているポートのアドレス
	volatile uint8_t *ptr = led;				//データ出力用の変数の先頭アドレス
	volatile uint16_t i = sizeof(led);			//データのバイト数
	volatile uint8_t b, hi, lo, next, bit;

	b = *ptr++;
	hi = PORTD | _BV(LED_PIN);
	lo = PORTD & ~_BV(LED_PIN);
	next = lo;
	bit = 8;
	
	//タイマ割り込み禁止
	TIMSK0 = 0x00;

	asm volatile(
		//One=14clk+5clk, Zero=5clk+14clk
		"HEAD20:"                  "\n\t"	// Clk  Pseudocode    (T =  0)
		"ST   %a[PORT],  %[HI]"    "\n\t"	// 2    PORT = hi     (T =  2)
		"SBRC %[BYTE],  7"         "\n\t"	// T:2,F:1 if(b & 128)
		"MOV  %[NEXT], %[HI]"      "\n\t"	// T:0,F:1 next = hi  (T =  4)
		"DEC  %[BIT]"              "\n\t"	// 1    bit--         (T =  5)
		"ST   %a[PORT],  %[NEXT]"  "\n\t"	// 2    PORT = next   (T =  7)
		"MOV  %[NEXT] ,  %[LO]"    "\n\t"	// 1    next = lo     (T =  8)
		"BREQ NEXTBYTE20"          "\n\t"	// T:2,F:1 if(bit == 0)
		"ROL  %[BYTE]"             "\n\t"	// 1    b <<= 1       (T = 10)
		"RJMP .+0"                 "\n\t"	// 2    nop nop       (T = 12)
		"RJMP .+0"                 "\n\t"	// 2    nop nop       (T = 14)
		//"NOP"                      "\n\t"	// 1    nop           (T = 13)
		"ST   %a[PORT],  %[LO]"    "\n\t"	// 2    PORT = lo     (T = 16)
		"NOP"                      "\n\t"	// 1    nop           (T = 17)
		//"RJMP .+0"                 "\n\t"	// 2    nop nop       (T = 18)
		"RJMP HEAD20"              "\n\t"	// 2    -> head20 (next bit out)
		"NEXTBYTE20:"              "\n\t"	//                    (T = 10)
		"LDI  %[BIT]  ,  8"        "\n\t"	// 1    bit = 8       (T = 11)
		"LD   %[BYTE] ,  %a[PTR]+" "\n\t"	// 2    b = *ptr++    (T = 13)
		"ST   %a[PORT], %[LO]"     "\n\t"	// 2    PORT = lo     (T = 15)
		//"LD   %[BYTE] ,  %a[PTR]+" "\n\t"	// 2    b = *ptr++    (T = 17)
		"NOP"                      "\n\t"	// 1    nop           (T = 16)
		"SBIW %[COUNT], 1"         "\n\t"	// 2    i--           (T = 18)
		"BRNE HEAD20"              "\n"		// 2    if(i != 0) -> (next byte)
		: [PORT]  "+e" (port),
		[BYTE]  "+r" (b),
		[BIT]   "+r" (bit),
		[NEXT]  "+r" (next),
		[COUNT] "+w" (i)
		: [PTR]    "e" (ptr),
		[HI]     "r" (hi),
		[LO]     "r" (lo));
	
	//タイマ割り込み再開
	TIMSK0 = 0x02;
}