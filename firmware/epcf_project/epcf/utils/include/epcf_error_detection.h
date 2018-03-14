/**
 * \file        error_detection.h
 * \brief       To detect errors in data transmission
 * \copyright   Copyright (c) 2014 <br> PhiRobotics Research Pvt Ltd
 * 
 */
 
#ifndef __EPCF_INCLUDED_UTILS_INCLUDE_ERROR_DETECTION_H
#define __EPCF_INCLUDED_UTILS_INCLUDE_ERROR_DETECTION_H

typedef enum EPCFEnParityType
{
	enEPCFOddParity,
	enEPCFEvenParity
}EPCFEnParityType_t;

int8_t epcfComputeParity(uint8_t *data, uint8_t size, EPCFEnParityType_t parityType);
uint8_t epcfValidateData_parity(uint8_t *data, uint8_t size, uint8_t parity, EPCFEnParityType_t parityType);

uint8_t epcfComputeLRCCheckSequence(uint8_t *data, uint8_t size);
uint8_t epcfValidateData_LRCCheckSequence(uint8_t *data, uint8_t size, uint8_t lrcCheckSequence);


#endif      //__EPCF_INCLUDED_UTILS_INCLUDE_ERROR_DETECTION_H
