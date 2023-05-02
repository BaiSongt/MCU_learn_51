#ifndef KEY_H
#define KEY_H

#include <8052.h>
#include "LED.h"


void KEY_to_LED(void)
{

 u8 LED_num = 0;
    while (1)
    {
        // // 按键抖动消除
        // if( K1 == 0 )
        // {
        //     delay_10us(20);
        //     while (K1 == 0); // 检测松手
        //     delay_10us(20);
        //     P2_0=~(P2_0);
        //     // P2_0 = 0;
        // }

        if (K1 == 0)
        {
            delay_10us(20);
            while (K1 == 0)
                ;
            delay_10us(20);

            LED_num++;
            if (LED_num >= 8)
                LED_num = 0;

            // 0000 0001 << 1 => 0000 0010
            // 高电平 取反
            // 1111 1101
            P2 = ~(0x01 << LED_num);
        }

        if (K2 == 0)
        {
            delay_10us(20);
            while (K2 == 0)
                ;
            delay_10us(20);

            if (LED_num <= 0)
                LED_num = 8;
            LED_num--;
            P2 = ~(0x01 << LED_num);
        }
    }
}

#endif