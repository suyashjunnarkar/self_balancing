/**
 * \file  adc.h
 * \brief This file is used to configure an Adc device
 */

#ifndef __EPCF_PERIPHERAL_INCLUDE_ADC_ADC_H
#define __EPCF_PERIPHERAL_INCLUDE_ADC_ADC_H

/** \brief Adc device   */
typedef struct EPCFAdcDevice EPCFAdcDevice_t;

/** \brief  Enumeration for channel number  */
typedef enum
{
    enEPCFAdcChannel_0  = 0x0001,       /**< Channel number 0       */
    enEPCFAdcChannel_1  = 0x0002,       /**< Channel number 1       */
    enEPCFAdcChannel_2  = 0x0004,       /**< Channel number 2       */
    enEPCFAdcChannel_3  = 0x0008,       /**< Channel number 3       */
    enEPCFAdcChannel_4  = 0x0010,       /**< Channel number 4       */
    enEPCFAdcChannel_5  = 0x0020,       /**< Channel number 5       */
    enEPCFAdcChannel_6  = 0x0040,       /**< Channel number 6       */
    enEPCFAdcChannel_7  = 0x0080,       /**< Channel number 7       */
    enEPCFAdcChannel_8  = 0x0100,       /**< Channel number 8       */
    enEPCFAdcChannel_9  = 0x0200,       /**< Channel number 9       */
    enEPCFAdcChannel_10 = 0x0400,       /**< Channel number 10      */
    enEPCFAdcChannel_11 = 0x0800,       /**< Channel number 11      */
    enEPCFAdcChannel_12 = 0x1000,       /**< Channel number 12      */
    enEPCFAdcChannel_13 = 0x2000,       /**< Channel number 13      */
    enEPCFAdcChannel_14 = 0x4000,       /**< Channel number 14      */
    enEPCFAdcChannel_15 = 0x8000,       /**< Channel number 15      */
    enEPCFAdcChannel_Max                /**< Special value for boundary checking    */
}EnEPCFAdcChannel_t;

/** \brief Enumeration for adc width            */
typedef enum
{
    enEPCFAdcWidth_3 = 3,   /**< 3 bits Adc width           */
    enEPCFAdcWidth_4,       /**< 4 bits Adc width           */
    enEPCFAdcWidth_5,       /**< 5 bits Adc width           */
    enEPCFAdcWidth_6,       /**< 6 bits Adc width           */
    enEPCFAdcWidth_7,       /**< 7 bits Adc width           */
    enEPCFAdcWidth_8,       /**< 8 bits Adc width           */
    enEPCFAdcWidth_9,       /**< 9 bits Adc width           */
    enEPCFAdcWidth_10,      /**< 10 bits Adc width          */
    enEPCFAdcWidth_11,      /**< 11 bits Adc width          */
    enEPCFAdcWidth_12,      /**< 12 bits Adc width          */
    enEPCFAdcWidth_13,      /**< 13 bits Adc width          */
    enEPCFAdcWidth_14,      /**< 14 bits Adc width          */
    enEPCFAdcWidth_15,      /**< 15 bits Adc width          */
    enEPCFAdcWidth_16,      /**< 16 bits Adc width          */
    enEPCFAdcWidth_Max      /**< Special value for boundary checking            */
}EnEPCFAdcWidth_t;

/** \brief Enumeration for current state of adc */
typedef enum
{
    enEPCFAdcState_Stopped = 0,   /**< adc is stopped, no user callback will get called		 */
    enEPCFAdcState_Running,       /**< adc is running (operational), user callback(s) will get called at respective period */
    enEPCFAdcState_Max            /**< Special value for boundary checking 		*/
}EnEPCFAdcState_t;

/**
 *  \brief  Adc configuration structure
 *  
 *  Example to configure adc device:
 *  
 *  EPCFAdcCfg_t adcConfig = 
 *  {
 *      0,                                              // adc id 0
 *      5000,                                           // reference voltage = 5 volts
 *      enEPCFAdcWidth_10,                              // 10-bit adc width
 *      enEPCFAdcChannel_0 | enEPCFAdcChannel_3,        // channel0 and channel3 enabled
 *      enEPCFBooleanTrue,                              // enable interrupt
 *      NULL                                            // No hardware specific config
 *  };
 */
typedef struct 
{
    uint8_t                 adcId;              /**< Adc Id. Refer to platform specific header file for appropriate adc id  */
    
    uint32_t                refVtg;             /**< Adc reference voltage in millivolts                                    */
    
    EnEPCFAdcWidth_t        adcWidth;           /**< output data width of adc device supported by controller.
                                                     It specifies the number of bits of accuracy of the result.
                                                     Resolution of an adc is determined by the reference voltage and
                                                     adc width. The resolution defines the smallest voltage change that
                                                     can be measured by the adc.
                                                     For example: Consider an 8-bit adc with reference voltage = 5 volts.
                                                     Now, adc resolution is equal to 5/256 = 19.5 milliVolts.
                                                     Resolution can be improved by reducing reference voltage or by 
                                                     increasing adcWidth.
                                                     However, by reducing the reference voltage, maximum voltage that 
                                                     can be measured by adc is also reduced.                                */

    EnEPCFBoolean_t         interruptEnable;    /**< Specifies to enable adc interrupt or not
                                                     enEPCFBooleanTrue  = To enable adc interrupt
                                                     enEPCFBooleanFalse = To disable adc interrupt                          */
                                                     
    void*                   hardwareCfg;        /**< Hardware platform specific configuration.
                                                     Define an enum for the various trigger sources depending upon the 
                                                     specific hardware device to trigger data conversion.
                                                     Define an enum for polarity of the trigger edge to trigger data
                                                     conversion.                                                            */
}EPCFAdcCfg_t;

/**
 *  \brief This function is used to create an adc device. Call this function in beginning to initialize the adc device.
 *        This function allocates memory for the device using malloc() function call and returns a pointer to the device. Pass this device pointer 
 *        while calling adc functions.
 *  
 *  \param pAdcConfig Pointer to the adc configuration structure.
 *  
 *  \return On success, it return the pointer to adc device.
 *         On error, it returns NULL.
 */
extern EPCFAdcDevice_t* epcf_adc_createNative(EPCFAdcCfg_t* pAdcConfig);

#ifdef EPCF_SUPPORT_EXTENDED_ADC

/** \brief Adc Controller   */
typedef struct EPCFAdcController EPCFAdcController_t;

/** 
 *  \brief  This function is used to create a Adc device in extended mode. Before calling this function,
 *  		user should create an adapter for communication between host and extended device.
 *        	For detail explaination, see ../../../../extended/adapter/adapter.h
 *        	Then, user should create a controller for controlling extended device from host.
 *   	  	Call this function in beginning to initialize the adc device. 
 *  		This function allocates memory for the device using malloc() function call and returns a pointer to the device.
 *  		Pass this device pointer while calling adc functions.
 *  
 *  \param   pAdcConfig      Pointer to the adc configuration structure.
 *  \param   pAdcController  Pointer to the adc Controller to which adc device will be attached.
 *  
 *  \return On success, it return the pointer to adc device.
 *         On error, it returns NULL.
 */
extern EPCFAdcDevice_t* epcf_adc_createExtended(EPCFAdcController_t* pAdcController, EPCFAdcCfg_t* pAdcConfig);

/**
 *  \brief This function returns total number of available adc devices on an extended controller.
 *  
 *  \param      pAdcController  Pointer to the adc controller.
 *  
 *  \return Returns the number of available adc devices on extended bound controller.
 *          Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern uint8_t epcf_adc_extGetDeviceCount(EPCFAdcController_t* pAdcController);

#endif

/**
 *  \brief This function is used to start continuous adc conversion. Adc will start data conversion according to the 
 *        configuration settings. Use epcf_adc_getValue and epcf_adc_getVoltage functions to read digital output data.
 *        User callback, if attached will be call after an adc conversion is completed when adc is configured
 *        in interrupt mode.
 *        Adc conversion can be stopped by a call to the function epcf_adc_conversionStop.
 *  
 *  \param pAdcDevice    Pointer to the adc device.
 *  \param channel       Adc channels to be configured. 
 *                      To enable multiple channels OR the respective channels numbers.
 *                      For eg: To enable channel0 and channel3, set channel value equal to: (enEPCFAdcChannel_0 | enEPCFAdcChannel_3)
 *
 *  \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_adc_continuousConversionStart(EPCFAdcDevice_t* pAdcDevice,uint16_t channel);

/**
 *  \brief This function is used to stop continuous adc conversion. User callback will not be called after data 
 *         conversion has been stopped. Adc data conversion can be started again by a call to the function
 *         epcf_adc_continuousConversionStart.
 *  
 *  \param pAdcDevice    Pointer to the adc device.
 *
 *  \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_adc_conversionStop(EPCFAdcDevice_t* pAdcDevice);

/**
 *  \brief This function is used to read the converted digital output value of the particular channel.
 *  
 *  \param pAdcDevice    Pointer to the adc device.
 *  \param data          Pointer to uint32_t variable to get output data value
 *  \param channel       adc channel
 *  
 *  \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_adc_getValue(EPCFAdcDevice_t* pAdcDevice, uint32_t* data, EnEPCFAdcChannel_t channel);

/**
 *  \brief This function is used to read the converted digital output value in millivolts of the particular channel.
 *  
 *  \param pAdcDevice    Pointer to the adc device.
 *  \param milliVolts    Pointer to uint32_t variable to get output data value in millivolts
 *  \param channel       adc channel
 *  
 *  \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_adc_getVoltage(EPCFAdcDevice_t* pAdcDevice, uint32_t* milliVolts, EnEPCFAdcChannel_t channel);

/**
 *  \brief This function is used to attach an adc callback called after adc conversion is completed when adc is configured in interrupt mode.
 *  
 *  \param pAdcDevice        Pointer to the adc device.
 *  \param callback          User callback to be called
 *  \param channel         	 adc channel
 *  
 *  \return return callbackId.
 *  
 *  \note Call this function before starting adc conversion. To attach a callback if adc has already started: 
 *        1. Stop adc conversion.
 *        2. Attach a callback.
 *        3. Start adc conversion again.
 */
extern int8_t epcf_adc_attachCallback(EPCFAdcDevice_t* pAdcDevice,epcfCallback_fp callback, EnEPCFAdcChannel_t channel);

/**
 *  \brief This function is used to detach the adc callback for the specific adc interrupt source.
 *  
 *  \param pAdcDevice    Pointer to the adc device.
 *  \param channel       Adc channel to get output data for.
 *  
 *  \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 *  
 *  \note Call this function before starting adc conversion. To detach the callback if adc has already started: 
 *        1. Stop adc conversion.
 *        2. Detach the callback.
 *        3. Start adc conversion again.
 */
extern int8_t epcf_adc_detachCallback(EPCFAdcDevice_t* pAdcDevice, EnEPCFAdcChannel_t channel);

/**
 *  \brief This function is used to perform a single adc conversion and read the converted digital output value of the particular channel in millivolts.
 *        This function blocks until adc conversion is completed on all enabled channels or timeout has occurred.
 *  
 *  \param pAdcDevice    Pointer to the adc device.
 *  \param channel       Adc channel to get output data for.                     
 *  \param data          Pointer to uint32_t variable to get output data value.
 *  \param timeout       timeout channel.
 *  
 *  \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 *  
 *  \note Before calling this function stop continuous adc conversion, if started.
 */
extern int8_t epcf_adc_singleConversion(EPCFAdcDevice_t* pAdcDevice,EnEPCFAdcChannel_t channel,uint32_t* data,EPCFTime_t timeout);

/**
 *  \brief This function is used to perform a single adc conversion and read the converted digital output value of the particular channel. 
 *         This function blocks until adc conversion is completed enabled channel or timeout has occurred.
 *  
 *  \param pAdcDevice    Pointer to the adc device.
 *  \param channel       Adc channel to get voltage in millivolts for.                       
 *  \param milliVolts    Pointer to uint32_t variable to get output data value in millivolts
 *  \param timeout       timeout channel.
 *  
 *  \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 *  
 *  \note Before calling this function stop continuous adc conversion, if started.
 */
extern int8_t epcf_adc_singleConversionGetVoltage(EPCFAdcDevice_t* pAdcDevice,EnEPCFAdcChannel_t channel,uint32_t* milliVolts,EPCFTime_t timeout);

/**
 *  \brief This function is used to close the adc device. It will free the memory allocated by the adc device.
 *  
 *  \param pAdcDevice Pointer to the adc device.
 *  
 *  \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_adc_close(EPCFAdcDevice_t* pAdcDevice);


/**
 *  \brief This function is used to get total number of available adc devices.
 *  
 *  \return Returns the number of available adc devices.
 */
extern uint8_t epcf_adc_getDeviceCount();

/**
 * \brief This function is used to get the current state of the adc.
 * 
 * \param pAdcDevice Pointer to the adc device.
 *
 * \return return adc state
 */
extern EnEPCFAdcState_t epcf_adc_getState(EPCFAdcDevice_t* pAdcDevice);


#ifdef EPCF_USING_MT_ENV
// TODO : Adding the Support for EPCF_USING_MT_ENV
// TODO : Add Comments for Function Discription.
/**
 *  \brief
 *  
 *  \param      pAdcDevice      Pointer to the adc device. 
 *
 * \return  Returns the lock status for adc device.
 */
extern int8_t epcf_adc_lock(EPCFAdcDevice_t* pAdcDevice);

/**
 *  \brief
 *  
 *  \param      pAdcDevice      Pointer to the adc device. 
 *
 * \return  Returns the unlock status for adc device.
 */
extern int8_t epcf_adc_unlock(EPCFAdcDevice_t* pAdcDevice);
#endif

#endif      //__EPCF_PERIPHERAL_INCLUDE_ADC_ADC_H
