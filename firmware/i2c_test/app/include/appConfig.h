/**
 * \file  appConfig.h
 * \brief This file is used to configure the application
 */

#ifndef __$USERPROJECT$_INCLUDE_APP_CONFIG_H
#define __$USERPROJECT$_INCLUDE_APP_CONFIG_H

#define DELAY()                     delay()
#define UART_PRINT  1

#if(UART_PRINT == 1)
#define APP_DEBUG(x)        //print debug msg over UART
#else
#define APP_DEBUG(x)
#endif

extern int8_t appInit(void);        //defined in appConfig.c
extern void delay(void);        //defined in appConfig.c
extern void serialBegin() ;
extern int32_t serialPrint(char x[]);

#endif  // __$USERPROJECT$_INCLUDE_APP_CONFIG_H
