/*
 * h8300_interrupt.c
 */


#include "h8300_interrupt.h"

#define USE_FRT

//void entry_ocia();
void OCIA_intr();
//void entry_irq0();
//void set_vector_table();


//0xffff, 0x10, 0x0
#ifdef USE_FRT
void init_frt_int(){
	uint16 ocra = 0xffff;
	uint8 tier = OCIAE;
//void init_frt_int(uint16 ocra, uint8 tier, uint8 clock_sorce) {
	uint8 tmp;

	set_vector_table(INT_OCIA, OCIA_intr);

	frt.TCSR |= 0x01;

	frt.TOCR |= 0x08;
	//tmp = frt.TOCR;
	//tmp &= ~OCRS;
	//frt.TOCR = tmp;

	frt.OCRAB = ocra;

	//frt.TCR |= clock_sorce;

	frt.TIER = tier;

}

uint16 counter;
void OCIA_HANDLE(){
	counter++;
	gio.P6DR |= 0x01;
	if(counter >= 500){
		print_hex(get_sensor_value(1));
		counter = 0;
	}
}
#endif

#ifdef USE_IRQ0
void init_irq0_int(){
	set_vector_table(INT_IRQ0, entry_irq0);

	sysctl.ISCR |= IRQ0SC;
	sysctl.IER |= IRQ0E;
}
#endif
