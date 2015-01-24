//#include "sev_seg.h"
#include "sensor.h"


#ifdef SENSOR_TEST
void entry();
#endif


#if 0
uint16 get_sensor_value(uint16 port){
  uint8 p6dr = gio.P6DR;
  //エラー処理1~3以外ならエラー
  if(!(1 <= port && port <= 3)){
    return 0;
  }

  //センサの電源供給を遮断
  switch(port){
  case 1:
    p6dr &= ~0x04;
    break;
  case 2:
    p6dr &= ~0x02;
    break;
  case 3:
    p6dr &= ~0x01;
    break;
  default:
    return 0;
  }

  //Port7のアナログ入力電圧の読み込み
  adc.ADCSR &= ~0x02;
  adc.ADCSR |= 0x10;
  while((adc.ADCSR & ADF) == 0);
  uint16 addrc = adc.ADDRC;
  addrc = addrc >> 6;
  

  //各センサへ電源を供給する
  switch(port){
  case 1:
    p6dr &= 0x04;
    break;
  case 2:
    p6dr &= 0x02;
    break;
  case 3:
    p6dr &= 0x01;
    break;
  default:
    return 0;
  }

  //読み取った値をLCDに表示する
  return addrc;
}
#endif


uint16 get_sensor_value(uint16 port){
	uint8 tmp;
	uint16 power;
	uint8  portChannel;
	uint16 result;
	uint16 adcsr;
	volatile unsigned short *pAddr;

	// 引数portにありえない値を設定されたとき
	if(!(1 <= port && port <= 3)){
		return 0xaa;	// 10101010 10101010
	}

	// 引数portより値を設定
	switch(port){
		case 1:
			power = 0x04;
			portChannel = 0x02;
			pAddr = &(adc.ADDRC);
			break;
		case 2:
			power = 0x02;
			portChannel = 0x01;
			pAddr = &(adc.ADDRB);
			break;
		case 3:
			power = 0x01;
			portChannel = 0x00;
			pAddr = &(adc.ADDRA);
			break;
	}

	// ポートの電源供給をきる
	tmp = gio.P6DR;
	tmp &= ~power;
	gio.P6DR = tmp;

	// ADCSRの各ビットを設定
	adcsr = 0;
	adcsr |= portChannel;
	adcsr |= ADST;
	adc.ADCSR = adcsr;

	// 読めるまで待つ
	while((adc.ADCSR & ADF) == 0);

	// 値を取得
	result = *pAddr;

	// ポートの電源供給を再開
	tmp = gio.P6DR;
	tmp |= power;
	gio.P6DR = tmp;

	return result;
}


#ifdef SENSOR_TEST
void entry(){
	uint16 lcd, value;

	while(1){
	  value = get_sensor_value(3) - get_sensor_value(1);
		print_hex(value);
		wait_1sec();
	}
}
#endif
