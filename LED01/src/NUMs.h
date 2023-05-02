#ifndef NUMS_H
#define NUMS_H

#include "8052.h"

// 数码管                     0    1      2     3     4      5      6   7     8     9
unsigned char NixieTube[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

// 388译码器
// P2_4 = 0; // 3
// P2_3 = 0; // 2
// P2_2 = 0; // 1

/*  6  ->   110
 *  6 / 2 = 3 yu 0   ->  余数 = 0 ->  第一位 为 0
 *  3 / 2 = 1 yu 1   ->  余数 = 1 ->  第二位 为 1
 *  1 / 2 = 0 yu 1  小于2 余数 = 1 -> 第三位 为 1
 */

// unsigned int *to_binary(unsigned int input_num)
// {
//     bool _to138[3] = 0;
//     unsigned int r, i = 0;
//     while (input_num > 1)
//     {
//         // 取余数
//         r = input_num % 2;
//         _to138[i] = r;
//         if (input_num >= 2)
//         {
//             do
//             {
//                 i++;
//                 input_num = input_num / 2;
//                 _to138[i] = input_num % 2;
//             } while (i > 2);
//         }
//     }
//     return _to138;
// }

void Nixie(unsigned char location, unsigned char number)
{
    switch (location)
    {
    case 8:
        P2_4 = 0;
        P2_3 = 0;
        P2_2 = 0;
        break;
    case 7:
        P2_4 = 0;
        P2_3 = 0;
        P2_2 = 1;
        break;
    case 6:
        P2_4 = 0;
        P2_3 = 1;
        P2_2 = 0;
        break;
    case 5:
        P2_4 = 0;
        P2_3 = 1;
        P2_2 = 1;
        break;
    case 4:
        P2_4 = 1;
        P2_3 = 0;
        P2_2 = 0;
        break;
    case 3:
        P2_4 = 1;
        P2_3 = 0;
        P2_2 = 1;
        break;
    case 2:
        P2_4 = 1;
        P2_3 = 1;
        P2_2 = 0;
        break;
    case 1:
        P2_4 = 1;
        P2_3 = 1;
        P2_2 = 1;
        break;

    default:
        P2_4 = 1;
        P2_3 = 1;
        P2_2 = 1;
        break;
    }

    P0 = NixieTube[number];
    delay_10us(10);
    P0 = 0x00;
}

#endif
