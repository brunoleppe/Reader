#include "initialization.h"
#include "FreeRTOS.h"
#include "task.h"

#include "hal_delay.h"
#include "TestStateMachine.h"
#include "Input/input_cpp.h"


[[noreturn]]int main(){
    /*Initialize processor*/
    initialize();
    TestStateMachine machine;
    input_register(&machine);

//    while(true){
        /*Start FreeRTOS scheduler*/
        vTaskStartScheduler();
//    }

//    return EXIT_FAILURE;
}