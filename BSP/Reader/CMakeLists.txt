add_library(BSP OBJECT
        bsp.c
        ../initialization.c
        ../initialization.h
        ../bsp.h
        ../linux_keys.h
        ../Drivers/SPI/spi_driver.c ../Drivers/SPI/spi_driver.h
        ../Drivers/driver_defs.h
        ../debug_bsp.c ../debug_bsp.h
        interrupts.c
        interrupts_as.S
        board_defs.h
        spi_driver_config.h
        Keypad/keypad.c ../keypad.h
        QTouch/qt1110.h QTouch/qt1110.c
        FreeRTOSConfig.h
        hal_config.h
        ../input.h
#        bitmap.c bitmap.h
        ../music.h
        FlashMem/sst26.c FlashMem/sst26.h
        ../printf.c ../printf.h ../printf_config.h
        os_port_config.h
        net_config.h
        ../bitmap.c ../bitmap.h ../virtual_term.c ../virtual_term.h ../tcp_port.c ../tcp_port.h FlashMem/sst26_alt.c)
target_link_libraries(BSP PUBLIC HAL)