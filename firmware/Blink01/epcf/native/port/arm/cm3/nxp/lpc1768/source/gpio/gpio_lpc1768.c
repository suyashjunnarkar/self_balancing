#include "pcf.h"

#define __EPCF_GPIO_HIDDEN_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_PATH/,peripheral/source/,gpio/,gpio_hidden.h)
#include  __EPCF_GPIO_HIDDEN_INCLUDE
#undef __EPCF_GPIO_HIDDEN_INCLUDE

#define __EPCF_UTILS_GPIO_H_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_PATH/,utils/,include/,epcf_string.h)
#include  __EPCF_UTILS_GPIO_H_INCLUDE
#undef __EPCF_UTILS_GPIO_H_INCLUDE

#define __EPCF_GPIO_MAX_PORT       5

#define __EPCF_GPIO_MAX_PINS       50   //Maximum No. of pins that can be configured as GPIO in lpc1768

/**
 * The macro is used to set the alternate function as GPIO.
 */
#define __EPCF_ALT_FUNCTION_GPIO              0
/**
 * The macro is used to set maximum GPIO interrupts available.
 */
#define __EPCF_GPIO_INT_MAX                 42

static uint8_t gpioIntMode[__EPCF_GPIO_INT_MAX]={0};
static uint8_t gpioDeviceCount = __EPCF_GPIO_MAX_PINS;
static EnEPCFBoolean_t gpioIntEnable=enEPCFBoolean_False;
static epcfCallback_fp gpioIntCallbackList[__EPCF_GPIO_INT_MAX];
static EnEPCFBoolean_t gpioIntCallbackAttached =enEPCFBoolean_False;
static EPCFGpioCfg_t gpioIntList[__EPCF_GPIO_INT_MAX]; //Max gpio interrupts in port 0 and port 2
static uint8_t gpioIntId =0;
static EnEPCFBoolean_t gpioIntBusy[__EPCF_GPIO_INT_MAX];
static EnEPCFBoolean_t gpioIntInit=enEPCFBoolean_False;

//void EPCF_EINT3_INT_HANDLER(void);
//EnEPCFBoolean_t isGpioIntEnable(void);
//EnEPCFBoolean_t isExtInt3Enable(void);
//EnEPCFBoolean_t getCallbackPointer(epcfCallback_fp* pCallback );


int8_t epcf_gpio_nativeInit(EPCFGpioCfg_t *pConfig)
{
    EPCFPinCfg_t pPinCfg;
    int8_t status = 0;
    int8_t index = 0;

    pPinCfg.altFunction  = (uint32_t)__EPCF_ALT_FUNCTION_GPIO;
    pPinCfg.direction    = pConfig->direction;
    pPinCfg.mode         = pConfig->mode;
    pPinCfg.openDrain    = pConfig->openDrain;
    pPinCfg.portPin.port = pConfig->portPin.port;
    pPinCfg.portPin.pin  = pConfig->portPin.pin;

    status = epcfPinInit(&pPinCfg);
    if(status != EPCF_STATUS_SUCCESS)
        return status;


    if(pConfig->intEnable == enEPCFBoolean_True)
    {
        if((pConfig->portPin.port!=EPCF_PORT_2)&&(pConfig->portPin.port!=EPCF_PORT_0))
            return EPCF_STATUS_ERROR;

        if((pConfig->portPin.port == EPCF_PORT_2)&&(pConfig->portPin.pin > EPCF_PIN_13))
            return EPCF_STATUS_ERROR;

        if((pConfig->portPin.port == EPCF_PORT_0)&&((pConfig->portPin.pin == EPCF_PIN_12)||(pConfig->portPin.pin == EPCF_PIN_13)||(pConfig->portPin.pin == EPCF_PIN_14)))
            return EPCF_STATUS_ERROR;

        if((EnEPCFGpioIntMode_t)pConfig->mode > enEPCFGpioIntMode_LowLevel) //supports edge not level
            return  EPCF_STATUS_ERROR;

//        if(isExtInt3Enable() == enEPCFBoolean_True)
//            return  EPCF_STATUS_ERROR;

        for (index = 0; index < __EPCF_GPIO_INT_MAX; index++)
        {
            if(gpioIntBusy[index] == enEPCFBoolean_False)
            {
                gpioIntId = index;
                gpioIntBusy[index] = enEPCFBoolean_True;
                gpioIntMode[index] = pConfig->intMode;
                break;
            }
        }

//        pcfMemCopy(&gpioIntList[gpioIntId],pConfig,sizeof(EPCFGpioCfg_t) );
        gpioIntInit = enEPCFBoolean_True;
    }

    gpioDeviceCount--;

    return status;
}

int8_t epcf_gpio_nativeSet(EPCFGpioDevice_t* pGpiodevice)
{
    EPCF_GPIO_PINS_SET(pGpiodevice->portPin.port, pGpiodevice->portPin.pin);
    return EPCF_STATUS_SUCCESS;
}

int8_t epcf_gpio_nativeClear(EPCFGpioDevice_t* pGpiodevice)
{
    EPCF_GPIO_PINS_CLEAR(pGpiodevice->portPin.port, pGpiodevice->portPin.pin);
    return EPCF_STATUS_SUCCESS;
}

int8_t epcf_gpio_nativeRead(EPCFGpioDevice_t* pGpiodevice)
{
    int32_t data;

    data = EPCF_GPIO_PORT_READ(pGpiodevice->portPin.port);
    return ( (int8_t)(((1<<(pGpiodevice->portPin.pin)) & data)>>(pGpiodevice->portPin.pin)) );
}

int8_t epcf_gpio_nativeSetDirection(EPCFGpioDevice_t* pGpiodevice, EnEPCFGpioDirection_t direction)
{
    EPCF_GPIO_SET_DIR(pGpiodevice->portPin.port, pGpiodevice->portPin.pin, direction);
    return EPCF_STATUS_SUCCESS;
}

uint32_t epcf_gpio_nativeGetDeviceCount()
{
    return gpioDeviceCount;
}

int8_t epcf_gpio_nativeIntEnable(EPCFGpioDevice_t* pGpioDevice)
{
    uint8_t index=0;
    if((pGpioDevice->portPin.port != EPCF_PORT_2 )&&(pGpioDevice->portPin.port != EPCF_PORT_0 ))
        return EPCF_STATUS_NOT_SUPPORTED;

    for(index=0;index<__EPCF_GPIO_INT_MAX;index++)
    {
        if(gpioIntList[index].portPin.pin == pGpioDevice->portPin.pin)
        {

            switch (pGpioDevice->portPin.port)
            {

                case EPCF_PORT_0:
                    if(gpioIntMode[index] == enEPCFGpioIntMode_FallingEdge )//falling edge
                    {
                        PERIPH_GPIOINT->IO0IntEnF |= 1 << pGpioDevice->portPin.pin;
                    }
                    if(gpioIntMode[index] == enEPCFGpioIntMode_RisingEdge) //rising edge
                    {
                        PERIPH_GPIOINT->IO0IntEnR |= 1 << pGpioDevice->portPin.pin;
                    }
                    if(gpioIntMode[index]==enEPCFGpioIntMode_BothEdge)
                    {
                        PERIPH_GPIOINT->IO0IntEnF |= 1 << pGpioDevice->portPin.pin;
                        PERIPH_GPIOINT->IO0IntEnR |= 1 << pGpioDevice->portPin.pin;
                    }
                    break;
                case EPCF_PORT_2:
                    if(gpioIntMode[index] == enEPCFGpioIntMode_FallingEdge )//falling edge
                    {
                        PERIPH_GPIOINT->IO2IntEnF |= 1 << pGpioDevice->portPin.pin;
                    }
                    if(gpioIntMode[index] == enEPCFGpioIntMode_RisingEdge) //rising edge
                    {
                        PERIPH_GPIOINT->IO2IntEnR |= 1 << pGpioDevice->portPin.pin;
                    }
                    if(gpioIntMode[index] ==enEPCFGpioIntMode_BothEdge)
                    {
                        PERIPH_GPIOINT->IO2IntEnF |= 1 << pGpioDevice->portPin.pin;
                        PERIPH_GPIOINT->IO2IntEnR |= 1 << pGpioDevice->portPin.pin;
                    }
                    break;

            }
        }
    }
   // NVIC_EnableIRQ(IRQ_NUM(EINT3));
    gpioIntEnable = enEPCFBoolean_True;

    return EPCF_STATUS_SUCCESS;
}

int8_t epcf_gpio_nativeIntDisable(EPCFGpioDevice_t* pGpioDevice)
{
    //NVIC_DisableIRQ(IRQ_NUM(EINT3));
    gpioIntEnable = enEPCFBoolean_False;

    return EPCF_STATUS_SUCCESS;
}

int8_t epcf_gpio_nativeIntAttachCallback(EPCFGpioDevice_t* pGpioDevice,epcfCallback_fp pCallback)
{
uint8_t index=0;
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
  CHECK_NULL_PTR(pCallback);

#endif  // #if (PCF_ENABLE_DEBUG == PCF_ENABLE)

    for (index = 0; index < __EPCF_GPIO_INT_MAX; index++)
    {
        if(gpioIntList[index].portPin.pin == pGpioDevice->portPin.pin)
        {
            gpioIntCallbackList[index]=pCallback;
            break;
        }
    }

    gpioIntCallbackAttached=enEPCFBoolean_True;

    return EPCF_STATUS_SUCCESS;

}

int8_t epcf_gpio_nativeIntDetachCallback(EPCFGpioDevice_t* pGpioDevice)
{

    uint8_t index=0;
    if(gpioIntCallbackAttached==1)
        return EPCF_STATUS_ERROR;

    for (index = 0; index < __EPCF_GPIO_INT_MAX; index++)
    {
        if(gpioIntList[index].portPin.pin == pGpioDevice->portPin.pin)
        {
            gpioIntCallbackList[index]=0;
            break;
        }
    }

    gpioIntCallbackAttached=enEPCFBoolean_False;

    return EPCF_STATUS_SUCCESS;

}

//void EPCF_EINT3_INT_HANDLER(void)
//{
//    epcfCallback_fp pCallback =0;
//    int8_t index=0;
//    int8_t status=0;
//    status = getCallbackPointer(&pCallback);
//    if(status == enEPCFBoolean_True )
//    {
//        // clear interrupt flag
//         PERIPH_SC->EXTINT  = (1 << EPCF_EXTINT3_CH  );
//         pCallback();
//    }
//    else
//    {
//        for(index = 0; index <(gpioIntId+1); index++)
//        {
//            if(gpioIntList[index].portPin.port == EPCF_PORT_2)
//            {
//                if((PERIPH_GPIOINT->IO2IntStatF & (1<<(gpioIntList[index].portPin.pin)))||(PERIPH_GPIOINT->IO2IntStatR &  (1<<(gpioIntList[index].portPin.pin))))
//                {
//                    PERIPH_GPIOINT->IO2IntClr |=  1<<(gpioIntList[index].portPin.pin);
//                    gpioIntCallbackList[index]();
//
//                }
//            }
//            if(gpioIntList[index].portPin.port == EPCF_PORT_0)
//            {
//                if((PERIPH_GPIOINT->IO0IntStatF & (1<<(gpioIntList[index].portPin.pin)))||(PERIPH_GPIOINT->IO0IntStatR &  (1<<(gpioIntList[index].portPin.pin))))
//                {
//                    PERIPH_GPIOINT->IO0IntClr |=  1<<(gpioIntList[index].portPin.pin);
//                    gpioIntCallbackList[index]();
//
//                }
//            }
//        }
//    }
//
//
//}
//EnEPCFBoolean_t isGpioIntEnable(void)
//{
//    if(gpioIntInit ==enEPCFBoolean_True)
//        return enEPCFBoolean_True;
//    else
//        return enEPCFBoolean_False;
//}
