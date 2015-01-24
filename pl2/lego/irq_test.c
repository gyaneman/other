#include "h8300_lib.h"
#include "h8300_interrupt.h"
#include "sensor.h"
#include "sev_seg.h"



void entry();


uint16 counter = 0;

void IRQ0_HANDLE(){
	counter++;

	if(gio.P6DR && 0x04){
		gio.P6DR &= ~0x04;
	}else{
		gio.P6DR |= 0x04;
	}

	print_hex(counter);
}



void entry(){
	init_irq0_int();
	gio.P6DR |= 0x04;
	print_hex(0x5555);
	while(1);
}
