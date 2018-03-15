/**
 * \file  peripheral.h
 * \brief This file is to be included by the application program in the begining to use epcf framework.
 */

#ifndef __EPCF_PERIPHERAL_INCLUDE_PERIPHERAL_H
#define __EPCF_PERIPHERAL_INCLUDE_PERIPHERAL_H

// All Peripheral check are done in epcf/common/epcf_peripheral.h
#if(EPCF_USE_SYSCLK == PCF_YES)
	#include "./sysClk/sysClk_config.h"
#endif

#if(EPCF_USE_GPIO == PCF_YES)
	#include "./gpio/gpio_config.h"
#endif

#if (EPCF_USE_UART == PCF_YES)
	#include "./uart/uart_config.h"
#endif

#if (EPCF_USE_TIMER == PCF_YES)
	#include "./timer/timer_config.h"
#endif

#if (EPCF_USE_I2C == PCF_YES)
	#include "./i2c/i2c_config.h"
#endif

#if (EPCF_USE_CAN == PCF_YES)
	#include "./can/can_config.h"
#endif

#if (EPCF_USE_PWM == PCF_YES)
	#include "./pwm/pwm_config.h"
#endif

#if (EPCF_USE_ADC == PCF_YES)
	#include "./adc/adc_config.h"
#endif

#if (EPCF_USE_EXTINT == PCF_YES)
	#include "./extInt/extInt_config.h"
#endif

#if (EPCF_USE_WDT == PCF_YES)
	#include "./wdt/wdt_config.h"
#endif

#if (EPCF_USE_SPI == PCF_YES)
	#include "./spi/spi_config.h"
#endif




//Include all the peripheral config headers here

#endif // __EPCF_PERIPHERAL_INCLUDE_PERIPHERAL_H
