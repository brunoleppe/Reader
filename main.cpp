#include "initialization.h"
#include "FreeRTOS.h"
#include "task.h"
#include "hal_delay.h"
#include "ui.h"

int main(){
    /*Initialize processor*/
    initialize();

    xTaskCreate(ui_task, "ui", 1024, nullptr, 3, nullptr);

    while(true){
        /*Start FreeRTOS scheduler*/
        vTaskStartScheduler();
    }

    return EXIT_FAILURE;
}