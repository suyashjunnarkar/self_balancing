/**
 * \file  adapter.h
 * \brief This file is used to configure a native UART peripheral in extended mode.
 */

#ifndef __EPCF_INCLUDED_EXTENDED_ADAPTER_ADAPTER_H
#define __EPCF_INCLUDED_EXTENDED_ADAPTER_ADAPTER_H

typedef struct EPCFAdapter EPCFAdapter_t;

typedef int32_t (*epcfAdapterWrite_fp)(EPCFAdapter_t*, const uint8_t*, uint32_t, EPCFTime_t);
typedef int32_t (*epcfAdapterRead_fp)(EPCFAdapter_t*, uint8_t*, uint32_t, EPCFTime_t);
typedef int8_t (*epcfAdapterAttachCallback_fp)(EPCFAdapter_t*, epcfCallback_fp);
typedef int8_t (*epcfAdapterDetachCallback_fp)(EPCFAdapter_t*, epcfCallback_fp);

#define UART_ADAPTER_ID		0

typedef struct EPCFAdapter
{
	uint8_t							adapterId;
	epcfAdapterWrite_fp 			adapterWrite;
	epcfAdapterRead_fp 				adapterRead;
	epcfAdapterAttachCallback_fp	adapterAttachCallback;
	epcfAdapterDetachCallback_fp	adapterDetachCallback;
	void*							pDevice;		
}EPCFAdapter_t;

EPCFAdapter_t* epcfCreateAdapter(uint8_t adapterId, void* pConfig);
EPCFAdapter_t* epcfCreateAdapter(uint8_t adapterId, void *pConfig);
int8_t epcfCloseAdapter(uint8_t adapterId, EPCFAdapter_t* pAdapter);

#endif //__EPCF_INCLUDED_EXTENDED_ADAPTER_ADAPTER_H
