/**
 * \file    adc_lpc1768.h
 * \brief   Native ADC Driver Description for LPC1768.
 *
 */
 
#ifndef __EPCF_NATIVE_PORT_ARM_CM3_NXP_LPC1768_INCLUDE_ADC_ADC_LPC1768_H
#define __EPCF_NATIVE_PORT_ARM_CM3_NXP_LPC1768_INCLUDE_ADC_ADC_LPC1768_H

#include "adc_lpc1768_config.h"

#define __EPCF_PIN_LPC1768_INCLUDE 		PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_NATIVE_PATH/	\
                ,port/PCF_ARCH_NAME/PCF_ARCH_VARIANT/PCF_ARCH_DEVICE_VENDOR/,PCF_ARCH_DEVICE/include/,pin_lpc1768.h)
#include __EPCF_PIN_LPC1768_INCLUDE
#undef __EPCF_PIN_LPC1768_INCLUDE


typedef enum
{
	enEPCFAdcStartNone = 0x00,					/**< Stop ADC conversion										*/
	enEPCFAdcStartNow,							/**< Start ADC for single conversion							*/
	enEPCFAdcStartNMIPinRisingEdge,				/**< Start ADC conversion on rising edge on NMI (P2.10) pin		*/
	enEPCFAdcStartCLKOUTPinRisingEdge,			/**< Start ADC conversion on rising edge on CLKOUT (P1.27) pin	*/
	enEPCFAdcStartMAT01PinRisingEdge,			/**< Start ADC conversion on rising edge on MAT0.1 pin			*/
	enEPCFAdcStartMAT03PinRisingEdge,			/**< Start ADC conversion on rising edge on MAT0.3 pin			*/
	enEPCFAdcStartMAT10PinRisingEdge,			/**< Start ADC conversion on rising edge on MAT1.0 pin			*/
	enEPCFAdcStartMAT11PinRisingEdge,			/**< Start ADC conversion on rising edge on MAT1.1 pin			*/
	enEPCFAdcStartNMIPinFallingEdge = 0x0A,		/**< Start ADC conversion on falling edge on NMI (P2.10) pin	*/
	enEPCFAdcStartCLKOUTPinFallingEdge,         /**< Start ADC conversion on falling edge on CLKOUT (P1.27) pin	*/
	enEPCFAdcStartMAT01PinFallingEdge,          /**< Start ADC conversion on falling edge on MAT0.1 pin			*/
	enEPCFAdcStartMAT03PinFallingEdge,          /**< Start ADC conversion on falling edge on MAT0.3 pin			*/
	enEPCFAdcStartMAT10PinFallingEdge,          /**< Start ADC conversion on falling edge on MAT1.0 pin			*/
	enEPCFAdcStartMAT11PinFallingEdge,          /**< Start ADC conversion on falling edge on MAT1.1 pin			*/
}EnEPCFAdcStart_t;

/**  \brief Platform specific structure for LPC1768 */
typedef struct EPCFAdcLpc1768Cfg
{
	uint8_t				noOfAdcChannel;
	EPCFPortPin_t		*adcChannelPin;
	uint8_t				noOfExternalSrc;
	EPCFPortPin_t		*externalSrcPin;
	EnEPCFAdcStart_t	adcSingleConvStart;		/** This should be used when using EPCF_ADC_SINGLE_CONVERSION
	 	 	 	 	 	 	 	 	 	 	 	 	 and EPCF_ADC_GET_VOLTAGE_SINGLE_CONVERSION function
	 	 	 	 	 	 	 	 	 	 	 	 	 otherwise pass enEPCFAdcStartNone. */
}EPCFAdcLpc1768Cfg_t;


extern int8_t epcf_adc_nativeInit(EPCFAdcDevice_t* pAdcDevice, EPCFAdcCfg_t* pConfig);
extern int8_t epcf_adc_nativeContinuousConversionStart(EPCFAdcDevice_t* pAdcDevice,uint16_t channel);
extern int8_t epcf_adc_nativeConversionStop(EPCFAdcDevice_t* pAdcDevice);
extern int8_t epcf_adc_nativeGetValue(EPCFAdcDevice_t* pAdcDevice,uint32_t* data,EnEPCFAdcChannel_t channel);
extern int8_t epcf_adc_nativeGetVoltage(EPCFAdcDevice_t* pAdcDevice,uint32_t* milliVolts,EnEPCFAdcChannel_t channel);
extern int8_t epcf_adc_nativeAttachCallback(EPCFAdcDevice_t* pAdcDevice,epcfCallback_fp callback, uint16_t channel);
extern int8_t epcf_adc_nativeDetachCallback(EPCFAdcDevice_t* pAdcDevice, uint16_t channel);
extern int8_t epcf_adc_nativeSingleConversion(EPCFAdcDevice_t* pAdcDevice,EnEPCFAdcChannel_t channel,uint32_t* data,EPCFTime_t timeout);
extern int8_t epcf_adc_nativeSingleConversionGetVoltage(EPCFAdcDevice_t* pAdcDevice,EnEPCFAdcChannel_t channel,uint32_t* milliVolts,EPCFTime_t timeout);
extern int8_t epcf_adc_nativeClose(EPCFAdcDevice_t* pAdcDevice);
extern uint8_t epcf_adc_nativeGetDeviceCount();
extern EnEPCFAdcState_t epcf_adc_nativeGetState(EPCFAdcDevice_t* pAdcDevice);


#endif      // __EPCF_NATIVE_PORT_ARM_CM3_NXP_LPC1768_INCLUDE_ADC_ADC_LPC1768_H

/** @} */
