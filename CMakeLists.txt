#Define the following variables in the CMake profile configurations tab -> CMake Options:
#PIC -> Ex: -DPIC=32MZ1024EFM100
#DFP -> Ex: -DDFP=/opt/microchip/mplabx/v6.05/packs/Microchip/PIC32MZ-EF_DFP/1.3.58
#ARCH -> Ex: -DARCH=MZ (for FreeRTOS port of pic32mz or pic32mx)
#user defines if any

cmake_minimum_required(VERSION 3.24.2)

#set(CMAKE_VERBOSE_MAKEFILE True)

#Compiler
set(CMAKE_C_COMPILER "/opt/microchip/xc32/v4.21/bin/xc32-gcc")
set(CMAKE_CXX_COMPILER "/opt/microchip/xc32/v4.21/bin/xc32-g++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden -flto -fno-exceptions -fno-unwind-tables -fno-rtti -Wno-write-strings -fpermissive -fdata-sections -ffunction-sections")
#Device Family Pack
#set(DFP /opt/microchip/mplabx/v6.00/packs/Microchip/PIC32MZ-EF_DFP/1.3.58)

#Device
set(OPTIMIZATION s)
set(USER_FLAGS -Wall)
set(USER_DEFINITIONS )
set(HEAP 0)


set(SOURCES
#        main.c
        main.cpp
        DynamicAlloc/dynamic_alloc.cpp
        )

project(Reader CXX C ASM)

# FreeRTOS Directories
include_directories(FreeRTOS/Source/include)
include_directories(HAL/)
include_directories(BSP/)
include_directories(LCD/)
include_directories(States/)
include_directories(Test_MVC/)

IF(READERV2 OR READERV1)
    include_directories(FreeRTOS/Source/portable/MPLAB/PIC32MZ)
    include_directories(HAL/PIC32MZEFM100)
    include_directories(BSP/Reader)

    include_directories(BSP/Reader/Ethernet/common)
    include_directories(BSP/Reader/Ethernet/cyclone_tcp/)
ELSEIF(PPPLUS)
    include_directories(FreeRTOS/Source/portable/MPLAB/PIC32MX)
    include_directories(HAL/PIC32MX795F512H)
    include_directories(BSP/PPP)

    include_directories(BSP/PPP/Ethernet/common)
    include_directories(BSP/PPP/Ethernet/cyclone_tcp/)
ELSEIF (PPP_EXT)
    include_directories(FreeRTOS/Source/portable/MPLAB/PIC32MZ)
    include_directories(HAL/PIC32MZEFM100)
    include_directories(BSP/PPP_EXT)

    include_directories(BSP/PPP_EXT/Ethernet/common)
    include_directories(BSP/PPP_EXT/Ethernet/cyclone_tcp/)

ENDIF()

# FreeRTOSConfig.h is located here
include_directories(.)

add_subdirectory(FreeRTOS)
add_subdirectory(LCD)
add_subdirectory(Test_MVC)

IF(READERV2 OR READERV1)
    add_subdirectory(HAL/PIC32MZEFM100)
    add_subdirectory(BSP/Reader)
    add_subdirectory(BSP/Reader/Ethernet)
ELSEIF(PPPLUS)
    add_subdirectory(BSP/PPP)
    add_subdirectory(HAL/PIC32MX795F512H)
    add_subdirectory(BSP/PPP/Ethernet)
ELSEIF (PPP_EXT)
    add_subdirectory(BSP/PPP_EXT)
    add_subdirectory(HAL/PIC32MZEFM100)
    add_subdirectory(BSP/PPP_EXT/Ethernet)

ENDIF()

add_executable(${PROJECT_NAME}.elf ${SOURCES})


target_link_libraries(${PROJECT_NAME}.elf   FreeRTOS)
target_link_libraries(${PROJECT_NAME}.elf   HAL)
target_link_libraries(${PROJECT_NAME}.elf   LCD)
target_link_libraries(${PROJECT_NAME}.elf   BSP)
target_link_libraries(${PROJECT_NAME}.elf   CycloneTCP)
target_link_libraries(${PROJECT_NAME}.elf   MVC)

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
#        ${SYM_HEAP},${LINKER_SCRIPT},${SYM_BUILD},${LINKER_OPTS},${LINKER_MAP},${MEMORY_FILE}
        ${SYM_HEAP},${SYM_BUILD},${LINKER_OPTS},${LINKER_MAP},${MEMORY_FILE}
        )


option(READERV2 "Version 2 del lector de escritorio" OFF)
IF(READERV2)
    add_compile_definitions(__READER_V2__)
    set(DEFINES ${DEFINES} __READER_V2__)
ELSE()
    add_compile_definitions(__READER_V1__)
    set(DEFINES ${DEFINES} __READER_V1__)
ENDIF(READERV2)

IF(DEBUG)
    set(DEFINES ${DEFINES} HAL_DEBUG)
ENDIF()


#HEX file build command
add_custom_command(
        OUTPUT  ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex
        DEPENDS ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf
        COMMAND /opt/microchip/xc32/v4.21/bin/xc32-bin2hex ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.elf
)
add_custom_target(${PROJECT_NAME}_hex ALL
        DEPENDS ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex
        )

set_target_properties(BSP PROPERTIES LINKER_LANGUAGE C)
target_compile_definitions(BSP PUBLIC XPRJ_default=default ${DEFINES})
target_compile_options(BSP PUBLIC ${USER_FLAGS} ${MPROCESSOR} ${MOPTIMIZATION} -fdata-sections -ffunction-sections -no-legacy-libc -mdfp=${DFP})

set_target_properties(HAL PROPERTIES LINKER_LANGUAGE C)
target_compile_definitions(HAL PUBLIC XPRJ_default=default ${DEFINES})
target_compile_options(HAL PUBLIC ${USER_FLAGS} ${MPROCESSOR} ${MOPTIMIZATION} -fdata-sections -ffunction-sections -no-legacy-libc -mdfp=${DFP})

set_target_properties(LCD PROPERTIES LINKER_LANGUAGE C)
target_compile_definitions(LCD PUBLIC XPRJ_default=default ${DEFINES})
target_compile_options(LCD PUBLIC ${USER_FLAGS} ${MPROCESSOR} ${MOPTIMIZATION} -fdata-sections -ffunction-sections -no-legacy-libc -mdfp=${DFP} )

set_target_properties(FreeRTOS PROPERTIES LINKER_LANGUAGE C)
target_compile_definitions(FreeRTOS PUBLIC XPRJ_default=default ${DEFINES})
target_compile_options(FreeRTOS PUBLIC ${USER_FLAGS} ${MPROCESSOR} ${MOPTIMIZATION} -fdata-sections -ffunction-sections -no-legacy-libc -mdfp=${DFP})

set_target_properties(CycloneTCP PROPERTIES LINKER_LANGUAGE C)
target_compile_definitions(CycloneTCP PUBLIC XPRJ_default=default ${DEFINES})
target_compile_options(CycloneTCP PUBLIC ${USER_FLAGS} ${MPROCESSOR} ${MOPTIMIZATION} -fdata-sections -ffunction-sections -no-legacy-libc -mdfp=${DFP})

target_compile_options(${PROJECT_NAME}.elf PUBLIC ${USER_FLAGS} ${MPROCESSOR} ${MOPTIMIZATION} -fdata-sections -ffunction-sections -no-legacy-libc -mdfp=${DFP})
target_compile_definitions(${PROJECT_NAME}.elf PUBLIC XPRJ_default=default ${DEFINES})
target_link_options(${PROJECT_NAME}.elf PUBLIC ${MPROCESSOR} ${MOPTIMIZATION} )
target_link_libraries(${PROJECT_NAME}.elf "-Wl,${XC32_LINK_FLAGS}")