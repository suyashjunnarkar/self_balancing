/**
 * \file  wdt.h
 * \brief This file is used to configure a Watchdog timer device
 */
 
#ifndef __EPCF_PERIPHERAL_INCLUDE_WDT_WDT_H
#define __EPCF_PERIPHERAL_INCLUDE_WDT_WDT_H

/** \brief  Wdt device    */
typedef struct EPCFWdtDevice EPCFWdtDevice_t;

/** \brief  Enumeration for Wdt width  */
typedef enum
{
    enEPCFWdtWidth_8,           /**< 8-bit wdt                              */
    enEPCFWdtWidth_16,          /**< 16-bit wdt                             */
    enEPCFWdtWidth_32,          /**< 32-bit wdt                             */
    enEPCFWdtWidth_64,          /**< 64-bit wdt                             */
    enEPCFWdtWidth_Max          /**< Special value for boundary checking    */
}EnEPCFWdtWidth_t;

/** \brief Enumeration for current state of watchdog timer  */
typedef enum
{
    enEPCFWdtState_Idle = 0,
    enEPCFWdtState_Stopped,      /**< Wdt is stopped                    */
    enEPCFWdtState_Running,      /**< Wdt is running                    */
    enEPCFWdtState_Max           /**< Special value for boundary checking       */
}EnEPCFWdtState_t;

/** Wdt configuration structure
    Example to configure watchdog timer:
    
    EPCFWdtCfg_t wdtConfig = 
    {
        0,                          // wdt id 0
        enEPCFWdtWidth_8,           // 8-bit wdt width
        {250,enEPCFTimeUnit_ns},    // resolution set to 0.25 microseconds
        NULL                        // No hardware specific config
    };
*/
typedef struct 
{
    uint8_t                 wdtId;              /**< Wdt Id. Refer to platform specific header file for appropriate wdt id          */
    
    EnEPCFWdtWidth_t        wdtWidth;           /**< Specifies the width of the wdt device                                          */

    EPCFTime_t              resolution;         /**< Specifies the resolution for the watchdog timer. Resolution refers to the minimum time which
                                                     is elapsed after every clock cycle. You can define maximum period of timer by setting appropriate
                                                     resolution value.
                                                     Wdt period = resolution x (2^timerWidth).
                                                     For example: Consider an 8-bit timer with resolution = 0.25 microseconds.
                                                                  Then,the maximum period of the timer is equal to 0.25 x 256 = 64 microseconds.
                                                                  To set 0.25 microseconds as the resolution, set time unit to enEPCFTimeUnit_ns
                                                                  and set 250 as the count.
                                                     Refer to platform specific header file for supported values of resolution.
                                                     Refer to "../../common/types.h" header file for the definition of \link EPCFTime_t \endlink structure.     */

    void*                   hardwareCfg;        /**< Hardware platform specific configuration       */
}EPCFWdtCfg_t;



/**
 * \brief This function is used to create a wdt device. Call this function in beginning to initialize the device.
 *        This function allocates memory for the device using malloc() function call and returns a pointer to the device. Pass this device pointer
 *        while calling wdt functions.
 *
 * \param pWdtConfig Pointer to the wdt configuration structure
 *
 * \return On success, it return the pointer to wdt device.
 *         On error, it returns NULL.
 */
extern EPCFWdtDevice_t* epcf_wdt_createNative(EPCFWdtCfg_t* pWdtConfig);

#ifdef	EPCF_SUPPORT_EXTENDED_WDT

/** \brief  wdt controller structure    */
typedef struct EPCFWdtController EPCFWdtController_t;

/**
 *  \brief This function is used to create a wdt device when using extended mode. 
 *  	   Before calling this function, user should create an adapter for communication between host and extended device.
 *         For detail explaination, see ../../../../extended/adapter/adapter.h
 *         Then, user should create a controller for controlling extended device from host.
 *  	   Call this function in beginning to initialize the device.This function allocates memory for the device using malloc() function call and returns a pointer to the device. 
 *         Pass this device pointer while calling wdt functions.
 *  
 *  \param pWdtController Pointer to the wdt controller structure
 *  \param pWdtConfig Pointer to the wdt configuration structure
 *  
 *  \return Returns the number of available wdt devices.
 */
extern EPCFWdtDevice_t* epcf_wdt_createExtended(EPCFWdtController_t* pWdtController, EPCFWdtCfg_t* pWdtConfig);

/**
 * \brief This function is used to get total number of available wdt devices in extended mode.
 *  
 *  \param pWdtController Pointer to the wdt controller structure
 *  
 *  \return Returns the number of available wdt devices.
 */
extern uint8_t epcf_wdt_extGetDeviceCount(EPCFWdtController_t* pWdtController);

#endif	//EPCF_SUPPORT_EXTENDED_WDT

/**
 * \brief This function is used to start watchdog timer device. After the specified timeout a 
 *        wdt event will occur and microcontroller will be reset.
 *
 * \param pWdtDevice Pointer to the wdt device
 * \param timeout    Timeout for watchdog timer device. In case user pass an unsupported value,
 *                   the driver should select the most close predefined timeout value
 *
 * \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 * 
 * \note  Call EPCF_WDT_RESET() function within the timeout value to restart watchdog timer.
 *        Call EPCF_WDT_STOP() function to stop watchdog timer.
 */
extern int8_t epcf_wdt_start(EPCFWdtDevice_t* pWdtDevice,EPCFTime_t timeout);

/**
 * \brief This function is used to stop watchdog timer device. It can be started again by a
 *        call to the function EPCF_WDT_START.
 *
 * \param pWdtDevice Pointer to the wdt device
 *
 * \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_wdt_stop(EPCFWdtDevice_t* pWdtDevice);

/**
 * \brief This function is used to reset the watchdog timer device. User shall call this function continuously
 *        within the timeout value to prevent microcontroller reset.
 *
 * \param pWdtDevice Pointer to the wdt device
 *
 * \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_wdt_reset(EPCFWdtDevice_t* pWdtDevice);

/**
 * \brief This function is used to get the remaining time which is left for timeout of the watchdog timer to 
 *        occur. Call this function after starting the wdt device using EPCF_WDT_START function. This function
 *        has no effect if it has been called before starting the wdt device and an appropriate error message 
 *        will be returned.
 *        For example: Consider an application in which wdt has started with a timeout value set to 5 milliseconds.
 *                     In this case, a wdt event will occur after 5 milliseconds and the microcontroller will be reset.
 *                     Now, if we call EPCF_WDT_GET_REMAINING_TIME_TO_TIMEOUT function after 2 milliseconds of starting
 *                     the wdt device, this function will return the remaining time i.e. (5ms - 2ms) equal to 3 milliseconds.
 *
 * \param pWdtDevice Pointer to the wdt device
 * \param time       Pointer to EPCFTime_t variable to get time value.
 *
 * \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_wdt_getRemainingTimeToTimeout(EPCFWdtDevice_t* pWdtDevice,EPCFTime_t* time);

/**
 * \brief This function is used to get the current state of the watchdog timer.
 *        Wdt can be started by a call to the function EPCF_WDT_START.
 *        Wdt can be stopped by a call to the function EPCF_WDT_STOP.
 * 
 * \param pWdtDevice Pointer to the wdt device
 *
 * \return return watchdog timer state
 */
extern EnEPCFWdtState_t epcf_wdt_getState(EPCFWdtDevice_t* pWdtDevice);

/**
 * \brief This function is used to close the wdt device. It will free all the memory allocated by the wdt device.
 *
 * \param pWdtDevice Pointer to the wdt device
 *
 * \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_wdt_close(EPCFWdtDevice_t* pWdtDevice);

/**
 * \brief This function is used to get total number of available wdt devices.
 *
 * \return Returns the number of available wdt devices.
 */
extern uint8_t epcf_wdt_getDeviceCount();



#ifdef EPCF_USING_MT_ENV
//ToDo: Adding support for EPCF_USING_MT_ENV
//ToDo: Add comment for function description
extern int8_t epcf_wdt_lock(EPCFWdtDevice_t* pWdtDevice);
extern int8_t epcf_wdt_unlock(EPCFWdtDevice_t* pWdtDevice);

#endif	//EPCF_USING_MT_ENV

#endif  //__EPCF_PERIPHERAL_INCLUDE_WDT_WDT_H
