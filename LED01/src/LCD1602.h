#ifndef LCD1602_H
#define LCD1602_h

#include <8052.h>
#include <string.h>

// LCD1602
// 接口定义
/**
 * P0------LCD1602a_D0~D7
 * P2_7----LCD1602a_EN
 * P2_6----LCD1602a_RS
 * P2_5----LCD1602a_WR
 *
 */

#define LCD1602a_RS P2_6
#define LCD1602a_RW P2_5
#define LCD1602a_E P2_7

#ifndef LCD1602a_DB
#define LCD1602a_DB P0
#endif

typedef unsigned int u16; // 对系统默认数据类型进行重定义
typedef unsigned char u8;

void LCD1602a_init(void);                    // 初始化函数
void LCD1602a_write_cmd(u8 cmd);             // 写指令函数
void LCD1602a_write_data(u8 dat);            // 写数据函数
void LCD1602a_disp_str(u8 x, u8 y, u8 *str); // x,y 位置显示字符
void CheckBusy(void);                        // 检查忙
void delay(u16 time);                        // 时延函数

// ****************************

void LCD1602a_init(void)
{
    delay(100);
    LCD1602a_write_cmd(0x38); // 设置 8 位格式，2 行
    LCD1602a_write_cmd(0x0c); // 显示开机光标设置
    LCD1602a_write_cmd(0x06); // 显示光标移动设置
    LCD1602a_write_cmd(0x01);
    delay(10);
}

void LCD1602a_write_cmd(u8 cmd)
{
    LCD1602a_RS = 0;   // 指令低电平
    LCD1602a_RW = 0;   // 写入
    LCD1602a_E = 0;    // 使能 = 0
    LCD1602a_DB = cmd; // 准备数据
    delay(1);
    LCD1602a_E = 1; // 使能脚E先上升沿写入
    delay(10);
    LCD1602a_E = 0; // 使能脚E后负跳变完成写入
    delay(1);
}

void LCD1602a_write_data(u8 dat)
{

    LCD1602a_RS = 1;   // 数据高电平
    LCD1602a_RW = 0;   // 写入
    LCD1602a_E = 0;    // 使能 = 0
    LCD1602a_DB = dat; // 准备数据
    delay(5);
    LCD1602a_E = 1; // 使能脚E先上升沿写入
    delay(100);
    LCD1602a_E = 0; // 使能脚E后负跳变完成写入
    delay(5);
}

void LCD1602a_disp_str(u8 x, u8 y, u8 *str)
{
    u8 i = 0; // 地址增加

    if (y > 1 || x > 16)
        return;

    if (y == 0) // y = 0 , 在第一行显示
    {
        while (*str != '\0') // 字符串是以'\0'结尾，只要前面有内容就显示
        {
            if (i < 16 - x && i >= 0) // 如果字符长度超过第一行显示范围，则在第一行继续显示
            {
                LCD1602a_write_cmd(0x80 + x + i); // 第一行显示地址设置
            }
            else
            {
                LCD1602a_write_cmd(0x80 + i + x - 16); // 第1行显示地址设置 折回
            }
            LCD1602a_write_data(*str); // 显示内容
            str++;                     // 指针递增
            i++;
        }
    }
    else if(y == 1)// 第2行显示 y = 1
    {
        i = 0;
        while (*str != '\0')
        {
            if (i < 16 - x && i >= 0) // 如果字符长度超过第二行显示范围，则在第二行继续显示
            {
                // 第二行开始位置 address + 字符串起始位置 x + 当前字符位置 i = 最终字符显示位置
                LCD1602a_write_cmd(0xc0 + i);
            }
            else
            {
                LCD1602a_write_cmd(0xc0 + i + x - 16);
            }
            LCD1602a_write_data(*str);
            str++;
            i++;
        }
    }
    delay(1);
}

void CheckBusy(void)
{
    u8 temp;
    LCD1602a_RS = 0; // 命令
    LCD1602a_RW = 1; // 读
    LCD1602a_E = 0;
    while (1)
    {
        LCD1602a_DB = 0xFF; // 端口为输入
        LCD1602a_E = 1;       // 高脉冲
        temp = LCD1602a_DB;
        LCD1602a_E = 0;
        if ((temp & 0x80) == 0) // 检查BF位是否为0
            break;
    }
}

void delay(u16 time)
{
    while (time--)
    {
    };
}

#endif