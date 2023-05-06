#include <8052.h>
#include "LCD1602.h"

void main()
{
    LCD_init();
    LCD_disp_char(0x00, 0x00, 0x41);
    while (1)
    {
    }
    
}
