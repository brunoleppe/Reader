#include <xc.h>
#include "Reader_bsp.h"
#include "gpio.h"
#include "spi.h"
#include "system.h"
#include "evic.h"
#include "pps.h"
#include "timer.h"

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

    SPI_initialize(
        LCD_SPI_CHANNEL,
        SPI_MASTER | SPI_SDI_DISABLE | SPI_MODE_3 ,
        20000000);
    SPI_initialize(QT_SPI_CHANNEL, SPI_MASTER | SPI_MODE_3 | SPI_SAMPLE_END, 1000000);

    TMR_initialize(TMR_CHANNEL_2, TMR_PRESCALER_256, 6);
    TMR_start(TMR_CHANNEL_2);


}

void interrupts_initialize( void )
{
    EVIC_channel_priority(EVIC_CHANNEL_CHANGE_NOTICE_E, EVIC_PRIORITY_4, EVIC_SUB_PRIORITY_2);
    EVIC_channel_set(EVIC_CHANNEL_CHANGE_NOTICE_E);
    EVIC_channel_priority(EVIC_CHANNEL_TIMER_2, EVIC_PRIORITY_1, EVIC_SUB_PRIORITY_1);
    EVIC_channel_set(EVIC_CHANNEL_TIMER_2);
}

void    GPIO_pin_interrupt_callback     (uint32_t pin)
{
    for(int i=0; i<sizeof(pinCallbackObj)/sizeof(GPIO_CALLBACK_OBJECT); i++){
        if((pinCallbackObj[i].pin & pin) && (pinCallbackObj[i].callback != NULL) ){
            pinCallbackObj[i].callback(pinCallbackObj[i].pin);
        }
    }
}

static void qt_change_callback(uint32_t pin)
{
    if(GPIO_pin_read(QT_CHANGE) == GPIO_LOW)
        GPIO_pin_toggle(LED4);
}

void TMR_channel_interrupt_callback(uint32_t channel)
{
    static volatile int counter = 0;
    if(counter++ == 1) {
        GPIO_pin_toggle(LED2);
        counter = 0;
    }
}