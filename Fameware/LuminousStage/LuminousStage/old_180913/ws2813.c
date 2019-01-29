#include <avr/io.h>
#include "ws2813.h"
//#include "common.h"  //ws2813.h内でインクルードしている

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
	各LEDの点灯色設定値変更
		adr:LED番号 0からLEDNUM-1まで
		presetNum:プリセットナンバー 0からPRESET_MAXまで
************************************************************/
void setColor(uint8_t  adr, uint8_t  presetNum)
{
	if(adr >= LEDNUM) adr = 0;
	if(presetNum > PRESET_MAX) presetNum = 0;

	led[adr].green = presetColor[presetNum].green;
	led[adr].red = presetColor[presetNum].red;
	led[adr].blue = presetColor[presetNum].blue;
}

/************************************************************
	各LEDの点灯色設定値変更
		adr:LED番号 0からLEDNUM-1まで
		brightness:輝度 0からBRIGHTNESS_MAXまで
************************************************************/
void setBrightness(uint8_t  adr, uint8_t  brightness)
{
	if (adr >= LEDNUM) adr = 0;
	if(brightness > BRIGHTNESS_MAX) brightness = BRIGHTNESS_MAX;
	else if(brightness < BRIGHTNESS_MIN) brightness = BRIGHTNESS_MIN;

}

/************************************************************
	全LEDの点灯色の更新
************************************************************/
void updateLed(void)
{
	volatile uint8_t *port = &LED_PORT;			//LEDが接続されているポートのアドレス
	volatile LedParam data[LEDNUM];				//データ出力用の変数
	volatile uint8_t *ptr = data;				//データ出力用の変数の先頭アドレス
	volatile uint16_t i = sizeof(data);			//データのバイト数
	volatile uint8_t b, hi, lo, next, bit;

	//ledの値に輝度を反映させて出力用変数にセット
	for(int i=0; i<LEDNUM; i++){
		//data[i].green = (float)led[i].green / BRIGHTNESS_MAX * brightness[i];
		//data[i].red = (float)led[i].red / BRIGHTNESS_MAX * brightness[i];
		//data[i].blue = (float)led[i].blue / BRIGHTNESS_MAX * brightness[i];
		data[i].green = led[i].green;
		data[i].red = led[i].red;
		data[i].blue = led[i].blue;
	}

	b = *ptr++;
	hi = PORTD | _BV(LED_PIN);
	lo = PORTD & ~_BV(LED_PIN);
	next = lo;
	bit = 8;

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
}