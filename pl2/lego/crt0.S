                .section .text
                .p2align 1
                .global _start
				.global	_wait_1sec
				.global _wait_1msec
_start:		ldc     #0x80,ccr       ; interrupt disable
; WDT
		mov.w	#0xA518,r1
		mov.w	r1,@0xFFA8	; TCSR write

; System Control
		xor.b	r0l,r0l

		mov.b	r0l,@0xFFBB:8	; P6DR = 0x00
		mov.b	#0x87,r0h	; P6-7(carrier),2/1/0(Sensor):out P6-6/5(LCD,4(spk),3:in 
		mov.b	r0h,@0xFFB9:8	; P6DDR

		bset	#0,@0xFFBA:8	; P5-0(TxD):1
		mov.b	#0xFD,r0h	; P5-2(On/Off out):out P5-1(RxD):in P5-0(TxD):out
		mov.b	r0h,@0xFFB8:8	; P5DDR
		
		mov.b	#0x01, r0l
		mov.b	r0l,@0xFFC3:8	; STCR
		mov.b	#0x00, r0l
		mov.b	r0l,@0xFFC7:8	; IER: disable all

; SCI: IR
		mov.b	r0l,@0xFFDA:8	; SCR
		mov.b	@0xFFDC:8,r0h	; SSR
		mov.b	#0x84,r0h
		mov.b	r0h,@0xFFDC:8

; TMR0: speaker
		mov.b	r0l,@0xFFC8:8	; TCR0
		mov.b	@0xFFC9:8,r0h	; TCSR0
		mov.b	r0l,@0xFFC9:8

; TMR1: IR carrier
		mov.b	r0l,@0xFFD0:8	; TCR1
		mov.b	@0xFFD1:8,r0h	; TCSR1
		mov.b	r0l,@0xFFD1:8

; FRT: 1ms
		mov.b	r0l,@0xFF96:8	; TCR
		mov.b	r0l,@0xFF90:8	
		mov.b	@0xFF91:8,r0h	; TCSR
		mov.b	r0l,@0xFF91:8
		mov.b	r0l,@0xFF97:8	; TOCR

; A/D: inputs
		mov.b	r0l,@0xFFE9:8	; ADCR
		mov.b	@0xFFE8:8,r0h	; ADCSR
		mov.b	r0l,@0xFFE8:8

		ldc     #0x00,ccr       ; interrupt enable

; user program
;_loop:
		jsr _entry		
;		jmp _loop


; utility program
_cold_boot:	mov.w	#0xA57F,r1	; reset by WDT
		mov.w	r1,@0xFFA8	; TCSR write
	9:	bra	9b		; wait 256*4096 ticks util reset

_warm_boot:	mov.w	@0,r0		; get reset address from RCX Executable
		jmp	@r0


_wait_1sec:
		mov.w	#1,r2
		mov.w	#999,r0
	0:	mov.w   #888,r1
	1:	sub.w   r2,r1
		bne	1b
		sub.w   r2, r0
		bne 	0b ;(12+12+(12+(6+12)*888+6+12)*999+8)*0.0625
	
		rts

_wait_1msec:
		mov.w	#1,r2
		mov.w	#1,r0
	0:	mov.w   #888,r1
	1:	sub.w   r2,r1
		bne	1b
		sub.w   r2, r0
		bne 	0b ;(12+12+(12+(6+12)*888+6+12)*999+8)*0.0625
	
		rts

; keyword for RCX Executive
                .section .data
                .string "Do you byte, when I knock?"

		.end

