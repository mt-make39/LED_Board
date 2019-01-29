#ifndef WS2813_H
#define WS2813_H
#include "common.h" //LEDNUMÇ∆PRESET_MAXÇéQè∆Ç∑ÇÈà◊

typedef struct {
	volatile uint8_t green;
	volatile uint8_t red;
	volatile uint8_t blue;
} LedParam;

extern volatile uint8_t colorNumber;
extern volatile LedParam led[LEDNUM];
extern volatile const LedParam presetColor[PRESET_MAX];
extern volatile uint8_t brightness[LEDNUM];
extern volatile uint8_t firstColor;
extern volatile uint8_t secondColor;
extern volatile uint8_t rRed, rGreen, rBlue;
extern volatile uint8_t rainbowUpFlg;

void singleColor(void);
void doubleColor_A(void);

void setColor(uint8_t, uint8_t);
void setBrightness(uint8_t, uint8_t);

void updateLed(void);

#endif