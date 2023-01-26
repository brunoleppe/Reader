#include "Reader_bsp.h"
#include "gpio.h"
#include "spi.h"
#include "system.h"
#include <xc.h>

void PORTS_Initialize()
{
    GPIO_PortDirectionSet(GPIO_PORTB, 0xf<<6, GPIO_OUTPUT);
    GPIO_PortWrite(GPIO_PORTB,0xf<<6,0);

    GPIO_PinDirectionSet(LCD_DC,  GPIO_OUTPUT);
    GPIO_PinDirectionSet(LCD_BLA, GPIO_OUTPUT);
    GPIO_PinDirectionSet(LCD_RST, GPIO_OUTPUT);
    GPIO_PinDirectionSet(LCD_SS,  GPIO_OUTPUT);

    GPIO_PinWrite(LCD_DC, GPIO_LOW);
    GPIO_PinWrite(LCD_BLA,GPIO_LOW);
    GPIO_PinWrite(LCD_RST,GPIO_LOW);
    GPIO_PinWrite(LCD_SS, GPIO_HIGH);

    SYS_Lock();
    RPD3R = 0b0101;
    SYS_Unlock();

}
