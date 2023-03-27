add_library(BSP OBJECT
        bsp.c
        initialization.c
        interrupts.c
        interrupts_as.S
        )
target_link_libraries(BSP PUBLIC HAL)