/**
 * \file  uart_controller.h
 * \brief This file is used to create UART controller.
 */

#ifndef __EPCF_INCLUDED_EXTENDED_CONTROLLER_UART_UART_CONTROLLER_H
#define __EPCF_INCLUDED_EXTENDED_CONTROLLER_UART_UART_CONTROLLER_H


typedef struct EPCFAdapter EPCFAdapter_t;
typedef struct EPCFUartController EPCFUartController_t;
typedef struct EPCFUartDevice EPCFUartDevice_t;

#define CMD_UART_ACK					0
#define CMD_UART_INIT					1
#define CMD_UART_CLOSE					2
#define CMD_UART_WRITE					3
#define CMD_UART_WRITE_STRING			4
#define CMD_UART_READ					5
#define CMD_UART_GET_DEVICE_COUNT		6
#define CMD_UART_GET_RX_BUFFER_COUNT	7
#define CMD_UART_GET_RX_BUFFER_FLUSH	8
#define CMD_UART_GET_TX_BUFFER_COUNT	9
#define CMD_UART_GET_TX_BUFFER_FLUSH	10
#define CMD_UART_WRITE_BLOCKING			11
#define CMD_UART_GET_HARDWARE_CFG_SIZE  12

EPCFUartController_t* epcfCreateUartController(EPCFAdapter_t *pAdapter);

#endif //__EPCF_INCLUDED_EXTENDED_CONTROLLER_UART_UART_CONTROLLER_H


