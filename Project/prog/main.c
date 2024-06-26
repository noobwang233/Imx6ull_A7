/**************************************************************
Copyright © zuozhongkai Co., Ltd. 1998-2019. All rights reserved.
文件名	: 	 mian.c
作者	   : 左忠凯
版本	   : V1.0
描述	   : I.MX6U开发板裸机实验16 LCD液晶屏实验
其他	   : 本实验学习如何在I.MX6U上驱动RGB LCD液晶屏幕，I.MX6U有个
 		 ELCDIF接口，通过此接口可以连接一个RGB LCD液晶屏。
论坛 	   : www.openedv.com
在线教育	: www.yuanzige.com
日志	   : 初版V1.0 2019/1/15 左忠凯创建
**************************************************************/
#include "bsp_clk.h"
#include "bsp_delay.h"
#include "bsp_led.h"
#include "bsp_beep.h"
#include "bsp_key.h"
#include "bsp_int.h"
#include "bsp_uart.h"
#include "stdio.h"
#include "bsp_lcd.h"
#include "bsp_lcdapi.h"
#include "oled.h"

/* 背景颜色索引 */
unsigned int backcolor[10] = {
	LCD_BLUE, 		LCD_GREEN, 		LCD_RED, 	LCD_CYAN, 	LCD_YELLOW, 
	LCD_LIGHTBLUE, 	LCD_DARKBLUE, 	LCD_WHITE, 	LCD_BLACK, 	LCD_ORANGE

}; 
	

/*
 * @description	: main函数
 * @param 		: 无
 * @return 		: 无
 */
int main(void)
{
	unsigned char index = 0;
	unsigned char state = OFF;

	int_init(); 				/* 初始化中断(一定要最先调用！) */
	imx6u_clkinit();			/* 初始化系统时钟 			*/
	delay_init();				/* 初始化延时 			*/
	clk_enable();				/* 使能所有的时钟 			*/
	//led_init();					/* 初始化led 			*/
	//beep_init();				/* 初始化beep	 		*/
	uart_init();				/* 初始化串口，波特率115200 */
	lcd_init();					/* 初始化LCD 			*/
	OLED_Init();

	tftlcd_dev.forecolor = LCD_RED;	  
	lcd_show_string(10,10,400,32,32,(char*)"ZERO-IMX6UL ELCD TEST");  /* 显示字符串 */
	lcd_draw_rectangle(10, 52, 790, 220);	/* 绘制矩形框  		*/
	lcd_drawline(10, 52,790, 220);			/* 绘制线条		  	*/
	lcd_drawline(10, 220,790, 52);			/* 绘制线条 		*/
	lcd_draw_Circle(400, 136, 84);			/* 绘制圆形 		*/

	while(1)				
	{	
		index++;
		if(index == 10)
			index = 0;
		lcd_fill(0, 240, 800, 480, backcolor[index]);
		lcd_show_string(600,10,240,32,32,(char*)"INDEX=");  /*显示字符串				  */
		lcd_shownum(700,10, index, 2, 32); 					/* 显示数字，叠加显示	*/

		OLED_NewFrame();
		OLED_PrintASCIIString(10, 10, "Hello world!", &afont16x8, OLED_COLOR_NORMAL);
		OLED_PrintASCIIChar(10, 30, (char)('0' + index), &afont16x8, OLED_COLOR_NORMAL);
		OLED_ShowFrame();
		printf("INDEX= %d\r\n", index);
		state = !state;
		led_switch(LED0,state);
		delayms(1000);	/* 延时一秒	*/
	}
	return 0;
}
