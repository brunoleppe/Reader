#include "initialization.h"
#include "FreeRTOS.h"
#include "task.h"
#include "gpio.h"
#include "spi.h"
#include "Reader_bsp.h"
#include "lcd.h"
#include "bitmap.h"
#include "hal_delay.h"
#include "TestClass.h"
#include <string>
#include <vector>

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


int main(void){
    /*Initialize processor*/
    Initialize();
    /*Create a FreeRTOS Task*/
    xTaskCreate(blink,"blink_task",256,(void*)&pinParamsLed1,1,NULL);
    xTaskCreate(blink,"blink_task",256,(void*)&pinParamsLed2,1,NULL);


    xTaskCreate(lcd_task, "lcd_task", 2048, NULL, 3, NULL);
    xTaskCreate(qt_task, "qt_task", 2048, NULL, 1, NULL);

    while(1){
        /*Start FreeRTOS scheduler*/
        vTaskStartScheduler();
    }

    return EXIT_FAILURE;
}

static void qt_task(void *params)
{
    static SPI_TransferSetup setup;
    setup.usDelay = 160;
    GPIO_pin_write(QT_RST, GPIO_LOW);
    vTaskDelay(10);
    GPIO_pin_write(QT_RST, GPIO_HIGH);
    vTaskDelay(100);

    while(1){
        vTaskDelay(500);
        if(GPIO_pin_read(QT_CHANGE) == GPIO_LOW)
        {
            uint8_t read_key[] = {0xC1, 0x00, 0x00};
            GPIO_pin_write(QT_SS, GPIO_LOW);
            SPI_transfer(QT_SPI_CHANNEL, &setup, read_key, NULL, sizeof(read_key));
            GPIO_pin_write(QT_SS, GPIO_HIGH);
            GPIO_pin_toggle(LED3);
        }

    }
}

static void lcd_task(void *params)
{
    LCD_init(LCD_SPI_CHANNEL, LCD_SS, LCD_BLA, LCD_DC, LCD_RST);

    LCD_draw_bitmap(0,0,bitmap,sizeof(bitmap));
    std::string s = "Hola Mundo";
    LCD_draw_string(0,1,(char*)s.c_str(),LCD_FONT_MEDIUM,LCD_COLOR_BLACK);

    int x=0,y=0;
    while(1){
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
//        LCD_print();
//        vTaskDelay(500);
//        GPIO_pin_toggle(LCD_SS);
//        LCD_print();
//        vTaskDelay(500);
//        GPIO_pin_toggle(LCD_SS);
//        vTaskDelay(portMAX_DELAY);

}

static void blink(void *params)
{
    PinParams *p = (PinParams*)params;
    while(1){
        /*Toggle pin B6 every ~500ms*/
        GPIO_pin_toggle(p->pinMap);
        vTaskDelay(p->delay_ms);
    }
}