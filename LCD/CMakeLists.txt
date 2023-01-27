set(PIC  32MZ1024EFM100)
set(OPTIMIZATION 1)
set(USER_FLAGS -Wall)
set(MPROCESSOR -mprocessor=${PIC})
set(MOPTIMIZATION -O${OPTIMIZATION})


add_library(LCD
    lm1076b_lcd.c lcd.h
)
set_target_properties(LCD PROPERTIES LINKER_LANGUAGE C)
target_compile_options(LCD PUBLIC ${USER_FLAGS} ${MPROCESSOR} ${MOPTIMIZATION} -fdata-sections -ffunction-sections -no-legacy-libc)