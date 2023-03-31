add_library(BSP OBJECT
        bsp.c
        ../initialization.c
        interrupts.c
        interrupts_as.S
        board_defs.h
        spi_driver_config.h
        keypad.c ../keypad.h
        qt1110.h qt1110.c
        FreeRTOSConfig.h
        hal_config.h
        ../input.h
        bitmap.c bitmap.h
        ../ui.c ../ui.h)
target_link_libraries(BSP PUBLIC HAL)