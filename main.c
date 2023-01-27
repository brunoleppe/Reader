#include "initialization.h"
#include "FreeRTOS.h"
#include "task.h"
#include "gpio.h"
#include "spi.h"
#include "Reader_bsp.h"
#include "lcd.h"

typedef struct{
    GPIO_PIN pin_number;
    int delay_ms;
}PinParams;

void blink(void *params);
void lcd_init(void *params);

int main(void){

    /*Initialize processor*/
    Initialize();
    /*Create a FreeRTOS Task*/
    xTaskCreate(blink,"blink_task",256,&(PinParams){.pin_number = GPIO_PORTB_6, .delay_ms = 500},1,NULL);
    xTaskCreate(blink,"blink_task",256,&(PinParams){.pin_number = GPIO_PORTB_7, .delay_ms = 400},1,NULL);
    xTaskCreate(blink,"blink_task",256,&(PinParams){.pin_number = GPIO_PORTB_8, .delay_ms = 300},1,NULL);
    xTaskCreate(blink,"blink_task",256,&(PinParams){.pin_number = GPIO_PORTB_9, .delay_ms = 600},1,NULL);

    xTaskCreate(lcd_init,"lcd_task",1024,NULL,1,NULL);

    while(1){
        /*Start FreeRTOS scheduler*/
        vTaskStartScheduler();
    }

    return EXIT_FAILURE;
}

void lcd_init(void *params)
{
//    static uint8_t config_buffer[]={
//    0x2a,0x27,0xc2,0xa1,0xd0,0xd5,0xc8,0x10,0xeb,0xa6,0xa4,0x81,0x35,0xd8,0xf1,
//    0x7f,0xf2,0x00,0xf3,0x7f,0x85,0xaf,0xf4,0,0xf5,0,0xf6,79,0xf7,127,0xf8,0x00,
//    0x10,0x60,0x70
//    };

    SPI_Handler __spi = &(struct _SPI_Handler){};
    SPI_Setup setup = {
            .baudrate = 20000000,
            .mastermode = SPI_MASTER,
            .mode = SPI_MODE_3,
            .sample = SPI_SAMPLE_MID,
    };
    SPI_Init(__spi, LCD_SPI_CHANNEL, &setup);
    LCD_init(__spi, LCD_SS, LCD_BLA, LCD_DC, LCD_RST);
    LCD_draw_hline(10,30,200,LCD_COLOR_BLACK);
    LCD_print();
//    GPIO_PinWrite(LCD_RST, GPIO_LOW);
//    vTaskDelay(10);
//    GPIO_PinWrite(LCD_RST, GPIO_HIGH);
//    vTaskDelay(100);
//    GPIO_PinWrite(LCD_BLA, GPIO_LOW);
//    vTaskDelay(10);
//
//    GPIO_PinWrite(LCD_DC, GPIO_LOW);
//    GPIO_PinWrite(LCD_SS, GPIO_LOW);
//    SPI_Transfer(__spi,config_buffer,NULL,sizeof(config_buffer));
//    GPIO_PinWrite(LCD_SS, GPIO_HIGH);
//
//    vTaskDelay(10);
//
//    GPIO_PinWrite(LCD_DC, GPIO_HIGH);
//    GPIO_PinWrite(LCD_SS, GPIO_LOW);
//    int i;
//    for(i = 0; i < 7680; i++){
//        uint8_t buffer[] = {0xF7, 0xa3};
//        SPI_Transfer(__spi,buffer,NULL,sizeof(buffer));
//    }
//    GPIO_PinWrite(LCD_SS, GPIO_HIGH);
    while(1);
}

void blink(void *params)
{
    PinParams *p = (PinParams*)params;
    while(1){
        /*Toggle pin B6 every ~500ms*/
        GPIO_PinToggle(p->pin_number);
        vTaskDelay(p->delay_ms);
    }
}