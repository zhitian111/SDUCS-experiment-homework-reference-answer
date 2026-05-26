#include <stc15.h>
#include "dataType.h"


								//ADC寄存器
#define ADC_POWER		0x80
#define ADC_SPEED(x)	(x<<5)	//AD转换速度，0-3
#define ADC_START		0x08	//启动AD转换
#define ADC_FLAG		0x10	//转换结束标志

u8	adc_ch;				//当前转换的ADC通道
u16 adcRes[2];			//转换结果

void adc_init()
{
	adc_ch = 0;
	adcRes[0] = 0;
	adcRes[1] = 0;
	
	P1ASF = 0x03;	//P1.0、P1.1作为A/D使用
	ADC_RES = 0;	//转换结果高8位，复位值为0，可不清零
	ADC_RESL = 0;	//转换结果低2位，复位值为0，可不清零
	ADC_CONTR = ADC_POWER|ADC_SPEED(0)|ADC_START|adc_ch;
	EADC = 1;
}

void adc_handle() interrupt 5
{
	ADC_CONTR &= ~ADC_FLAG;			//将ADC_FLAG位清零
	adcRes[adc_ch] = ADC_RES;		//转换结果高8位
	adcRes[adc_ch] <<= 2;
	adcRes[adc_ch] |= ADC_RESL&0x03;//低2位
	adc_ch ++ ;
	if(adc_ch>=2) {
		adc_ch = 0;
	}
	ADC_CONTR = ADC_POWER|ADC_SPEED(1)|ADC_START|adc_ch;
}