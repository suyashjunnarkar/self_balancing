/**
 * \file  epcf_time.h
 * \brief This file defines time interface
 */

#ifndef __EPCF_UTILIS_INCLUDE_EPCF_TIME_H
#define __EPCF_UTILIS_INCLUDE_EPCF_TIME_H

/** \brief  Enumeration for Timer width         */
typedef enum
{
    enEPCFTimerDelayWidth_8 = 0,        /**< 8-bit timer.Timer count MIN=0x00, MAX=0xFF                                 */
    enEPCFTimerDelayWidth_16,       /**< 16-bit timer.Timer count MIN=0x0000, MAX=0xFFFF                            */
    enEPCFTimerDelayWidth_32,       /**< 32-bit timer.Timer count MIN=0x00000000, MAX=0xFFFFFFFF                    */
    enEPCFTimerDelayWidth_64,       /**< 64-bit timer.Timer count MIN=0x0000000000000000, MAX=0xFFFFFFFFFFFFFFFF    */
    enEPCFTimerDelayWidth_Max       /**< Special value for boundary checking                                        */
}EnEPCFTimerDelayWidth_t;

typedef struct
{
    uint8_t                 timerId;            /**< Timer Id. Refer to platform specific header file for appropriate timer id  */

    EnEPCFTimerDelayWidth_t     timerWidth;         /**< Specifies the width of the timer                                           */
}EPCFTimeCfg_t;

/** Time Stamp Structure */
typedef struct
{
    uint32_t    time_sec;
    uint32_t    time_nanoSec;
}EPCFTimeStamp_t;

/** Tick return Structure */
typedef struct
{
    uint32_t    cycles;
    uint32_t    tickValue;
}EPCFTick_t;

/**
 * \brief This function is used initialize the time interface. Call this function while initializing the system in the beginning.
 *        This function configures the timer for the system and then starts the timer.
 *
 * \param pTimeConfig Pointer to the time configuration structure.
 *  
 * \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
*/
extern int8_t epcf_time_init(EPCFTimeCfg_t* pTimeConfig);

/**
 * \brief This function is used to get the CPU time since epcf_time_init() function is called.
 *
 * \param time Pointer to EPCFTimeStamp_t variable to get time value.
 *
 * \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
*/

extern int8_t epcf_getCpuTime(EPCFTimeStamp_t* time);

/**
 * \brief This function is used to generate a delay in milli seconds.
 *          This function gives error of +20 micro seconds.
 *
 * \param delayMs Delay value
 *
 * \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
*/
extern int8_t epcf_delayMilliSec(uint32_t delayMs);

/**
 * \brief This function is used to generate a delay in micro seconds.
 *          This function gives error of +20 micro seconds.
 *
 * \param delayUs Delay value
 *
 * \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
*/
extern int8_t epcf_delayMicroSec(uint32_t delayUs);

/**
 * \brief This function is used to set timeout value in ticks.
 *
 * \param timeoutValue Timeout value in EPCFTick_t structure
 *
 * \return return time value at which timeout will occur.
*/
extern EPCFTick_t epcf_setTimeout(EPCFTick_t timeoutValue);

/**
 * \brief This function is used to check whether timeout is occurred or not.
 *
 * \param timeoutValue pass the return value of epcf_setTimeout function
 *
 * \return if timeout is occurred, return enEPCFBoolean_True
 *          else return enEPCFBoolean_False
*/
extern EnEPCFBoolean_t epcf_checkTimeout(EPCFTick_t timeoutValue);

#endif  //__EPCF_UTILIS_INCLUDE_EPCF_TIME_H
