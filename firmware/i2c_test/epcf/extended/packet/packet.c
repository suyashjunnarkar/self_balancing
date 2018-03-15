#include "epcf.h"

#define PROTOCOL_VERSION_MAJOR		1
#define PROTOCOL_VERSION_MINOR		0

//Send packet via adapter
#define EPCF_SEND_PACKET(pAdapter,txData,txDataSize, timeout)				\
		pAdapter->adapterWrite(pAdapter, (const uint8_t*)txData, txDataSize, timeout)

//Receive packet via adapter
#define EPCF_GET_RECEIVED_PACKET(pAdapter,rxData,rxDataSize, timeout)		\
		pAdapter->adapterRead(pAdapter, rxData, rxDataSize, timeout);

static uint8_t _epcfCreatePacket(uint8_t* pPacket, EPCFHeaderCfg_t *pHeader);
static int8_t _epcfGetPacket(EPCFAdapter_t *pAdapter, uint8_t* pPacket);
static int8_t _epcfIsDataAvailable(EPCFAdapter_t *pAdapter);

//System messages
static void _epcfGetProtocolVersion(uint8_t *rxData, uint8_t dummy);

#define MAX_PAYLOAD_SIZE	30
#define PACKET_PADDING		3

static uint8_t txPacket[MAX_PAYLOAD_SIZE + PACKET_PADDING] = {0};
static uint8_t rxPacket[MAX_PAYLOAD_SIZE + PACKET_PADDING] = {0};
static EPCFAdapter_t *pLocalAdapter;
static EPCFTime_t fakeTime;

static epcfCommandCallback_fp cmdCallbackList[TOTAL_MODULES][TOTAL_COMMANDS] =
{
	{0}
};

void epcfPacketInit(EPCFAdapter_t *pAdapter)
{
	pLocalAdapter = pAdapter;
	attachCallback(MODULE_ID_SYSTEM, CMD_SYSTEM_GET_PROTOCOL_VER, _epcfGetProtocolVersion);
}

int8_t epcfSendMessage(EPCFAdapter_t *pAdapter, EPCFHeaderCfg_t *pHeader, uint8_t *rxData)
{
	int8_t retVal=0;
	uint8_t txPacketSize=0;

	txPacketSize = _epcfCreatePacket(txPacket, pHeader);

	//Send Packet
	retVal = EPCF_SEND_PACKET(pAdapter, txPacket, txPacketSize, fakeTime);
	if(retVal < 0)
		return -1;			//error in sending packet
	
	if(pHeader->isResponseMsg == enEPCFBoolean_False)
	{
		retVal = epcfReceiveMessage(pAdapter, rxData);		//Wait for Acknowledgement
		if(retVal < 0)
			return -1;			//error in receiving packet
	}
	return EPCF_STATUS_SUCCESS;
}

int8_t epcfReceiveMessage(EPCFAdapter_t *pAdapter, uint8_t *rxData)
{
	uint8_t stx, moduleId, commandId, dataLen,responseMsgFlag;
	uint8_t  rxPacketIndex=0;
	int8_t retVal=0;

	retVal = _epcfGetPacket(pAdapter, rxPacket);
	if(retVal < 0)
		return retVal;

	//Now parse the received packet
	stx 		= rxPacket[rxPacketIndex++];
	moduleId 	= rxPacket[rxPacketIndex++];
	commandId	= rxPacket[rxPacketIndex++];
	dataLen		= rxPacket[rxPacketIndex++];
	rxPacketIndex += 1;							//neglecting reserved byte

	responseMsgFlag = ((commandId & ((uint8_t)BIT_MASK(BIT_7))) >> BIT_7);
	if(responseMsgFlag)
	{
		memcpy(rxData, &(rxPacket[rxPacketIndex]),dataLen);
		return EPCF_STATUS_SUCCESS;
	}
	else
	{
		if(cmdCallbackList[moduleId][commandId] != NULL)
		{
			cmdCallbackList[moduleId][commandId](&(rxPacket[rxPacketIndex]), dataLen);
		}
	}
	return dataLen;
}

int8_t attachCallback(uint8_t moduleId, uint8_t commandId, epcfCommandCallback_fp pCommandCallback)
{
	if(moduleId < TOTAL_MODULES)
	{
		if(commandId < TOTAL_COMMANDS)
		{
			cmdCallbackList[moduleId][commandId] = pCommandCallback;
			return EPCF_STATUS_SUCCESS;
		}
		else
		{
			return -1;
		}
	}
	else
	{
		return -1;
	}
}

int8_t deattachCallback(uint8_t moduleId, uint8_t commandId)
{
	if(moduleId < TOTAL_MODULES)
	{
		if(commandId < TOTAL_COMMANDS)
		{
			cmdCallbackList[moduleId][commandId] = NULL;
			return EPCF_STATUS_SUCCESS;
		}
		else
		{
			return -1;
		}
	}
	else
	{
		return -1;
	}
}

static int8_t _epcfIsDataAvailable(EPCFAdapter_t *pAdapter)
{
	uint8_t stx=0;
	int8_t retVal=0;

	//Receive start byte
	retVal = EPCF_GET_RECEIVED_PACKET(pAdapter, &stx, 1, fakeTime);
	if(retVal < 0)
		return retVal;				//error in receiving STX

	if (stx == '$')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

static int8_t _epcfGetPacket(EPCFAdapter_t *pAdapter, uint8_t* pPacket)
{
	int8_t retVal=0;
	uint8_t dataLen=0;
	uint8_t rxPacketIndex=0;

	retVal = _epcfIsDataAvailable(pAdapter);		//checking STX of the packet
	if(retVal < 0)
		return -1;								//error in receiving data length
	else
	{
		if(retVal == 0)
			return EPCF_STATUS_PACKET_ERROR;
		else
			pPacket[rxPacketIndex++] = '$';
	}

	//Receive Module Id
	retVal = EPCF_GET_RECEIVED_PACKET(pAdapter, &(pPacket[rxPacketIndex++]),1, fakeTime);
	if(retVal < 0)
		return -1;								//error in receiving module ID

	//Receive command
	retVal = EPCF_GET_RECEIVED_PACKET(pAdapter, &(pPacket[rxPacketIndex++]),1, fakeTime);
	if(retVal < 0)
		return -1;								//error in receiving command

	//Receive Data length
	retVal = EPCF_GET_RECEIVED_PACKET(pAdapter, &(pPacket[rxPacketIndex++]),1, fakeTime);
	if(retVal < 0)
		return -1;								//error in receiving data length
	dataLen  = pPacket[rxPacketIndex-1];

	//Receive Reserved byte
	retVal = EPCF_GET_RECEIVED_PACKET(pAdapter, &(pPacket[rxPacketIndex++]),1, fakeTime);
	if(retVal < 0)
		return -1;								//error in receiving data length

	//Receive Rest of the packet
	retVal = EPCF_GET_RECEIVED_PACKET(pAdapter, &(pPacket[rxPacketIndex]),dataLen, fakeTime);
	if(retVal < 0)
		return -1;								//error in receiving rest of the packet

	rxPacketIndex += dataLen;

	//Receive Error checking sequence
	retVal = EPCF_GET_RECEIVED_PACKET(pAdapter, &(pPacket[rxPacketIndex++]),1, fakeTime);
	if(retVal < 0)
		return -1;								//error in receiving rest of the packet

	retVal = epcfValidateData_LRCCheckSequence(pPacket, rxPacketIndex-1, pPacket[rxPacketIndex-1]);
	if(retVal == enEPCFBoolean_True)
	{
		rxPacketIndex += 1;
		return rxPacketIndex;								//valid packet
	}
	else
		return -1;
}

static uint8_t _epcfCreatePacket(uint8_t* pPacket, EPCFHeaderCfg_t *pHeader)
{
	uint32_t index=0;
	uint8_t packetIndex=0;
	
	//STX - '$'
	pPacket[packetIndex++] = '$';

	//Peripheral Id and Role bit
	if(pHeader->msgType == enEPCFUseNative)
	{
		pPacket[packetIndex++] = (pHeader->moduleId) & ((uint8_t)INV_BIT_MASK(BIT_7));
	}
	else
	{
		pPacket[packetIndex++] = (pHeader->moduleId) | ((uint8_t)BIT_MASK(BIT_7));
	}

	//Command and response flag
	if(pHeader->isResponseMsg == enEPCFBoolean_True)
	{
		pPacket[packetIndex++] = (pHeader->commandId) | ((uint8_t)BIT_MASK(BIT_7));
	}
	else
	{
		pPacket[packetIndex++] = (pHeader->commandId) & ((uint8_t)INV_BIT_MASK(BIT_7));
	}

	//Data Length
	pPacket[packetIndex++] = pHeader->txDataSize;
	
	//Reserved byte
	pPacket[packetIndex++] = 0xFF;

	//Data
	for(index=0;index<(pHeader->txDataSize);index++)
	{
		pPacket[packetIndex] = pHeader->txData[index];
		packetIndex += 1;
	}
	
	//Error checking sequence
	pPacket[packetIndex] = epcfComputeLRCCheckSequence(pPacket, packetIndex);
	packetIndex += 1;

	return packetIndex;
}

static void _epcfGetProtocolVersion(uint8_t *rxData,uint8_t dummy)
{
	EPCFHeaderCfg_t txHeader;
	uint8_t txData[2], txDataIndex=0;

	txData[txDataIndex++] = PROTOCOL_VERSION_MAJOR;
	txData[txDataIndex++] = PROTOCOL_VERSION_MINOR;

	txHeader.moduleId 		= MODULE_ID_SYSTEM;
	txHeader.commandId 		= CMD_SYSTEM_GET_PROTOCOL_VER;
	txHeader.isResponseMsg 	= enEPCFBoolean_True;
	txHeader.msgType		= enEPCFUseNative;
	txHeader.txData			= txData;
	txHeader.txDataSize		= txDataIndex;

	epcfSendMessage(pLocalAdapter, &txHeader, rxData);
	//We can add retries if epcfSendMessage() fails.
}
