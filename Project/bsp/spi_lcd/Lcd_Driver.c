//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//  ��������   : 1.8��LCD 4�ӿ���ʾ����(STM32ϵ��)
/******************************************************************************
//������������STM32F103C8
//              GND   ��Դ��
//              VCC   ��5V��3.3v��Դ
//              RES   ��PB0
//              DC    ��PB1
//				BL	  ��PB10
*******************************************************************************/
#include "Lcd_Driver.h"
#include "LCD_Config.h"
#include "bsp_delay.h"
#include "bsp_spi.h"
#include "bsp_gpio.h"


/* st7735s数据集 */
uint8_t lcd_datas[] = {
    0x01,0x2C,0x2D,
    0x01,0x2C,0x2D,
    0x01,0x2C,0x2D,0x01,0x2C,0x2D,
    0x07,
    0xA2,0x02,0x84,
	0xC5,
    0x0A,0x00,
    0x8A,0x2A,
    0x8A,0xEE,
    0x0E,
    0xC0,// 0x36配置：横屏RGB 0xA0 | 竖屏RGB 0xC0 | 横屏BGE 0xA8 | 竖屏RGB 0xC8
    0x0f,0x1a,0x0f,0x18,0x2f,0x28,0x20,0x22,0x1f,0x1b,0x23,0x37,0x00,0x07,0x02,0x10,
    0x0f,0x1b,0x0f,0x17,0x33,0x2c,0x29,0x2e,0x30,0x30,0x39,0x3f,0x00,0x07,0x03,0x10,
    0x00,0x00,0x00,0x7F,
    0x00,0x00,0x00,0x9F,
    0x01,
    0x00,
    0x05,
};
 


void LCD_GPIO_Init(void)
{
	gpio_pin_config_t cs_config, cfg;
	/* 1、IO初始化复用功能 */
	IOMUXC_SetPinMux(IOMUXC_UART3_RX_DATA_GPIO1_IO25,0);
	IOMUXC_SetPinMux(IOMUXC_UART3_TX_DATA_GPIO1_IO24,0);
	IOMUXC_SetPinMux(IOMUXC_GPIO1_IO01_GPIO1_IO01,0);
	IOMUXC_SetPinMux(IOMUXC_UART2_RX_DATA_ECSPI3_SCLK, 0);
	IOMUXC_SetPinMux(IOMUXC_UART2_CTS_B_ECSPI3_MOSI, 0);
	IOMUXC_SetPinMux(IOMUXC_UART2_RTS_B_ECSPI3_MISO, 0);

	IOMUXC_SetPinConfig(IOMUXC_UART2_RX_DATA_ECSPI3_SCLK, 0x10B1);
	IOMUXC_SetPinConfig(IOMUXC_UART2_CTS_B_ECSPI3_MOSI, 0x10B1);
	IOMUXC_SetPinConfig(IOMUXC_UART2_RTS_B_ECSPI3_MISO, 0x10B1);
	
	/* 初始化片选引脚 */
	IOMUXC_SetPinMux(IOMUXC_UART2_TX_DATA_GPIO1_IO20, 0);
	IOMUXC_SetPinConfig(IOMUXC_UART2_TX_DATA_GPIO1_IO20, 0X10B0);


	cs_config.direction = kGPIO_DigitalOutput;
	cs_config.outputLogic = 0;
	gpio_init(GPIO1, 20, &cs_config);

	
	cfg.direction = kGPIO_DigitalOutput;
	cfg.outputLogic = 1;
	cfg.interruptMode = kGPIO_NoIntmode;

	gpio_init(LCD_GPIO_BASE, LCD_RST, &cfg);
	gpio_init(LCD_GPIO_BASE, LCD_RS, &cfg);
	gpio_init(LCD_GPIO_BASE, LCD_LED, &cfg);

}

void LCD_SPI_Init(void)
{
	spi_init(ECSPI3);
}

void  SPI_WriteData(uint8_t Data)
{
	spich0_readwrite_byte(ECSPI3, Data);
}

void  SPI_WriteDatas(const uint8_t *Data, uint16_t len)
{
	uint16_t i =0;
	for (i =0; i < len; i++) {
		spich0_readwrite_byte(ECSPI3, Data[i]);
	}

}


void Lcd_WriteIndex(uint8_t Index)
{
    LCD_RS_CLR;
    SPI_WriteData(Index);
}


void Lcd_WriteData(uint8_t Data)
{
   LCD_RS_SET;
   SPI_WriteData(Data);
}

void LCD_WriteData_16Bit(uint16_t Data)
{
	uint8_t buf[2];
	buf[0] = Data>>8;
	buf[1] = Data;

    LCD_RS_SET;
    SPI_WriteDatas(&buf[0], 2);
}

void LCD_WriteDatas(const uint8_t *Data, uint16_t len)
{
    LCD_RS_SET;
    SPI_WriteDatas(Data, len);
}



void Lcd_WriteReg(uint8_t Index,uint8_t Data)
{
    Lcd_WriteIndex(Index);
    Lcd_WriteData(Data);
}

void Lcd_Reset(void)
{
    LCD_RST_CLR;
    delayms(100);
    LCD_RST_SET;
    delayms(50);
}

//LCD Init For 1.44Inch LCD Panel with ST7735R.
void Lcd_Init(void)
{
	uint8_t i = 0;
	LCD_GPIO_Init();
	LCD_SPI_Init();
	Lcd_Reset(); //Reset before LCD Init.

	//LCD Init For 1.44Inch LCD Panel with ST7735R.
	Lcd_WriteIndex(0x11);//Sleep exit 
	delayms (120);
		
	//ST7735R Frame Rate
	Lcd_WriteIndex(0xB1);

	LCD_WriteDatas(&lcd_datas[i], 3);
	i += 3;

	Lcd_WriteIndex(0xB2); 
	LCD_WriteDatas(&lcd_datas[i], 3);
	i += 3;

	Lcd_WriteIndex(0xB3); 
	LCD_WriteDatas(&lcd_datas[i], 6);
	i += 6;
	
	Lcd_WriteIndex(0xB4); //Column inversion 
	LCD_WriteDatas(&lcd_datas[i], 1);
	i += 1;
	
	//ST7735R Power Sequence
	Lcd_WriteIndex(0xC0); 
	LCD_WriteDatas(&lcd_datas[i], 3);
	i += 3;

	Lcd_WriteIndex(0xC1); 
	LCD_WriteDatas(&lcd_datas[i], 1);
	i += 1;

	Lcd_WriteIndex(0xC2); 
	LCD_WriteDatas(&lcd_datas[i], 2);
	i += 2;

	Lcd_WriteIndex(0xC3); 
	LCD_WriteDatas(&lcd_datas[i], 2);
	i += 2;
	Lcd_WriteIndex(0xC4); 
	LCD_WriteDatas(&lcd_datas[i], 2);
	i += 2;
	
	Lcd_WriteIndex(0xC5); //VCOM 
	LCD_WriteDatas(&lcd_datas[i], 1);
	i += 1;
	
	Lcd_WriteIndex(0x36); //MX, MY, RGB mode 
	LCD_WriteDatas(&lcd_datas[i], 1);
	i += 1;
	
	//ST7735R Gamma Sequence
	Lcd_WriteIndex(0xe0); 
	LCD_WriteDatas(&lcd_datas[i], 16);
	i += 16;

	Lcd_WriteIndex(0xe1); 
	LCD_WriteDatas(&lcd_datas[i], 16);
	i += 16;
	
	Lcd_WriteIndex(0x2a);
	LCD_WriteDatas(&lcd_datas[i], 4);
	i += 4;

	Lcd_WriteIndex(0x2b);
	LCD_WriteDatas(&lcd_datas[i], 4);
	i += 4;
	
	Lcd_WriteIndex(0xF0); //Enable test command  
	LCD_WriteDatas(&lcd_datas[i], 1);
	i += 1;
	Lcd_WriteIndex(0xF6); //Disable ram power save mode 
	LCD_WriteDatas(&lcd_datas[i], 1);
	i += 1;
	
	Lcd_WriteIndex(0x3A); //65k mode 
	LCD_WriteDatas(&lcd_datas[i], 1);
	i += 1;

	
	Lcd_WriteIndex(0x29);//Display on	 
}


void Lcd_SetRegion(uint16_t x_start,uint16_t y_start,uint16_t x_end,uint16_t y_end)
{		
	Lcd_WriteIndex(0x2a);
	Lcd_WriteData(0x00);
	Lcd_WriteData(x_start);//Lcd_WriteData(x_start+2);
	Lcd_WriteData(0x00);
	Lcd_WriteData(x_end+2);

	Lcd_WriteIndex(0x2b);
	Lcd_WriteData(0x00);
	Lcd_WriteData(y_start+0);
	Lcd_WriteData(0x00);
	Lcd_WriteData(y_end+1);
	
	Lcd_WriteIndex(0x2c);

}


void Lcd_SetXY(uint16_t x,uint16_t y)
{
  	Lcd_SetRegion(x,y,x,y);
}


void Gui_DrawPoint(uint16_t x,uint16_t y,uint16_t Data)
{
	Lcd_SetRegion(x,y,x+1,y+1);
	LCD_WriteData_16Bit(Data);

}    



void Lcd_Clear(uint16_t Color)               
{	
   unsigned int i,m;
   Lcd_SetRegion(0,0,X_MAX_PIXEL-1,Y_MAX_PIXEL-1);
   Lcd_WriteIndex(0x2C);
   for(i=0;i<X_MAX_PIXEL;i++)
    for(m=0;m<Y_MAX_PIXEL;m++)
    {	
	  	LCD_WriteData_16Bit(Color);
    }   
}

