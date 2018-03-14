/*
 * \file  portpin.h
 * \brief This file is used to define port and pin
 */

#ifndef __EPCF_INCLUDED_PERIPHERAL_COMMON_PORTPIN_H
#define __EPCF_INCLUDED_PERIPHERAL_COMMON_PORTPIN_H

/**
 * Port number definitions
 */
 
#define EPCF_PORT_0                 0
#define EPCF_PORT_1                 1
#define EPCF_PORT_2                 2
#define EPCF_PORT_3                 3
#define EPCF_PORT_4                 4
#define EPCF_PORT_5                 5
#define EPCF_PORT_6                 6
#define EPCF_PORT_7                 7
#define EPCF_PORT_8                 8
#define EPCF_PORT_9                 9
#define EPCF_PORT_10                10
#define EPCF_PORT_11                11
#define EPCF_PORT_12                12
#define EPCF_PORT_13                13
#define EPCF_PORT_14                14
#define EPCF_PORT_15                15
#define EPCF_PORT_16                16

/**
 * Pin number definitions
 */

#define EPCF_PIN_0                  0
#define EPCF_PIN_1                  1
#define EPCF_PIN_2                  2
#define EPCF_PIN_3                  3
#define EPCF_PIN_4                  4
#define EPCF_PIN_5                  5
#define EPCF_PIN_6                  6
#define EPCF_PIN_7                  7
#define EPCF_PIN_8                  8
#define EPCF_PIN_9                  9
#define EPCF_PIN_10                 10
#define EPCF_PIN_11                 11
#define EPCF_PIN_12                 12
#define EPCF_PIN_13                 13
#define EPCF_PIN_14                 14
#define EPCF_PIN_15                 15
#define EPCF_PIN_16                 16
#define EPCF_PIN_17                 17
#define EPCF_PIN_18                 18
#define EPCF_PIN_19                 19
#define EPCF_PIN_20                 20
#define EPCF_PIN_21                 21
#define EPCF_PIN_22                 22
#define EPCF_PIN_23                 23
#define EPCF_PIN_24                 24
#define EPCF_PIN_25                 25
#define EPCF_PIN_26                 26
#define EPCF_PIN_27                 27
#define EPCF_PIN_28                 28
#define EPCF_PIN_29                 29
#define EPCF_PIN_30                 30
#define EPCF_PIN_31                 31

/** Structure to define a pin from a port       
 *  Use MACROS defined in pinPort.h header file. 
 */
typedef struct
{
   uint8_t port;
   uint8_t pin;
}EPCFPortPin_t;

/** Enumeration for multiplexed pin functionality		*/
// typedef enum EnEPCFAltFunction
// {
	// enEPCFGpioFunctionGpio = 0,		/**< configure pin as GPIO							*/
	// enEPCFGpioFunctionAlt1,			/**< configure pin for alternate function 1			*/
	// enEPCFGpioFunctionAlt2,			/**< configure pin for alternate function 2			*/
	// enEPCFGpioFunctionAlt3,			/**< configure pin for alternate function 3			*/
	// enEPCFGpioFunctionAlt4,			/**< configure pin for alternate function 4			*/
	// enEPCFGpioFunctionAlt5,			/**< configure pin for alternate function 5			*/
	// enEPCFGpioFunctionAlt6,			/**< configure pin for alternate function 6			*/
	// enEPCFGpioFunctionAlt7			/**< configure pin for alternate function 7			*/
// }EnEPCFAltFunction_t;

#endif          // __EPCF_INCLUDED_PERIPHERAL_COMMON_PORTPIN_H
