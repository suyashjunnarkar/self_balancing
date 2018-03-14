#ifndef __EPCF_INCLUDED_PERIPHERAL_COMMON_BIT_MASK_H
#define __EPCF_INCLUDED_PERIPHERAL_COMMON_BIT_MASK_H

/** Bit definitions			*/
#define BIT_0		0
#define BIT_1		1
#define BIT_2		2
#define BIT_3		3
#define BIT_4		4
#define BIT_5		5
#define BIT_6		6
#define BIT_7		7
#define BIT_8		8
#define BIT_9		9
#define BIT_10		10
#define BIT_11		11
#define BIT_12		12
#define BIT_13		13
#define BIT_14		14
#define BIT_15		15
#define BIT_16		16
#define BIT_17		17
#define BIT_18		18
#define BIT_19		19
#define BIT_20		20
#define BIT_21		21
#define BIT_22		22
#define BIT_23		23
#define BIT_24		24
#define BIT_25		25
#define BIT_26		26
#define BIT_27		27
#define BIT_28		28
#define BIT_29		29
#define BIT_30		30
#define BIT_31		31

/** Bit mask
 * 	x: bit number
 */
#define BIT_MASK(x)			((uint32_t)1<<x)

/**	Inverted bit mask
 * 	x: bit number
 */
#define INV_BIT_MASK(x)		(~BIT_MASK(x))

#endif /* __EPCF_INCLUDED_PERIPHERAL_COMMON_BIT_MASK_H */
