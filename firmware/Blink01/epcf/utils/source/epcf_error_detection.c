#include "epcf.h"

#define __EPCF_UTIL_ERROR_DETECTION_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_PATH/,utils/,include/,epcf_error_detection.h)
#include  __EPCF_UTIL_ERROR_DETECTION_INCLUDE
#undef __EPCF_UTIL_ERROR_DETECTION_INCLUDE

int8_t epcfComputeParity(uint8_t *data, uint8_t size, EPCFEnParityType_t parityType)
{
	uint8_t value=0, bitVal=0;
	uint8_t byte, bit;
	
	for(byte=0;byte<size;byte++)
	{
		for(bit=0;bit<8;bit++)
		{
			bitVal = (data[byte] & 1<<bit)>>bit;
			value ^= bitVal;
		}
	}
	if(parityType == enEPCFOddParity)
	{
		if(value == 1)
			return 0;
		else 
			return 1;
	}
	else if(parityType == enEPCFEvenParity)
	{
		if(value == 1)
			return 1;
		else
			return 0;
	}
	else
		return EPCF_STATUS_ERROR;
}

uint8_t epcfValidateData_parity(uint8_t *data, uint8_t size, uint8_t parity, EPCFEnParityType_t parityType)
{
	uint8_t byte, bit;
	uint8_t value=0, bitVal;
	
	for(byte=0;byte<size;byte++)
	{
		for(bit=0;bit<8;bit++)
		{
			bitVal = (data[byte] & 1<<bit)>>bit;
			value ^= bitVal;
		}
	}
	value ^= parity;
	if(parityType == enEPCFOddParity)
	{
		if(value == 1)
			return enEPCFBoolean_True;		//no error
		else
			return enEPCFBoolean_False;		//error
	}
	else if(parityType == enEPCFEvenParity)
	{
		if(value == 1)
			return enEPCFBoolean_False;		//error
		else
			return enEPCFBoolean_True;		//no error
	}
	else
		return enEPCFBoolean_False;
}

uint8_t epcfComputeLRCCheckSequence(uint8_t *data, uint8_t size)
{
	uint8_t value=0;
	uint8_t byte;
	
	for(byte=0;byte<size;byte++)
	{
		value ^= data[byte];
	}
	return value;
}

uint8_t epcfValidateData_LRCCheckSequence(uint8_t *data,uint8_t size,uint8_t lrcCheckSequence)
{
	uint8_t value=0;
	uint8_t byte;
	
	for(byte=0;byte<size;byte++)
	{
		value ^= data[byte];
	}
	value ^= lrcCheckSequence;
	
	if(value == 0)
		return enEPCFBoolean_True;
	else
		return enEPCFBoolean_False;
}
