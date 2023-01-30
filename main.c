#include "initialization.h"
#include "FreeRTOS.h"
#include "task.h"
#include "gpio.h"
#include "spi.h"
#include "Reader_bsp.h"
#include "lcd.h"
#include "bitmap.h"
#include "hal_delay.h"

typedef struct{
    GPIO_PIN pin_number;
    int delay_ms;
}PinParams;

static void blink(void *params);
static void lcd_task(void *params);
static void qt_task(void *params);

int main(void){

    /*Initialize processor*/
    Initialize();
    /*Create a FreeRTOS Task*/
    xTaskCreate(blink,"blink_task",256,&(PinParams){.pin_number = LED1, .delay_ms = 500},1,NULL);
    xTaskCreate(blink,"blink_task",256,&(PinParams){.pin_number = LED2, .delay_ms = 400},1,NULL);
//    xTaskCreate(blink,"blink_task",256,&(PinParams){.pin_number = LED3, .delay_ms = 300},1,NULL);

    xTaskCreate(lcd_task, "lcd_task", 1024, NULL, 3, NULL);
    xTaskCreate(qt_task, "qt_task", 2048, NULL, 1, NULL);

    while(1){
        /*Start FreeRTOS scheduler*/
        vTaskStartScheduler();
    }

    return EXIT_FAILURE;
}

static void qt_task(void *params)
{
    SPI_Handler __spi = &(struct  _SPI_Handler){
        .usDelay = 160
    };
    SPI_Setup setup = {
            .baudrate = 1000000,
            .mastermode = SPI_MASTER,
            .mode = SPI_MODE_3,
            .sample = SPI_SAMPLE_END,
    };
    SPI_Init(__spi, QT_SPI_CHANNEL, &setup);
    GPIO_pin_write(QT_RST, GPIO_LOW);
    vTaskDelay(10);
    GPIO_pin_write(QT_RST, GPIO_HIGH);
    vTaskDelay(100);

    while(1){
        vTaskDelay(20);
        if(GPIO_pin_read(QT_CHANGE) == GPIO_LOW)
        {
            uint8_t read_key[] = {0xC1, 0x00, 0x00};
            GPIO_pin_write(QT_SS, GPIO_LOW);
            SPI_Transfer(__spi, read_key, NULL, sizeof(read_key));
            GPIO_pin_write(QT_SS, GPIO_HIGH);
            GPIO_pin_toggle(LED3);
        }

    }
}

static void lcd_task(void *params)
{
    SPI_Handler __spi = &(struct _SPI_Handler){};
    SPI_Setup setup = {
            .baudrate = 20000000,
            .mastermode = SPI_MASTER,
            .mode = SPI_MODE_3,
            .sample = SPI_SAMPLE_MID,
    };
    SPI_Init(__spi, LCD_SPI_CHANNEL, &setup);
    LCD_init(__spi, LCD_SS, LCD_BLA, LCD_DC, LCD_RST);

    LCD_draw_bitmap(0,0,bitmap,sizeof(bitmap));
    int i=0,j=0;
    while(1) {
        vTaskDelay(33);
        LCD_print();
    }
}

static void blink(void *params)
{
    PinParams *p = (PinParams*)params;
    while(1){
        /*Toggle pin B6 every ~500ms*/
        GPIO_pin_toggle(p->pin_number);
        vTaskDelay(p->delay_ms);
    }
}