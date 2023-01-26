#include "initialization.h"
#include "FreeRTOS.h"
#include "task.h"
#include "gpio.h"
#include "spi.h"
#include "Reader_bsp.h"

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
    SPI_Handler spi = &(struct _SPI_HANDLER){};
    SPI_Setup setup={
            .baudrate = 20000000,
            .mastermode = SPI_MASTER,
            .mode = SPI_MODE_3,
            .mode = SPI_SAMPLE_MID
    };
    SPI_Init(spi, LCD_SPI_CHANNEL, &setup);
    GPIO_PinWrite(LCD_BLA, GPIO_LOW);
    vTaskDelay(portMAX_DELAY);
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