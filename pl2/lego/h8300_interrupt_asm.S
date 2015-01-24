/*
 * h8300 interrupt
 * 
 */

	.section .text
	.p2align 1
	.global _set_vector_table
	.global _entry_ocia
	.global _entry_irq0

.if 0
.equ INT_OCIA	0xfda2
.equ INT_OCIB	0xfda4
.equ TIER		0xff90
.equ TCSR		0xff91
.equ FRC		0xff92
.equ OCRAB		0xff94
.equ TCR		0xff96
.equ TOCR		0xff97


;; void init_frt_int(uint8 tier, uint8 ocra);

_init_frt_intasm:
	push r6
	mov r7, r6

	;割り込みハンドラ
	mov #INT_OCIA, r0
	mov #_entry_ocia, r1
	mov r1, @r0

	;output compare register Aの設定
	mov @(6, r6), r0
	mov @TOCR, r1l
	mov #0xef, r1h
	or r1h, r1l
	mov r1l, @TOCR
	mov r0, @OCRAB

	;割り込み許可
	;mov #0x08, r0
	mov @(4, r6), r0
	mov @TIER, r1
	or  r0, r1
	mov r1, @TIER

	mov r6, r7
	pop r6
	rts
.endif


; void set_vector_table(uint16 *vectorAddress, void *funcAddress);
_set_vector_table:
	push r6
	mov r7, r6
	push r0
	push r1

	mov @(4, r6), r0
	mov @(6, r6), r1
	mov r1, @r0

	pop r1
	pop r0
	mov r6, r7
	pop r6
	rts


_entry_ocia:

	push r0
	push r1
	push r2
	push r3
	push r4
	push r5
	push r6
	push r7

	;mov @(22, r7), r0
	;push r0
	;jsr _print_hex
	;pop r0
	ldc #0, ccr

	jsr _OCIA_HANDLE
	mov #0xFF91, r0
	mov @r0, r2l
	and #0xf7:8, r2l
	mov r2l, @r0:8

	;mov #0xFF90, r0
	;mov @r0, r2l
	;and #0xf7:8, r2l
	;mov r2l, @r0:8

	;mov #0x10, r0
	;push r0
	;jsr _print_hex
	;pop r0

	pop r7
	pop r6
	pop r5
	pop r4
	pop r3
	pop r2
	pop r1
	pop r0

	rts



.if 0
_entry_irq0:
	push r0
	push r1
	push r2
	push r3
	push r4
	push r5
	push r6
	push r7

	jsr _IRQ0_HANDLE

	pop r7
	pop r6
	pop r5
	pop r4
	pop r3
	pop r2
	pop r1
	pop r0

	rts
.endif
.end
