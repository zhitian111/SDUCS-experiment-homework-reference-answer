#include <STC15.h>
#include "dataType.h"
#include <string.h>

typedef unsigned char u8;
typedef unsigned int  u16;


u8 num_buf[4] = {0,0,0,0};


#define RECEIVE_BUF_SIZE 32

u8 Receive_Buf[RECEIVE_BUF_SIZE];
u8 Receive_Cursor = 0;
u8 Receive_Times = 0;

bit Frame_Ready = 0;


u8 code seg_code[] =
{
    0xC0, //0
    0xF9, //1
    0xA4, //2
    0xB0, //3
    0x99, //4
    0x92, //5
    0x82, //6
    0xF8, //7
    0x80, //8
    0x90, //9
    0x88, //A
    0x83, //B
    0xC6, //C
    0xA1, //D
    0x86, //E
    0x8E  //F
};


void delay_us(u16 t)
{
    while(t--);
}


void u4_num_disp(u8 index, u8 num)
{
    num &= 0x0F;

    switch(index)
    {
        case 0:
            P0 = seg_code[num];
            P41 = 0;
            delay_us(200);
            P41 = 1;
            break;

        case 1:
            P0 = seg_code[num];
            P42 = 0;
            delay_us(200);
            P42 = 1;
            break;

        case 2:
            P0 = seg_code[num];
            P43 = 0;
            delay_us(200);
            P43 = 1;
            break;

        case 3:
            P0 = seg_code[num];
            P44 = 0;
            delay_us(200);
            P44 = 1;
            break;
    }
}


void disp_buf()
{
    u4_num_disp(0, num_buf[0]);
    u4_num_disp(1, num_buf[1]);
    u4_num_disp(2, num_buf[2]);
    u4_num_disp(3, num_buf[3]);
}


void send_byte(u8 dat)
{
    SBUF = dat;

    while(!TI);

    TI = 0;
}


void send_str(char *str)
{
    while(*str)
    {
        send_byte(*str++);
    }
}


void send_world()
{
    send_str("world\r\n");
}


void uart_init()
{
    SCON = 0x50;

    /*
        Timer1:
        模式2
        8位自动重装
    */
    TMOD &= 0x0F;
    TMOD |= 0x20;

    /*
        STC15:
        Timer1工作在1T模式
    */
    AUXR |= 0x40;

    /*
        11.0592MHz
        19200bps
    */
    TH1 = 0xEE;
    TL1 = 0xEE;

    TR1 = 1;

    RI = 0;
    TI = 0;

    ES = 1;
}


void uart_handler(void) interrupt 4
{
    u8 rx_data;

    if(RI)
    {
        RI = 0;

        rx_data = SBUF;

        Receive_Times++;

        // 接收到回车/换行
        if(rx_data == '\r' || rx_data == '\n')
        {
            Receive_Buf[Receive_Cursor] = '\0';

            Frame_Ready = 1;

            Receive_Cursor = 0;
        }
        else
        {
            if(Receive_Cursor < RECEIVE_BUF_SIZE - 1)
            {
                Receive_Buf[Receive_Cursor++] = rx_data;
            }
        }
    }

    if(TI)
    {
        TI = 0;
    }
}


void main()
{
    /* P0 推挽输出 */
    P0M0 = 0xFF;
    P0M1 = 0x00;

    /* P4 推挽输出 */
    P4M0 |= 0x1E;
    P4M1 &= ~0x1E;

    uart_init();

    EA = 1;

    while(1)
    {
        // 显示接收计数
        num_buf[3] = Receive_Times & 0x0F;

        disp_buf();

        // 一帧接收完成
        if(Frame_Ready)
        {
            // 收到hello
            if(strcmp((char*)Receive_Buf, "hello") == 0)
            {
                send_world();
            }

            Frame_Ready = 0;

            memset(Receive_Buf, 0, sizeof(Receive_Buf));
        }
    }
}