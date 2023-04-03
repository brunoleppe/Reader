#include "initialization.h"
#include "FreeRTOS.h"
#include "task.h"
#include "hal_delay.h"



int main(){
    /*Initialize processor*/
    initialize();


    while(true){
        /*Start FreeRTOS scheduler*/
        vTaskStartScheduler();
    }

    return EXIT_FAILURE;
}