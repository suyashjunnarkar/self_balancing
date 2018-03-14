/**
 * \file    gpio_lpc1768.h
 * \brief   Native GPIO Driver Description for LPC1768.
 *
 */

#ifndef __EPCF_INCLUDED_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_PIN_LPC1768_H
#define __EPCF_INCLUDED_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_PIN_LPC1768_H

/**
 *  LPC1768 has the following ports and each port has 32 pins:
 *  1.  PORT 0
 *  2.  PORT 1
 *  3.  PORT 2
 *  4.  PORT 3
 *  5.  PORT 4
 *  Refer to portpin.h header file for port and pin MACROS.
*/
#define EPCF_LPC1768_MAX_PORT  5
//Undefine rest of the port and pin MACROS
#undef EPCF_PORT_5
#undef EPCF_PORT_6
#undef EPCF_PORT_7
#undef EPCF_PORT_8
#undef EPCF_PORT_9
#undef EPCF_PORT_10
#undef EPCF_PORT_11
#undef EPCF_PORT_12
#undef EPCF_PORT_13
#undef EPCF_PORT_14
#undef EPCF_PORT_15
#undef EPCF_PORT_16

#define MAX_PINS_PER_PORT         32

/** PIN configuration structure.        */

typedef struct EPCFPinCfg
{
    EPCFPortPin_t   portPin;      /**< Port Pin                         */
    uint32_t        direction;    /**< Pin direction, 1:output 0:input  */
    uint32_t        mode;         /**< Pin pull up/down mode            */
    uint32_t        openDrain;    /**< Pin Open Drain on/off            */
    uint32_t        altFunction;  /**< Alternate Function               */
}EPCFPinCfg_t;

extern int8_t epcfPinInit(EPCFPinCfg_t *pConfig);

#endif      // __EPCF_INCLUDED_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_PIN_LPC1768_H
