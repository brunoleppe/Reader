#include <xc.h>
#include "ISR_Support.h"
#include "Reader_bsp.h"

//
//.extern  QTOUCH_CHANGE_Handler
//
//.section   QTOUCH_VECTOR ,code, keep
////.equ     QTOUCH_VECTOR_DISPATCH, IntVectorCHANGE_NOTICE_E_Handler
//.global  QTOUCH_VECTOR_DISPATCH
//.set     nomicromips
//.set     noreorder
//.set     nomips16
//.set     noat
//.ent  QTOUCH_VECTOR_DISPATCH
//
//QTOUCH_VECTOR_DISPATCH:
//portSAVE_CONTEXT
//        la    s6,  QTOUCH_CHANGE_Handler
//        jalr  s6
//        nop
//portRESTORE_CONTEXT
//.end   QTOUCH_VECTOR_DISPATCH

    .global PORTE_Change_Notice_IRQ
    .extern GPIO_interrupt_handler
    .set nomips16
    .set noreorder
    .set noat
    .ent PORTE_Change_Notice_IRQ
PORTE_Change_Notice_IRQ:
    portSAVE_CONTEXT
    li a0,4
    jal GPIO_interrupt_handler
    nop
    portRESTORE_CONTEXT
    .end PORTE_Change_Notice_IRQ
