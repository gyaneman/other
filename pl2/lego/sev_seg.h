/*
 * 7segの表示に関する定義だよん
 */


#ifndef SEV_SEG_H
#define SEV_SEG_H

#define NULL 0x0000


/* 
 * frame_bufferに書き込むときに
 * これ使うと楽になるはず
 */
#define SEG0 0x01
#define SEG1 0x02
#define SEG2 0x04
#define SEG3 0x08
#define SEG4 0x10
#define SEG5 0x20
#define SEG6 0x40
#define SEG7 0x80

/* 
 * display 0~9 and a~f
 */
#define D_0 0x3F//ok
#define D_1 0x06//ok
#define D_2 0x5B//ok
#define D_3 0x4F//ok
#define D_4 0x66//ok
#define D_5 0x6D//ok
#define D_6 0x7D//ok
#define D_7 0x07//ok
#define D_8 0x7F//ok
#define D_9 0x6F//ok

#define D_a 0x77//ok
#define D_b 0x7C//ok
#define D_c 0x39//ok
#define D_d 0x5E//ok
#define D_e 0x79//ok
#define D_f 0x71//ok


/*
  g-zまで追加
*/
#define D_g 0x3D
#define D_h 0x74
#define D_i 0x04
#define D_j 0x1E
#define D_k 0x75 
#define D_l 0x38
#define D_m 0x37
#define D_n 0x54
#define D_o 0x5C
#define D_p 0x73
#define D_q 0x67
#define D_r 0x50
#define D_s 0x6C
#define D_t 0x78
#define D_u 0x1C
#define D_v 0x3E
#define D_w 0x7E
#define D_x 0x76
#define D_y 0x6E
#define D_z 0x1B   



/*
 * charとかshortとかintは使わないようにしようず
 */
#ifndef H8300_TYPEDEF
#define H8300_TYPEDEF
typedef char int8;
typedef short int16;
typedef unsigned char uint8;
typedef unsigned short uint16;
#endif /* H8300_TYPEDEF */



/*
 * lcd.Sより
 */
extern uint8 frame_buffer[9];
void lcd_flush();
void wait_1sec();

/*
 * ひとつの数字を表示する為のデータ構造の定義
 * 2014.12.08修正
 *     ビットフィールドを逆に定義
 */
typedef union _SingleNum{
	uint8 Num;
	struct{
		uint8 unused : 1;	// 128 未使用領域
		uint8 bit6 : 1;		//  64 
		uint8 bit5 : 1;		//  32 
		uint8 bit4 : 1;		//  16 
		uint8 bit3 : 1;		//   8
		uint8 bit2 : 1;		//   4
		uint8 bit1 : 1;		//   2
		uint8 bit0 : 1;		//   1
	}Bit;
}SingleNum;





/*
 * 関数定義
 */
//void entry();
void print_hex(uint16 num);
void print_slide(char* str);
void print_string(char* str);
uint8 print_char(uint8 d, char c);


#endif /* SEV_SEG_H */
