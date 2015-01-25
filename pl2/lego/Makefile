#h8300 
# LCD仕様

XAS = h8300-elf-as
XLD = h8300-elf-ld
XCC = h8300-elf-gcc -fpcc-struct-return -mno-quickcall -c
XOBJCOPY = h8300-elf-objcopy -O srec
#CP = h8300-elf-objcopy -O srec

#OBJS = lcd.o lcd_test.o crt0.o
#SEV_SEG_OBJS = hex.o crt0.o lcd.o
#SENSOR_OBJS = sensor.o crt0.o hex.o lcd.o
#IIR_OBJS = sensor.o crt0.o hex.o lcd.o h8300_lib_asm.o iir.o iir_main.o
INTTEST_OBJS = sensor.o crt0.o hex.o lcd.o h8300_lib_asm.o h8300_interrupt_asm.o h8300_interrupt.o

IRQTEST_OBJS = sensor.o hex.o lcd.o h8300_lib_asm.o h8300_interrupt_asm.o h8300_interrupt.o irq_test.o crt0.o

FRT_OBJS = frt.o crt0.o hex.o lcd.o

SETO_OBJS = setofrt.o setocrt0.o hex.o lcd.o h8300_interrupt.o

#.PHONY: beep_test.mot lcd_test.mot clean
#.PHONY: lcd_test.mot clean all
#.PHONY: hex.mot clean
.PHONY: inttest.mot clean
.SUFFIXES: .S .o .c


#all: sensor.mot
all: inttest.mot
#all: irqtest.mot
#all: frt.mot


.S.o: 
	$(XAS) -o $@ $<

.c.o:
	$(XCC) $< -o $@


seto.elf: $(SETO_OBJS)
	$(XLD) $(SETO_OBJS) -o $@ -Map seto.map --script=lego.lds

seto.mot: seto.elf
	$(XOBJCOPY) $< $@



sensor.elf: $(SENSOR_OBJS)
	$(XLD) $(SENSOR_OBJS) -o $@ -Map sensor.map --script=lego.lds

sensor.mot: sensor.elf
	$(XOBJCOPY) $< $@




iir.elf: $(IIR_OBJS)
	$(XLD) $(IIR_OBJS) -o $@ -Map iir.map --script=lego.lds

iir.mot: iir.elf
	$(XOBJCOPY) $< $@




inttest.elf: $(INTTEST_OBJS)
	$(XLD) $(INTTEST_OBJS) -o $@ -Map inttest.map --script=lego.lds

inttest.mot: inttest.elf
	$(XOBJCOPY) $< $@



irqtest.elf: $(IRQTEST_OBJS)
	$(XLD) $(IRQTEST_OBJS) -o $@ -Map irqtest.map --script=lego.lds

irqtest.mot: irqtest.elf
	$(XOBJCOPY) $< $@



frt.elf: $(FRT_OBJS)
	$(XLD) $(FRT_OBJS) -o $@ -Map frt.map --script=lego.lds

frt.mot: frt.elf
	$(XOBJCOPY) $< $@

########## sev_seg ##########
#hex.elf: $(SEV_SEG_OBJS)
#	$(XLD) $(SEV_SEG_OBJS) -o $@ -Ttext 0x8000 -e _start

#hex.mot: hex.elf
#	$(XOBJCOPY) $< $@





#lcd_test.mot: $(OBJS)
#	$(XLD) $(OBJS) -o $*.elf -Ttext 0x8000 -e _start
#	$(CP) $*.elf $@




#beep_test.mot:
#	$(AS) -o beep_test.o beep_test.S
#	$(AS) -o crt0.o crt0.S
#	$(AS) -o data.o data.S
#	$(LD) beep_test.o crt0.o -o beep_test.elf -Ttext 0x8000 -e _start
#	$(CP) beep_test.elf beep_test.mot

clean:
	rm -f *~ *.o *.aux *.log *.mot *.elf
