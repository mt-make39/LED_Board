#include <avr/io.h>
#include "common.h"

void EEPROM_write(uint16_t uiAddress, uint8_t ucData)
{
	while(EECR & (1<<EEPE));		//以前のEEPROMﾌﾟﾛｸﾞﾗﾐﾝｸﾞ完了まで待機
	EECR = (0<<EEPM1)|(0<<EEPM0);	//対応ﾌﾟﾛｸﾞﾗﾐﾝｸﾞ種別設定
	EEAR = uiAddress;				//EEPROMｱﾄﾞﾚｽ設定
	EEDR = ucData;					//EEPROM書き込み値を設定
	EECR |= (1<<EEMPE);				//EEPROM主ﾌﾟﾛｸﾞﾗﾑ許可
	EECR |= (1<<EEPE);				//EEPROMﾌﾟﾛｸﾞﾗﾐﾝｸﾞ開始
}

uint8_t EEPROM_read(uint16_t uiAddress)
{
	while(EECR & (1<<EEPE));		//以前のEEPROMﾌﾟﾛｸﾞﾗﾐﾝｸﾞ完了まで待機
	EEAR = uiAddress;				//EEPROMｱﾄﾞﾚｽ設定
	EECR |= (1<<EERE);				//EEPROM読み出し開始
	return EEDR;					//EEPROM読み出し値を取得,復帰
}