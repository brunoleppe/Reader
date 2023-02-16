//
// Created by bruno on 25/01/23.
//

#ifndef READER_SYSTEM_H
#define READER_SYSTEM_H
/**********************************************************************
* Includes
**********************************************************************/
#include "hal_defs.h"
/**********************************************************************
* Preprocessor Constants
**********************************************************************/
#define SYS_PERIPHERAL_CLOCK_1              (0)
#define SYS_PERIPHERAL_CLOCK_2              (1)
#define SYS_PERIPHERAL_CLOCK_3              (2)
#define SYS_PERIPHERAL_CLOCK_4              (3)
#define SYS_PERIPHERAL_CLOCK_5              (4)
#define SYS_PERIPHERAL_CLOCK_6              (5)
#define SYS_PERIPHERAL_CLOCK_7              (6)
#define SYS_PERIPHERAL_CLOCK_8              (7)


/**********************************************************************
* Typedefs
**********************************************************************/
#if defined (__LANGUAGE_C__) || defined (__LANGUAGE_C_PLUS_PLUS)


/**********************************************************************
* Function Prototypes
**********************************************************************/


#ifdef __cplusplus
extern "C"{
#endif
void SYS_Initialize();
void SYS_Unlock();
void SYS_Lock();
void SYS_peripheral_clock_config(uint32_t clockChannel, uint32_t flags);


#ifdef __cplusplus
}
#endif //__cplusplus
#endif // defined (__LANGUAGE_C__) || defined (__LANGUAGE_C_PLUS_PLUS)

#define SYS_PBCLK_ENABLED                   (0)
#define SYS_PBCLK_DISABLED                  (0x0100)
#define SYS_PBCLK_DIVISOR_1				    (0)
#define SYS_PBCLK_DIVISOR_2				    (1)
#define SYS_PBCLK_DIVISOR_3				    (2)
#define SYS_PBCLK_DIVISOR_4				    (3)
#define SYS_PBCLK_DIVISOR_5				    (4)
#define SYS_PBCLK_DIVISOR_6				    (5)
#define SYS_PBCLK_DIVISOR_7				    (6)
#define SYS_PBCLK_DIVISOR_8				    (7)
#define SYS_PBCLK_DIVISOR_9				    (8)
#define SYS_PBCLK_DIVISOR_10				(9)
#define SYS_PBCLK_DIVISOR_11				(10)
#define SYS_PBCLK_DIVISOR_12				(11)
#define SYS_PBCLK_DIVISOR_13				(12)
#define SYS_PBCLK_DIVISOR_14				(13)
#define SYS_PBCLK_DIVISOR_15				(14)
#define SYS_PBCLK_DIVISOR_16				(15)
#define SYS_PBCLK_DIVISOR_17				(16)
#define SYS_PBCLK_DIVISOR_18				(17)
#define SYS_PBCLK_DIVISOR_19				(18)
#define SYS_PBCLK_DIVISOR_20				(19)
#define SYS_PBCLK_DIVISOR_21				(20)
#define SYS_PBCLK_DIVISOR_22				(21)
#define SYS_PBCLK_DIVISOR_23				(22)
#define SYS_PBCLK_DIVISOR_24				(23)
#define SYS_PBCLK_DIVISOR_25				(24)
#define SYS_PBCLK_DIVISOR_26				(25)
#define SYS_PBCLK_DIVISOR_27				(26)
#define SYS_PBCLK_DIVISOR_28				(27)
#define SYS_PBCLK_DIVISOR_29				(28)
#define SYS_PBCLK_DIVISOR_30				(29)
#define SYS_PBCLK_DIVISOR_31				(30)
#define SYS_PBCLK_DIVISOR_32				(31)
#define SYS_PBCLK_DIVISOR_33				(32)
#define SYS_PBCLK_DIVISOR_34				(33)
#define SYS_PBCLK_DIVISOR_35				(34)
#define SYS_PBCLK_DIVISOR_36				(35)
#define SYS_PBCLK_DIVISOR_37				(36)
#define SYS_PBCLK_DIVISOR_38				(37)
#define SYS_PBCLK_DIVISOR_39				(38)
#define SYS_PBCLK_DIVISOR_40				(39)
#define SYS_PBCLK_DIVISOR_41				(40)
#define SYS_PBCLK_DIVISOR_42				(41)
#define SYS_PBCLK_DIVISOR_43				(42)
#define SYS_PBCLK_DIVISOR_44				(43)
#define SYS_PBCLK_DIVISOR_45				(44)
#define SYS_PBCLK_DIVISOR_46				(45)
#define SYS_PBCLK_DIVISOR_47				(46)
#define SYS_PBCLK_DIVISOR_48				(47)
#define SYS_PBCLK_DIVISOR_49				(48)
#define SYS_PBCLK_DIVISOR_50				(49)
#define SYS_PBCLK_DIVISOR_51				(50)
#define SYS_PBCLK_DIVISOR_52				(51)
#define SYS_PBCLK_DIVISOR_53				(52)
#define SYS_PBCLK_DIVISOR_54				(53)
#define SYS_PBCLK_DIVISOR_55				(54)
#define SYS_PBCLK_DIVISOR_56				(55)
#define SYS_PBCLK_DIVISOR_57				(56)
#define SYS_PBCLK_DIVISOR_58				(57)
#define SYS_PBCLK_DIVISOR_59				(58)
#define SYS_PBCLK_DIVISOR_60				(59)
#define SYS_PBCLK_DIVISOR_61				(60)
#define SYS_PBCLK_DIVISOR_62				(61)
#define SYS_PBCLK_DIVISOR_63				(62)
#define SYS_PBCLK_DIVISOR_64				(63)
#define SYS_PBCLK_DIVISOR_65				(64)
#define SYS_PBCLK_DIVISOR_66				(65)
#define SYS_PBCLK_DIVISOR_67				(66)
#define SYS_PBCLK_DIVISOR_68				(67)
#define SYS_PBCLK_DIVISOR_69				(68)
#define SYS_PBCLK_DIVISOR_70				(69)
#define SYS_PBCLK_DIVISOR_71				(70)
#define SYS_PBCLK_DIVISOR_72				(71)
#define SYS_PBCLK_DIVISOR_73				(72)
#define SYS_PBCLK_DIVISOR_74				(73)
#define SYS_PBCLK_DIVISOR_75				(74)
#define SYS_PBCLK_DIVISOR_76				(75)
#define SYS_PBCLK_DIVISOR_77				(76)
#define SYS_PBCLK_DIVISOR_78				(77)
#define SYS_PBCLK_DIVISOR_79				(78)
#define SYS_PBCLK_DIVISOR_80				(79)
#define SYS_PBCLK_DIVISOR_81				(80)
#define SYS_PBCLK_DIVISOR_82				(81)
#define SYS_PBCLK_DIVISOR_83				(82)
#define SYS_PBCLK_DIVISOR_84				(83)
#define SYS_PBCLK_DIVISOR_85				(84)
#define SYS_PBCLK_DIVISOR_86				(85)
#define SYS_PBCLK_DIVISOR_87				(86)
#define SYS_PBCLK_DIVISOR_88				(87)
#define SYS_PBCLK_DIVISOR_89				(88)
#define SYS_PBCLK_DIVISOR_90				(89)
#define SYS_PBCLK_DIVISOR_91				(90)
#define SYS_PBCLK_DIVISOR_92				(91)
#define SYS_PBCLK_DIVISOR_93				(92)
#define SYS_PBCLK_DIVISOR_94				(93)
#define SYS_PBCLK_DIVISOR_95				(94)
#define SYS_PBCLK_DIVISOR_96				(95)
#define SYS_PBCLK_DIVISOR_97				(96)
#define SYS_PBCLK_DIVISOR_98				(97)
#define SYS_PBCLK_DIVISOR_99				(98)
#define SYS_PBCLK_DIVISOR_100				(99)
#define SYS_PBCLK_DIVISOR_101				(100)
#define SYS_PBCLK_DIVISOR_102				(101)
#define SYS_PBCLK_DIVISOR_103				(102)
#define SYS_PBCLK_DIVISOR_104				(103)
#define SYS_PBCLK_DIVISOR_105				(104)
#define SYS_PBCLK_DIVISOR_106				(105)
#define SYS_PBCLK_DIVISOR_107				(106)
#define SYS_PBCLK_DIVISOR_108				(107)
#define SYS_PBCLK_DIVISOR_109				(108)
#define SYS_PBCLK_DIVISOR_110				(109)
#define SYS_PBCLK_DIVISOR_111				(110)
#define SYS_PBCLK_DIVISOR_112				(111)
#define SYS_PBCLK_DIVISOR_113				(112)
#define SYS_PBCLK_DIVISOR_114				(113)
#define SYS_PBCLK_DIVISOR_115				(114)
#define SYS_PBCLK_DIVISOR_116				(115)
#define SYS_PBCLK_DIVISOR_117				(116)
#define SYS_PBCLK_DIVISOR_118				(117)
#define SYS_PBCLK_DIVISOR_119				(118)
#define SYS_PBCLK_DIVISOR_120				(119)
#define SYS_PBCLK_DIVISOR_121				(120)
#define SYS_PBCLK_DIVISOR_122				(121)
#define SYS_PBCLK_DIVISOR_123				(122)
#define SYS_PBCLK_DIVISOR_124				(123)
#define SYS_PBCLK_DIVISOR_125				(124)
#define SYS_PBCLK_DIVISOR_126				(125)
#define SYS_PBCLK_DIVISOR_127				(126)
#define SYS_PBCLK_DIVISOR_128				(127)





#endif //READER_SYSTEM_H
