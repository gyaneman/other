/*
 * 割り込みのテスト
 */


#include "h8300_lib.h"
#include "h8300_interrupt.h"
#include "sensor.h"
#include "sev_seg.h"


void entry();

uint16 counter = 0;

/*
void entry_ocia(){
	asm("push r0");
	asm("push r1");
	asm("push r2");
	asm("push r3");
	asm("push r4");
	asm("push r5");

	print_hex(0x5555);
	gio.P6DR |= 0x04;

	asm("pop r5");
	asm("pop r4");
	asm("pop r3");
	asm("pop r2");
	asm("pop r1");
	asm("pop r0");
}*/


void OCIA_HANDLE(){
	//int i;
	//counter++;
	/*for( i = 0; i < 100; i++){
		print_hex(i);
	}*/
	//get_sensor_value(1);
	//gio.P6DR |= 0x01;
	//print_hex(i);
	/*if(counter >= 500) {
		//print_hex(get_sensor_value(1));
		counter = 0;
	}*/
	//frt.TIER &= ~0x08;
}


void entry() {
	uint8 tmp;
	//get_sensor_value(1);
	//get_sensor_value(3);
	
	init_frt_int(0xffff, OCIAE, CS_32);
	//get_sensor_value(1);
	//get_sensor_value(3);
	gio.P6DR |= 0x04;

	while(1){
		if(gio.P6DR && 0x01){
			//print_hex(0x55);
			gio.P6DR &= ~0x01;
		}else{
			gio.P6DR |= 0x01;
		}
		wait_1sec();
	}
}
