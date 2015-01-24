#include "sev_seg.h"


/* 1桁目の表示関数 */
void print_1digit(SingleNum c){
        // clear
	frame_buffer[0] &= ~0xB0;
	frame_buffer[4] &= ~0x0A;
	frame_buffer[5] &= ~0xA0;

	if(c.Bit.bit0){
		frame_buffer[0] |= SEG4;
	}
	if(c.Bit.bit1){
		frame_buffer[4] |= SEG1;
	}
	if(c.Bit.bit2){
		frame_buffer[4] |= SEG3;
	}
	if(c.Bit.bit3){
		frame_buffer[0] |= SEG7;
	}
	if(c.Bit.bit4){
		frame_buffer[5] |= SEG7;
	}
	if(c.Bit.bit5){
		frame_buffer[5] |= SEG5;
	}
	if(c.Bit.bit6){
		frame_buffer[0] |= SEG5;
	}
}

/* 2桁目の表示関数 */
void print_2digit(SingleNum c){
  // clear
  frame_buffer[1] &= ~0x0B;
  frame_buffer[5] &= ~0x0A;
  frame_buffer[6] &= ~0xA0;

    if(c.Bit.bit0){
		frame_buffer[1] |= SEG0;
	}
	if(c.Bit.bit1){
		frame_buffer[5] |= SEG1;
	}
	if(c.Bit.bit2){
		frame_buffer[5] |= SEG3;
	}
	if(c.Bit.bit3){
		frame_buffer[1] |= SEG3;
	}
	if(c.Bit.bit4){
		frame_buffer[6] |= SEG7;
	}
	if(c.Bit.bit5){
		frame_buffer[6] |= SEG5;
	}
	if(c.Bit.bit6){
		frame_buffer[1] |= SEG1;
	}
}

/* 3桁目の表示関数 */
void print_3digit(SingleNum c){
          // clear
	frame_buffer[3] &= ~0x0B;
	frame_buffer[8] &= ~0xAA;
	

	if(c.Bit.bit0){
		frame_buffer[3] |= SEG0;
	}
	if(c.Bit.bit1){
		frame_buffer[8] |= SEG1;
	}
	if(c.Bit.bit2){
		frame_buffer[8] |= SEG3;
	}
	if(c.Bit.bit3){
		frame_buffer[3] |= SEG3;
	}
	if(c.Bit.bit4){
		frame_buffer[8] |= SEG7;
	}
	if(c.Bit.bit5){
		frame_buffer[8] |= SEG5;
	}
	if(c.Bit.bit6){
		frame_buffer[3] |= SEG1;
	}

}

/* 4桁目の表示関数 */
void print_4digit(SingleNum c){
           // clear
	frame_buffer[3] &= ~0xB0;
	frame_buffer[7] &= ~0xAA;
	

	if(c.Bit.bit0){
		frame_buffer[3] |= SEG4;
	}
	if(c.Bit.bit1){
		frame_buffer[7] |= SEG1;
	}
	if(c.Bit.bit2){
		frame_buffer[7] |= SEG3;
	}
	if(c.Bit.bit3){
		frame_buffer[3] |= SEG7;
	}
	if(c.Bit.bit4){
		frame_buffer[7] |= SEG7;
	}
	if(c.Bit.bit5){
		frame_buffer[7] |= SEG5;
	}
	if(c.Bit.bit6){
		frame_buffer[3] |= SEG5;
	}

}


/*
 * d桁目にnumを表示
 * dの範囲は0~3の4つ
 */
uint8 print_SingleNum(uint8 d, SingleNum c){
	switch(d){
		case 0:
			print_1digit(c);
			break;
		case 1:
			print_2digit(c);
			break;
		case 2:
			print_3digit(c);
			break;
		case 3:
			print_4digit(c);
			break;
		default:
			return 1;	// error
	}
	lcd_flush();
	return 0;
}

SingleNum hex2SingleNum(uint16 hexnum){
	SingleNum ret;
	hexnum &= 0x000f;
	switch(hexnum){
	  
	        case 0x0:
	                ret.Num = D_0;
	                break;
		case 0x1:
			ret.Num = D_1;
			break;
		case 0x2:
			ret.Num = D_2;
			break;
	        case 0x3:
			ret.Num = D_3;
			break;
	        case 0x4:
			ret.Num = D_4;
			break;
	        case 0x5:
			ret.Num = D_5;
			break;
	        case 0x6:
			ret.Num = D_6;
			break;
	        case 0x7:
			ret.Num = D_7;
			break;
	        case 0x8:
			ret.Num = D_8;
			break;
		case 0x9:
			ret.Num = D_9;
			break;
		case 0xa:
			ret.Num = D_a;
			break;
	        case 0xb:
			ret.Num = D_b;
			break;
	        case 0xc:
			ret.Num = D_c;
			break;
	        case 0xd:
			ret.Num = D_d;
			break;
		case 0xe:
			ret.Num = D_e;
			break;
		case 0xf:
			ret.Num = D_f;
			break;
		default:
			break;
	}
	return ret;
}

/*
 * numをlegoの7segに表示
 */
void print_hex(uint16 num){
	uint16 tmp;
	SingleNum c;

	tmp = num;
	tmp &= 0x000f;
	c = hex2SingleNum(tmp);
	print_SingleNum(0, c);

	tmp = num;
	tmp &= 0x00f0;
	tmp = tmp >> 4;
	c = hex2SingleNum(tmp);
	print_SingleNum(1, c);

	tmp = num;
	tmp &= 0x0f00;
	tmp = tmp >> 8;
	c = hex2SingleNum(tmp);
	print_SingleNum(2, c);

	tmp = num;
	tmp &= 0xf000;
	tmp = tmp >> 12;
	c = hex2SingleNum(tmp);
	print_SingleNum(3, c);
}


void entry(){
	SingleNum c;

	c.Num = D_b;


	/*
	print_SingleNum(0, c);
	c.Num = D_d;
	print_SingleNum(1, c);
	c.Num = D_e;
	print_SingleNum(2, c);
	c.Num = D_f;
	print_SingleNum(3, c);
	*/
	print_hex(3210);
	while(1);
}
