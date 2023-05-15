#include "initialization.h"
#include "FreeRTOS.h"
#include "task.h"
#include "hal_delay.h"
#include "MVC_Test/MVC/Views/View.h"
#include "MVC_Test/MVC/Controller.h"
#include "MVC_Test/MVC/States/StateLogo.h"
#include "MVC_Test/MVC/States/StateMainMenu.h"

 [[noreturn]]int main(){
    /*Initialize processor*/
    initialize();

//    xTaskCreate(ui_task, "ui", 1024, nullptr, 3, nullptr);

    auto *s = new ModelStateService();
//    s->set_state(&StateMainMenu::instance);
    s->set_state(&StateLogo::instance);
    auto *c = new Controller(s, &ViewService::instance);
//    input_register(c);

    xTaskCreate(Controller::controller_task, "c", 2048, c, 3, nullptr);

    while(true){
        /*Start FreeRTOS scheduler*/
        vTaskStartScheduler();
    }

//    return EXIT_FAILURE;
}