#include "Reader_bsp.h"
#include "gpio.h"
#include "spi.h"
#include "system.h"
#include "evic.h"
#include <xc.h>

void gpio_initialize( void )
{
    GPIO_port_direction_set(GPIO_PORTB, 0xf << 6, GPIO_OUTPUT);
    GPIO_port_write(GPIO_PORTB, 0xf << 6, 0);

    GPIO_pin_direction_set(LCD_DC, GPIO_OUTPUT);
    GPIO_pin_direction_set(LCD_BLA, GPIO_OUTPUT);
    GPIO_pin_direction_set(LCD_RST, GPIO_OUTPUT);
    GPIO_pin_direction_set(LCD_SS, GPIO_OUTPUT);

    GPIO_pin_direction_set(QT_CHANGE, GPIO_INPUT);
    GPIO_pin_pullup_set(QT_CHANGE, GPIO_PULLUP_ENABLE);
    GPIO_pin_irq_set(QT_CHANGE, GPIO_IRQ_ENABLE);
    GPIO_pin_direction_set(QT_RST, GPIO_OUTPUT);
    GPIO_pin_direction_set(QT_SS, GPIO_OUTPUT);
    GPIO_pin_direction_set(QT_SDO, GPIO_OUTPUT);
    GPIO_pin_direction_set(QT_SDI, GPIO_INPUT);


    GPIO_pin_write(LCD_DC, GPIO_LOW);
    GPIO_pin_write(LCD_BLA, GPIO_LOW);
    GPIO_pin_write(LCD_RST, GPIO_LOW);
    GPIO_pin_write(LCD_SS, GPIO_HIGH);

    GPIO_pin_write(QT_RST, GPIO_HIGH);
    GPIO_pin_write(QT_SS, GPIO_HIGH);

    SYS_Unlock();
    /* LCD SPI */
    GPIO_output_mapping(LCD_SDO, LCD_SDO_AF);
    /* QTOUCH SPI */
    GPIO_output_mapping(QT_SDO, QT_SDO_AF);
    SPI_InputMapping(QT_SPI_CHANNEL, QT_SDI_AF);

    SYS_Lock();

}

void interrupts_initialize( void )
{
    EVIC_channel_state_Set(
            EVIC_CHANNEL_CHANGE_NOTICE_E,
            EVIC_STATE_ENABLED,
            EVIC_PRIORITY_4,
            EVIC_SUB_PRIORITY_2);

}

void qtouch_change_interrupt_handler( void )
{
    uint32_t status;

    status  = CNSTATE;
    status &= CNENE;

    PORTE;
    EVIC_channel_pending_clear(EVIC_CHANNEL_CHANGE_NOTICE_E);
    if(GPIO_pin_read(QT_CHANGE) == GPIO_LOW)
        GPIO_pin_toggle(LED4);

}