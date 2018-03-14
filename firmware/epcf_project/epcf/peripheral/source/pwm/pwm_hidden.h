/**
 * \file    pwm_hidden.h
 * \brief   hidden header file for PWM Driver Description for LPC1768.
 *          This file is for internal use and will not be shared with the user.
 *
 */

#ifndef __EPCF_PERIPHERAL_SOURCE_PWM_PWM_HIDDEN_H
#define __EPCF_PERIPHERAL_SOURCE_PWM_PWM_HIDDEN_H

typedef struct EPCFPwmController    EPCFPwmController_t;
typedef struct EPCFPwmDevice        EPCFPwmDevice_t;

typedef struct EPCFPwmDevice
{
	EPCFPwmController_t*   controllerConfig;
    uint8_t                 pwmId;
    void*                   pwmChannelAddr;
    EnEPCFPwmWidth_t        pwmWidth;
    EPCFTime_t              resolution;
    EnEPCFBoolean_t         interruptEnable;
#if(EPCF_BUILD_MODE == EPCF_BUILD_EXTENDED)
    uint8_t                 extendedPwmDeviceId;         // ID Returned from the Device.
#endif
}EPCFPwmDevice_t;


#endif      //  __EPCF_PERIPHERAL_SOURCE_PWM_PWM_HIDDEN_H
