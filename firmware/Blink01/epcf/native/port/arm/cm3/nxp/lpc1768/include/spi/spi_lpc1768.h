/**
 * \file    spi_lpc1768.h
 * \brief   Native SPI Driver Description for LPC1768.
 *
 */

#ifndef __EPCF_INCLUDE_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_SPI_SPI_LPC1768_H
#define __EPCF_INCLUDE_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_SPI_SPI_LPC1768_H

#define EPCF_PIN_LPC1768_INCLUDE    PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_NATIVE_PATH/  \
                                    ,port/PCF_ARCH_NAME/PCF_ARCH_VARIANT/PCF_ARCH_DEVICE_VENDOR/    \
                                    ,PCF_ARCH_DEVICE/include/,pin_lpc1768.h)
#include EPCF_PIN_LPC1768_INCLUDE
#undef EPCF_PIN_LPC1768_INCLUDE

#define EPCF_FIFO_INCLUDE           PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_PATH/,utils/,include/,epcf_fifo.h)
#include EPCF_FIFO_INCLUDE
#undef EPCF_FIFO_INCLUDE

/**  \brief Platform specific structure for LPC1768 */
typedef struct EPCFSpiLpc1768Cfg
{
      EPCFPortPin_t           misoPin;      /**< Pin description of MISO pin and port        */
      EPCFPortPin_t           mosiPin;      /**< Pin description of MOSI pin and port        */
      EPCFPortPin_t           sckPin;       /**< Pin description of MOSI pin and port        */
      EPCFPortPin_t           csPin;        /**< Pin description of MOSI pin and port        */
}EPCFSpiLpc1768Cfg_t;

int8_t epcf_Spi_nativeInit(EPCFSpiDevice_t* pSpiDevice,EPCFSpiCfg_t* pCnfig);
int8_t epcf_spi_nativeRegisterSlaveDevice(EPCFSpiDevice_t* pSpiDevice,EPCFPortPin_t slaveSelectPin);
int8_t epcf_spi_nativeDeRegisterSlaveDevice(EPCFSpiDevice_t* pSpiDevice,uint8_t slaveId);
int8_t epcf_spi_nativeSlaveSelect(EPCFSpiDevice_t* pSpiDevice, uint8_t slaveId);
int8_t epcf_spi_nativeSlaveDeSelect(EPCFSpiDevice_t* pSpiDevice, uint8_t slaveId);
int8_t epcf_spi_nativeExchange(EPCFSpiDevice_t* pSpiDevice,uint16_t txData,uint16_t* rxData,EPCFTime_t timeout);
int8_t epcf_spi_nativeWrite(EPCFSpiDevice_t* pSpiDevice,const uint8_t* data,uint32_t size,EPCFTime_t timeout);
int8_t epcf_spi_nativeRead(EPCFSpiDevice_t* pSpiDevice,uint8_t* data,uint32_t size,EPCFTime_t timeout);
int8_t epcf_spi_nativeIntEnable(EPCFSpiDevice_t* pSpiDevice,EnEPCFSpiIntType intType);
int8_t epcf_spi_nativeIntDisable(EPCFSpiDevice_t* pSpiDevice , EnEPCFSpiIntType intType);
int32_t epcf_spi_nativeGetRxBufferCount(EPCFSpiDevice_t* pSpiDevice);
int8_t epcf_spi_nativeRxBufferFlush(EPCFSpiDevice_t* pSpiDevice);
int32_t epcf_spi_nativeGetTxBufferCount(EPCFSpiDevice_t* pSpiDevice);
int8_t epcf_spi_nativeTxBufferFlush(EPCFSpiDevice_t* pSpiDevice);
int8_t epcf_spi_nativeClose(EPCFSpiDevice_t* pSpiDevice);
uint8_t epcf_spi_nativeGetDeviceCount();

#endif      // __EPCF_INCLUDE_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_SPI_SPI_LPC1768_H

/** @} */
