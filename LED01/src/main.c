#include <8052.h>
#include "LCD1602.h"

void main()
{
    LCD1602a_init();
    LCD1602a_disp_str(4, 0, "Hello World");

    while (1)
    {
        // for (u8 i = 0; i < 16; i++)
        // {
        //     LCD1602a_write_cmd(0x01);
        //     // LCD1602a_disp_str(x, 1, "<Welcome>");
        //     LCD1602a_disp_str(i, 0,"---->");
        //     // LCD1602a_disp_str(x, 1, "Yang_Shumiao");
        //     delay(50000);
        // }
        // LCD1602a_write_cmd(0x01);
        // LCD1602a_disp_str(3, 1, "Hello");
        // delay(50000);
        // LCD1602a_write_cmd(0x01);

        // delay(50000);
    }
}
