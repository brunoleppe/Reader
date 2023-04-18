add_library(BSP OBJECT
        bsp.c
        ../initialization.c
        ../initialization.h
        ../bsp.h
        ../linux_keys.h
        ../Drivers/SPI/spi_driver.c ../Drivers/SPI/spi_driver.h
        ../Drivers/driver_defs.h
        ../debug.c ../debug.h
        interrupts.c
        interrupts_as.S
        board_defs.h
        spi_driver_config.h
        keypad.c
        FreeRTOSConfig.h
        hal_config.h qt1245.c qt1245.h
        led_matrix.c led_matrix.h
        ../input.h
        ../music.h
        sst26.c sst26.h
        ../printf.c ../printf.h ../printf_config.h
        ../virtual_term.c ../virtual_term.h)
target_link_libraries(BSP PUBLIC HAL)