#include "initialization.h"
#include "FreeRTOS.h"
#include "task.h"
#include "bsp.h"
#include "lcd.h"
#include "Reader/bitmap.h"
#include "hal_delay.h"

int main(){
    /*Initialize processor*/
    initialize();
    /*Create a FreeRTOS Task*/

    while(true){
        /*Start FreeRTOS scheduler*/
        vTaskStartScheduler();
    }

    return EXIT_FAILURE;
}