;; kadai2.s
;;
;; 
;; 
;;
;; 2014/10/21
;;
;; sort program

	%include "pl2.def"
	%include "rand.def"

	section .text
	global start


ARRAY: equ data
NUM:   equ ndata


LEFT: equ 8		;quick sort
RIGHT: equ 12	;quick sort
PIVOT: equ 4	;quick sort


; main
start:
	;バブルソート
	;call bubble_sort	

	;インサーションソート
	;call insertion_sort

	;セレクションソート
	;call selection_sort

	;クイックソートを呼び出してクイックソート
	call do_quick_sort
	call print_array
	sys_exit 0



;; 配列の表示関数
print_array:
	xor ecx, ecx
	mov esi, ARRAY
.loop0:
	cmp ecx, NUM
	jge .return
	mov eax, [esi]
	call print_eax
	inc ecx
	add esi, 0x4
	jmp .loop0
.return:
	ret

;;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
;; バブルソート(data1~data8において正常な動作を確認済み)
bubble_sort:
	;; mov esi, ARRAY
	mov ebx, NUM - 1 	;syusei
	;; dec ebx
.loop0:
	cmp ebx, 0x0
	je .return
	mov esi, ARRAY
	xor ecx, ecx
.loop1:
	cmp ecx, ebx
	jge .finloop1
	mov eax, [esi]
	mov edx, [esi+4]
	call .cmp_eax_edx
	mov [esi], eax
	mov [esi+4], edx
	;call print_eax
	inc ecx
	add esi, 0x4
	jmp .loop1

.finloop1:
	dec ebx
	jmp .loop0

.return:
	ret

.cmp_eax_edx:
	cmp eax, edx
	jle .cmp_return
	push ebx
	mov ebx, eax
	mov eax, edx
	mov edx, ebx
	pop ebx
.cmp_return:
	ret


;;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;挿入ソート(data1~data8において正常な動作を確認済み)
insertion_sort:
	mov	ebx, 1
	mov	esi, ARRAY
.loop0:
	mov	edx, [esi + 4 * ebx] 	; edx == temp
	cmp	ebx, NUM		; ebx == out
	jge	.return			; out >= NUMで終了 
	mov	ecx, ebx		; ecx == in

.loop1:
	cmp	ecx, 0
	jle	.finloop	; in <= 0で終了
	cmp	edx, [esi + 4 * (ecx - 1)]
	jge	.finloop	; temp >= [0 < in < out]のとき終了
	mov	eax, [esi + 4 * (ecx - 1)]
	mov	[esi + 4 * ecx], eax 
	dec	ecx
	
	jmp	.loop1

.finloop:
	inc	ebx
	mov	[esi + 4 * ecx], edx
	jmp	.loop0
	
.return:
	ret

;;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	
;;選択ソート
selection_sort:
	mov	ebx, 0		;ebx == out
	mov	esi, ARRAY
.loop0:
	mov	eax, NUM
	dec	eax
	cmp	ebx, eax
	jge	.return		;out >  NUM - 1で終了
	mov	edx, ebx	;edx == min
	mov	ecx, ebx	;ecx == in
	add	ecx, 1		;in == out + 1

.loop1:
	cmp	ecx, NUM
	jge	.finloop	;in >= NUMで終了
	mov	eax, [esi + edx * 4]	;eaxに[min]の値を一時的に保存
	mov	edi, [esi + ecx * 4]	;ediに[in]の値を一時的に保存
	call	.cmp_eax_edi
	inc	ecx		;in++
	jmp	.loop1
	
.finloop:
	call	.swap		;[min]と[out]を交換
	inc	ebx		;out++
	jmp	.loop0
	
.return:
	ret

.cmp_eax_edi:
	cmp	eax, edi	;eax == [min], edi == [in]
	jle	.cmp_return		;eax > edi で minにinを代入
	mov	edx, ecx	;min == in
.cmp_return:
	ret

.swap:
	mov	eax, [esi + edx * 4]	;eaxに[min]の値を一時的に保存
	mov	edi, [esi + ebx * 4]	;ediに[out]の値を一時的に保存
	push	eax
	mov	eax, edi	;edi = eax
	pop	edi		;edi = eax
	mov	[esi + edx * 4], eax
	mov	[esi + ebx * 4], edi
	ret
	
;;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;クイックソート(多分全部動く)
do_quick_sort:
	push NUM-1
	push 0
	call quick_sort
	pop ebx
	pop ebx
	ret			;重要
quick_sort:
	push ebp
	mov ebp, esp
	sub esp, 4

	mov eax, [ebp+LEFT]		;基準値の決定
	mov ecx, eax			;配列の真ん中の値を基準値にする
	mov ebx, [ebp+RIGHT]
	add eax, ebx
	shr eax, 1				;array[(left+right)/2]
	shl eax, 2				;のアドレスを算出
	add eax, ARRAY			;(shl eax, 1だけでもよい)
	mov ebx, [eax]
	mov [ebp-PIVOT], ebx

	mov ecx, [ebp+LEFT]		;ecxはソートする配列の一番左の要素番号
	mov edx, [ebp+RIGHT]	;edxはソートする配列の一番右の要素番号

.loop:
	mov ebx, [ebp-PIVOT]	;ebxは基準値

.loopLeft:					;配列の左から, 基準値よりも
	mov eax, ecx			;大きい値を探す
	shl eax, 2				;eaxを4倍
	add eax, ARRAY
	cmp ebx, [eax]
	jle .loopRight
	inc ecx
	jmp .loopLeft

.loopRight:					;配列の右から, 基準値よりも
	mov eax, edx			;小さい値を探す
	shl eax, 2				;eaxを4倍
	add eax, ARRAY
	cmp ebx, [eax]
	jge .judge
	dec edx
	jmp .loopRight

.judge:
	cmp ecx, edx
	jge .ReFuncLeft
	push ecx				;要素番号をswap関数に渡す
	push edx				
	call .swap				;値を交換
	pop edx
	pop ecx
	inc ecx
	dec edx
	jmp .loop

.ReFuncLeft:				;基準値の左側を再帰
	dec ecx
	mov ebx, [ebp+LEFT]
	cmp ecx, ebx
	jle .ReFuncRight
	push ecx
	push ebx
	call quick_sort
	pop ebx
	pop ecx

.ReFuncRight:				;基準値の右側を再帰
	inc edx
	mov ebx, [ebp+RIGHT]
	cmp edx, ebx
	jge .returnq
	push ebx
	push edx
	call quick_sort
	pop edx
	pop ebx

.returnq:
	mov esp, ebp
	pop ebp
	ret



;; 二つの要素番号を引数にとり, その値を交換する
.swap:
	push ebp
	mov ebp, esp
	push eax
	push ebx
	push ecx
	push edx

	mov ecx, [ebp+12]
	mov edx, [ebp+8]

	mov eax, ecx
	shl eax, 2
	add eax, ARRAY
	mov ebx, eax
	mov ecx, [eax]

	mov eax, edx
	shl eax, 2
	add eax, ARRAY
	mov edx, [eax]

	mov [ebx], edx
	mov [eax], ecx

	pop edx
	pop ecx
	pop ebx
	pop eax
	mov esp, ebp
	pop ebp
	ret

;;; ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;; 配列
	section .data
;ランダム
data1: 	dd 16, 12, 15, 9, 11
	dd 7, 5, 6, 1, 0
	dd 13, 8, 4, 17, 14
	dd 19, 3, 10, 18, 2
	dd 0, 10, 19
ndata1: equ ($-data1)/4

;昇順
data2: 	dd 0, 1, 2, 3, 4
	dd 5, 6, 7, 8, 9
	dd 10, 11, 12, 13, 14
	dd 15, 16, 17, 18, 19
ndata2: equ ($-data2)/4

;降順
data3: 	dd 19, 18, 17, 16, 15
	dd 14, 13, 12, 11, 10
	dd 9, 8, 7, 6, 5
	dd 4, 3, 2, 1, 0
ndata3: equ ($-data3)/4

;1要素のみ
data4:	dd 1
ndata4:	equ ($ - data4)/4

;2要素のみ
data5:	dd 1, 5
ndata5:	equ ($ - data5)/4

;0x7fffffffを含む
data6:	dd 0, 3, 5, 0x7fffffff
	dd 9, 4, 8, 12
ndata6:	equ ($ - data6)/4

;要素が全て等しいデータ
data7:	dd 8, 8, 8, 8
	dd 8, 8, 8, 8
	dd 8, 8, 8, 8
ndata7:	equ ($ - data7)/4

;一部重複した要素を含む
data8:	dd 3, 9, 0, 7
	dd 24, 24, 0, 8
	dd 9, 2, 3, 8
ndata8:	equ ($ -data8)/4
	

	
