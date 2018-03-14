/**
 * \file    uart_lpc1768_config.h
 * \brief   Native UART Driver Configuration for LPC1768.
 *
 */
#ifndef __EPCF_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_INCLUDE_UART_UART_LPC1768_CONFIG_H
#define __EPCF_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_INCLUDE_UART_UART_LPC1768_CONFIG_H


/**  \brief Platform specific structure for LPC1768 */
typedef struct EPCFUartLpc1768Cfg
{
  EPCFPortPin_t           uartTxPin;     /**< Pin discription of UartTx pin and port        */
  EPCFPortPin_t           uartRxPin;     /**< Pin discription of UartRx pin and port        */
}EPCFUartLpc1768Cfg_t;

/** \brief ARCH SPECIFIC Configuration macros       */
#define UART0_CH            UART0
#define UART1_CH            UART1
#define UART2_CH            UART2
#define UART3_CH            UART3

#define UART0_CHANNEL       PERIPH(UART0_CH)
#define UART1_CHANNEL       PERIPH(UART1_CH)
#define UART2_CHANNEL       PERIPH(UART2_CH)
#define UART3_CHANNEL       PERIPH(UART3_CH)

#define UART0_INT_HANDLER   PCF_CONCATE(UART0,_IRQHandler)
#define UART1_INT_HANDLER   PCF_CONCATE(UART1,_IRQHandler)
#define UART2_INT_HANDLER   PCF_CONCATE(UART2,_IRQHandler)
#define UART3_INT_HANDLER   PCF_CONCATE(UART3,_IRQHandler)


#define PWR_UART0       (1<<3)
#define PWR_UART1       (1<<4)
#define PWR_UART2       (1<<24)
#define PWR_UART3       (1<<25)

#define	PWR_UART_CH(X)		PCF_CONCATE(PWR_,X)
#define PCLK_DIV(X)         PCF_CONCATE(PCLK_DIV_,X)
#define PERIPH(X)			PCF_CONCATE(PERIPH_,X)
#define POWER_ON(X) 		PERIPH_SC->PCONP |= X
#define POWER_OFF(X) 		PERIPH_SC->PCONP &= ~(X)
#define IRQ_NUM(X)			PCF_CONCATE(X,_IRQn)

#endif      // __EPCF_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_INCLUDE_UART_UART_LPC1768_CONFIG_H
