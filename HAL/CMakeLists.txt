add_library(HAL
        hal.h
        pic32mz_registers.h
        gpio.h gpio_config.h gpio.c
        spi.c spi.h
        system.c system.h
        evic.h evic.c
        hal_delay.c hal_delay.h
        dma.c dma.h
        pps.c pps.h
        hal_defs.h hal_config.h
        timer.c timer.h
        oc.c oc.h)