#include "Reader_bsp.h"
#include "gpio.h"
#include "spi.h"
#include "system.h"
#include "evic.h"
#include "pps.h"
#include <xc.h>

static void qt_change_callback(uint32_t pin);

GPIO_CALLBACK_OBJECT pinCallbackObj[] = {
        {.pin = QT_CHANGE, .callback = qt_change_callback}
};

void gpio_initialize( void )
{
    GPIO_pin_initialize(LED1, GPIO_OUTPUT);
    GPIO_pin_initialize(LED2, GPIO_OUTPUT);
    GPIO_pin_initialize(LED3, GPIO_OUTPUT);
    GPIO_pin_initialize(LED4, GPIO_OUTPUT);

    GPIO_pin_write(LED1, 1);
    GPIO_pin_write(LED2, 1);
    GPIO_pin_write(LED3, 1);
    GPIO_pin_write(LED4, 1);

    GPIO_pin_initialize(LCD_DC, GPIO_OUTPUT);
    GPIO_pin_initialize(LCD_BLA, GPIO_OUTPUT);
    GPIO_pin_initialize(LCD_RST, GPIO_OUTPUT);
    GPIO_pin_initialize(LCD_SS, GPIO_OUTPUT);

    GPIO_pin_initialize(QT_CHANGE, GPIO_INPUT_PULLUP | GPIO_IRQ);
    GPIO_pin_initialize(QT_RST, GPIO_OUTPUT);
    GPIO_pin_initialize(QT_SS, GPIO_OUTPUT);
    GPIO_pin_initialize(QT_SDO, GPIO_OUTPUT);
    GPIO_pin_initialize(QT_SDI, GPIO_INPUT);

    GPIO_pin_write(LCD_DC, GPIO_LOW);
    GPIO_pin_write(LCD_BLA, GPIO_LOW);
    GPIO_pin_write(LCD_RST, GPIO_LOW);
    GPIO_pin_write(LCD_SS, GPIO_HIGH);

    GPIO_pin_write(QT_RST, GPIO_HIGH);
    GPIO_pin_write(QT_SS, GPIO_HIGH);

    SYS_Unlock();
    /* LCD SPI */
    PPS_pin_mapping(LCD_SPI_OUTPUT_REG, LCD_SPI_OUTPUT_MAP);
    /* QTOUCH SPI */
    PPS_pin_mapping(QT_SPI_OUTPUT_REG, QT_SPI_OUTPUT_MAP);
    PPS_pin_mapping(QT_SPI_INPUT_REG, QT_SPI_INPUT_MAP);


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

void    GPIO_pin_interrupt_callback     (uint32_t pin)
{
    for(int i=0; i<sizeof(pinCallbackObj)/sizeof(GPIO_CALLBACK_OBJECT); i++){
        if(((1 << pinCallbackObj[i].pin) & pin) && (pinCallbackObj[i].callback != NULL) ){
            pinCallbackObj[i].callback(pinCallbackObj[i].pin);
        }
    }
}

static void qt_change_callback(uint32_t pin)
{
    uint32_t array[pin];
    array[pin-1] = LED4;
    if(GPIO_pin_read(QT_CHANGE) == GPIO_LOW)
        GPIO_pin_toggle(array[pin-1]);
}