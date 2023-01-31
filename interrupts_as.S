#include <xc.h>
#include "ISR_Support.h"
#include "Reader_bsp.h"


.extern  QTOUCH_CHANGE_Handler

.section   QTOUCH_VECTOR ,code, keep
//.equ     QTOUCH_VECTOR_DISPATCH, IntVectorCHANGE_NOTICE_E_Handler
.global  QTOUCH_VECTOR_DISPATCH
.set     nomicromips
.set     noreorder
.set     nomips16
.set     noat
.ent  QTOUCH_VECTOR_DISPATCH

QTOUCH_VECTOR_DISPATCH:
portSAVE_CONTEXT
        la    s6,  QTOUCH_CHANGE_Handler
        jalr  s6
        nop
portRESTORE_CONTEXT
.end   QTOUCH_VECTOR_DISPATCH
