#Define the following variables in the CMake profile configurations tab -> CMake Options:
#PIC -> Ex: -DPIC=32MZ1024EFM100
#DFP -> Ex: -DDFP=/opt/microchip/mplabx/v6.05/packs/Microchip/PIC32MZ-EF_DFP/1.3.58
#ARCH -> Ex: -DARCH=MZ (for FreeRTOS port of pic32mz or pic32mx)
#user defines if any

cmake_minimum_required(VERSION 3.24.2)

#Compiler
set(CMAKE_C_COMPILER "/opt/microchip/xc32/v4.21/bin/xc32-gcc")
set(CMAKE_CXX_COMPILER "/opt/microchip/xc32/v4.21/bin/xc32-g++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -fno-rtti -Wno-write-strings")
#Device Family Pack
#set(DFP /opt/microchip/mplabx/v6.00/packs/Microchip/PIC32MZ-EF_DFP/1.3.58)

#Device
set(OPTIMIZATION 1)
set(USER_FLAGS -Wall)
set(USER_DEFINITIONS )
set(HEAP 0)

set(READER_TYPE     __DesktopReaderV2__)

# set(CMAKE_VERBOSE_MAKEFILE True)

set(SOURCES
        main.c
        FreeRTOSConfig.h
        initialization.c initialization.h
        Reader_bsp.h Reader_bsp.c
        bitmap.c bitmap.h
        interrupts.c
        interrupts_as.S
#        main.cpp
#        TestClass.cpp TestClass.h
        )

project(Reader CXX C ASM)

# FreeRTOS Directories
include_directories(FreeRTOS/Source/include)
include_directories(FreeRTOS/Source/portable/MPLAB/PIC32MZ)
include_directories(HAL/)
include_directories(LCD/)
# FreeRTOSConfig.h is located here
include_directories(.)

add_subdirectory(FreeRTOS)
add_subdirectory(HAL)
add_subdirectory(LCD)

add_executable(${PROJECT_NAME}.elf ${SOURCES})


target_link_libraries(${PROJECT_NAME}.elf   FreeRTOS)
target_link_libraries(${PROJECT_NAME}.elf   HAL)
target_link_libraries(${PROJECT_NAME}.elf   LCD)
#Assembly options
set(CMAKE_ASM_FLAGS "${CFLAGS} -Wa,--defsym=__MPLAB_BUILD=1,--gdwarf-2")
#Compiler flags and options
set(MPROCESSOR -mprocessor=${PIC})
set(MOPTIMIZATION -O${OPTIMIZATION})
set(DEFINES ${USER_DEFINITIONS})
set(SYM_HEAP --defsym=_min_heap_size=${HEAP})
set(SYM_BUILD --defsym=__MPLAB_BUILD=1)
set(LINKER_OPTS --gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem)
set(LINKER_MAP -Map=${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.map)
set(MEMORY_FILE --memorysummary,${CMAKE_CURRENT_BINARY_DIR}/memoryfile.xml)
set(LINKER_SCRIPT --script=${CMAKE_SOURCE_DIR}/Linker/p32MZ1024EFM100.ld)
set(XC32_LINK_FLAGS
        ${SYM_HEAP},${LINKER_SCRIPT},${SYM_BUILD},${LINKER_OPTS},${LINKER_MAP},${MEMORY_FILE}
        )


#HEX file build command
add_custom_command(
        OUTPUT  ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex
        DEPENDS ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf
        COMMAND /opt/microchip/xc32/v4.21/bin/xc32-bin2hex ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf
)
add_custom_target(${PROJECT_NAME}_hex ALL
        DEPENDS ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex
        )

set_target_properties(LCD PROPERTIES LINKER_LANGUAGE C)
target_compile_options(LCD PUBLIC ${USER_FLAGS} ${MPROCESSOR} ${MOPTIMIZATION} -fdata-sections -ffunction-sections -no-legacy-libc)

set_target_properties(HAL PROPERTIES LINKER_LANGUAGE C)
target_compile_options(HAL PUBLIC ${USER_FLAGS} ${MPROCESSOR} ${MOPTIMIZATION} -fdata-sections -ffunction-sections -no-legacy-libc)

target_compile_options(FreeRTOS PUBLIC ${USER_FLAGS} ${MPROCESSOR} ${MOPTIMIZATION} -fdata-sections -ffunction-sections -no-legacy-libc)
target_compile_options(${PROJECT_NAME}.elf PUBLIC ${USER_FLAGS} ${MPROCESSOR} ${MOPTIMIZATION} -fdata-sections -ffunction-sections -no-legacy-libc -mdfp=${DFP})

target_compile_definitions(${PROJECT_NAME}.elf PUBLIC XPRJ_default=default ${DEFINES})
target_link_options(${PROJECT_NAME}.elf PUBLIC ${MPROCESSOR} ${MOPTIMIZATION} )
target_link_libraries(${PROJECT_NAME}.elf "-Wl,${XC32_LINK_FLAGS}")


option(READERV2 "Version 2 del lector de escritorio" OFF)
IF(READERV2)
    add_compile_definitions(__READER_V2__)
ELSE()
    add_compile_definitions(__READER_V1__)
ENDIF(READERV2)