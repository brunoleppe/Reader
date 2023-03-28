#include "initialization.h"
#include "FreeRTOS.h"
#include "task.h"
#include "bsp.h"
#include "lcd.h"
#include "bitmap.h"
#include "hal_delay.h"
#include "keypad.h"

int main(){
    /*Initialize processor*/
    initialize();
    /*Create a FreeRTOS Task*/
    xTaskCreate(keypad_task, "qt_task", 2048, NULL, 1, NULL);

    while(true){
        /*Start FreeRTOS scheduler*/
        vTaskStartScheduler();
    }

    return EXIT_FAILURE;
}