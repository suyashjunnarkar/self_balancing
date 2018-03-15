/**
 * \file    timer_hidden.h
 * \brief   hidden header file for TIMER Driver Description for LPC1768.
 *          This file is for internal use and will not be shared with the user.
 *          It contains TimerDevice and TimerController structure defination.
 *
 */
 
#ifndef __EPCF_PERIPHERAL_SOURCE_TIMER_TIMER_HIDDEN_H
#define __EPCF_PERIPHERAL_SOURCE_TIMER_TIMER_HIDDEN_H

typedef struct EPCFTimerController EPCFTimerController_t;

typedef struct EPCFTimerDevice
{
	EPCFTimerController_t*   controllerConfig;
	uint8_t					timerId;
	void*                   timerChannelAddr;
	EPCFTime_t				resolution;
	EnEPCFTimerWidth_t		timerWidth;
	EnEPCFTimerMode_t		mode;
	EnEPCFBoolean_t			interruptEnable;
#if(EPCF_BUILD_MODE == EPCF_BUILD_EXTENDED)
    uint8_t                 extendedTimerDeviceId;         // ID Returned from the Device.
#endif
}EPCFTimerDevice_t;

#endif      //  __EPCF_PERIPHERAL_SOURCE_TIMER_TIMER_HIDDEN_H
