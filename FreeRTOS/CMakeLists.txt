include_directories(Source/include)
IF(ARCH STREQUAL MZ)
    message(ARCH="${ARCH}")
    include_directories(Source/portable/MPLAB/PIC32MZ)
    set(PORTABLE_SOURCES
            Source/portable/MPLAB/PIC32MZ/ISR_Support.h
            Source/portable/MPLAB/PIC32MZ/port.c
            Source/portable/MPLAB/PIC32MZ/port_asm.S
            Source/portable/MPLAB/PIC32MZ/portmacro.h)
ELSEIF(ARCH STREQUAL MX)

    message(ARCH="${ARCH}")

    include_directories(Source/portable/MPLAB/PIC32MX)
    set(PORTABLE_SOURCES
            Source/portable/MPLAB/PIC32MX/ISR_Support.h
            Source/portable/MPLAB/PIC32MX/port.c
            Source/portable/MPLAB/PIC32MX/port_asm.S
            Source/portable/MPLAB/PIC32MX/portmacro.h)
ENDIF()

add_library(FreeRTOS
        Source/include/croutine.h
        Source/include/deprecated_definitions.h
        Source/include/event_groups.h
        Source/include/FreeRTOS.h
        Source/include/list.h
        Source/include/message_buffer.h
        Source/include/mpu_prototypes.h
        Source/include/mpu_wrappers.h
        Source/include/portable.h
        Source/include/projdefs.h
        Source/include/queue.h
        Source/include/semphr.h
        Source/include/stack_macros.h
        Source/include/stream_buffer.h
        Source/include/task.h
        Source/include/timers.h
        Source/portable/MemMang/heap_4.c
        ${PORTABLE_SOURCES}
        Source/croutine.c
        Source/event_groups.c
        Source/FreeRTOS_tasks.c
        Source/list.c
        Source/queue.c
        Source/stream_buffer.c
        Source/timers.c
)
