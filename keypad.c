//
// Created by bleppe on 20/03/23.
//

#include "keypad.h"
#include "hal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "bsp.h"

static TaskHandle_t thisTask;

static void qt_change_handler(GPIO_PinMap pin, uintptr_t context)
{
    BaseType_t xHigherPriorityTaskWoken;
    bool val;
    val = GPIO_pin_read(QT_CHANGE);
    if(val == false)
    {
        xHigherPriorityTaskWoken = pdFALSE;
        xTaskNotifyFromISR(thisTask,0,eNoAction,&xHigherPriorityTaskWoken);
        portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
    }
}

void keypad_task(void *params)
{
    (void)params;
    thisTask = xTaskGetCurrentTaskHandle();
    BSP_gpio_callback_register(QT_CHANGE, qt_change_handler, 0);


    GPIO_pin_write(QT_RST, GPIO_LOW);
    vTaskDelay(10);
    GPIO_pin_write(QT_RST, GPIO_HIGH);
    vTaskDelay(100);


    while(true){

        xTaskNotifyWait(0,0,NULL,portMAX_DELAY );
        uint8_t read_key[] = {0xC1, 0x00, 0x00};
        GPIO_pin_write(QT_SS, GPIO_LOW);
        SPI_transfer(QT_SPI_CHANNEL, read_key, NULL, 1);
        HAL_delay_us(160);
        SPI_transfer(QT_SPI_CHANNEL, read_key, NULL, 2);
        HAL_delay_us(160);
        SPI_transfer(QT_SPI_CHANNEL, read_key, NULL, 3);
        HAL_delay_us(160);
        GPIO_pin_write(QT_SS, GPIO_HIGH);
        GPIO_pin_toggle(LED3);
    }
}