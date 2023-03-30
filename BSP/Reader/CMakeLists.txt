add_library(BSP OBJECT
        bsp.c
        initialization.c
        interrupts.c
        interrupts_as.S
        board_defs.h
        spi_driver_config.h
        keypad.c ../keypad.h
        qtouch.h qtouch.c
        FreeRTOSConfig.h
        hal_config.h)
target_link_libraries(BSP PUBLIC HAL)