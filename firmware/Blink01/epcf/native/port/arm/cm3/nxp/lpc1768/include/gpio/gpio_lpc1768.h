/**
 * \file    gpio_lpc1768.h
 * \brief   Native GPIO Driver Description for LPC1768.
 *
 */

#ifndef __EPCF_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_INCLUDE_GPIO_GPIO_LPC1768_H
#define __EPCF_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_INCLUDE_GPIO_GPIO_LPC1768_H

#include "gpio_lpc1768_config.h"

#define EPCF_PIN_LPC1768_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_NATIVE_PATH/    \
        ,port/PCF_ARCH_NAME/PCF_ARCH_VARIANT/PCF_ARCH_DEVICE_VENDOR/,PCF_ARCH_DEVICE/include/,pin_lpc1768.h)
#include EPCF_PIN_LPC1768_INCLUDE
#undef EPCF_PIN_LPC1768_INCLUDE



/**
 * The macro is used to set one or more pins on a particular port.
 *
 * \param   port    Port number on which pins to be set. Port numbers defined in portpin.h should be used.
 * \param   pin     Pins to set. Pin numbers defined in portpin.h can be used.
 *                  Multiple pins should be ORed together to set multiple pins on the same port.
 *
 * \note This macro will not affect all the pins on the port. It will affect only the pins selected by user.
 */
#define EPCF_GPIO_PINS_SET(port, pin)                       *((volatile uint32_t*)(GPIO_SET_BASE + (port*0x20))) = (1<<pin)

/**
 * The macro is used to clear one or more pins on a particular port.
 *
 * \param   port    Port number on which pins to be set. Port numbers defined in portpin.h should be used.
 * \param   pin     Pins to set. Pin numbers defined in portpin.h can be used.
 *                  Multiple pins should be ORed together to clear multiple pins on the same port.
 *
 * \note This macro will not affect all the pins on the port. It will affect only the pins selected by user.
 */
#define EPCF_GPIO_PINS_CLEAR(port, pin)                     *((volatile uint32_t*)(GPIO_CLEAR_BASE + (port*0x20))) = (1<<pin)

/**
 * The macro is used to write 32 bit data to a particular port.
 *
 * \param   port    Port number to write. Port numbers defined in portpin.h should be used.
 * \param   data    32 bit Data to write on port. The pins should be mentioned in bit shifted format.
                    For Example: data = 0x00000011 will set BIT_0 and BIT_4 and Clear remaining pins.
 *
 * \note This macro will affect all the pins on the port.
 */
#define EPCF_GPIO_PORT_WRITE(port, data)                    *((volatile uint32_t*)(GPIO_PIN_BASE + (port*0x20))) = data

/**
 * The macro is used to write 16 bit data to a particular port.
 *
 * \param   port      Port number to write. Port numbers defined in portpin.h should be used.
 * \param   data      16 bit Data to write on port. The pins should be mentioned in bit shifted format.
                      For Example: data = 0x0011 will set BIT_0 and BIT_4 and Clear remaining pins.
 * \param   halfword  halfword : 0 (ZERO) to write lower half, 1 (ONE) to write upper half.
 *
 * \note This macro will affect all the pins on the port.
 */
 // IMPORTANT:  Below Macro Need to be tested
#define EPCF_GPIO_PORT_WRITE_WORD(port, data, halfword)         *((volatile uint16_t*)(GPIO_PIN_BASE + (port*0x20) + (halfword * 2))) = data

/**
 *The macro is used to write 8 bit data to a particular port.
 *
 * \param   port    Port number to write. Port numbers defined in portpin.h should be used.
 * \param   data    16 bit Data to write on port. The pins should be mentioned in bit shifted format.
                    For Example: data = 0x11 will set BIT_0 and BIT_4 and Clear remaining pins.
 * \param   byte    Byte number to read (0-3). 0 for Lower Byte and 1 for Higher Byte.
 *
 * \note This macro will affect all the pins on the port.
 */
 // IMPORTANT:  Below Macro Need to be tested
#define EPCF_GPIO_PORT_WRITE_BYTE(port, data, byte)         *((volatile uint8_t*)(GPIO_PIN_BASE + (port*0x20) + byte)) = data

/**
 * The macro is used to read 32 bit data from a particular port.
 *
 * \param   port    Port number to read. Port numbers defined in portpin.h should be used.
 */
#define EPCF_GPIO_PORT_READ(port)                           *((volatile uint32_t*)(GPIO_PIN_BASE + (port*0x20)))

/**
 * The macro is used to read 16 bit data from a particular port.
 *
 * \param   port      Port number to read. Port numbers defined in portpin.h should be used.
 * \param   halfword  0 to read lower half, 1 to read upper half.
 */
#define EPCF_GPIO_PORT_READ_HALF_WORD(port, halfword)       *((volatile uint16_t*)(GPIO_PIN_BASE + (port*0x20) + (halfword * 2)))

/**
 * The macro is used to read 8 bit data from a particular port.
 *
 * \param port Port number to read. Port numbers defined in portpin.h should be used.
 * \param byte Byte number to read (0-3).
 */
#define EPCF_GPIO_PORT_READ_BYTE(port, byte)                *((volatile uint8_t*)(GPIO_PIN_BASE + (port*0x20) + byte))

/**
 * The macro is used to Set Direction of a particular port.
 *
 * \param port  Port number to set direction. Port numbers defined in portpin.h should be used.
 * \param pin Pin or Pins of the Port for setting the direction. Should be in bit shifted format.
 * \param dir direction of the pin or Pins. should be enGpioDirOutput or enGpioDirInput
 */
#define EPCF_GPIO_SET_DIR(port, pin, dir )  dir ?   \
                    (*((uint32_t*)(GPIO_IODIR_BASE + (port*0x20))) |= (1<<pin)) : \
                    (*((uint32_t*)(GPIO_IODIR_BASE + (port*0x20))) &= ~(1<<pin) )


int8_t epcf_gpio_nativeInit(EPCFGpioCfg_t* pConfig);
int8_t epcf_gpio_nativeSet(EPCFGpioDevice_t* pGpiodevice);
int8_t epcf_gpio_nativeClear(EPCFGpioDevice_t* pGpiodevice);
int8_t epcf_gpio_nativeRead(EPCFGpioDevice_t* pGpiodevice);
int8_t epcf_gpio_nativeSetDirection(EPCFGpioDevice_t* pGpiodevice, EnEPCFGpioDirection_t direction);
uint32_t epcf_gpio_nativeGetDeviceCount();

int8_t epcf_gpio_nativeIntEnable(EPCFGpioDevice_t* pGpioDevice);
int8_t epcf_gpio_nativeIntDisable(EPCFGpioDevice_t* pGpioDevice);
int8_t epcf_gpio_nativeIntAttachCallback(EPCFGpioDevice_t* pGpioDevice,epcfCallback_fp pCallback);
int8_t epcf_gpio_nativeIntDetachCallback(EPCFGpioDevice_t* pGpioDevice);
#endif      // __EPCF_INCLUDED_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_GPIO_GPIO_LPC1768_H

/** @} */
