#ifndef LED_H
#define LED_H

#include <8052.h>

typedef unsigned int u16; // 对系统默认数据类型进行重定义
typedef unsigned char u8;

#ifndef K_
#define K1 P3_1
#define K2 P3_0
#define K3 P3_2
#define K4 P3_3
#endif

#ifndef LED
#define LED P2
#endif

/**
 * @brief 时延函数 ten_us=1时，大约延时10us
 * @param ten_us
 */
int delay_10us(u16 ten_us)
{
    while (ten_us--)
        ;
    return 0;
}

void LED_options(u16 times)
{
    // LED = 0xFF; // 1111 1110
    // do
    // {
    // 	LED=0xFE;	//点亮
    // 	delay_10us(50000); //大约延时450ms
    // 	// LED=0xFF;	//熄灭
    // 	// delay_10us(50000);
    //     LED-=0x01;
    //     delay_10us(50000);
    //     if(LED == 0x00)
    //     {
    //         LED = 0xFE;
    //         delay_10us(50000);
    //     }
    // } while (1);

    while (!K1)
    {
        // LED = 0xFE; // 0000 0001
        // 0000 00011
        for (u8 i = 0; i < 8; i++)
        {
            LED = 0xFE << i;
            delay_10us(times);
        }
        // LED = 0xFE;
        // delay_10us(times);
        for (u8 i = 0; i < 8; i++)
        {

            LED = ~(0xFE << i); // 0000 0001
            delay_10us(times);
            // 1 3 7 15 31
        }
    }

    while (!K2)
    {
        // LED = 0xFE; // 0000 0001
        // 0000 00011
        for (u8 i = 0; i < 8; i++)
        {
            LED = 0xFE << i;
            delay_10us(times);
        }
    }
    while (!K3)
    {
        // LED = 0xFE; // 0000 0001
        // 0000 00011
        delay_10us(times);
        for (u8 i = 8; i > 0; i--)
        {
            LED = 0xFE << i;
            delay_10us(times);
        }
    }
}


#endif