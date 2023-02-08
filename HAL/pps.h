#ifndef PPS_H
#define PPS_H
/**********************************************************************
* Includes
**********************************************************************/
#include "hal_defs.h"
/**********************************************************************
* Preprocessor Constants
**********************************************************************/
#define PPS_INPUT_REG_INT3              (volatile uint32_t*)(&INT3R)
#define PPS_INPUT_REG_T2CK              (volatile uint32_t*)(&T2CKR)
#define PPS_INPUT_REG_T6CK              (volatile uint32_t*)(&T6CKR)
#define PPS_INPUT_REG_IC3               (volatile uint32_t*)(&IC3R)
#define PPS_INPUT_REG_IC7               (volatile uint32_t*)(&IC7R)
#define PPS_INPUT_REG_U1RX              (volatile uint32_t*)(&U1RXR)
#define PPS_INPUT_REG_U2CTS             (volatile uint32_t*)(&U2CTSR)
#define PPS_INPUT_REG_U5RX              (volatile uint32_t*)(&U5RXR)
#define PPS_INPUT_REG_U6CTS             (volatile uint32_t*)(&U6CTSR)
#define PPS_INPUT_REG_SDI1              (volatile uint32_t*)(&SDI1R)
#define PPS_INPUT_REG_SDI3              (volatile uint32_t*)(&SDI3R)
#define PPS_INPUT_REG_SDI5              (volatile uint32_t*)(&SDI5R)
#define PPS_INPUT_REG_SS6               (volatile uint32_t*)(&SS6R)
#define PPS_INPUT_REG_REFCLKI1          (volatile uint32_t*)(&REFCLKI1R)
#define PPS_INPUT_REG_INT4              (volatile uint32_t*)(&INT4R)
#define PPS_INPUT_REG_T5CK              (volatile uint32_t*)(&T5CKR)
#define PPS_INPUT_REG_T7CK              (volatile uint32_t*)(&T7CKR)
#define PPS_INPUT_REG_IC4               (volatile uint32_t*)(&IC4R)
#define PPS_INPUT_REG_IC8               (volatile uint32_t*)(&IC8R)
#define PPS_INPUT_REG_U3RX              (volatile uint32_t*)(&U3RXR)
#define PPS_INPUT_REG_U4CTS             (volatile uint32_t*)(&U4CTSR)
#define PPS_INPUT_REG_SDI2              (volatile uint32_t*)(&SDI2R)
#define PPS_INPUT_REG_SDI4              (volatile uint32_t*)(&SDI4R)
#define PPS_INPUT_REG_C1RX              (volatile uint32_t*)(&C1RXR)
#define PPS_INPUT_REG_REFCLKI4          (volatile uint32_t*)(&REFCLKI4R)
#define PPS_INPUT_REG_INT2              (volatile uint32_t*)(&INT2R)
#define PPS_INPUT_REG_T3CK              (volatile uint32_t*)(&T3CKR)
#define PPS_INPUT_REG_T8CK              (volatile uint32_t*)(&T8CKR)
#define PPS_INPUT_REG_IC2               (volatile uint32_t*)(&IC2R)
#define PPS_INPUT_REG_IC5               (volatile uint32_t*)(&IC5R)
#define PPS_INPUT_REG_IC9               (volatile uint32_t*)(&IC9R)
#define PPS_INPUT_REG_U1CTS             (volatile uint32_t*)(&U1CTSR)
#define PPS_INPUT_REG_U2RX              (volatile uint32_t*)(&U2RXR)
#define PPS_INPUT_REG_U5CTS             (volatile uint32_t*)(&U5CTSR)
#define PPS_INPUT_REG_SS1               (volatile uint32_t*)(&SS1R)
#define PPS_INPUT_REG_SS3               (volatile uint32_t*)(&SS3R)
#define PPS_INPUT_REG_SS4               (volatile uint32_t*)(&SS4R)
#define PPS_INPUT_REG_SS5               (volatile uint32_t*)(&SS5R)
#define PPS_INPUT_REG_C2RX              (volatile uint32_t*)(&C2RXR)
#define PPS_INPUT_REG_INT1              (volatile uint32_t*)(&INT1R)
#define PPS_INPUT_REG_T4CK              (volatile uint32_t*)(&T4CKR)
#define PPS_INPUT_REG_T9CK              (volatile uint32_t*)(&T9CKR)
#define PPS_INPUT_REG_IC1               (volatile uint32_t*)(&IC1R)
#define PPS_INPUT_REG_IC6               (volatile uint32_t*)(&IC6R)
#define PPS_INPUT_REG_U3CTS             (volatile uint32_t*)(&U3CTSR)
#define PPS_INPUT_REG_U4RX              (volatile uint32_t*)(&U4R)
#define PPS_INPUT_REG_U6RX              (volatile uint32_t*)(&U6R)
#define PPS_INPUT_REG_SS2               (volatile uint32_t*)(&SS2R)
#define PPS_INPUT_REG_SDI6              (volatile uint32_t*)(&SDI6R)
#define PPS_INPUT_REG_OCFA              (volatile uint32_t*)(&OCFAR)
#define PPS_INPUT_REG_REFCLKI3          (volatile uint32_t*)(&REFCLKI3R)

#define PPS_OUTPUT_REG_RPD2             (volatile uint32_t*)(&RPD2R)
#define PPS_OUTPUT_REG_RPG8             (volatile uint32_t*)(&RPG8R)
#define PPS_OUTPUT_REG_RPF4             (volatile uint32_t*)(&RPF4R)
#define PPS_OUTPUT_REG_RPD10            (volatile uint32_t*)(&RPD10R)
#define PPS_OUTPUT_REG_RPF1             (volatile uint32_t*)(&RPF1R)
#define PPS_OUTPUT_REG_RPB9             (volatile uint32_t*)(&RPB9R)
#define PPS_OUTPUT_REG_RPB10            (volatile uint32_t*)(&RPB10R)
#define PPS_OUTPUT_REG_RPC14            (volatile uint32_t*)(&RPC14R)
#define PPS_OUTPUT_REG_RPB5             (volatile uint32_t*)(&RPB5R)
#define PPS_OUTPUT_REG_RPC1             (volatile uint32_t*)(&RPC1R)
#define PPS_OUTPUT_REG_RPD14            (volatile uint32_t*)(&RPD14R)
#define PPS_OUTPUT_REG_RPG1             (volatile uint32_t*)(&RPG1R)
#define PPS_OUTPUT_REG_RPA14            (volatile uint32_t*)(&RPA14R)
#define PPS_OUTPUT_REG_RPD6             (volatile uint32_t*)(&RPD6R)
#define PPS_OUTPUT_REG_RPD3             (volatile uint32_t*)(&RPD3R)
#define PPS_OUTPUT_REG_RPG7             (volatile uint32_t*)(&RPG7R)
#define PPS_OUTPUT_REG_RPF5             (volatile uint32_t*)(&RPF5R)
#define PPS_OUTPUT_REG_RPD11            (volatile uint32_t*)(&RPD11R)
#define PPS_OUTPUT_REG_RPF0             (volatile uint32_t*)(&RPF0R)
#define PPS_OUTPUT_REG_RPB1             (volatile uint32_t*)(&RPB1R)
#define PPS_OUTPUT_REG_RPE5             (volatile uint32_t*)(&RPE5R)
#define PPS_OUTPUT_REG_RPC13            (volatile uint32_t*)(&RPC13R)
#define PPS_OUTPUT_REG_RPB3             (volatile uint32_t*)(&RPB3R)
#define PPS_OUTPUT_REG_RPC4             (volatile uint32_t*)(&RPC4R)
#define PPS_OUTPUT_REG_RPD15            (volatile uint32_t*)(&RPD15R)
#define PPS_OUTPUT_REG_RPG0             (volatile uint32_t*)(&RPG0R)
#define PPS_OUTPUT_REG_RPA15            (volatile uint32_t*)(&RPA15R)
#define PPS_OUTPUT_REG_RPD7             (volatile uint32_t*)(&RPD7R)
#define PPS_OUTPUT_REG_RPD9             (volatile uint32_t*)(&RPD9R)
#define PPS_OUTPUT_REG_RPG6             (volatile uint32_t*)(&RPG6R)
#define PPS_OUTPUT_REG_RPB8             (volatile uint32_t*)(&RPB8R)
#define PPS_OUTPUT_REG_RPb15            (volatile uint32_t*)(&RPb15R)
#define PPS_OUTPUT_REG_RPD4             (volatile uint32_t*)(&RPD4R)
#define PPS_OUTPUT_REG_RPB0             (volatile uint32_t*)(&RPB0R)
#define PPS_OUTPUT_REG_RPE3             (volatile uint32_t*)(&RPE3R)
#define PPS_OUTPUT_REG_RPB7             (volatile uint32_t*)(&RPB7R)
#define PPS_OUTPUT_REG_RPF12            (volatile uint32_t*)(&RPF12R)
#define PPS_OUTPUT_REG_RPD12            (volatile uint32_t*)(&RPD12R)
#define PPS_OUTPUT_REG_RPF8             (volatile uint32_t*)(&RPF8R)
#define PPS_OUTPUT_REG_RPC3             (volatile uint32_t*)(&RPC3R)
#define PPS_OUTPUT_REG_RPE9             (volatile uint32_t*)(&RPE9R)
#define PPS_OUTPUT_REG_RPD1             (volatile uint32_t*)(&RPD1R)
#define PPS_OUTPUT_REG_RPG9             (volatile uint32_t*)(&RPG9R)
#define PPS_OUTPUT_REG_RPB14            (volatile uint32_t*)(&RPB14R)
#define PPS_OUTPUT_REG_RPD0             (volatile uint32_t*)(&RPD0R)
#define PPS_OUTPUT_REG_RPB6             (volatile uint32_t*)(&RPB6R)
#define PPS_OUTPUT_REG_RPD5             (volatile uint32_t*)(&RPD5R)
#define PPS_OUTPUT_REG_RPB2             (volatile uint32_t*)(&RPB2R)
#define PPS_OUTPUT_REG_RPF3             (volatile uint32_t*)(&RPF3R)
#define PPS_OUTPUT_REG_RPF13            (volatile uint32_t*)(&RPF13R)
#define PPS_OUTPUT_REG_RPC2             (volatile uint32_t*)(&RPC2R)
#define PPS_OUTPUT_REG_RPE8             (volatile uint32_t*)(&RPE8R)
#define PPS_OUTPUT_REG_RPF2             (volatile uint32_t*)(&RPF2R)

/**********************************************************************
* Typedefs
**********************************************************************/
typedef volatile uint32_t * PPS_Register;
typedef uint32_t PPS_AlternateFunction;
/**********************************************************************
* Function Prototypes
**********************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

void PPS_pin_mapping(PPS_Register reg, PPS_AlternateFunction af);

#ifdef __cplusplus
}
#endif

#define PPS_GROUP_1_INPUT_MAPPING_RPD2              0x0
#define PPS_GROUP_1_INPUT_MAPPING_RPG8              0x1
#define PPS_GROUP_1_INPUT_MAPPING_RPF4              0x2
#define PPS_GROUP_1_INPUT_MAPPING_RPD10             0x3
#define PPS_GROUP_1_INPUT_MAPPING_RPF1              0x4
#define PPS_GROUP_1_INPUT_MAPPING_RPB9              0x5
#define PPS_GROUP_1_INPUT_MAPPING_RPB10             0x6
#define PPS_GROUP_1_INPUT_MAPPING_RPC14             0x7
#define PPS_GROUP_1_INPUT_MAPPING_RPB5              0x8
#define PPS_GROUP_1_INPUT_MAPPING_RPC1              0xa
#define PPS_GROUP_1_INPUT_MAPPING_RPD14             0xb
#define PPS_GROUP_1_INPUT_MAPPING_RPG1              0xc
#define PPS_GROUP_1_INPUT_MAPPING_RPA14             0xd
#define PPS_GROUP_1_INPUT_MAPPING_RPD6              0xe

#define PPS_GROUP_2_INPUT_MAPPING_RPD3              0x0
#define PPS_GROUP_2_INPUT_MAPPING_RPG7              0x1
#define PPS_GROUP_2_INPUT_MAPPING_RPF5              0x2
#define PPS_GROUP_2_INPUT_MAPPING_RPD11             0x3
#define PPS_GROUP_2_INPUT_MAPPING_RPF0              0x4
#define PPS_GROUP_2_INPUT_MAPPING_RPB1              0x5
#define PPS_GROUP_2_INPUT_MAPPING_RPE5              0x6
#define PPS_GROUP_2_INPUT_MAPPING_RPC13             0x7
#define PPS_GROUP_2_INPUT_MAPPING_RPB3              0x8
#define PPS_GROUP_2_INPUT_MAPPING_RPC4              0xa
#define PPS_GROUP_2_INPUT_MAPPING_RPD15             0xb
#define PPS_GROUP_2_INPUT_MAPPING_RPG0              0xc
#define PPS_GROUP_2_INPUT_MAPPING_RPA15             0xd
#define PPS_GROUP_2_INPUT_MAPPING_RPD7              0xe

#define PPS_GROUP_3_INPUT_MAPPING_RPD9              0x0
#define PPS_GROUP_3_INPUT_MAPPING_RPG6              0x1
#define PPS_GROUP_3_INPUT_MAPPING_RPB8              0x2
#define PPS_GROUP_3_INPUT_MAPPING_RPB15             0x3
#define PPS_GROUP_3_INPUT_MAPPING_RPD4              0x4
#define PPS_GROUP_3_INPUT_MAPPING_RPB0              0x5
#define PPS_GROUP_3_INPUT_MAPPING_RPE3              0x6
#define PPS_GROUP_3_INPUT_MAPPING_RPB7              0x7
#define PPS_GROUP_3_INPUT_MAPPING_RPF12             0x9
#define PPS_GROUP_3_INPUT_MAPPING_RPD12             0xa
#define PPS_GROUP_3_INPUT_MAPPING_RPF8              0xb
#define PPS_GROUP_3_INPUT_MAPPING_RPC3              0xc
#define PPS_GROUP_3_INPUT_MAPPING_RPE9              0xd

#define PPS_GROUP_4_INPUT_MAPPING_RPD1              0x0
#define PPS_GROUP_4_INPUT_MAPPING_RPG9              0x1
#define PPS_GROUP_4_INPUT_MAPPING_RPB14             0x2
#define PPS_GROUP_4_INPUT_MAPPING_RPD0              0x3
#define PPS_GROUP_4_INPUT_MAPPING_RPB6              0x5
#define PPS_GROUP_4_INPUT_MAPPING_RPD5              0x6
#define PPS_GROUP_4_INPUT_MAPPING_RPB2              0x7
#define PPS_GROUP_4_INPUT_MAPPING_RPF3              0x8
#define PPS_GROUP_4_INPUT_MAPPING_RPF13             0x9
#define PPS_GROUP_4_INPUT_MAPPING_No_Connect        0xa
#define PPS_GROUP_4_INPUT_MAPPING_RPF2              0xb
#define PPS_GROUP_4_INPUT_MAPPING_RPC2              0xc
#define PPS_GROUP_4_INPUT_MAPPING_RPE8              0xd


#define PPS_GROUP_1_OUTPUT_MAPPING_U3TX             0x1
#define PPS_GROUP_1_OUTPUT_MAPPING_U4RTS            0x2
#define PPS_GROUP_1_OUTPUT_MAPPING_SDO1             0x5
#define PPS_GROUP_1_OUTPUT_MAPPING_SDO2             0x6
#define PPS_GROUP_1_OUTPUT_MAPPING_SDO3             0x7
#define PPS_GROUP_1_OUTPUT_MAPPING_SDO5             0x9
#define PPS_GROUP_1_OUTPUT_MAPPING_SS6              0xa
#define PPS_GROUP_1_OUTPUT_MAPPING_OC3              0xb
#define PPS_GROUP_1_OUTPUT_MAPPING_OC6              0xc
#define PPS_GROUP_1_OUTPUT_MAPPING_REFCLKO4         0xd
#define PPS_GROUP_1_OUTPUT_MAPPING_C2OUT            0xe
#define PPS_GROUP_1_OUTPUT_MAPPING_C1TX             0xf

#define PPS_GROUP_2_OUTPUT_MAPPING_U1TX             0x1
#define PPS_GROUP_2_OUTPUT_MAPPING_U2RTS            0x2
#define PPS_GROUP_2_OUTPUT_MAPPING_U5TX             0x3
#define PPS_GROUP_2_OUTPUT_MAPPING_U6RTS            0x4
#define PPS_GROUP_2_OUTPUT_MAPPING_SDO1             0x5
#define PPS_GROUP_2_OUTPUT_MAPPING_SDO2             0x6
#define PPS_GROUP_2_OUTPUT_MAPPING_SDO3             0x7
#define PPS_GROUP_2_OUTPUT_MAPPING_SDO4             0x8
#define PPS_GROUP_2_OUTPUT_MAPPING_SDO5             0x9
#define PPS_GROUP_2_OUTPUT_MAPPING_OC4              0xb
#define PPS_GROUP_2_OUTPUT_MAPPING_OC7              0xc
#define PPS_GROUP_2_OUTPUT_MAPPING_REFCLKO1         0xf

#define PPS_GROUP_3_OUTPUT_MAPPING_U3RTS            0x1
#define PPS_GROUP_3_OUTPUT_MAPPING_U4TX             0x2
#define PPS_GROUP_3_OUTPUT_MAPPING_U6TX             0x4
#define PPS_GROUP_3_OUTPUT_MAPPING_SS1              0x5
#define PPS_GROUP_3_OUTPUT_MAPPING_SS3              0x7
#define PPS_GROUP_3_OUTPUT_MAPPING_SS4              0x8
#define PPS_GROUP_3_OUTPUT_MAPPING_SS5              0x9
#define PPS_GROUP_3_OUTPUT_MAPPING_SDO6             0xa
#define PPS_GROUP_3_OUTPUT_MAPPING_OC5              0xb
#define PPS_GROUP_3_OUTPUT_MAPPING_OC8              0xc
#define PPS_GROUP_3_OUTPUT_MAPPING_C1OUT            0xe
#define PPS_GROUP_3_OUTPUT_MAPPING_REFCLKO3         0xf

#define PPS_GROUP_4_OUTPUT_MAPPING_U1RTS            0x1
#define PPS_GROUP_4_OUTPUT_MAPPING_U2TX             0x2
#define PPS_GROUP_4_OUTPUT_MAPPING_U5RTS            0x3
#define PPS_GROUP_4_OUTPUT_MAPPING_U6TX             0x4
#define PPS_GROUP_4_OUTPUT_MAPPING_SS2              0x6
#define PPS_GROUP_4_OUTPUT_MAPPING_SDO4             0x8
#define PPS_GROUP_4_OUTPUT_MAPPING_SDO6             0xa
#define PPS_GROUP_4_OUTPUT_MAPPING_OC2              0xb
#define PPS_GROUP_4_OUTPUT_MAPPING_OC1              0xc
#define PPS_GROUP_4_OUTPUT_MAPPING_OC9              0xd
#define PPS_GROUP_4_OUTPUT_MAPPING_C2TX             0xf

#endif //PPS_H
