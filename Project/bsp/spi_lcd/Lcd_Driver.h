#ifndef  __LCD_DRVIER_H
#define  __LCD_DRVIER_H

#include "imx6ul.h"
#include "bsp_gpio.h"

#define RED  	0xf800
#define GREEN	0x07e0
#define BLUE 	0x001f
#define WHITE	0xffff
#define BLACK	0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D
#define GRAY1   0x8410
#define GRAY2   0x4208


/**************接线******************/
/* UART2_RXD    SPI3_SCLk   PIN18 ------ SCL          */
/* UART2_CTS    SPI3_MOSI   PIN20 ------ SDA          */
/* UART2_TXD    SPI3_SS0    PIN17 ------ CS           */
/* UART3_RXD    GPIO1_IO25  PIN35 ------ BLK          */
/* UART3_TXD    GPIO1_IO24  PIN33  ------ DC          */
/* GPIO_1                   PIN7  ------ RST          */


#define LCD_GPIO_BASE    GPIO1

#define	LCD_RST          1
#define	LCD_RS           24
#define	LCD_LED          25

//#define LCD_CS_SET(x) LCD_CTRL->ODR=(LCD_CTRL->ODR&~LCD_CS)|(x ? LCD_CS:0)

#define	LCD_LED_SET  	gpio_pinwrite(LCD_GPIO_BASE, LCD_LED, 1)
#define	LCD_RS_SET  	gpio_pinwrite(LCD_GPIO_BASE, LCD_RS, 1)
#define	LCD_RST_SET  	gpio_pinwrite(LCD_GPIO_BASE, LCD_RST, 1)

#define	LCD_LED_CLR  	gpio_pinwrite(LCD_GPIO_BASE, LCD_LED, 0)
#define	LCD_RST_CLR  	gpio_pinwrite(LCD_GPIO_BASE, LCD_RS, 0)
#define	LCD_RS_CLR  	gpio_pinwrite(LCD_GPIO_BASE, LCD_RST, 0)

void LCD_GPIO_Init(void);
void Lcd_WriteIndex(uint8_t Index);
void Lcd_WriteData(uint8_t Data);
void Lcd_WriteReg(uint8_t Index,uint8_t Data);
uint16_t Lcd_ReadReg(uint8_t LCD_Reg);
void Lcd_Reset(void);
void Lcd_Init(void);
void Lcd_Clear(uint16_t Color);
void Lcd_SetXY(uint16_t x,uint16_t y);
void Gui_DrawPoint(uint16_t x,uint16_t y,uint16_t Data);
unsigned int Lcd_ReadPoint(uint16_t x,uint16_t y);
void Lcd_SetRegion(uint16_t x_start,uint16_t y_start,uint16_t x_end,uint16_t y_end);
void LCD_WriteData_16Bit(uint16_t Data);

#endif
