/*
 * H8300用ライブラリ
 * h8300_lib.h
 *
 * date: 2014.12.09
 * author: kataoka
 */


#ifndef H8300_LIB_H
#define H8300_LIB_H


#ifndef H8300_TYPEDEF
#define H8300_TYPEDEF
typedef char int8;
typedef short int16;
typedef unsigned char uint8;
typedef unsigned short uint16;
#endif /* H8300_TYPEDEF */




#ifndef H8300_STRUCTDEF
#define H8300_STRUCTDEF

/*
 * A/D converter
 */
extern struct {
  volatile unsigned short ADDRA;
  volatile unsigned short ADDRB;
  volatile unsigned short ADDRC;
  volatile unsigned short ADDRD;
  volatile unsigned char  ADCSR;
           unsigned char  ADCR;
  unsigned char  reserved[2];
} adc;  


/*
 * General I/O port
 */
extern struct {
  volatile unsigned char P1RCR; /* FFAC */
  volatile unsigned char P2CCR;
  volatile unsigned char P3PCR;
  unsigned char reserved1;
  volatile unsigned char P1DDR; /* FFB0 */
  volatile unsigned char P2DDR;
  volatile unsigned char P1DR; /* FFB2 */
  volatile unsigned char P2DR;
  volatile unsigned char P3DDR; /* FFB4 */
  volatile unsigned char P4DDR;
  volatile unsigned char P3DR; /* FFB6 */
  volatile unsigned char P4DR;
  volatile unsigned char P5DDR; /* FFB8 */
  volatile unsigned char P6DDR;
  volatile unsigned char P5DR;
  volatile unsigned char P6DR;
  unsigned char reserved2;
  unsigned char reserved3;
  volatile unsigned char P7PIN; /* FFBE */
  unsigned char reserved4;
} gio;


/*
 * Timer register 0
 * (music)
 */
extern struct {
  volatile unsigned char TCR; /* FFAC */
  volatile unsigned char TCSR;
  volatile unsigned char TCORA;
  volatile unsigned char TCORB;
  volatile unsigned char TCNT;
} timer0;

/*
 * Timer register 1
 */
extern struct {
  volatile unsigned char TCR; /* FFD0 */
  volatile unsigned char TCSR;
  volatile unsigned char TCORA;
  volatile unsigned char TCORB;
  volatile unsigned char TCNT;
} timer1;


extern struct {
  volatile unsigned char WCSR; /* FFC2 */
  volatile unsigned char STCR;
  volatile unsigned char SYSCR;
  volatile unsigned char MDCR;
  volatile unsigned char ISCR;
  volatile unsigned char IER;
} sysctl;

extern struct {
  volatile unsigned char TIER; /* FF90 */
  volatile unsigned char TCSR;
  volatile unsigned short FRC;
  volatile unsigned short OCRAB; /* OCRA and OCRB share the same address. Access is controled by the OCRS bit in TOCR */
  volatile unsigned char TCR;
  volatile unsigned char TOCR;
  volatile unsigned short ICRA;
  volatile unsigned short ICRB;
  volatile unsigned short ICRC;
  volatile unsigned short ICRD;
} frt;

#endif /* H8300_STRUCTDEF */


#define SET_INT(address,func) *address=func

/*
 * Init Interrupt
 */
void set_interrupt_frt(void (*func)());


/*
 * functions
 */
//unsigned long mul16m(unsigned short src1, unsigned short src2);
//unsigned long sub32m(unsigned long src1, unsigned long src2);



#endif /* H8300_LIB_H */

