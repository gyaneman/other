;H8300用ライブラリ
;h8300_lib_asm.S
;date: 2014.12.09
;author: kataoka
;
;
;ここで定義した関数とかはh8300_lib.hをインクルードすることで
;使うことができるお



	.section .text
	.p2align 1
;;	.global _div
	.global _mul16m, _sub32m


;; unsigned long mul16m(unsigned short src1, unsigned short src2);
_mul16m:
	push r6
	mov r7, r6
	push r4
	mov @(4, r6), r4
	mov @(6, r6), r1
	mov r1h, r2l
	mov r1l, r3l
	mov r1h, r0l
	mulxu r4l, r1
	mulxu r4l, r2
	mulxu r4h, r3
	mulxu r4h, r0
	add r2l, r1h
	addx r2h, r0l
	addx #0, r0h
	add r3l, r1h
	addx r3h, r0l
	addx #0, r0h
	pop r4
	pop r6
	rts

;; unsigned long sub32m(unsigned long src1, unsigned long src2);
_sub32m:
	push r6
	mov r7, r6
	mov @(6, r6), r1
	mov @(10, r6), r0
	sub r0, r1
	mov @(4, r6), r0
	mov @(8, r6), r2
	subx r2l, r0l
	subx r2h, r0h
	pop r6
	rts



;割り算命令
;uint16 div(uint16 dividend, uint16 divisor);
;返り値:r0 商
;一応、r1に剰余
.if 0
_div:
	push r6
	mov r7, r6

	push r4
	xor r0, r0
	xor r2, r2

	mov @(4, r6), r4	;; dividend
	mov @(6, r6), r1	;; divisor

shl:
	cmp r1, r4
	bhi shr
	shll r1
	inc r0l
	jmp shl

shr:
	cmp 0, r0l
	beq return
	dec r0l
	shlr r1
	shll r2
	cmp r1, r4
	bcs shr
	sub r1, r4
	inc r2
	jmp shr

;return:
	;;返り値の設定

	mov r6, r7
	pop r6

	rts
.endif
