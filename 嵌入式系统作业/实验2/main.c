#include<STC15.h>
#include"dataType.h"

u8 num_buf[] = {1 , 2 , 3 , 4};
void u4_num_disp(u8 index, u8 num){
	static u8 code seg_code[]={	0xC0,
															0xF9,
															0xA4,
															0xB0,
															0x99,
															0x92,
															0x82,
															0xF8,
															0x80,
															0x90,
															0x88,
															0x83,
															0xC6,
															0xA1,
															0x86,
															0x8E
														};//数码管段码
	
	// 数字有效位截断
	num = num & 0xF;
	index = (index % 4) + 1;
	// 定位数码管
	P4 = 0x1E;
  P4 = P4 & 1 << index;
	P4 = ~P4;
	// 点亮数码管
	P0 = seg_code[num];
	// 重置定位信号
	P4 = 0xff;
	P0 = 0xff;
}

u8 K1(){
	return (P1 & 1 << 2) == 0;
}
u8 K2(){
	return (P1 & 1 << 3) == 0;
}
u8 K3(){
	return (P1 & 1 << 4) == 0;
}
u8 K4(){
	return (P1 & 1 << 5) == 0;
}

void disp_buf(){
	u4_num_disp(0, num_buf[0]);
	u4_num_disp(1, num_buf[1]);
	u4_num_disp(2, num_buf[2]);
	u4_num_disp(3, num_buf[3]);
}

void main(){
	// IO 初始化
	P0M0 = 0xFF;  P0M1 = 0x00;
	P4M0 = 0xFF;  P4M1 = 0x00;
	P1M0 = 0x00;  P1M1 = 0x00;
	// 初始化数码管
	P4 = 0x0;
	P0 = 0x00;
	

	
	while(1){
		// 检测按键组合类型
		// 设置数字
		if (K1() && K4()){
			num_buf[0] = 4;
			num_buf[1] = 3;
			num_buf[2] = 2;
			num_buf[3] = 1;
		}else if (K2() && K3()){
			num_buf[0] = 3;
			num_buf[1] = 2;
			num_buf[2] = 1;
			num_buf[3] = 0;
		}else if (K3() && K1()) {
			num_buf[0] = 2;
			num_buf[1] = 1;
			num_buf[2] = 0;
			num_buf[3] = 1;		
		} else if (K4() && K2()) {
			num_buf[0] = 1;
			num_buf[1] = 0;
			num_buf[2] = 0;
			num_buf[3] = 0;
		}
		// 显示
		disp_buf();
	}
}