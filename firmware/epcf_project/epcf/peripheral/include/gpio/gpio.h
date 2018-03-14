/**
 *  \file  gpio.h
 *  \brief This file is used to configure a GPIO device
 */

#ifndef __EPCF_INCLUDED_PERIPHERAL_INCLUDE_GPIO_GPIO_H
#define __EPCF_INCLUDED_PERIPHERAL_INCLUDE_GPIO_GPIO_H

/** \brief Gpio Device */
typedef struct EPCFGpioDevice EPCFGpioDevice_t;

/** \brief Enumeration for pin direction       */
typedef enum EnEPCFGpioDirection
{
    enEPCFGpioDirection_Input = 0,      /**< Gpio pin input direction               */
    enEPCFGpioDirection_Output,         /**< Gpio pin output direction              */
    enEPCFGpioDirection_HighZ,          /**< Gpio pin high impedence                */
    enEPCFGpioDirection_Max             /**< Special value for boundary checking    */
}EnEPCFGpioDirection_t;

/** \brief Enumeration for pin mode                */
typedef enum EnEPCFGpioPinMode
{
    enEPCFGpioPinMode_PullUp = 0,       /**< Gpio pin pull-up enable                */
    enEPCFGpioPinMode_Repeater,         /**< Gpio pin repeater mode enable          */
    enEPCFGpioPinMode_NoPullUpDown,     /**< Gpio pin no pull-up or pull-down       */
    enEPCFGpioPinMode_PullDown,         /**< Gpio pin pull-down enable              */
    enEPCFGpioPinMode_Max               /**< Special value for boundary checking    */
}EnEPCFGpioPinMode_t;

/** \brief Enumeration for open drain settings     */
typedef enum EnEPCFOpenDrain
{
    enEPCFGpioOpenDrain_Disable = 0,     /**< Gpio pin open drain disable           */
    enEPCFGpioOpenDrain_Enable,          /**< Gpio pin open drain enable            */
    enEPCFGpioOpenDrain_Max              /**< Special value for boundary checking   */  
}EnEPCFGpioOpenDrain_t;

/** \brief  Enumeration for gpio interrupt mode */
typedef enum
{
    enEPCFGpioIntMode_FallingEdge,      /**< Falling edge triggered gpio interrupt       */
    enEPCFGpioIntMode_RisingEdge,       /**< Rising edge triggered gpio interrupt        */
    enEPCFGpioIntMode_BothEdge,         /**< Both edge triggered gpio interrupt          */
    enEPCFGpioIntMode_LowLevel,         /**< Low level triggered gpio interrupt          */
    enEPCFGpioIntMode_HighLevel,        /**< High level triggered gpio interrupt         */
    enEPCFGpioIntMode_Max               /**< Special value for boundary checking         */
}EnEPCFGpioIntMode_t;

/** \brief Gpio configuration structure
 *  
 *  Example to configure Gpio device:
 *  
 *  EPCFGpioCfg_t pGpioConfig = 
 *  {
 *     TODO : Add example
 *  };
 */
typedef struct
{
    EPCFPortPin_t           portPin;        /**< Port Pin                           */
    EnEPCFGpioDirection_t   direction;      /**< Pin direction, 1:output 0:input    */
    EnEPCFGpioPinMode_t     mode;           /**< Pin pull up/down mode              */
    EnEPCFGpioOpenDrain_t   openDrain;      /**< Pin open drain on/off              */
    EnEPCFBoolean_t         intEnable;      /**< Pin interrupt enable               */
    EnEPCFGpioIntMode_t     intMode;        /**< Pin interrupt mode                 */
    void*                   hardwareCfg;    /**< Hardware platform specific configuration, pass NULL for default configuration  */
}EPCFGpioCfg_t;

/**
 *  \brief This function is used to create an gpio device. Call this function in beginning to initialize the gpio device.
 *        This function allocates memory for the device using malloc() function call and returns a pointer to the device.
 *        Pass this device pointer while calling gpio functions.
 *  
 *  \param pGpioConfig Pointer to the gpio configuration structure.
 *  
 *  \return On success, it return the pointer to gpio device.
 *         On error, it returns NULL.
 */
extern EPCFGpioDevice_t* epcf_gpio_createNative(EPCFGpioCfg_t* pGpioConfig);

#ifdef EPCF_SUPPORT_EXTENDED_GPIO

/** \brief Gpio Controller   */
typedef struct EPCFGpioController EPCFGpioController_t;

/** 
 *  \brief  This function is used to create a gpio device in extended mode. Before calling this function,
 *  		user should create an adapter for communication between host and extended device.
 *        	For detail explaination, see ../../../../extended/adapter/adapter.h
 *        	Then, user should create a controller for controlling extended device from host.
 *   	  	Call this function in beginning to initialize the gpio device. 
 *  		This function allocates memory for the device using malloc() function call and returns a pointer to the device.
 *  		Pass this device pointer while calling gpio functions.
 *  
 *  \param   pAdcConfig      Pointer to the gpio configuration structure.
 *  \param   pAdcController  Pointer to the gpio Controller to which gpio device will be attached.
 *  
 *  \return On success, it return the pointer to gpio device.
 *          On error, it returns NULL.
 */
extern EPCFAdcDevice_t* epcf_gpio_createExtended(EPCFGpioController_t* pGpioController, EPCFGpioCfg_t* pGpioConfig);

/**
 *  \brief This function returns total number of available Gpio devices on an extended controller.
 *  
 *  \param      pAdcController  Pointer to the gpio controller.
 *  
 *  \return Returns the number of available gpio devices on extended bound controller.
 *          Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern uint8_t epcf_gpio_extGetDeviceCount(EPCFGpioController_t* pGpioController);

#endif

/**
 *  \brief This function is used to set an gpio, for a particular gpio device.
 *  
 *  \param pGpiodevice Pointer to the gpio device structure.
 *  
 *  \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_gpio_set(EPCFGpioDevice_t* pGpiodevice);

/**
 *  \brief This function is used to clear an gpio, for a particular gpio device.
 *  
 *  \param pGpiodevice Pointer to the gpio device structure.
 *  
 *  \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_gpio_clear(EPCFGpioDevice_t* pGpiodevice);

/**
 *  \brief This function is used to read an gpio, for a particular gpio device.
 *  
 *  \param pGpiodevice Pointer to the gpio device structure.
 *  
 *  \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_gpio_read(EPCFGpioDevice_t* pGpiodevice);

/**
 *  \brief This function is used to set direction of gpio, for a particular gpio device.
 *  
 *  \param pGpiodevice Pointer to the gpio device structure.
 *  
 *  \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_gpio_setDirection(EPCFGpioDevice_t* pGpiodevice, EnEPCFGpioDirection_t direction);
//int8_t epcf_gpio_setDirection(EPCFGpioDevice_t* pGpiodevice, EnEPCFGpioDirection_t direction)
/**
 *  \brief This function is used to set an gpio, for a particular gpio device.
 *  
 *  \param pGpiodevice Pointer to the gpio device structure.
 *  
 *  \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern uint8_t epcf_gpio_getDeviceCount();

/* TODO : GPIO Interrupt  */
/**
 *  \brief This function is used to enable the interrupt on gpio device. User callback, if attached will be called when the status of
 *         pin changes according to mode of the device while configuring. It can be disabled by a call to the function EPCF_GPIOINT_DISABLE.
 *
 *  \param pGpioDevice Pointer to the Gpio device.
 *
 *  \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
int8_t epcf_gpio_intEnable(EPCFGpioDevice_t* pGpioDevice);

/**
 *  \brief This function is used to disable interrupt on Gpio device. User callback will not get called after the device
 *         interrupt has been disabled. The device interrupt can be enabled again by a call to the function EPCF_GPIOINT_ENABLE.
 *
 *  \param pGpioDevice Pointer to the Gpio device.
 *
 *  \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
 int8_t epcf_gpio_intDisable(EPCFGpioDevice_t* pGpioDevice);

/**
 *  \brief This function is used to attach an Gpio interrupt callback according to the interrupt mode selected while
 *         configuring the device.
 *
 *  \param pGpioDevice   Pointer to the Gpio device.
 *  \param callback      User callback to be called
 *
 *  \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 *
 *  \note Call this function before enabling the Gpio interrupt device. To attach a callback if Gpio interrupt
 *        has already enabled:
 *        1. Disable interrupt on Gpio device.
 *        2. Attach a callback.
 *        3. Enable interrupt on Gpio device again.
 */
 int8_t epcf_gpio_intAttachCallback(EPCFGpioDevice_t* pGpioDevice,epcfCallback_fp pCallback);

/**
 *  \brief This function is used to detach an Gpio interrupt callback for the device.
 *
 *  \param pGpioDevice   Pointer to the Gpio interrupt device.
 *
 *  \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 *
 *  \note Call this function before enabling the Gpio interrupt device. To detach a callback if Gpio interrupt
         has already enabled:
 *        1. Disable interrupt on Gpio device.
 *        2. Detach the callback.
 *        3. Enable interrupt on Gpio device again.
 */
int8_t epcf_gpio_intDetachCallback(EPCFGpioDevice_t* pGpioDevice);


#ifdef EPCF_USING_MT_ENV
// TODO : Adding the Support for EPCF_USING_MT_ENV
// TODO : Add Comments for Function Discription.
/**
 *  \brief
 *  
 *  \param      pGpioDevice      Pointer to the gpio device. 
 *
 * \return  Returns the lock status for gpio device.
 */
extern int8_t epcf_gpio_lock(EPCFGpioDevice_t* pGpioDevice);

/**
 *  \brief
 *  
 *  \param      pGpioDevice      Pointer to the gpio device. 
 *
 * \return  Returns the unlock status for gpio device.
 */
extern int8_t epcf_gpio_unlock(EPCFGpioDevice_t* pGpioDevice);
#endif

#endif      //__EPCF_INCLUDED_PERIPHERAL_INCLUDE_GPIO_GPIO_H
