#ifndef LCD1602_H
#define LCD1602_h

#include <8052.h>

// LCD1602
// 接口定义
/**
 * P0------LCD_D0~D7
 * P2_7----LCD_EN
 * P2_6----LCD_RS
 * P2_5----LCD_WR
 *
 */

#define LCD_RS P2^6 // 0xA6;
#define LCD_RW P2^5 // 0xA5;
#define LCD_E P2^7  // 0xA7;

#ifndef LCD_DB
#define LCD_DB P0
#endif

typedef unsigned int u16; // 对系统默认数据类型进行重定义
typedef unsigned char u8;

void LCD_init(void);                    // 初始化函数
void LCD_write_cmd(u8 cmd);             // 写指令函数
void LCD_write_data(u8 dat);            // 写数据函数
void LCD_disp_char(u8 x, u8 y, u8 dat); // x,y 位置显示单个字符
void delay(u16 time);                   // 时延函数

// ****************************

void LCD_init(void)
{
    delay(10);
    // LCD_write_cmd(0x38); // 设置 8 位格式，2 行，5x7
    delay(10);
    LCD_write_cmd(0x3B); // 设置 8 位格式，2 行，5x7、
    delay(10);
    // LCD_write_cmd(0x0c); // 显示开机光标设置
    delay(10);
    // LCD_write_cmd(0x06); // 显示光标移动设置
    delay(10);
    LCD_write_cmd(0x01);
    delay(10);
}

void LCD_write_cmd(u8 cmd)
{
    LCD_RS = 0;   // 指令低电平
    LCD_RW = 0;   // 写入
    LCD_E = 0;    // 使能 = 0
    LCD_DB = cmd; // 准备数据
    delay(1);
    LCD_E = 1; // 使能脚E先上升沿写入
    delay(10);
    LCD_E = 0; // 使能脚E后负跳变完成写入
    delay(1);
}

void LCD_write_data(u8 dat)
{

    LCD_RS = 1;   // 数据高电平
    LCD_RW = 0;   // 写入
    LCD_E = 0;    // 使能 = 0
    LCD_DB = dat; // 准备数据
    delay(1);
    LCD_E = 1; // 使能脚E先上升沿写入
    delay(10);
    LCD_E = 0; // 使能脚E后负跳变完成写入
    delay(1);
}

void LCD_disp_char(u8 x, u8 y, u8 dat)
{
    unsigned char address;
    if (y == 1)
    {
        address = 0x80 + x;
    }
    else
    {
        address = 0xc0 + x;
    }
    LCD_write_cmd(address);
    delay(10);
    LCD_write_data(dat);
}

void delay(u16 time)
{
    while (time--)
    {
    };
}

#endif