#include "initialization.h"
#include "FreeRTOS.h"
#include "task.h"
#include "Reader_bsp.h"
#include "lcd.h"
#include "bitmap.h"
#include "hal_delay.h"
#include <string>

typedef struct{
    GPIO_PinMap pinMap;
    int delay_ms;
}PinParams;

static void blink(void *params);
static void lcd_task(void *params);
static void qt_task(void *params);

static const PinParams pinParamsLed1 = {
        .pinMap = LED1,
        .delay_ms = 500
};
static const PinParams pinParamsLed2 = {
        .pinMap = LED2,
        .delay_ms = 500
};


int main(){
    /*Initialize processor*/
    Initialize();
    /*Create a FreeRTOS Task*/
    xTaskCreate(blink,"blink_task",256,(void*)&pinParamsLed1,1,nullptr);
    xTaskCreate(blink,"blink_task",256,(void*)&pinParamsLed2,1,nullptr);

    xTaskCreate(lcd_task, "lcd_task", 2048, nullptr, 3, nullptr);
    xTaskCreate(qt_task, "qt_task", 2048, nullptr, 1, nullptr);

    while(true){
        /*Start FreeRTOS scheduler*/
        vTaskStartScheduler();
    }

    return EXIT_FAILURE;
}

static void qt_task(void *params)
{
    (void)params;
//    static SPI_TransferSetup setup;
//    setup.usDelay = 160;
    GPIO_pin_write(QT_RST, GPIO_LOW);
    vTaskDelay(10);
    GPIO_pin_write(QT_RST, GPIO_HIGH);
    vTaskDelay(100);

    while(true){
        vTaskDelay(500);
        if(GPIO_pin_read(QT_CHANGE) == GPIO_LOW)
        {
            uint8_t read_key[] = {0xC1, 0x00, 0x00};
            GPIO_pin_write(QT_SS, GPIO_LOW);
            SPI_byte_transfer(QT_SPI_CHANNEL, read_key[0]);
            HAL_delay_us(160);
            SPI_byte_transfer(QT_SPI_CHANNEL, read_key[1]);
            HAL_delay_us(160);
            SPI_byte_transfer(QT_SPI_CHANNEL, read_key[2]);
            HAL_delay_us(160);
            GPIO_pin_write(QT_SS, GPIO_HIGH);
            GPIO_pin_toggle(LED3);
        }

    }
}

static void lcd_task(void *params)
{
    (void)params;
    LCD_init(LCD_SPI_CHANNEL, LCD_SS, LCD_BLA, LCD_DC, LCD_RST);

    LCD_draw_bitmap(0,0,bitmap,sizeof(bitmap));
    std::string s = "Hola Mundo";
    LCD_draw_string(0,1,(char*)s.c_str(),LCD_FONT_MEDIUM,LCD_COLOR_BLACK);

    int x=0,y=0;
    while(true){
        LCD_print();
        vTaskDelay(17);
        GPIO_pin_toggle(LCD_SS);
        LCD_draw_point(x++,y,LCD_COLOR_BLACK);
        if(x>=240){
            x=0;
            if(y++>=128)
                y=0;
        }
    }
}

static void blink(void *params)
{
    auto *p = (PinParams*)params;
    while(true){
        /*Toggle pin B6 every ~500ms*/
        GPIO_pin_toggle(p->pinMap);
        vTaskDelay(p->delay_ms);
    }
}