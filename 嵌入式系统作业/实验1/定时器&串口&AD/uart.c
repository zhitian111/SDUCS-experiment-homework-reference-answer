#include <stc15.h>		//STC单片机头文件
#include "dataType.h"	//自定义

extern u8 Tx_Buffer[];
extern u8 Tx_Ptr,Tx_Tail,Rx_Ptr;

void uart_handler(void) interrupt 4//串口1中断服务程序
{
	u8 rx_data;

	if(RI) {
		RI = 0;
		rx_data = SBUF;
	}

	if(TI) {
		TI = 0;
		Tx_Ptr ++ ;
		if(Tx_Ptr <= Tx_Tail) {
			SBUF = Tx_Buffer[Tx_Ptr];
		}
	}
}
