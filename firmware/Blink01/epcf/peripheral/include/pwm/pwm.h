/**
 * \file  pwm.h
 * \brief This file is used to configure a PWM device
 */
 
#ifndef __EPCF_PERIPHERAL_INCLUDE_PWM_PWM_H
#define __EPCF_PERIPHERAL_INCLUDE_PWM_PWM_H

/** \brief  Pwm device    */
typedef struct EPCFPwmDevice EPCFPwmDevice_t;

/** \brief  Enumeration for Channel number  */
typedef enum
{
    enEPCFPwmChannel_0=0,       /**< Channel number 0       */
    enEPCFPwmChannel_1,     /**< Channel number 1       */
    enEPCFPwmChannel_2,     /**< Channel number 2       */
    enEPCFPwmChannel_3,     /**< Channel number 3       */
    enEPCFPwmChannel_4,     /**< Channel number 4       */
    enEPCFPwmChannel_5,     /**< Channel number 5       */
    enEPCFPwmChannel_6,     /**< Channel number 6       */
    enEPCFPwmChannel_7,     /**< Channel number 7       */
    enEPCFPwmChannel_8,     /**< Channel number 8       */
    enEPCFPwmChannel_9,     /**< Channel number 9       */
    enEPCFPwmChannel_10,    /**< Channel number 10      */
    enEPCFPwmChannel_11,    /**< Channel number 11      */
    enEPCFPwmChannel_12,    /**< Channel number 12      */
    enEPCFPwmChannel_13,    /**< Channel number 13      */
    enEPCFPwmChannel_14,    /**< Channel number 14      */
    enEPCFPwmChannel_15,    /**< Channel number 15      */
    enEPCFPwmChannel_Max    /**< Special value for boundary checking    */
}EnEPCFPwmChannel_t;

/** \brief  Enumeration for Pwm width  */
typedef enum
{
    enEPCFPwmWidth_8,       /**< 8-bit pwm  device      */
    enEPCFPwmWidth_16,      /**< 16-bit pwm device      */
    enEPCFPwmWidth_32,      /**< 32-bit pwm device      */
    enEPCFPwmWidth_64,      /**< 64-bit pwm device      */
    enEPCFPwmWidth_Max      /**< Special value for boundary checking    */
}EnEPCFPwmWidth_t;

/**
 * \brief Enumeration for Pwm signal generated on the output pin.
 */
typedef enum
{
    enEPCFPwmOutputSignal_Normal,       /**< Normal signal output                   */
    enEPCFPwmOutputSignal_Inverted,     /**< Inverted signal output                 */
    enEPCFPwmOutputSignal_Max           /**< Special value for boundary checking    */
}EnEPCFPwmOutputSignal_t;

/** \brief Enumeration for interrupt source */
typedef enum
{
    enEPCFPwmPulse_Start,           /**< Interrupt when pwm pulse starts        */
    enEPCFPwmPulse_End,             /**< Interrupt when pwm pulse ends          */
    enEPCFPwmInterruptSource_Max,   /**< Special value for boundary checking    */
}EnEPCFPwmInterruptSource_t;

/** \brief Enumeration for current state of pwm */
typedef enum
{
    enEPCFPwmState_Stopped = 0,   /**< pwm is stopped, no user callback will get called		 */
    enEPCFPwmState_Running,       /**< pwm is running (operational), user callback(s) will get called at respective period */
    enEPCFPwmState_Max            /**< Special value for boundary checking 		*/
}EnEPCFPwmState_t;

/** \brief  Pwm configuration structure
    Example to configure pwm:
    
    EPCFPwmCfg_t pwmConfig = 
    {
        0,                          // pwm id 0
        enEPCFPwmWidth_8,           // 8-bit pwm width
        {250,enEPCFTimeUnit_ns},    // resolution set to 0.25 microseconds
        enEPCFBooleanTrue,          // enable interrupt
        NULL                        // No hardware specific config
    };
*/
typedef struct 
{
    uint8_t                 pwmId;              /**< Pwm Id. Refer to platform specific header file for appropriate pwm id              */

    EnEPCFPwmWidth_t        pwmWidth;           /**< Specifies the width of the pwm device                                              */

    EPCFTime_t              resolution;         /**< Specifies the resolution for the pwm. Resolution refers to the mimimum time which
                                                     is elapsed after every clock cycle. You can define maximum period of pwm by setting appropriate
                                                     resolution value. Also,frequency of the pwm device is inverse of the pwm period.
                                                     Pwm period     = resolution x (2^pwmWidth).
                                                     Pwm frequency  = 1/Pwm period
                                                     For example: Consider an 8-bit pwm device with resolution = 0.25 microseconds.
                                                                  Then,the maximum period of the pwm device is equal to 0.25 x 256 = 64 microseconds.
                                                                  To set 0.25 microseconds as the resolution, set time unit to enEPCFTimeUnit_ns
                                                                  and set 250 as the count.
                                                                  Maximum Pwm frequency = 1/64 microseconds = 15.6khz
                                                     Refer to platform specific header file for supported values of resolution.
                                                     Refer to "../../common/types.h" header file for the definition of \link EPCFTime_t \endlink structure.     */

    EnEPCFBoolean_t         interruptEnable;    /**< Specifies to enable pwm interrupt or not
                                                     enEPCFBooleanTrue  = To enable pwm interrupt
                                                     enEPCFBooleanFalse = To disable pwm interrupt  */
    
    void*                   hardwareCfg;        /**< Hardware platform specific configuration,  Pass NULL for default configuration     */
}EPCFPwmCfg_t;



/**
 * \brief This function is used to create a pwm device. Call this function in beginning to initialize the pwm device.
 *        This function allocates memory for the device using malloc() function call and returns a pointer to the device. Pass this device pointer 
 *        while calling pwm functions.
 *
 * \param pPwmConfig Pointer to the pwm configuration structure.
 *
 * \return On success, it returns a pointer to the pwm device.
 *         On error, it returns NULL. 
 */
extern EPCFPwmDevice_t* epcf_pwm_createNative(EPCFPwmCfg_t* pPwmConfig);

#ifdef	EPCF_SUPPORT_EXTENDED_PWM

/** \brief  pwm controller structure    */
typedef struct EPCFPwmController EPCFPwmController_t;

/**
 *  \brief This function is used to create a pwm device in extended mode.
 *  		Before calling this function, user should create an adapter for communication between host and extended device.
 *        	For detail explaination, see ../../../../extended/adapter/adapter.h
 *        	Then, user should create a controller for controlling extended device from host.
 *   	  	Call this function in beginning to initialize the pwm device. This function allocates memory for the device using malloc() function call and returns a pointer to the device.
 *  		Pass this device pointer while calling pwm functions.
 *
 *  \param pPwmController Pointer to the pwm controller structure.
 *  \param pPwmConfig Pointer to the pwm configuration structure.
 *
 *  \return On success, it returns a pointer to the pwm device.
 *         On error, it returns NULL. 
 */
extern EPCFPwmDevice_t* epcf_pwm_CreateExtended(EPCFPwmController_t* pPwmController, EPCFPwmCfg_t* pPwmConfig);

/**
 *  \brief This function is used to get the total number of available pwm devices.
 *  
 *  \param pPwmController Pointer to the pwm controller structure.
 *
 *  \return Returns the number of available pwm devices.
 */
extern uint8_t epcf_pwm_extGetDeviceCount(EPCFPwmController_t* pPwmController);

#endif

/**
 * \brief This function is used to start the pwm device. Pwm starts generating the output signal according to
 *  channel configuration. It can be stopped by a call to the function epcf_pwm_stop.
 *
 * \param pPwmDevice Pointer to the pwm device.
 *
 * \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_pwm_start(EPCFPwmDevice_t* pPwmDevice);

/**
 * \brief This function is used to stop the running pwm device. The pwm signal is stopped and can be started again by a
 *        call to the function epcf_pwm_start.
 *
 * \param pPwmDevice Pointer to the pwm device.
 *
 * \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_pwm_stop(EPCFPwmDevice_t* pPwmDevice);

/**
 * \brief This function is used to attach a pwm callback for the specific pwm interrupt source.
 *
 * \param pPwmDevice        Pointer to the pwm device returned after successful creation of the pwm device
 * \param interruptSource   Interrupt source for the callback.
 * \param callback          User callback to be called at the specified interrupt source
 * \param channel           Pwm output channel
 *
 * \return return callback Id.
 *
 * \note Call this function before starting the pwm device using epcf_pwm_start function.
 *       To attach a callback if pwm has already started: 
 *       1. Stop the pwm device.
 *       2. Attach a callback.
 *       3. Start the pwm device again.
 */
extern int8_t epcf_pwm_attachCallback(EPCFPwmDevice_t* pPwmDevice,EnEPCFPwmChannel_t channel,EnEPCFPwmInterruptSource_t interruptSource,epcfCallback_fp callback);

/**
 * \brief This function is used to detach the pwm callback for the specific pwm interrupt source.
 *
 * \param pPwmDevice        Pointer to the pwm device.
 * \param callbackId        callbackId returned by epcf_pwm_attachCallback function.
 *
 * \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 *
 * \note Call this function before starting the pwm device using epcf_pwm_start function.
 *       To detach a callback if pwm has already started: 
 *       1. Stop the pwm device.
 *       2. Detach the callback.
 *       3. Start the pwm device again.
 */
extern int8_t epcf_pwm_detachCallback(EPCFPwmDevice_t* pPwmDevice,uint8_t callbackId);

/**
 * \brief This function is used to change period of the pwm device. A period is the time it takes for a signal to complete
 *        an on-and-off cycle. Period value should be less than the maximum pwm period which is defined by the resolution value
 *        in pwm configuration.
 * 
 * \param pPwmDevice    Pointer to the pwm device.
 * \param period        Period of the pwm device.
 * 
 * \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 *
 * \note Call this function before starting the pwm device using epcf_pwm_start function.
 *
 * \remark Refer to platform specific header file for the actual behaviour of this function.
 */
extern int8_t epcf_pwm_setPeriod(EPCFPwmDevice_t* pPwmDevice,EPCFTime_t period);

/**
 * \brief This function is used to enable pwm output channel and pulse width. It can be used to generate a pwm signal for a specific pulse width
 *        on the respective pwm channel.
 *
 * \param pPwmDevice    Pointer to the pwm device.
 * \param channel       Pwm output channel.
 * \param dutyCycle     Set the duty cycle of the pwm signal.
 * \param signal        To select whether the normal or inverted signal will occur on the pwm output pin.
 *
 * \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 *
 * \note Call this function before starting the pwm device using epcf_pwm_start function.
 */
extern int8_t epcf_pwm_setDutyCycle(EPCFPwmDevice_t* pPwmDevice,EnEPCFPwmChannel_t channel,uint8_t dutyCycle,EnEPCFPwmOutputSignal_t signal);

/**
 * \brief This function is used to close the pwm device. It will free the memory allocated by the pwm device.
 *
 * \param pPwmDevice Pointer to the pwm device.
 *
 * \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_pwm_close(EPCFPwmDevice_t* pPwmDevice);

/**
 * \brief This function is used to get the total number of available pwm devices.
 *
 * \return Returns the number of available pwm devices.
 */
extern uint8_t epcf_pwm_getDeviceCount();

/**
 * \brief This function is used to get the current state of the pwm.
 * 
 * \param pPwmDevice Pointer to the pwm device.
 *
 * \return return pwm state
 */
extern EnEPCFPwmState_t epcf_pwm_getState(EPCFPwmDevice_t* pPwmDevice);


#ifdef EPCF_USING_MT_ENV
//ToDo: Adding support for EPCF_USING_MT_ENV
//ToDo: Add comment for function description
extern int8_t epcf_uart_lock(EPCFPwmDevice_t* pPwmDevice);
extern int8_t epcf_uart_unlock(EPCFPwmDevice_t* pPwmDevice);

#endif	//EPCF_USING_MT_ENV


#endif      //__EPCF_PERIPHERAL_INCLUDE_PWM_PWM_H
