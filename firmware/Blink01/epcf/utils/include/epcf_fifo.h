/**
 * \file  pcf_fifo.h
 * \brief FIFO library utility functions
 */
 
#ifndef __PCF_INCLUDED_UTILS_FIFO_H
#define __PCF_INCLUDED_UTILS_FIFO_H

/** \brief To enable or disable FIFO overwrite          */
#define PCF_FIFO_OVERWRITE_ENABLE               1

/** \brief	FIFO descriptor    		*/
typedef struct PCFFifoDesc PCFFifoDesc_t;

/**
 * \brief Initializes FIFO.
 *
 * \param pBuf pointer to storage buffer.
 * \param uSize size of storage buffer.
 *
 * \return return FIFO descriptor. Refer to "../common/status.h" header file for the appropriate status codes.
 */
PCFFifoDesc_t* pcfFifoInit(uint8_t* pBuf, uint32_t uSize);

/**
 * \brief Returns length of the FIFO.
 *
 * \param pFifo pointer to FIFO descriptor.
 *
 * \return length of the FIFO.
 */
uint32_t pcfFifoLength(PCFFifoDesc_t* pFifo);

/**
 * \brief This function pushes byte into the FIFO.
 *
 * \param pFifo pointer to FIFO descriptor.
 * \param c byte to be pushed.
 *
 * \return enEPCFBooleanTrue : success
 *         enEPCFBooleanFalse: error
 */
EnEPCFBoolean_t pcfFifoPush(PCFFifoDesc_t* pFifo, uint8_t c);

/**
 * \brief This function pops a byte from the FIFO.
 *
 * \param pFifo pointer to FIFO descriptor.
 *
 * \return popped byte.
 */
uint8_t pcfFifoPop(PCFFifoDesc_t* pFifo);

/**
 * \brief This function empties the FIFO.
 *
 * \param pFifo pointer to FIFO descriptor.
 */
void pcfFifoFlush(PCFFifoDesc_t* pFifo);

/**
 * \brief This function checks whether the FIFO is empty.
 *
 * \param pFifo pointer to FIFO descriptor.
 *
 * \return enEPCFBoolean_True if FIFO is empty, otherwise enPCFBooleanFalse.
 */
EnEPCFBoolean_t pcfFifoIsEmpty(const PCFFifoDesc_t* pFifo);

/**
 * \brief This function checks whether the FIFO is full.
 *
 * \param pFifo pointer to FIFO descriptor.
 *
 * \return enEPCFBoolean_True if FIFO is full, otherwise enPCFBooleanFalse.
 */
EnEPCFBoolean_t pcfFifoIsFull(const PCFFifoDesc_t* pFifo);

uint32_t pcfFifoCount(PCFFifoDesc_t* pFifo);

#endif		//__PCF_INCLUDED_UTILS_FIFO_H
