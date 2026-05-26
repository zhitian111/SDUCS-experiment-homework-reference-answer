#include <stc15.h>		//STC单片机头文件
#include <intrins.h>	//内含nop指令，用于延时
#include <absacc.h>		//绝对地址访问

#include "dataType.h"	//#include <>，只在系统指定文件夹搜索该头文件，系统头文件一般采用#include <>
						//#include ""，先在当前工程所在文件夹搜索该头文件，若找不到再到系统指定文件夹搜索。用户自定义头文件一般用#include ""

//将鼠标移动到头文件所在行，点下左键，然后鼠标右键，选择"Open document <xxx.h>"可打开该头文件
//头文件打开后，将鼠标箭头移动至该头文件选项卡，点鼠标右键，选择"Open Containing Folder"，可定位头文件所在文件夹
//注释容易出现乱码，点击“Edit”---》“Configuration”---》General Editor Settings：Encoding---》Chinese GB2312 (Simplified)

#define Tx_Array_Size	32
#define Rx_Array_Size	32

u8 Tx_Buffer[Tx_Array_Size];
u8 Tx_Ptr,Tx_Tail,Rx_Ptr;

//float code PI=3.1415926;

u16 xdata array[4]={0x1122,0x3344,0x5566,0x7788};//数组赋初值，存储时数据高字节在低地址
//u16 code array[4]={0x1122,0x3344,0x5566,0x7788};//数组赋初值，存储时数据高字节在低地址
u8 *ptr;

u8 code seg_code[]={0xC0,0xF9,0xA4,0xB0,0x99};//数码管段码
//0，0xC0
//1，0xF9
//2，0xA4
//3，0xB0
//4，0x99
//5，
//6，
//7，
//8，
//9，

extern u8 task_500ms;
extern void timer0_init(void);	//20毫秒@11.0592MHz

extern void adc_init();
extern u16 adcRes[2];			//转换结果


void uart_start()//串口启动发送
{
	Tx_Ptr = 0;
	SBUF = Tx_Buffer[0];
}

	
void uart_init()//串口初始化
{
	Rx_Ptr = 0;			//变量初始化
						//SFR配置，9600bps
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x40;		//定时器时钟1T模式
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器，波特率=溢出率/4
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0xE0;			//设置定时初始值，f=11.0592MHz
	TH1 = 0xFE;			//设置定时初始值
	ET1 = 0;			//禁止定时器1中断
	ES = 1;				//允许串口1中断
	TR1 = 1;			//定时器1开始计时
}


void main()//主程序
{
//	u8 i=0;

	P2M0 = 0xff;
	P2M1 = 0x00; 
	
	    P0M0 = 0xff; P0M1 = 0x00; 
    P4M0 = 0xff; P4M1 = 0x00; 
	
	
	
	P41=1;
	P42=1;
	P43=1;
	P44=0;
	
	P0=seg_code[0];


	timer0_init();	//定时器0初始化
	uart_init();	//串口初始化
	adc_init();		//ADC初始化
	
	EA=1;//开全局中断
	
	while(1)
	{	
		if(task_500ms)
		{
			task_500ms = 0;

			P2=~P2;	//P2口发光二极管状态取反
		
//		Tx_Buffer[0] = 1-2;//怎么理解补码？？？
		
			Tx_Buffer[0] = sizeof(char);
			Tx_Buffer[1] = sizeof(int);
			Tx_Buffer[2] = sizeof(long);
		
			ptr=(u8 *)array;

			Tx_Buffer[3] = *ptr;
			Tx_Buffer[4] = *(ptr+1);
			Tx_Buffer[5] = *(ptr+2);
			Tx_Buffer[6] = *(ptr+3);
			Tx_Buffer[7] = *(ptr+4);
			Tx_Buffer[8] = *(ptr+5);
			Tx_Buffer[9] = *(ptr+6);
			Tx_Buffer[10] = *(ptr+7);
		
			Tx_Buffer[11] = adcRes[0]>>8;
			Tx_Buffer[12] = adcRes[0]&0xff;

			Tx_Buffer[13] = adcRes[1]>>8;
			Tx_Buffer[14] = adcRes[1]&0xff;

		
			Tx_Tail = 14;

			uart_start();
			}				
		}
	}