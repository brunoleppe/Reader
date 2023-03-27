add_library(HAL
        ../hal_defs.h
        pic32mx_registers.h
        evic.c evic.h
        dma.c
        gpio.c
        hal_delay.c
        hal_ring_buffer.c
        oc.c
        timer.c
        spi.c
        uart.c
        system.c)