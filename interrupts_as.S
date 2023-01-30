#include <xc.h>
#include "ISR_Support.h"

#ifdef __READER_V1__
.extern  QTOUCH_CHANGE_Handler

.section   .vector_122,code, keep
.equ     __vector_dispatch_122, IntVectorCHANGE_NOTICE_E_Handler
.global  __vector_dispatch_122
.set     nomicromips
.set     noreorder
.set     nomips16
.set     noat
.ent  IntVectorCHANGE_NOTICE_E_Handler

IntVectorCHANGE_NOTICE_E_Handler:
portSAVE_CONTEXT
        la    s6,  QTOUCH_CHANGE_Handler
        jalr  s6
        nop
portRESTORE_CONTEXT
.end   IntVectorCHANGE_NOTICE_E_Handler
#endif