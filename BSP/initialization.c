//
// Created by bruno on 21/01/23.
//

#include "initialization.h"
#include "bsp.h"

void initialize(void)
{
    BSP_system_initialize();
    BSP_gpio_initialize();
    BSP_drivers_initialize();
    BSP_task_initialize();
    BSP_interrupts_initialize();

}