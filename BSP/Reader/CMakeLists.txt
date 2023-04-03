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
        keypad.c ../keypad.h
        qt1110.h qt1110.c
        FreeRTOSConfig.h
        hal_config.h
        ../input.h
#        bitmap.c bitmap.h
        ../music.h ../sst26.c ../sst26.h)
target_link_libraries(BSP PUBLIC HAL)