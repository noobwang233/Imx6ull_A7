#include "key.h"
#include "imx6ull.h"
#include <stdint.h>

void keyInit(void)
{
    /* 1、初始化IO复用 */
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03,0);

    /* 2、、配置GPIO1_IO03的IO属性 */
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03,0X10B0);

    /* 3、初始化GPIO,GPIO1_IO03设置为输出*/
    GPIO1->GDIR |= (1 << 3);

    /* 4、设置GPIO1_IO03输出低电平，打开LED0*/
    GPIO1->DR &= ~(1 << 3);
}

uint8_t readKey()
{

}