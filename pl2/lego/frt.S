	.section .text
	.p2align 1
	.global _entry

_entry:
	push r6
	mov r7, r6
	
	mov #0xffbb, r0
	mov @r0, r1
	mov #0x01, r2
	or r2, r1
	mov r1, @r0

	;FRTの設定
	;ハンドラのポインタ設定
	mov #0xFDA2, r0
	mov #_OCIA_intr, r1
	mov r1, @r0
	
	;TOCR OEA enable
	mov #0xFF97, r0
	mov @r0, r1l
	and #0x08, r1l
	mov r1l, @r0

	;割り込みタイマー設定
	mov #0xFF95, r0		;high<-0xFF94 low<-0xFF95
	mov #0x1F40, r1		;8000 1ms
	mov r1, @r0
	
	;割り込み許可
	;mov #0xFF90, r0
	;mov @r0, r1l
	;or #0x08, r1l
	;mov r1l, @r0

.loop:

	
	mov #0x5555, r1
	push r1
	;jsr _print_hex
	pop r1
	jmp .loop
	
	mov r6, r7
	pop r6
	rts





	
	.section .text
	.p2align 1
	.global _OCIA_intr
	
	;OCIAハンドラ
_OCIA_intr:
	push r0
	push r1
	push r7
	push r6
	push r5
	push r4
	push r3
	push r2
	
		
	;以下割り込み処理
	mov #count, r0
	mov @r0, r1
	mov #1, r2
	add r2, r1
	mov r1, @r0
	
	mov #0x03E8, r2		;1000
	cmp r1, r2		;1000回に1回:1秒に1回
	bne through
	
	mov #count, r0
	mov #0x0000, r1
	mov r1, @r0		;countリセット
	
	mov #time, r0
	mov @r0, r1
	mov #1, r2
	add r2, r1
	mov r1,@r0

	mov #0xffbb, r0
	mov @r0, r1
	mov #0x04, r2
	or r2, r1
	mov r1, @r0
	;push r1
	;jsr _print_hex
	;pop r1

through:
	
	;割り込み処理ここまで
	pop r2
	pop r3
	pop r4
	pop r5
	pop r6
	pop r7

	;フラグリセット
	mov #0xFF91, r0
	mov @r0, r1l
	and #0xF7:8, r1l
	mov r1l, @r0:8

	pop r1
	pop r0

	rts

	.section .data
	.p2align 1

count:	.word 0
time:	.word 0
