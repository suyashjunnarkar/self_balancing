/**
 * \file        packet.h
 * \brief       To create data transmission packets
 * \copyright   Copyright (c) 2014 <br> PhiRobotics Research Pvt Ltd
 * 
 */
 
#ifndef __EPCF_INCLUDED_UTIS_INCLUDE_PACKET_H
#define __EPCF_INCLUDED_UTIS_INCLUDE_PACKET_H

typedef struct EPCFAdapter EPCFAdapter_t;

#define TOTAL_MODULES		5	//total modules supported, MAX:127
#define TOTAL_COMMANDS		20	//total commands as per GPIO module, MAX:127

//Module Ids
#define	MODULE_ID_SYSTEM	0
#define	MODULE_ID_GPIO		1
#define	MODULE_ID_UART		2

//System module commands
#define CMD_SYSTEM_GET_PROTOCOL_VER		0

//Function pointer to register the module callback
typedef void (*epcfCommandCallback_fp)(uint8_t*, uint8_t);

typedef enum EPCFEnMsgType
{
	enEPCFUseNative,
	enEPCFUseExtended
}EPCFEnMsgType_t;

typedef struct EPCFHeaderCfg
{
	EnEPCFBoolean_t	isResponseMsg;
	uint8_t 		moduleId;
	uint8_t 		commandId;
	EPCFEnMsgType_t msgType;
	uint8_t*		txData;
	uint8_t 		txDataSize;
}EPCFHeaderCfg_t;

void epcfPacketInit(EPCFAdapter_t *pAdapter);
int8_t epcfSendMessage(EPCFAdapter_t *pAdapter, EPCFHeaderCfg_t *pHeader, uint8_t *rxData);
int8_t epcfReceiveMessage(EPCFAdapter_t *pAdapter, uint8_t *rxData);
int8_t attachCallback(uint8_t moduleId, uint8_t commandId, epcfCommandCallback_fp pCommandCallback);
int8_t deattachCallback(uint8_t moduleId, uint8_t commandId);

#endif      //__EPCF_INCLUDED_UTIS_INCLUDE_PACKET_H

