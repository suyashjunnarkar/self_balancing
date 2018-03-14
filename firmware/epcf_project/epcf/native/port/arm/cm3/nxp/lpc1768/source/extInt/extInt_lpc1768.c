#if (EPCF_USE_EXTINT == PCF_ENABLE)
#include "epcf.h"
#include <stdlib.h>

#define __EPCF_EXTINT_HIDDEN_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_PATH/,peripheral/,extInt/,extInt_hidden.h)
#include  __EPCF_EXTINT_HIDDEN_INCLUDE
#undef __EPCF_EXTINT_HIDDEN_INCLUDE

// Macros to change later
#define __CHECK_DEV_INIT(dev)         if(dev == enEPCFBoolean_False){ return EPCF_STATUS_NOT_CONFIGURED; }

#define __CHECK_NULL_PTR(ptr)         if(ptr == 0){ return EPCF_STATUS_INVALID_ARGS; }

static uint32_t extIntIrqNum[4] = { IRQ_NUM(EPCF_EINT0_CH), IRQ_NUM(EPCF_EINT1_CH), IRQ_NUM(EPCF_EINT2_CH),IRQ_NUM(EPCF_EINT3_CH) };

#define __EPCF_EXT_PIN_ALT_FUNCTION_1     1

#define __EPCF_EXTINT_MAX_DEVICE         4

EnEPCFBoolean_t getCallbackPointer(epcfCallback_fp* pCallback);
EnEPCFBoolean_t isExtInt3Enable(void);
EnEPCFBoolean_t isGpioIntEnable(void);

// Static Variable Declaration
static uint32_t extIntDeviceCount = __EPCF_EXTINT_MAX_DEVICE;
static EPCFExtIntDevice_t* extIntDevice[__EPCF_EXTINT_MAX_DEVICE] = { 0, 0, 0, 0 };
static EnEPCFBoolean_t extIntChInit[4] = { enEPCFBoolean_False,enEPCFBoolean_False, enEPCFBoolean_False, enEPCFBoolean_False }; // initialize flag for the channel
static uint32_t extIntPinNumber[4] = { EPCF_PIN_10, EPCF_PIN_11, EPCF_PIN_12,EPCF_PIN_13 };        // Array to hold external interrupt pin number
static EnEPCFBoolean_t extIntEnable[4] = { enEPCFBoolean_False,enEPCFBoolean_False, enEPCFBoolean_False, enEPCFBoolean_False };
static epcfCallback_fp extIntCallback[__EPCF_EXTINT_MAX_DEVICE];
static uint32_t extInt_channel_addr = SC_BASE;

// Static Function Declaration
static int8_t __epcfExtIntInit(EPCFExtIntCfg_t *pConfig,EPCFExtIntDevice_t* pExtIntDevice);

//EPCFPlatfromSpecificCfg_t
// Function Definition
int8_t epcfNativeExtIntInit(EPCFExtIntDevice_t* pExtIntDevice,EPCFExtIntCfg_t *pConfig) 
{
    EPCFPinCfg_t pPinCfg;
    int8_t status = EPCF_STATUS_SUCCESS;

#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    __CHECK_NULL_PTR(pConfig);
    if (pConfig->extIntId >= __EPCF_EXTINT_MAX_DEVICE)
        return EPCF_STATUS_INVALID_ARGS;    //Invalid Arguments
    if (pConfig->mode >= enEPCFExtIntMode_Max)
        return EPCF_STATUS_INVALID_ARGS;
#endif  // PCF_ENABLE_DEBUG

    pExtIntDevice->extIntId = pConfig->extIntId;
    (pExtIntDevice->ExtIntChannelAddr) = (SC_TypeDef *) extInt_channel_addr;

    extIntDevice[pExtIntDevice->extIntId] = pExtIntDevice;

    pPinCfg.direction = 0; // enEPCFGpioDirInput
    pPinCfg.mode = 0; // enEPCFGpioPinModePullUp
    pPinCfg.openDrain = 0; // open Drain disable
    pPinCfg.portPin.port = EPCF_PORT_2;
    pPinCfg.portPin.pin = extIntPinNumber[pExtIntDevice->extIntId];
    pPinCfg.altFunction = __EPCF_EXT_PIN_ALT_FUNCTION_1;

    if (pExtIntDevice->extIntId == 3)
    {
        if (isGpioIntEnable() == enEPCFBoolean_True)
            return EPCF_STATUS_ERROR;
    }
    status = epcfPinInit(&pPinCfg);
    if (status != EPCF_STATUS_SUCCESS)
        return EPCF_STATUS_ERROR;

    status = __epcfExtIntInit(pConfig, pExtIntDevice);
    if (status != EPCF_STATUS_SUCCESS)
        return EPCF_STATUS_ERROR;

    extIntDeviceCount--;

    return EPCF_STATUS_SUCCESS;
}

int8_t epcfNativeExtIntClose(EPCFExtIntDevice_t* pExtIntDevice)
{
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    __CHECK_DEV_INIT(extIntChInit[pExtIntDevice->extIntId]);
#endif  // #if (PCF_ENABLE_DEBUG == PCF_ENABLE)

    extIntChInit[pExtIntDevice->extIntId] = enEPCFBoolean_False;

    return EPCF_STATUS_SUCCESS;
}

uint8_t epcfNativeExtIntGetDeviceCount()
{
    return extIntDeviceCount;
}

int8_t epcfNativeExtIntEnable(EPCFExtIntDevice_t* pExtIntDevice)
{
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    __CHECK_DEV_INIT(extIntChInit[pExtIntDevice->extIntId]);
#endif  // #if (PCF_ENABLE_DEBUG == PCF_ENABLE)

    // Interrupt Initialization //
    extIntEnable[pExtIntDevice->extIntId] = enEPCFBoolean_True;
    NVIC_EnableIRQ(extIntIrqNum[pExtIntDevice->extIntId]);

    return EPCF_STATUS_SUCCESS;
}

int8_t epcfNativeExtIntDisable(EPCFExtIntDevice_t* pExtIntDevice)
{
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    __CHECK_DEV_INIT(extIntChInit[pExtIntDevice->extIntId]);
#endif  // #if (PCF_ENABLE_DEBUG == PCF_ENABLE)

    // Interrupt Initialization //
    NVIC_DisableIRQ(extIntIrqNum[pExtIntDevice->extIntId]);
    extIntEnable[pExtIntDevice->extIntId] = enEPCFBoolean_False;

    return EPCF_STATUS_SUCCESS;
}
int8_t epcfNativeExtIntAttachCallback(EPCFExtIntDevice_t* pExtIntDevice,epcfCallback_fp pCallback)
{

#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    __CHECK_DEV_INIT(extIntChInit[pExtIntDevice->extIntId]);
    __CHECK_NULL_PTR(pCallback);

#endif  // #if (PCF_ENABLE_DEBUG == PCF_ENABLE)

    extIntCallback[pExtIntDevice->extIntId] = pCallback;

    return EPCF_STATUS_SUCCESS;

}
int8_t epcfNativeExtIntDetachCallback(EPCFExtIntDevice_t* pExtIntDevice)
{

#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    __CHECK_DEV_INIT(extIntChInit[pExtIntDevice->extIntId]);
#endif  // #if (PCF_ENABLE_DEBUG == PCF_ENABLE)

    extIntCallback[pExtIntDevice->extIntId] = 0;

    return EPCF_STATUS_SUCCESS;

}

//return values:
//0 : success
//-1: error
static int8_t __epcfExtIntInit(EPCFExtIntCfg_t *pConfig,EPCFExtIntDevice_t* pExtIntDevice)
{

    NVIC_DisableIRQ(extIntIrqNum[pConfig->extIntId]);

    if (pConfig->mode > enEPCFExtIntMode_BothEdge)  //level sensitive
    {
        ((SC_TypeDef*) (pExtIntDevice->ExtIntChannelAddr))->EXTMODE |= 0 << pExtIntDevice->extIntId;
    }
    else                    // edge sensitive
    {
        ((SC_TypeDef*) (pExtIntDevice->ExtIntChannelAddr))->EXTMODE |= 1<< pExtIntDevice->extIntId;
    }

    if ((pConfig->mode == enEPCFExtIntMode_FallingEdge) || (pConfig->mode == enEPCFExtIntMode_LowLevel))// Falling edge and low level
    {
        ((SC_TypeDef*) (pExtIntDevice->ExtIntChannelAddr))->EXTPOLAR |= 0<< pExtIntDevice->extIntId;
    }
    else                    // Rising edge or high level
    {
        ((SC_TypeDef*) (pExtIntDevice->ExtIntChannelAddr))->EXTPOLAR |= 1<< pExtIntDevice->extIntId;
    }

    if (pConfig->mode == enEPCFExtIntMode_BothEdge)
    {
        return EPCF_STATUS_INVALID_ARGS;
    }

    extIntChInit[pConfig->extIntId] = enEPCFBoolean_True;

    return EPCF_STATUS_SUCCESS;
}

// Interrupt Handler for all External Interrupt Handler
void EPCF_EINT0_INT_HANDLER(void)
{
    // clear interrupt flag
    PERIPH_SC->EXTINT = (1 << EPCF_EXTINT0_CH);

    if (extIntCallback[EPCF_EXTINT0_CH] != 0)
    {

        extIntCallback[EPCF_EXTINT0_CH]();

    }

}

void EPCF_EINT1_INT_HANDLER(void)
{
    // clear interrupt flag
    PERIPH_SC->EXTINT = (1 << EPCF_EXTINT1_CH);

    if (extIntCallback[EPCF_EXTINT1_CH] != 0)
    {
        extIntCallback[EPCF_EXTINT1_CH]();
    }

}

void EPCF_EINT2_INT_HANDLER(void)
{
    // clear interrupt flag
    PERIPH_SC->EXTINT = (1 << EPCF_EXTINT2_CH);

    if (extIntCallback[EPCF_EXTINT2_CH] != 0)
    {
        extIntCallback[EPCF_EXTINT2_CH]();
    }

}
EnEPCFBoolean_t getCallbackPointer(epcfCallback_fp* pCallback)
{
    if (extIntEnable[3] == enEPCFBoolean_True)
    {
        *pCallback = extIntCallback[EPCF_EXTINT3_CH];
        return enEPCFBoolean_True;
    }
    else
        return enEPCFBoolean_False;

}

EnEPCFBoolean_t isExtInt3Enable(void)
{
    if (extIntEnable[3] == enEPCFBoolean_True)
    {
        return enEPCFBoolean_True;
    }
    else
        return enEPCFBoolean_False;

}
//Handler for external interrupt 3 is available in gpio file as gpio interrupt and external interrupt shares the handler

#endif// (EPCF_USE_EXTINT == PCF_ENABLE)
