add_library(BSP OBJECT
        bsp.c
        initialization.c
        interrupts.c
        interrupts_as.S
        board_defs.h
        spi_driver_config.h
        keypad.c
        FreeRTOSConfig.h
        hal_config.h qtouch.c qtouch.h led_matrix.c led_matrix.h)
target_link_libraries(BSP PUBLIC HAL)