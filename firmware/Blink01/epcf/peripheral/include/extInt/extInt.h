/**
 *  \file  extInt.h
 *  \brief This file is used to configure an External Interrupt device
 */

#ifndef __EPCF_INCLUDE_PERIPHERAL_INCLUDE_EXTINT_EXTINT_H
#define __EPCF_INCLUDE_PERIPHERAL_INCLUDE_EXTINT_EXTINT_H

/** \brief External interrupt device   */
typedef struct EPCFExtIntDevice EPCFExtIntDevice_t;

/** \brief  Enumeration for external interrupt mode */
typedef enum
{
    enEPCFExtIntMode_FallingEdge,       /**< Falling edge triggered interrupt       */
    enEPCFExtIntMode_RisingEdge,        /**< Rising edge triggered interrupt        */
    enEPCFExtIntMode_BothEdge,          /**< Interrupt on both edge                 */
    enEPCFExtIntMode_LowLevel,          /**< Low level triggered interrupt          */
    enEPCFExtIntMode_HighLevel,         /**< High level triggered interrupt         */
    enEPCFExtIntMode_Max                /**< Special value for boundary checking    */  
}EnEPCFExtIntMode_t;

/**
 *  \brief  External interrupt configuration structure
 *  
 *  Example to configure external Interrupt device:
 *   
 *  EPCFExtIntCfg_t extIntConfig = 
 *  {
 *      0,                              // extInt id 0
 *      enEPCFExtIntMode_RisingEdge,    // trigger interrupt on every rising edge
 *      NULL                            // No hardware specific config
 *  };
 */
typedef struct
{
    uint8_t                 extIntId;       /** External interrupt Id. Refer to platform specific header file for appropriate interrupt id  */
    
    EnEPCFExtIntMode_t      mode;           /** External interrupt mode                         */
    
    void*                   hardwareCfg;    /** Hardware platform specific configuration, Pass NULL for default configuration   */
}EPCFExtIntCfg_t;

/**
 *  \brief This function is used to create an external interrupt device. Call this function in beginning to initialize the external interrupt.
 *         This function allocates memory for the device using malloc() function call and returns a pointer to the device. Pass this device pointer 
 *         while calling external interrupt functions.
 *
 *  \param pExtIntConfig Pointer to the external interrupt configuration structure.
 *
 *  \return On success, it return the pointer to external interrupt device.
 *          On error, it returns NULL.
 */
EPCFExtIntDevice_t* epcf_extInt_createNative(EPCFExtIntCfg_t* pExtIntConfig);

#ifdef EPCF_SUPPORT_EXTENDED_EXTINT

/** \brief External Interrupt Controller   */
typedef struct EPCFExtIntController EPCFExtIntController_t;

/** 
 *  \brief  This function is used to create a external Interrupt device in extended mode. Before calling this function,
 *  		user should create an adapter for communication between host and extended device.
 *        	For detail explaination, see ../../../../extended/adapter/adapter.h
 *        	Then, user should create a controller for controlling extended device from host.
 *   	  	Call this function in beginning to initialize the external Interrupt device. 
 *  		This function allocates memory for the device using malloc() function call and returns a pointer to the device.
 *  		Pass this device pointer while calling external Interrupt functions.
 *   
 *  \param   pExtIntConfig      Pointer to the external interrupt configuration structure.
 *  \param   pExtIntController  Pointer to the external interrupt Controller to which external interrupt device will be attached.
 *   
 *  \return On success, it return the pointer to external interrupt device.
 *          On error, it returns NULL.
 */
extern EPCFExtIntDevice_t* epcf_extInt_createExtended(EPCFExtIntController_t* pExtIntController, EPCFExtIntCfg_t* pExtIntConfig);

/**
 *  \brief This function returns total number of available external interrupt devices on an extended controller.
 *  
 *  \param      pExtIntController  Pointer to the external interrupt controller.
 *  
 *  \return Returns the number of available external interrupt devices on extended bound controller.
 *          Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern uint8_t epcf_extInt_extGetDeviceCount(EPCFExtIntController_t* pExtIntController);

#endif

/**
 *  \brief This function is used to enable the external interrupt device. User callback, if attached will be called when the status of
 *         pin changes according to mode of the device. It can be disabled by a call to the function epcf_extInt_disable().
 *
 *  \param pExtIntDevice Pointer to the external interrupt device.
 *
 *  \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_extInt_enable(EPCFExtIntDevice_t* pExtIntDevice);

/**
 *  \brief This function is used to disable the external interrupt device. User callback will not get called after the device 
 *         has been disabled. The device can be enabled again by a call to the function epcf_extInt_enable().
 *
 *  \param pExtIntDevice Pointer to the external interrupt device.
 *
 *  \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_extInt_disable(EPCFExtIntDevice_t* pExtIntDevice)

/**
 *  \brief This function is used to attach an external interrupt callback according to the interrupt mode selected while
 *         configuring the device.
 *
 *  \param pExtIntDevice     Pointer to the external interrupt device.
 *  \param callback          User callback to be called
 *
 *  \return return callbackId.
 *
 *  \note Call this function before enabling the external interrupt device. To attach a callback if external interrupt
 *        has already enabled: 
 *        1. Disable external interrupt device.
 *        2. Attach a callback.
 *        3. Enable external interrupt device again.
 */
extern int8_t epcf_extInt_attachCallback(EPCFExtIntDevice_t* pExtIntDevice,epcfCallback_fp pCallback);
    
/**
 *  \brief This function is used to detach an external interrupt callback for the device.
 *
 *  \param pExtIntDevice     Pointer to the external interrupt device.
 *
 *  \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 *
 *  \note Call this function before enabling the external interrupt device. To detach a callback if external interrupt
         has already enabled: 
 *        1. Disable external interrupt device.
 *        2. Detach the callback.
 *        3. Enable external interrupt device again.
 */
extern int8_t epcf_extInt_detachCallback(EPCFExtIntDevice_t* pExtIntDevice);

/**
 *  \brief This function is used to close the external interrupt device. It will free the memory allocated by the external interrupt
 *         device.
 *
 *  \param pExtIntDevice Pointer to the external interrupt device.
 *
 *  \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_extInt_close(EPCFExtIntDevice_t* pExtIntDevice);

/**
 *  \brief This function is used to get total number of available external interrupt devices.
 *
 *  \return Returns the number of available external interrupt devices.
 */
extern uint8_t epcf_extInt_getDeviceCount();

#ifdef EPCF_USING_MT_ENV
// TODO : Adding the Support for EPCF_USING_MT_ENV
// TODO : Add Comments for Function Discription.
/**
 *  \brief
 *  
 *  \param      pExtIntDevice      Pointer to the external Interrupt device. 
 *
 * \return  Returns the lock status for external Interrupt device.
 */
extern int8_t epcf_extInt_lock(EPCFExtIntDevice_t* pExtIntDevice);

/**
 *  \brief
 *  
 *  \param      pExtIntDevice      Pointer to the external Interrupt device. 
 *
 * \return  Returns the unlock status for external Interrupt device.
 */
extern int8_t epcf_extInt_unlock(EPCFExtIntDevice_t* pExtIntDevice);
#endif

#endif      //__EPCF_INCLUDE_PERIPHERAL_INCLUDE_EXTINT_EXTINT_H
