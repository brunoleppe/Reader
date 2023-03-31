add_library(BSP OBJECT
        bsp.c
        ../initialization.c
        interrupts.c
        interrupts_as.S
        board_defs.h
        spi_driver_config.h
        keypad.c
        FreeRTOSConfig.h
        hal_config.h qt1245.c qt1245.h led_matrix.c led_matrix.h ../input.h ../ui.c ../ui.h)
target_link_libraries(BSP PUBLIC HAL)