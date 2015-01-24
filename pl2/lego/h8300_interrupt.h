/*
 * h8300_interrupt.h
 */

#ifndef H8300_INTERRUPT_H
#define H8300_INTERRUPT_H

#include "h8300_lib.h"



/*
 * Vector table
 */
#define INT_OCIA	0xfda2
#define INT_IRQ0	0xfd94
#define INT_IRQ1	0xfd96




/*
 * free running timer
 */
/* TOCR */
#define OCRS	0x10
#define OEA		0x08
#define OEB		0x04
#define OLVLA	0x02
#define OLVLB	0x01

/* TIER */
#define ICIAE
#define ICIBE
#define ICICE
#define ICIDE
#define OCIAE	0x08
#define OCIBE	0x04
#define OVIE	0x02

/* clock sorce */
#define CS_2	0x0
#define CS_8	0x1
#define CS_32	0x2
#define CS_EX	0x3



/*
 * IRQ 0~2
 */
/* ISCR  FFC6 */
#define IRQ2SC	0x04
#define IRQ1SC	0x02
#define IRQ0SC	0x01

/* IRQ Enable Register */
#define IRQ2E	0x04
#define IRQ1E	0x02
#define IRQ0E	0x01




/*
 * functions
 */
/* free running timer */
void init_frt_int(uint16 ocra, uint8 tier, uint8 clock_sorce);
void OCIA_HANDLE();

/* IRQ */
void init_irq0_int();
void IRQ0_HANDLE();

#endif /* H8300_INTERRUPT_H */
