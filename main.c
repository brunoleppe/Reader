#include "initialization.h"
#include "FreeRTOS.h"
#include "task.h"
#include "bsp.h"
#include "lcd.h"
#include "bitmap.h"
#include "hal_delay.h"
#include "keypad.h"

typedef struct{
    GPIO_PinMap pinMap;
    int delay_ms;
}PinParams;

static void blink(void *params);
static void lcd_task(void *params);

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
    xTaskCreate(blink,"blink_task",256,(void*)&pinParamsLed1,1,NULL);
    xTaskCreate(blink,"blink_task",256,(void*)&pinParamsLed2,1,NULL);

    xTaskCreate(lcd_task, "lcd_task", 2048, NULL, 3, NULL);
    xTaskCreate(keypad_task, "qt_task", 2048, NULL, 1, NULL);

    while(true){
        /*Start FreeRTOS scheduler*/
        vTaskStartScheduler();
    }

    return EXIT_FAILURE;
}

static void lcd_task(void *params)
{
    (void)params;
    LCD_init(LCD_SPI_CHANNEL, LCD_DMA_CHANNEL, LCD_SS, LCD_BLA, LCD_DC, LCD_RST);

    LCD_draw_bitmap(0,0,bitmap,sizeof(bitmap));
    char *s = "Hola Mundo";
    LCD_draw_string(0,1,(char*)s,LCD_FONT_MEDIUM,LCD_COLOR_BLACK);
    while(true){
        LCD_print();
        vTaskDelay(17);
//        GPIO_pin_toggle(LCD_SS);
//        LCD_draw_point(x++,y,LCD_COLOR_BLACK);
//        if(x>=240){
//            x=0;
//            if(y++>=128)
//                y=0;
//        }
    }
}

static void blink(void *params)
{
    PinParams *p = (PinParams*)params;
    while(true){
        /*Toggle pin B6 every ~500ms*/
        GPIO_pin_toggle(p->pinMap);
        vTaskDelay(p->delay_ms);
    }
}