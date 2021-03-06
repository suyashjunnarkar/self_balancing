/**
 *  \file       app_config.c
 *  \brief      Configuration settings to use GPIO device in extended mode from EduARM side
 *
 */

#include "pcf.h"
#include "appConfig.h"

EPCFSysClkDevice_t *myClock;
EPCFGpioDevice_t   *myGpio;
EPCFGpioDevice_t   *LED;
EPCFGpioDevice_t   *myLED;
EPCFGpioDevice_t   *Switch;
EPCFUartDevice_t   *myUART; 

EPCFSysClkCfg_t myClockCfg =
{
    100000000,
    12000000,
    enEPCFPllClkSrcMainOSC
};

EPCFGpioCfg_t myGpioCfg =
{
	{0, 26},
	enEPCFGpioDirection_Output,
	enEPCFGpioPinMode_PullUp,
    enEPCFGpioOpenDrain_Disable,
};

EPCFGpioCfg_t LED_Config=
{
	{0, 25},
	enEPCFGpioDirection_Output,
	enEPCFGpioPinMode_PullUp,
	enEPCFGpioOpenDrain_Disable,
};

EPCFGpioCfg_t myLED_Config=
{
    {4, 29},
    enEPCFGpioDirection_Output,
    enEPCFGpioPinMode_PullUp,
    enEPCFGpioOpenDrain_Disable,
};

EPCFGpioCfg_t Switch_Config=
{
	{0,24},
	enEPCFGpioDirection_Input,
	enEPCFGpioPinMode_PullUp,
	enEPCFGpioOpenDrain_Disable,
};


/** Uart config Structure */
EPCFUartLpc1768Cfg_t uartHWCfg =
{
    {EPCF_PORT_0, EPCF_PIN_2},      //TX
    {EPCF_PORT_0, EPCF_PIN_3},      //RX
};

EPCFUartCfg_t uart_Config = 
{
    0,
    enEPCFUartBaudrate_115200,
    enEPCFUartDatabits_8,
    enEPCFUartParity_None,
    enEPCFUartStopBits_1,
    enEPCFBoolean_False,
    0,
    0,
    (EPCFUartLpc1768Cfg_t*)&uartHWCfg,
};





void delay(void)
{
    uint32_t index=0;
    for(index=0; index<50000000;index++);
}

int8_t appInit(void)
{
    myClock = epcfCreateSysClk(&myClockCfg);
    if(myClock == NULL)
    {
        APP_DEBUG("Error in creating SysClk!");
        return -1;
    }

    myUART = epcf_uart_createNative(&uart_Config);
    myGpio = epcf_gpio_createNative(&myGpioCfg);
	LED = epcf_gpio_createNative(&LED_Config);
    myLED = epcf_gpio_createNative(&myLED_Config);
	Switch = epcf_gpio_createNative(&Switch_Config);

	
    if((LED == NULL) || (Switch == NULL) || (myGpio == NULL))
    {
        APP_DEBUG("Error in Initializing GPIO!\n");
        return -1;
    }
    else
    {
        APP_DEBUG("GPIO Initialized!\n");
    }

    return 0;
}
