#ifndef __EPCF_INCLUDED_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_SYSCLK_SYSCLK_LPC1768_CONFIG_H
#define __EPCF_INCLUDED_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_SYSCLK_SYSCLK_LPC1768_CONFIG_H

/** Peripheral for clock division */
/** Bit defines for PCLKSEL registers		*/
#define PCLK_DIV_WDT			0
#define PCLK_DIV_TIMER0			2
#define PCLK_DIV_TIMER1			4
#define PCLK_DIV_UART0			6
#define PCLK_DIV_UART1			8
// Bit 10:11 in PCLKSEL0 are reserved
#define PCLK_DIV_PWM1			12
#define PCLK_DIV_I2C0			14
#define PCLK_DIV_SPI			16
// Bit 18:19 in PCLKSEL0 are reserved
#define PCLK_DIV_SSP1			20
#define PCLK_DIV_DAC			22
#define PCLK_DIV_ADC			24
#define PCLK_DIV_CAN1			26
#define PCLK_DIV_CAN2			28
#define PCLK_DIV_ACF			30
#define PCLK_DIV_QEI			32
#define PCLK_DIV_GPIOINT		34
#define PCLK_DIV_PCB			36
#define PCLK_DIV_I2C1			38
// Bit 8:9 in PCLKSEL1 are reserved
#define PCLK_DIV_SSP0			42
#define PCLK_DIV_TIMER2			44
#define PCLK_DIV_TIMER3			46
#define PCLK_DIV_UART2			48
#define PCLK_DIV_UART3			50
#define PCLK_DIV_I2C2			52
#define PCLK_DIV_I2S			54
// Bit 24:25 in PCLKSEL1 are reserved
#define PCLK_DIV_RIT			58
#define PCLK_DIV_SYSCON			60
#define PCLK_DIV_MCPWM			62

#define SYSCLK_SC_OSCSTAT		0x00000040      /**< main oscillator state         			*/
#define PLL_PLLC0_STAT			0x02000000      /**< Read-back for the PLL0 Connect bit		*/
#define PLL_PLLE0_STAT			0x01000000   	/**< Read-back for the PLL0 Enable bit.		*/
#define PLL_PLOCKO				0x04000000      /**< Reflects the PLL0 Lock status			*/

#endif			// __EPCF_INCLUDED_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_SYSCLK_SYSCLK_LPC1768_CONFIG_H
/** @} */



