                .equ    P6DR, 0xFFBB
                .equ    P6DDR, 0xFFB9
                .equ    SDA, 6
                .equ    SCL, 5
                .equ    P6DDV, 0x87

                .section .data
                .p2align 1
                .global _frame_buffer
                .byte   0       ; padding to align _frame_buffer
lcd_init_cmd:   .byte   0x7C    ; sub-address 0, write
                .byte   0xC8    ; Normal, Enable, 1/3bias, 1:4MUX, continue
                .byte   0x80    ; set data pointer to 0, continue
                .byte   0xE0    ; address 0, continue
                .byte   0x70    ; no blink, last command
_frame_buffer:  .byte   0, 0, 0, 0, 0, 0, 0, 0, 0
                .equ    lcd_data_size, . - lcd_init_cmd
                .byte   0       ; padding

                .section .text
                .p2align 1
                .global _lcd_flush
_lcd_flush:     bsr     send_start

                mov     #lcd_data_size,r1l
                mov     #lcd_init_cmd,r2
        0:      mov     @r2+,r0l
                bsr     send_byte
                add     #-1,r1l
                bne     0b

                bsr     send_stop
                rts

; modify r0l
send_start:     mov     @P6DR:8,r0l
                and     #~((1<<SDA)|(1<<SCL)),r0l
                mov     r0l,@P6DR:8
                mov     #(P6DDV|(1<<SDA)),r0l           ; 6
                mov     r0l,@P6DDR:8                    ;       9
                bsr     wait54                          ; 54
                mov     #(P6DDV|(1<<SDA)|(1<<SCL)),r0l  ; 6
                mov     r0l,@P6DDR:8                    ;       9
                rts                                     ; 16

; modify r0l, r0h
send_byte:      mov     #(P6DDV|(1<<SDA)|(1<<SCL)),r0h  ; 6
                orc     #0x01,ccr                       ; 6
                rotxl   r0l                             ; 6
        0:      bist    #SDA,r0h                        ; 6
                mov     r0h,@P6DDR:8                    ; 9
                bclr    #SCL,r0h                        ; 6
                mov     r0h,@P6DDR:8                    ;       9
                bsr     wait54                          ; 54
                bset    #SCL,r0h                        ; 6
                mov     r0h,@P6DDR:8                    ;       9
                bsr     wait30                          ; 30
                shll    r0l                             ; 6
                bne     0b                              ; 12

                bclr    #SDA,r0h                        ; 6
                mov     r0h,@P6DDR:8                    ; 9
                bclr    #SCL,r0h                        ; 6
                mov     r0h,@P6DDR:8                    ;       9
                bsr     wait54                          ; 54
                bset    #SCL,r0h                        ; 6
                mov     r0h,@P6DDR:8                    ;       9
                rts                                     ; 16

; modify r0l
send_stop:      mov     #(P6DDV|(1<<SDA)|(1<<SCL)),r0l  ; 6
                mov     r0l,@P6DDR:8                    ; 9
                bsr     wait42                          ; 42
                bclr    #SCL,r0l                        ; 6
                mov     r0l,@P6DDR:8                    ;       9
                bsr     wait66                          ; 66
                bclr    #SDA,r0l                        ; 6
                mov     r0l,@P6DDR:8                    ;       9
                rts                                     ; 16

wait66:         bra     wait54          ; 12
wait54:         bra     wait42          ; 12
wait42:         bra     wait30          ; 12
wait30:         rts                     ; 16

                .end

