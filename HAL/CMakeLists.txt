set(PIC  32MZ1024EFM100)
set(OPTIMIZATION 1)
set(USER_FLAGS -Wall)
set(MPROCESSOR -mprocessor=${PIC})
set(MOPTIMIZATION -O${OPTIMIZATION})


add_library(HAL
        hal.h
        pic32mz_registers.h
        gpio.h gpio_config.h gpio.c
        spi.c spi.h
        system.c system.h
        evic.h evic.c
        hal_delay.c hal_delay.h dma.c dma.h pps.c pps.h hal_defs.h hal_config.h)
set_target_properties(HAL PROPERTIES LINKER_LANGUAGE C)
target_compile_options(HAL PUBLIC ${USER_FLAGS} ${MPROCESSOR} ${MOPTIMIZATION} -fdata-sections -ffunction-sections -no-legacy-libc)