#define FIFO_ENABLE 1
#if (EPCF_USE_CAN == PCF_YES)
#include "pcf.h"
extern EPCFUartDevice_t	*myUart;

EPCFTime_t fakeTime;
#define __EPCF_PRIVATE_CAN_H_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_PATH/,peripheral/source/,can/,can_hidden.h)
#include  __EPCF_PRIVATE_CAN_H_INCLUDE
#undef __EPCF_PRIVATE_CAN_H_INCLUDE

#define __EPCF_UTILS_CAN_H_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_PATH/,utils/,include/,epcf_string.h)
#include  __EPCF_UTILS_CAN_H_INCLUDE
#undef __EPCF_UTILS_CAN_H_INCLUDE

static epcfCallbackWithArg_fp canCallbackList[2][5];

const uint8_t _can_AltFunction[3][32] =
{
 //0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
  {1, 1, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

//Filter static variable
static uint32_t CAN_std_cnt = 0;
static uint32_t CAN_std_cnt_grp = 0;
static uint32_t CAN_ext_cnt = 0;
static uint32_t CAN_ext_cnt_grp = 0;


static uint8_t *can1RxBuffer = 0;							// CAN1 transmit buffer
static uint8_t *can1TxBuffer = 0;							// CAN1 receive buffer


static uint8_t *can2RxBuffer= 0;								// CAN2 transmit buffer
static uint8_t *can2TxBuffer= 0;								// CAN2 receive buffer

static uint32_t canTxBufferSize=0, canRxBufferSize=0;
static uint32_t canMsgHeader = 0;
static uint32_t canMsgLength = 0;
static uint32_t canMsgId = 0;
static uint32_t intFlags = 0;
static uint32_t  canDeviceCount = CAN_MAX_CHANNEL;
static EPCFCanDevice_t* canDevice[CAN_MAX_CHANNEL] = {0,0};
static EnEPCFBoolean_t canChInit[2] = {0,0};        // initialize flag for the can channel
uint32_t pwr_can_ch[2]      = {PWR_CAN_CH(CAN1_CH),PWR_CAN_CH(CAN2_CH)};
uint32_t pdiv_clk_can_ch[2]  = {PCLK_DIV(CAN1_CH),PCLK_DIV(CAN2_CH)};
uint32_t can_channel_addr[2] = {CAN1_BASE, CAN2_BASE};
// Static Function Declaration
static int8_t _epcfCanInit(EPCFCanCfg_t *pConfig, EPCFCanDevice_t* pCanDevice);
static uint8_t epcfCanSetBaudRate(EPCFCanDevice_t* pCanDevice, uint32_t CANBaudRate,uint32_t canId);
static int8_t epcfCanWriteMessage(EPCFCanDevice_t*  pCanDevice,uint8_t* data);
static int8_t epcfCanReadMessage(EPCFCanDevice_t*  pCanDevice,EPCFpCanRxMessage_t message);
static int8_t epcfCanSetCommand(EPCFCanDevice_t*  pCanDevice,uint32_t cmd, EnEPCFBoolean_t enable);
static int8_t epcfCanPushTxMessage(EPCFCanDevice_t* pCanDevice,uint8_t* dataByte);
static int8_t epcfCanPopTxMessage(EPCFCanDevice_t* pCanDevice,uint8_t* dataByte);
static int8_t epcfCanPushRxMessage(EPCFCanDevice_t*  pCanDevice,EPCFpCanRxMessage_t msg);
static int8_t epcfCanPopRxMessage(EPCFCanDevice_t*  pCanDevice,EPCFpCanRxMessage_t msg);



static uint8_t epcfCanSetBaudRate(EPCFCanDevice_t* pCanDevice,uint32_t pClk, uint32_t CANBaudRate)
{
	uint32_t result = 0,BRP;
	uint8_t nominalTime, TSEG1, TSEG2, BRFail;
	result = pClk / CANBaudRate;
	/* Calculate suitable nominal time value
	 * nominalTime = (TSEG1 + TSEG2 + 3)
	 * nominalTime <= 24
	 * TSEG1 >= 2*TSEG2
	 */
	BRFail = 1;
	for(nominalTime=24;nominalTime>0;nominalTime=nominalTime-2)
	{
		if ((result%nominalTime)==0)
		{
			BRP = result / nominalTime - 1;
			nominalTime--;
			TSEG2 = (nominalTime/3) - 1;
			TSEG1 = nominalTime -(nominalTime/3) - 1;
			BRFail = 0;
			break;
		}
	}
	if(BRFail)
	return 1; // Failed to calculate exact CAN baud rate
	/* Enter reset mode */
	((CAN_TypeDef*)(pCanDevice->canChannelAddr))->MOD = 0x01;
	/* Set bit timing
	 * Default: SAM = 0x00;
	 *          SJW = 0x03;
	 */
	((CAN_TypeDef*)(pCanDevice->canChannelAddr))->BTR  = (TSEG2<<20)|(TSEG1<<16)|(3<<14)|BRP;
	/* Return to normal operating */
	((CAN_TypeDef*)(pCanDevice->canChannelAddr))->MOD = 0;
	return 0;
}

int8_t epcfNativeCanInit(EPCFCanDevice_t* pCanDevice, EPCFCanCfg_t *pCanConfig)
{
  EPCFPinCfg_t pPinCfg;
  int8_t status = EPCF_STATUS_SUCCESS;

#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
  CHECK_NULL_PTR(pCanConfig);
  if(pCanConfig->baudrate > 1000000)
      return (-2);    //Invalid Arguments
  if(pCanConfig->canId > 2)
      return (-2);    //Invalid Arguments
  CHECK_NULL_PTR(pCanConfig->hardwareCfg);
#endif  // PCF_ENABLE_DEBUG


    pCanDevice->canId = pCanConfig->canId;
    pCanDevice->interrupt = pCanConfig->interrupt;
  	(pCanDevice->canChannelAddr) = (CAN_TypeDef*)can_channel_addr[pCanConfig->canId - 1];
	canDevice[pCanConfig->canId - 1] = pCanDevice;


    pPinCfg.direction    = 1; // enEPCFGpioDirOutput
    pPinCfg.mode         = 0; // enEPCFGpioPinModePullUp
    pPinCfg.openDrain    = 0; // open Drain disable
    pPinCfg.portPin.port = ((EPCFCanLpc1768Cfg_t*)(pCanConfig->hardwareCfg))->canTxPin.port;
    pPinCfg.portPin.pin  = ((EPCFCanLpc1768Cfg_t*)(pCanConfig->hardwareCfg))->canTxPin.pin;

    if(pPinCfg.portPin.port == EPCF_PORT_0 || pPinCfg.portPin.port == EPCF_PORT_2 ||(pPinCfg.portPin.port == EPCF_PORT_4))
    {
      pPinCfg.altFunction = _can_AltFunction[pPinCfg.portPin.port][pPinCfg.portPin.pin];
    }
    else
    {
      return -1;
    }

    status = epcfPinInit(&pPinCfg);
    if(status != EPCF_STATUS_SUCCESS)
      return -1;

    pPinCfg.direction    = 0; // enEPCFGpioDirOutput
    pPinCfg.mode         = 0; // enEPCFGpioPinModePullUp
    pPinCfg.openDrain    = 0; // open Drain disable
    pPinCfg.portPin.port = ((EPCFCanLpc1768Cfg_t*)(pCanConfig->hardwareCfg))->canRxPin.port;
    pPinCfg.portPin.pin  = ((EPCFCanLpc1768Cfg_t*)(pCanConfig->hardwareCfg))->canRxPin.pin;
    
    if(pPinCfg.portPin.port == EPCF_PORT_0 || pPinCfg.portPin.port == EPCF_PORT_2 ||(pPinCfg.portPin.port == EPCF_PORT_4))
    {
    	pPinCfg.altFunction = _can_AltFunction[pPinCfg.portPin.port][pPinCfg.portPin.pin];
    }
    else
    {
      return -1;
    }
    status = epcfPinInit(&pPinCfg);
    if(status != EPCF_STATUS_SUCCESS)
      return -1;

    status = _epcfCanInit(pCanConfig, pCanDevice);
    if(status != EPCF_STATUS_SUCCESS)
      return -1;

    canDeviceCount--;
	return EPCF_STATUS_SUCCESS;
}
static int8_t _epcfCanInit(EPCFCanCfg_t *pConfig, EPCFCanDevice_t* pCanDevice)
{
	uint32_t canPclk;
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
	CHECK_NULL_PTR(pConfig);
#endif  // PCF_ENABLE_DEBUG

	// power on CAN1 module
	POWER_ON(pwr_can_ch[pConfig->canId - 1]);

	// set PCLK divider
	epcfNativeSysSetPclkDiv(NULL, pdiv_clk_can_ch[pConfig->canId - 1],CAN_PCLK_DIV);
	epcfNativeSysSetPclkDiv(NULL, PCLK_DIV_ACF,CAN_PCLK_DIV);

	// Put CAN controller in reset mode
    ((CAN_TypeDef*)(pCanDevice->canChannelAddr))->MOD = CAN_MOD_RM;

	// Bypass acceptance filter
	PERIPH_CANAF->AFMR = 2;

	// Set baudrate
	canPclk = epcfNativeSysGetPclk(NULL, pdiv_clk_can_ch[pConfig->canId - 1]);
	epcfCanSetBaudRate(pCanDevice,canPclk,pConfig->baudrate);

	canTxBufferSize=pConfig->txBufferSize;
	canRxBufferSize=pConfig->rxBufferSize;

   // initialize fifo irrespective of interrupt is enabled or disabled.
	if(pConfig->canId==1)
	{
	    // Rx & Tx buffer initialization
	    can1RxBuffer = (uint8_t*)malloc(canRxBufferSize);
	    can1TxBuffer = (uint8_t*)malloc(canTxBufferSize);

	    pcfMemSet(can1RxBuffer, 0, canRxBufferSize);
	    pcfMemSet(can1TxBuffer, 0, canTxBufferSize);

        pCanDevice->canTxFifo = pcfFifoInit(can1TxBuffer, canTxBufferSize);
        if(pCanDevice->canTxFifo == NULL)    // enStatusSuccess
            return EPCF_STATUS_ERROR;

        pCanDevice->canRxFifo = pcfFifoInit(can1RxBuffer, canRxBufferSize);
        if(pCanDevice->canRxFifo == NULL) //enStatusSuccess
            return EPCF_STATUS_ERROR;

	}
	else
	{
	    // Rx & Tx buffer initialization
	    can2RxBuffer = (uint8_t*)malloc(canRxBufferSize);
	    can2TxBuffer = (uint8_t*)malloc(canTxBufferSize);

	    pcfMemSet(can2RxBuffer, 0, canRxBufferSize);
	    pcfMemSet(can2TxBuffer, 0, canTxBufferSize);

        pCanDevice->canTxFifo = pcfFifoInit(can2TxBuffer, canTxBufferSize);
        if(pCanDevice->canTxFifo == NULL)    // enStatusSuccess
            return EPCF_STATUS_ERROR;

        pCanDevice->canRxFifo = pcfFifoInit(can2RxBuffer, canRxBufferSize);
        if(pCanDevice->canRxFifo == NULL) //enStatusSuccess
            return EPCF_STATUS_ERROR;

	}
	if(pCanDevice->interrupt == enEPCFCanIntType_TI_RI || enEPCFCanIntType_TI)
	{
    	((CAN_TypeDef*)(pCanDevice->canChannelAddr))->IER |= BIT_MASK(0);
	}

	if(pCanDevice->interrupt == enEPCFCanIntType_TI_RI || enEPCFCanIntType_RI)
	{
		((CAN_TypeDef*)(pCanDevice->canChannelAddr))->IER |= (BIT_MASK(1) | BIT_MASK(9) | BIT_MASK(10));

	}
	if(pCanDevice->interrupt != enEPCFCanIntType_None)
	{
		NVIC_EnableIRQ(CAN_IRQn);
	}
	// Put CAN controller in operating mode
	((CAN_TypeDef*)(pCanDevice->canChannelAddr))->MOD = 0;

	// Transmitter ready for transmission
	while((((CAN_TypeDef*)(pCanDevice->canChannelAddr))->GSR & CAN_GSR_TBS) == 0);
	canChInit[pCanDevice->canId - 1] = enEPCFBoolean_True;

	//pfCanSetChannelStatus(0,enEPCFBoolean_True);
	return EPCF_STATUS_SUCCESS;
}
int8_t epcf_can_close(EPCFCanDevice_t* pCanDevice)
{
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
	CHECK_NULL_PTR(pConfig);
#endif  // PCF_ENABLE_DEBUG
    canChInit[pCanDevice->canId - 1] = enEPCFBoolean_False;
    pCanDevice->canChBusy = enEPCFBoolean_False;
    // power off CAN0 peripheral
    POWER_OFF(pwr_can_ch[pCanDevice->canId - 1]);
    return EPCF_STATUS_SUCCESS;
}

int8_t epcf_can_setMsgHeader(EPCFCanDevice_t* pCanDevice,EPCFCanMsgHeader_t* pMsgHeader)
{
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
	CHECK_NULL_PTR(pCanDevice);
	CHECK_NULL_PTR(pMsgHeader);
#endif  // PCF_ENABLE_DEBUG
	canMsgId = pMsgHeader->id;
	if(pMsgHeader->frameType == enEPCFCanFrameType_RemoteRequestFrame)
	{
		canMsgHeader |= BIT_MASK(30);
	}
	if(pMsgHeader->frameFormat == enEPCFCanFrameFormat_Extended)
	{
		canMsgHeader |= BIT_MASK(31);
	}
	return 0;
}
/**/
int8_t epcf_can_write(EPCFCanDevice_t* pCanDevice, const uint8_t* data, uint32_t size,EPCFTime_t timeout)
{
	int8_t status;
	uint32_t index =0,remainingBytes=0,cpByte=0;
	uint8_t dataByte[8];
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    // check if the channel is initialized
    CHECK_DEV_INIT(canChInit[pCanDevice->canId - 1]);
    CHECK_NULL_PTR(data);
#endif  // PCF_ENABLE_DEBUG
	remainingBytes = size;
//	if(size > ((canTxBufferSize/CAN_DATA_SIZE) * 8))
//		return EPCF_STATUS_NO_MEMORY;
	if(pCanDevice->interrupt != enEPCFCanIntType_None)
	{
		while(remainingBytes != 0)
		{
			if(remainingBytes >= 8)
				cpByte = 8;
			else
				cpByte =remainingBytes;
			pcfMemCopy(&dataByte,&data[index],cpByte);
			canMsgLength = cpByte;
			remainingBytes -= cpByte;
			index +=cpByte;
			epcfCanPushTxMessage(pCanDevice,dataByte);
		}
		epcfCanPopTxMessage(pCanDevice,&dataByte);
		status = epcfCanWriteMessage(pCanDevice,dataByte);
	}
	else
	{
		while(remainingBytes != 0)
		{
			if(remainingBytes >= 8)
				cpByte = 8;
			else
				cpByte =remainingBytes;
			
			pcfMemCopy(dataByte,&data[index],cpByte);
			canMsgLength = cpByte;
			remainingBytes -= cpByte;
			index +=cpByte;
			status = epcfCanWriteMessage(pCanDevice,dataByte);
			if(status != EPCF_STATUS_SUCCESS)
				return status;

			while((((CAN_TypeDef*)(pCanDevice->canChannelAddr))->SR & CAN_SR_TCS1) == 0);
			while((((CAN_TypeDef*)(pCanDevice->canChannelAddr))->SR & CAN_SR_TCS2) == 0);
			while((((CAN_TypeDef*)(pCanDevice->canChannelAddr))->SR & CAN_SR_TCS3) == 0);
		}
	}
	return status; 	// Success


}

int8_t epcf_can_read(EPCFCanDevice_t*  pCanDevice,EPCFpCanRxMessage_t rxMessage,EPCFTime_t timeout)
{
	int8_t status;
	uint32_t buffCount;
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    // check if the channel is initialized
    CHECK_DEV_INIT(canChInit[pCanDevice->canId - 1]);
    CHECK_NULL_PTR(rxMessage);
#endif  // PCF_ENABLE_DEBUG

	if(pCanDevice->interrupt != enEPCFCanIntType_None)
	{
//#if(FIFO_ENABLE == 1)
		buffCount = epcf_can_getRxBufferCount(pCanDevice);
	#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
		if(status != EPCF_STATUS_SUCCESS)
		{
			return status;
		}
	#endif	// #if (PCF_ENABLE_DEBUG == 1)
		if(buffCount != 0)
		{
			epcfCanPopRxMessage(pCanDevice,rxMessage);
			return EPCF_STATUS_SUCCESS;
		}
		else
		{
			return EPCF_STATUS_ERROR;
		}
	}
	//#endif//(FIFO_ENABLE == 1)
	else
	{
		status = epcfCanReadMessage(pCanDevice,&rxMessage);
		return status;
	}
}
static int8_t epcfCanReadMessage(EPCFCanDevice_t*  pCanDevice,EPCFpCanRxMessage_t message)
{
	uint8_t loop, byteCount = 0;
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    CHECK_DEV_INIT(canChInit[pCanDevice->canId - 1]);
	CHECK_NULL_PTR(message);
#endif	// #if (PCF_ENABLE_DEBUG == 1)
	// Check if there is any unread message in the receive buffer
	if((((CAN_TypeDef*)(pCanDevice->canChannelAddr))->SR & CAN_SR_RBS) == 0)
	{
		return EPCF_STATUS_ERROR;
	}
	// Check data length of received message
	message->header.length = (((CAN_TypeDef*)(pCanDevice->canChannelAddr))->RFS >> 16) & 0x0F;
	if(message->header.length > 8)
	{
		message->header.length = 8;
	}
	
	// Check if the received message is remote frame request
	if((((CAN_TypeDef*)(pCanDevice->canChannelAddr))->RFS & CAN_RFS_RTR) != 0)
	{
		message->header.frameType = enEPCFCanFrameType_RemoteRequestFrame;
	}
	else
	{
		message->header.frameType = enEPCFCanFrameType_DataFrame;
	}
	
	// Check frame format for received message
	if((((CAN_TypeDef*)(pCanDevice->canChannelAddr))->RFS & CAN_RFS_FF) != 0)
	{
		message->header.frameFormat = enEPCFCanFrameFormat_Extended;
	}
	else
	{
		message->header.frameFormat = enEPCFCanFrameFormat_Standard;
	}	
	
	message->header.id = ((CAN_TypeDef*)(pCanDevice->canChannelAddr))->RID;
	
	for(loop = 0; (loop < 4)&&(byteCount < message->header.length); loop++)
	{
		message-> rxData[loop] = ((CAN_TypeDef*)(pCanDevice->canChannelAddr))->RDA >> (loop*8);
		byteCount++;
	}
	for(loop = 0; (loop < 4)&&(byteCount < message->header.length); loop++)
	{
		message->rxData[loop + 4] = ((CAN_TypeDef*)(pCanDevice->canChannelAddr))->RDB >> (loop*8);
		byteCount++;
	}
	while(byteCount < 8)
	{
		message->rxData[byteCount] = 0;
		byteCount++;
	}
		
	epcfCanSetCommand(pCanDevice,CAN_CMR_RRB, enEPCFBoolean_True);
	return EPCF_STATUS_SUCCESS;
}

static int8_t epcfCanWriteMessage(EPCFCanDevice_t*  pCanDevice,uint8_t* data)
{
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
	CHECK_DEV_INIT(canChInit[pCanDevice->canId - 1]);
    CHECK_NULL_PTR(data);
#endif	// PCF_ENABLE_DEBUG
	while(1)
	{
		canMsgHeader |= (canMsgLength << 16);
		// check status for transmit buffer 1
		if((((CAN_TypeDef*)(pCanDevice->canChannelAddr))->SR & CAN_SR_TCS1) == CAN_SR_TCS1)
		{

			((CAN_TypeDef*)(pCanDevice->canChannelAddr))->TFI1 = canMsgHeader;
			((CAN_TypeDef*)(pCanDevice->canChannelAddr))->TID1 = canMsgId;

			((CAN_TypeDef*)(pCanDevice->canChannelAddr))->TDA1 = data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
			((CAN_TypeDef*)(pCanDevice->canChannelAddr))->TDB1 = data[4] | (data[5] << 8) | (data[6] << 16) | (data[7] << 24);
			epcfCanSetCommand(pCanDevice,CAN_CMR_TR | CAN_CMR_STB1, enEPCFBoolean_True);
			break;
		}
		else if((((CAN_TypeDef*)(pCanDevice->canChannelAddr))->SR & CAN_SR_TCS2) == CAN_SR_TCS2)		// check status for transmit buffer 2
		{

			((CAN_TypeDef*)(pCanDevice->canChannelAddr))->TFI2 = canMsgHeader;
			((CAN_TypeDef*)(pCanDevice->canChannelAddr))->TID2 = canMsgId;
			((CAN_TypeDef*)(pCanDevice->canChannelAddr))->TDA2 = data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
			((CAN_TypeDef*)(pCanDevice->canChannelAddr))->TDB2 = data[4] | (data[5] << 8) | (data[6] << 16) | (data[7] << 24);
			epcfCanSetCommand(pCanDevice,CAN_CMR_TR | CAN_CMR_STB2, enEPCFBoolean_True);
			break;
		}
		else if((((CAN_TypeDef*)(pCanDevice->canChannelAddr))->SR & CAN_SR_TCS3) == CAN_SR_TCS3)		// check status for transmit buffer 3
		{

			((CAN_TypeDef*)(pCanDevice->canChannelAddr))->TFI3 = canMsgHeader;
			((CAN_TypeDef*)(pCanDevice->canChannelAddr))->TID3 = canMsgId;
			((CAN_TypeDef*)(pCanDevice->canChannelAddr))->TDA3 = data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
			((CAN_TypeDef*)(pCanDevice->canChannelAddr))->TDB3 = data[4] | (data[5] << 8) | (data[6] << 16) | (data[7] << 24);
			epcfCanSetCommand(pCanDevice,CAN_CMR_TR | CAN_CMR_STB3, enEPCFBoolean_True);
			break;
		}
	}	//while(1)
	return EPCF_STATUS_SUCCESS;
}
static int8_t epcfCanSetCommand(EPCFCanDevice_t*  pCanDevice,uint32_t cmd, EnEPCFBoolean_t enable)
{
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
	CHECK_DEV_INIT(canChInit);
#endif	// #if (PCF_ENABLE_DEBUG == 1)

	if(enable == enEPCFBoolean_True)
	{
		((CAN_TypeDef*)(pCanDevice->canChannelAddr))->CMR |= cmd;
	}
	else
	{
		((CAN_TypeDef*)(pCanDevice->canChannelAddr))->CMR &= ~(cmd);
	}
	return EPCF_STATUS_SUCCESS;
}


static int8_t epcfCanPushTxMessage(EPCFCanDevice_t* pCanDevice,uint8_t* dataByte)
{
	uint8_t loop;
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    CHECK_DEV_INIT(canChInit[pCanDevice->canId - 1]);
	CHECK_NULL_PTR(dataByte);
#endif	// #if (PCF_ENABLE_DEBUG == 1)

	for(loop = 0; loop < 8; loop++)
	{
		pcfFifoPush(pCanDevice->canTxFifo, dataByte[loop]);
	}
	return EPCF_STATUS_SUCCESS;
}

static int8_t epcfCanPopTxMessage(EPCFCanDevice_t* pCanDevice,uint8_t* dataByte)
{
	uint8_t loop;
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    CHECK_DEV_INIT(canChInit[pCanDevice->canId - 1]);
	CHECK_NULL_PTR(dataByte);
#endif	// #if (PCF_ENABLE_DEBUG == 1)
	
	if(pcfFifoIsEmpty(pCanDevice->canTxFifo) == enEPCFBoolean_True)
	{
		return EPCF_STATUS_ERROR;
	}
	for(loop = 0; loop < 8; loop++)
	{
		dataByte[loop] = pcfFifoPop(pCanDevice->canTxFifo);
	}
	
	return EPCF_STATUS_SUCCESS;
}
static int8_t epcfCanPushRxMessage(EPCFCanDevice_t* pCanDevice,EPCFpCanRxMessage_t msg)
{
	uint8_t loop;
	uint8_t* msgPtr;
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    CHECK_DEV_INIT(canChInit[pCanDevice->canId - 1]);
	CHECK_NULL_PTR(msg);
#endif	// #if (PCF_ENABLE_DEBUG == 1)

	msgPtr = (uint8_t*)msg;
	for(loop = 0; loop < CAN_DATA_SIZE; loop++)
	{
		pcfFifoPush(pCanDevice->canRxFifo, *(msgPtr + loop));
	}
	return EPCF_STATUS_SUCCESS;
}

static int8_t epcfCanPopRxMessage(EPCFCanDevice_t* pCanDevice,EPCFpCanRxMessage_t msg)
{
	uint8_t loop;
	uint8_t* msgPtr;
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    CHECK_DEV_INIT(canChInit[pCanDevice->canId - 1]);
	CHECK_NULL_PTR(msg);
#endif	// #if (PCF_ENABLE_DEBUG == 1)

	msgPtr = (uint8_t*)msg;
	if(pcfFifoIsEmpty(pCanDevice->canRxFifo) == enEPCFBoolean_True)
	{
		return EPCF_STATUS_ERROR;
	}
	for(loop = 0; loop < CAN_DATA_SIZE; loop++)
	{
		*(msgPtr + loop) = pcfFifoPop(pCanDevice->canRxFifo);
	}
	return EPCF_STATUS_SUCCESS;
}
EnEPCFBoolean_t epcf_can_getRxFifoEmpty(EPCFCanDevice_t* pCanDevice)
{
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    CHECK_DEV_INIT(canChInit[pCanDevice->canId - 1]);
#endif	// #if (PCF_ENABLE_DEBUG == 1)
    return pcfFifoIsEmpty(pCanDevice->canRxFifo);
}
uint32_t epcf_can_getRxBufferCount(EPCFCanDevice_t* pCanDevice)
{
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    CHECK_DEV_INIT(canChInit[pCanDevice->canId - 1]);
#endif	// #if (PCF_ENABLE_DEBUG == 1)
    return pcfFifoCount(pCanDevice->canRxFifo);
}

int8_t epcf_can_rxBufferFlush(EPCFCanDevice_t* pCanDevice)
{
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    CHECK_DEV_INIT(canChInit[pCanDevice->canId - 1]);
#endif	// #if (PCF_ENABLE_DEBUG == 1)
	pcfFifoFlush(pCanDevice->canRxFifo);
	return EPCF_STATUS_SUCCESS;
}

uint32_t epcf_can_getTxBufferCount( EPCFCanDevice_t* pCanDevice)
{
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    CHECK_DEV_INIT(canChInit[pCanDevice->canId - 1]);
#endif	// #if (PCF_ENABLE_DEBUG == 1)
    return pcfFifoCount(pCanDevice->canTxFifo);
}

int8_t epcf_can_txBufferFlush(EPCFCanDevice_t* pCanDevice)
{
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    CHECK_DEV_INIT(canChInit[pCanDevice->canId - 1]);
#endif	// #if (PCF_ENABLE_DEBUG == 1)
	pcfFifoFlush(pCanDevice->canTxFifo);
	return EPCF_STATUS_SUCCESS;
}

int8_t epcf_can_intEnable(EPCFCanDevice_t* pCanDevice,EnEPCFIntType_t intType)
{
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
	CHECK_NULL_PTR(pCanDevice);
#endif  // PCF_ENABLE_DEBUG
	switch(intType)
	{
		case enEPCFCanIntType_None:break;
		case enEPCFCanIntType_RI:((CAN_TypeDef*)(pCanDevice->canChannelAddr))->IER |= BIT_MASK(0);break;
		case enEPCFCanIntType_TI:((CAN_TypeDef*)(pCanDevice->canChannelAddr))->IER |= (BIT_MASK(1) | BIT_MASK(9) | BIT_MASK(10));break;
		case enEPCFCanIntType_TI_RI:((CAN_TypeDef*)(pCanDevice->canChannelAddr))->IER |= BIT_MASK(0)|(BIT_MASK(1) | BIT_MASK(9) | BIT_MASK(10));break;
		case enEPCFCanIntType_EWI:((CAN_TypeDef*)(pCanDevice->canChannelAddr))->IER |= BIT_MASK(2);break;
		case enEPCFCanIntType_DOI:((CAN_TypeDef*)(pCanDevice->canChannelAddr))->IER |= BIT_MASK(3);break;
		case enEPCFCanIntType_ALI:((CAN_TypeDef*)(pCanDevice->canChannelAddr))->IER |= BIT_MASK(6);break;
		case enEPCFCanIntType_Max:return EPCF_STATUS_INVALID_ARGS;
	}

	NVIC_EnableIRQ(CAN_IRQn);
	return EPCF_STATUS_SUCCESS;
}
int8_t epcf_can_intDisable(EPCFCanDevice_t* pCanDevice,EnEPCFIntType_t intType)
{
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
	CHECK_NULL_PTR(pCanDevice);
#endif  // PCF_ENABLE_DEBUG
	switch(intType)
	{
		case enEPCFCanIntType_None:break;
		case enEPCFCanIntType_RI:((CAN_TypeDef*)(pCanDevice->canChannelAddr))->IER |= INV_BIT_MASK(0);break;
		case enEPCFCanIntType_TI:((CAN_TypeDef*)(pCanDevice->canChannelAddr))->IER |= (INV_BIT_MASK(1) | INV_BIT_MASK(9) | INV_BIT_MASK(10));break;
		case enEPCFCanIntType_TI_RI:((CAN_TypeDef*)(pCanDevice->canChannelAddr))->IER |= INV_BIT_MASK(0)|(INV_BIT_MASK(1) | INV_BIT_MASK(9) | INV_BIT_MASK(10));break;
		case enEPCFCanIntType_EWI:((CAN_TypeDef*)(pCanDevice->canChannelAddr))->IER |= INV_BIT_MASK(2);break;
		case enEPCFCanIntType_DOI:((CAN_TypeDef*)(pCanDevice->canChannelAddr))->IER |= INV_BIT_MASK(3);break;
		case enEPCFCanIntType_ALI:((CAN_TypeDef*)(pCanDevice->canChannelAddr))->IER |= INV_BIT_MASK(6);break;
		case enEPCFCanIntType_Max:return EPCF_STATUS_INVALID_ARGS;
	}
	NVIC_DisableIRQ(CAN_IRQn);
	return EPCF_STATUS_SUCCESS;
}

int8_t epcf_can_intAttachCallback(EPCFCanDevice_t* pCanDevice,EnEPCFCanCallback_t intType,epcfCallbackWithArg_fp pCallback)
{
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
	CHECK_NULL_PTR(pCanDevice);
    CHECK_NULL_PTR(pCallback);
#endif  // PCF_ENABLE_DEBUGCAN_DEBUG == 1)
    canCallbackList[pCanDevice->canId - 1][intType] = pCallback;

    return EPCF_STATUS_SUCCESS;
}
int8_t epcf_can_intDetachCallback(EPCFCanDevice_t* pCanDevice,EnEPCFCanCallback_t intType)
{
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
	CHECK_NULL_PTR(pCanDevice);
#endif  // PCF_ENABLE_DEBUG
    canCallbackList[pCanDevice->canId - 1][intType] = 0;
    return EPCF_STATUS_SUCCESS;
}

int8_t epcf_can_getIntStatus(EPCFCanDevice_t* pCanDevice,uint32_t* status)
{
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
	CHECK_NULL_PTR(status);
#endif	// #if (PCF_ENABLE_DEBUG == 1)
	*status = ((CAN_TypeDef*)(pCanDevice->canChannelAddr))->ICR;
	return EPCF_STATUS_SUCCESS;
}
int8_t epcf_can_getCtrlStatus(EPCFCanDevice_t* pCanDevice,uint32_t* status)
{
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
	CHECK_NULL_PTR(status);
#endif	// #if (PCF_ENABLE_DEBUG == 1)
	*status = ((CAN_TypeDef*)(pCanDevice->canChannelAddr))->SR;
	return EPCF_STATUS_SUCCESS;
}
int8_t epcf_can_getTxErrCounter(EPCFCanDevice_t* pCanDevice,uint8_t* errCount)
{
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    CHECK_DEV_INIT(canChInit[pCanDevice->canId - 1]);
	CHECK_NULL_PTR(errCount);
#endif	// #if (PCF_ENABLE_DEBUG == 1)

	*errCount = ((CAN_TypeDef*)(pCanDevice->canChannelAddr))->GSR >> 24;
	return EPCF_STATUS_SUCCESS;
}
int8_t epcf_can_getRxErrCounter(EPCFCanDevice_t* pCanDevice,uint8_t* errCount)
{
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
    CHECK_DEV_INIT(canChInit[pCanDevice->canId - 1]);
	CHECK_NULL_PTR(errCount);
#endif	// #if (PCF_ENABLE_DEBUG == 1)

	*errCount = ((CAN_TypeDef*)(pCanDevice->canChannelAddr))->GSR >> 16;
	return EPCF_STATUS_SUCCESS;
}

int8_t epcf_can_filterInit(EPCFCanDevice_t* pCanDevice,EPCFpCfgFilter config)
{
#if (PCF_ENABLE_DEBUG == PCF_ENABLE)
	CHECK_NULL_PTR(pCanDevice);
#endif  // PCF_ENABLE_DEBUGCAN_DEBUG == 1)
    uint32_t buf0, buf1, buf2 ,buf3,message = 0;
    uint32_t cnt1, cnt2, bound1;

	// Acceptance Filter Memory full
	if ((((CAN_std_cnt + 1) >> 1) + CAN_std_cnt_grp + CAN_ext_cnt +(CAN_ext_cnt_grp << 1 )) >= 512)
		return EPCF_STATUS_ERROR;                                       // error: objects full

	// Setup Acceptance Filter Configuration
    // Acceptance Filter Mode Register = Off
		PERIPH_CANAF->AFMR = 0x00000001;

	if ((config->msgHeader[0].frameFormat == enEPCFCanFrameFormat_Standard) && ( config->mode ==  enEPCFCanFilterModeIdList)) 	// Add mask for standard identifiers
	{
		config->msgHeader[0].id  |= (pCanDevice->canId-1) << 13;           // Add controller number
		config->msgHeader[0].id  &= 0x0000F7FF;                            // Mask out 16-bits of ID

		// Move all remaining extended mask entries one place up
		// if new entry will increase standard ID filters list
		if ((CAN_std_cnt & 0x0001) == 0 && CAN_ext_cnt != 0 && CAN_std_cnt_grp != 0 && CAN_ext_cnt_grp != 0)
		{
			cnt1   = (CAN_std_cnt >> 1);
			bound1 = ((CAN_ext_cnt_grp * 2) + CAN_ext_cnt +CAN_std_cnt_grp);
			buf0   = PERIPH_CANAF_RAM->mask[cnt1];
			while (bound1--)
			{
				cnt1++;
				buf1 = PERIPH_CANAF_RAM->mask[cnt1];
				PERIPH_CANAF_RAM->mask[cnt1] = buf0;
				buf0 = buf1;
			}
		}

		if(CAN_std_cnt == 0)  	        // For entering first  ID
		{
			PERIPH_CANAF_RAM->mask[0] = 0x0000FFFF | (config->msgHeader[0].id << 16);
		}
		else if (CAN_std_cnt == 1) 		// For entering second ID
		{
			if ((PERIPH_CANAF_RAM->mask[0] >> 16) > config->msgHeader[0].id)
			{
				PERIPH_CANAF_RAM->mask[0] = (PERIPH_CANAF_RAM->mask[0] >> 16) | (config->msgHeader[0].id<< 16);
			}
			else
			{
				PERIPH_CANAF_RAM->mask[0] = (PERIPH_CANAF_RAM->mask[0] & 0xFFFF0000) | config->msgHeader[0].id;
			}
		}
		else
		{
			// Find where to insert new ID
			cnt1 = 0;
			cnt2 = CAN_std_cnt;
			bound1 = (CAN_std_cnt - 1) >> 1;
			while (cnt1 <= bound1)  	     // Loop through standard existing IDs
			{
				if ((PERIPH_CANAF_RAM->mask[cnt1] >> 16) > config->msgHeader[0].id)
				{
					cnt2 = cnt1 * 2;
					break;
				}
				if ((PERIPH_CANAF_RAM->mask[cnt1] & 0x0000FFFF) > config->msgHeader[0].id)
				{
					cnt2 = cnt1 * 2 + 1;
					break;
				}
				cnt1++;               	// cnt1 = U32 where to insert new ID
			}                           // cnt2 = U16 where to insert new ID

			if (cnt1 > bound1)  		// Adding ID as last entry
			{
				if ((CAN_std_cnt & 0x0001) == 0)         // Even number of IDs exists
				{
					PERIPH_CANAF_RAM->mask[cnt1]  = 0x0000FFFF | (config->msgHeader[0].id << 16);
				}
				else                                     // Odd  number of IDs exists
				{
					PERIPH_CANAF_RAM->mask[cnt1]  = (PERIPH_CANAF_RAM->mask[cnt1] & 0xFFFF0000) | config->msgHeader[0].id;
				}
			}
			else
			{
				buf0 = PERIPH_CANAF_RAM->mask[cnt1];		// Remember current entry
				if ((cnt2 & 0x0001) == 0)               	// Insert new mask to even address
				{
					buf1 = (config->msgHeader[0].id << 16) | (buf0 >> 16);
				}
				else                                     	// Insert new mask to odd  address
				{
					buf1 = (buf0 & 0xFFFF0000) | config->msgHeader[0].id;
				}
				PERIPH_CANAF_RAM->mask[cnt1] = buf1;        // Insert mask
				bound1 = CAN_std_cnt >> 1;
				// Move all remaining standard mask entries one place up
				while (cnt1 < bound1)
				{
					cnt1++;
					buf1  = PERIPH_CANAF_RAM->mask[cnt1];
					PERIPH_CANAF_RAM->mask[cnt1] = (buf1 >> 16) | (buf0 << 16);
					buf0  = buf1;
				}
				if ((CAN_std_cnt & 0x0001) == 0)         	// Even number of IDs exists
				{
					PERIPH_CANAF_RAM->mask[cnt1] = (PERIPH_CANAF_RAM->mask[cnt1] & 0xFFFF0000) | (0x0000FFFF);
				}
			}
		}
		CAN_std_cnt++;
	}
  else if ((config->msgHeader[0].frameFormat == enEPCFCanFrameFormat_Standard) && ( config->mode ==  enEPCFCanFilterModeIdGroup))
	{
		 message = ((config->msgHeader[1].id) \
							| ((pCanDevice->canId)<<13) \
		          |((config->msgHeader[0].id)<<16)	\
		          | ((pCanDevice->canId)<<28));

		// Move all remaining extended mask entries one place up
		// if new entry will increase standard ID filters list
		if (CAN_ext_cnt != 0 && CAN_ext_cnt_grp != 0)
		{
			cnt1   = (CAN_std_cnt >> 1) + CAN_std_cnt_grp ;
			bound1 = (CAN_ext_cnt_grp * 2) + CAN_ext_cnt;
			buf0   = PERIPH_CANAF_RAM->mask[cnt1];
			while (bound1--)
			{
				cnt1++;
				buf1 = PERIPH_CANAF_RAM->mask[cnt1];
				PERIPH_CANAF_RAM->mask[cnt1] = buf0;
				buf0 = buf1;
			}
		}
		cnt1 = ((CAN_std_cnt + 1) >> 1);
		cnt2 = 0;
		while (cnt2 < CAN_std_cnt_grp)  			//Loop through standard group existing masks
		{
			if (PERIPH_CANAF_RAM->mask[cnt1] > message)
			{
				break;
			}
			cnt1++;                                    	// cnt1 = U32 where to insert new mask
			cnt2++;
		}

		buf0 = PERIPH_CANAF_RAM->mask[cnt1];            // Remember current entry
		PERIPH_CANAF_RAM->mask[cnt1] = message;              // Insert mask

		CAN_std_cnt_grp++;

		bound1 = CAN_std_cnt_grp - 1;
		// Move all remaining extended mask entries one place up
		while (cnt2 < bound1)
		{
			cnt1++;
			cnt2++;
			buf1 = PERIPH_CANAF_RAM->mask[cnt1];
			PERIPH_CANAF_RAM->mask[cnt1] = buf0;
			buf0 = buf1;
		}
	}
	else if((config->msgHeader[0].frameFormat == enEPCFCanFrameFormat_Extended) && ( config->mode ==  enEPCFCanFilterModeIdList))										// Add mask for extended identifiers
	{
		config->msgHeader[0].id |= (pCanDevice->canId -1) << 29;  		// Add controller number

		if (CAN_ext_cnt_grp != 0)
		{
			cnt1   = (CAN_std_cnt >> 1) + CAN_std_cnt_grp + CAN_ext_cnt;
			bound1 = (CAN_ext_cnt_grp * 2);
			buf0   = PERIPH_CANAF_RAM->mask[cnt1];
			while (bound1--)
			{
				cnt1++;
				buf1 = PERIPH_CANAF_RAM->mask[cnt1];
				PERIPH_CANAF_RAM->mask[cnt1] = buf0;
				buf0 = buf1;
			}
		}
		cnt1 = (((CAN_std_cnt + 1) >> 1) + CAN_std_cnt_grp);
		cnt2 = 0;
		while (cnt2 < CAN_ext_cnt)  			//Loop through extended existing masks
		{
			if (PERIPH_CANAF_RAM->mask[cnt1] > config->msgHeader[0].id)
			{
				break;
			}
			cnt1++;                                    	// cnt1 = U32 where to insert new mask
			cnt2++;
		}

		buf0 = PERIPH_CANAF_RAM->mask[cnt1];            // Remember current entry
		PERIPH_CANAF_RAM->mask[cnt1] = config->msgHeader[0].id;              // Insert mask

		CAN_ext_cnt++;

		bound1 = CAN_ext_cnt - 1;
		// Move all remaining extended mask entries one place up
		while (cnt2 < bound1)
		{
			cnt1++;
			cnt2++;
			buf1 = PERIPH_CANAF_RAM->mask[cnt1];
			PERIPH_CANAF_RAM->mask[cnt1] = buf0;
			buf0 = buf1;
		}
	}

  else
	{
		config->msgHeader[1].id |= (pCanDevice->canId -1) << 29;  		// Add controller number
		config->msgHeader[0].id |= (pCanDevice->canId -1) << 29;  		// Add controller number

		cnt1 = (((CAN_std_cnt + 1) >> 1) + CAN_std_cnt_grp + CAN_ext_cnt);
		cnt2 = 0;
		while (cnt2 < CAN_ext_cnt_grp)  			//Loop through extended existing masks
		{
			if (PERIPH_CANAF_RAM->mask[cnt1] > config->msgHeader[1].id)
			{
				break;
			}
			cnt1++;                                    	// cnt1 = U32 where to insert new mask
			cnt2++;
		}

		buf0 = PERIPH_CANAF_RAM->mask[cnt1];		// Remember current entry
		buf1 = PERIPH_CANAF_RAM->mask[cnt1+1];
		PERIPH_CANAF_RAM->mask[cnt1] = config->msgHeader[0].id; 		// Insert mask
		cnt1++;
		PERIPH_CANAF_RAM->mask[cnt1] = config->msgHeader[1].id;              // Insert mask
		CAN_ext_cnt_grp++;
    cnt1--;
		bound1 = (CAN_ext_cnt_grp -1) * 2;
		// Move all remaining extended mask entries one place up
		while (cnt2 < bound1)
		{
			cnt1 = cnt1+2;
			cnt2 = cnt2+2;
			buf2 = PERIPH_CANAF_RAM->mask[cnt1];
			buf3 = PERIPH_CANAF_RAM->mask[cnt1+1];
			PERIPH_CANAF_RAM->mask[cnt1] = buf0;
			PERIPH_CANAF_RAM->mask[cnt1+1] = buf1;
			buf0 = buf2;
			buf1 = buf3;
		}

	}
	// Calculate std ID start address (buf0) and ext ID start address (buf1)
	buf0 = ((CAN_std_cnt + 1) >> 1) << 2;
	cnt1 =  buf0 + (CAN_std_cnt_grp << 2);
	buf1 = cnt1 + (CAN_ext_cnt << 2);
	buf2 = buf1 + (CAN_ext_cnt_grp <<3);

	// Setup acceptance filter pointers
	PERIPH_CANAF->SFF_sa     = 0;
	PERIPH_CANAF->SFF_GRP_sa = buf0;
	PERIPH_CANAF->EFF_sa     = cnt1;
	PERIPH_CANAF->EFF_GRP_sa = buf1;
	PERIPH_CANAF->ENDofTable = buf2;

	PERIPH_CANAF->AFMR = 0x00000000;
	return EPCF_STATUS_SUCCESS;
}

void CAN_INT_HANDLER(void)
{
	uint8_t txMsg[8];
	EPCFCanRxMessage_t rxMsg;
	if(canChInit[0]==enEPCFBoolean_True)
	{
		intFlags = PERIPH_CAN1->ICR;

		// Check CAN1 RX flag
		if((intFlags & CAN_ICR_RI) != 0)
		{
		    epcfCanReadMessage(canDevice[0],&rxMsg);
		    epcfCanPushRxMessage(canDevice[0],&rxMsg);
			if(canCallbackList[0][enEPCFCanCallback_RxCallback] != 0)
			{
                canCallbackList[0][enEPCFCanCallback_RxCallback](canDevice[0]);
            }
		}
		// Check CAN1 TX flags
		if((intFlags & CAN_ICR_TI1) != 0)
		{
		    epcfCanSetCommand(canDevice[0],CAN_CMR_STB1, enEPCFBoolean_False);

		    if(pcfFifoIsEmpty(canDevice[0]->canTxFifo) == enEPCFBoolean_False)
		    {
				epcfCanPopTxMessage(canDevice[0],&txMsg);
				epcfCanWriteMessage(canDevice[0],&txMsg);
		    }
			if(canCallbackList[0][enEPCFCanCallback_Buff1TxCallback] != 0)
			{
				canCallbackList[0][enEPCFCanCallback_Buff1TxCallback](canDevice[0]);
            }
		}
		if((intFlags & CAN_ICR_TI2) != 0)
		{
		    epcfCanSetCommand(canDevice[0],CAN_CMR_STB2, enEPCFBoolean_False);

		    if(pcfFifoIsEmpty(canDevice[0]->canTxFifo) == enEPCFBoolean_False)
		    {
				epcfCanPopTxMessage(canDevice[0],&txMsg);
				epcfCanWriteMessage(canDevice[0],&txMsg);
		    }
			if(canCallbackList[0][enEPCFCanCallback_Buff2TxCallback] != 0)
			{
				canCallbackList[0][enEPCFCanCallback_Buff2TxCallback](canDevice[0]);
			}
		}
		if((intFlags & CAN_ICR_TI3) != 0)
		{
		    epcfCanSetCommand(canDevice[0],CAN_CMR_STB1, enEPCFBoolean_False);

		    if(pcfFifoIsEmpty(canDevice[0]->canTxFifo) == enEPCFBoolean_False)
		    {
				epcfCanPopTxMessage(canDevice[0],&txMsg);
				epcfCanWriteMessage(canDevice[0],&txMsg);
		    }
            if(canCallbackList[0][enEPCFCanCallback_Buff2TxCallback] != 0)
			{
				canCallbackList[0][enEPCFCanCallback_Buff2TxCallback](canDevice[0]);
            }
		}
        if(((intFlags & CAN_ICR_EI) != 0) || ((intFlags & CAN_ICR_EPI) != 0) || ((intFlags & CAN_ICR_BEI) != 0))        //either Error Warning or Error Passive or Bus Error Interrupt
        {
            if(canCallbackList[0][enEPCFCanCallback_ErrCallback] != 0)
			{
				canCallbackList[0][enEPCFCanCallback_ErrCallback](canDevice[0]);
            }
        }
	}

	if(canChInit[1]==enEPCFBoolean_True)
	{
		intFlags = PERIPH_CAN2->ICR;

		// Check CAN1 RX flag
		if((intFlags & CAN_ICR_RI) != 0)
		{
		    epcfCanReadMessage(canDevice[1],&rxMsg);
		    epcfCanPushRxMessage(canDevice[1],&rxMsg);
			if(canCallbackList[1][enEPCFCanCallback_RxCallback] != 0)
			{
                canCallbackList[1][enEPCFCanCallback_RxCallback](canDevice[1]);
            }
		}
		// Check CAN1 TX flags
		if((intFlags & CAN_ICR_TI1) != 0)
		{
		    epcfCanSetCommand(canDevice[1],CAN_CMR_STB1, enEPCFBoolean_False);

		    if(pcfFifoIsEmpty(canDevice[1]->canTxFifo) == enEPCFBoolean_False)
		    {
				epcfCanPopTxMessage(canDevice[1],&txMsg);
				epcfCanWriteMessage(canDevice[1],&txMsg);
		    }
			if(canCallbackList[1][enEPCFCanCallback_Buff1TxCallback] != 0)
			{
				canCallbackList[1][enEPCFCanCallback_Buff1TxCallback](canDevice[1]);
            }
		}
		if((intFlags & CAN_ICR_TI2) != 0)
		{
		    epcfCanSetCommand(canDevice[1],CAN_CMR_STB1, enEPCFBoolean_False);

		    if(pcfFifoIsEmpty(canDevice[1]->canTxFifo) == enEPCFBoolean_False)
		    {
				epcfCanPopTxMessage(canDevice[1],&txMsg);
				epcfCanWriteMessage(canDevice[1],&txMsg);
		    }
			if(canCallbackList[1][enEPCFCanCallback_Buff2TxCallback] != 0)
			{
				canCallbackList[1][enEPCFCanCallback_Buff2TxCallback](canDevice[1]);
			}
		}
		if((intFlags & CAN_ICR_TI3) != 0)
		{
		    epcfCanSetCommand(canDevice[1],CAN_CMR_STB1, enEPCFBoolean_False);

		    if(pcfFifoIsEmpty(canDevice[1]->canTxFifo) == enEPCFBoolean_False)
		    {
				epcfCanPopTxMessage(canDevice[1],&txMsg);
				epcfCanWriteMessage(canDevice[1],&txMsg);
		    }
            if(canCallbackList[1][enEPCFCanCallback_Buff2TxCallback] != 0)
			{
				canCallbackList[1][enEPCFCanCallback_Buff2TxCallback](canDevice[1]);
            }
		}
        if(((intFlags & CAN_ICR_EI) != 0) || ((intFlags & CAN_ICR_EPI) != 0) || ((intFlags & CAN_ICR_BEI) != 0))        //either Error Warning or Error Passive or Bus Error Interrupt
        {
            if(canCallbackList[1][enEPCFCanCallback_ErrCallback] != 0)
			{
				canCallbackList[1][enEPCFCanCallback_ErrCallback](canDevice[1]);
            }
        }
	}	//  if(canChInit[1] == enEPCFBoolean_True)

}



#endif
