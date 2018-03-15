#include "pcf.h"

#define __EPCF_UTILS_FIFO_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_PATH/,utils/,include/,epcf_fifo.h)
#include __EPCF_UTILS_FIFO_INCLUDE
#undef __EPCF_UTILS_FIFO_INCLUDE

/** \brief FIFO descriptor */
typedef struct PCFFifoDesc
{
  uint8_t* pBegin;          /**< pointer to the beginning of storage buffer */
  uint8_t* volatile pHead;  /**< pointer to the first element               */
  uint8_t* volatile pTail;  /**< pointer to the last element                */
  uint8_t* pEnd;            /**< pointer to the end of storage buffer       */
  uint32_t size;            /**< fifo buffer size in bytes                  */
  uint32_t count;           /**< count of the elements in buffer            */
}PCFFifoDesc_t;

PCFFifoDesc_t* pcfFifoInit(uint8_t* pBuf, uint32_t uSize)
{
    PCFFifoDesc_t* pFifo;
    
#if (PF_UTILS_DEBUG == 1)
	if(pBuf == 0)
	{
		return EPCF_STATUS_INVALID_ARGS;
	}
#endif	//	#if (PF_UTILS_DEBUG == 1)
        
    pFifo = (PCFFifoDesc_t*)malloc(sizeof(PCFFifoDesc_t));
    if(pFifo == 0)
        return NULL;
    
	pFifo->pHead = pBuf;
	pFifo->pTail = pBuf;
	pFifo->pBegin = pBuf;
	pFifo->pEnd = pBuf + uSize - 1;
	pFifo->size = uSize;
	pFifo->count = 0;
	
	if(pFifo->pBegin > pFifo->pEnd)
	{
		return NULL;
	}
	return pFifo;
}

uint32_t pcfFifoLength(PCFFifoDesc_t* pFifo)
{
	return pFifo->size;
}


uint32_t pcfFifoCount(PCFFifoDesc_t* pFifo)
{
	return pFifo->count;
}


EnEPCFBoolean_t pcfFifoPush(PCFFifoDesc_t* pFifo, uint8_t c)
{
	if(pFifo->count < pFifo->size)
	{
		*(pFifo->pTail) = c;
		pFifo->count++;
		if (pFifo->pTail == pFifo->pEnd)
		{
			pFifo->pTail = pFifo->pBegin;
		}
		else
		{
			pFifo->pTail++;
		}
	}
	else
	{
	#if(PF_FIFO_OVERWRITE_ENABLE == 0)
		return enEPCFBoolean_False;
	#else
		*(pFifo->pTail) = c;
		if(pFifo->pTail == pFifo->pHead)
		{
			if (pFifo->pTail == pFifo->pEnd)
			{
				pFifo->pTail = pFifo->pBegin;
				pFifo->pHead = pFifo->pBegin;
			}
			else
			{
				pFifo->pTail++;
				pFifo->pHead++;
			}
		}
	#endif
	}
	return enEPCFBoolean_True;
}

uint8_t pcfFifoPop(PCFFifoDesc_t* pFifo)
{
	if(pFifo->count == 0)
	{
		return 0xFF;
	}
	pFifo->count--;
	if (pFifo->pHead == pFifo->pEnd)
	{
		pFifo->pHead = pFifo->pBegin;
		return *(pFifo->pEnd);
	}
	else
	{
		return *(pFifo->pHead++);
	}
}

void pcfFifoFlush(PCFFifoDesc_t* pFifo)
{
	pFifo->pHead = pFifo->pTail;
	pFifo->count = 0;
}

EnEPCFBoolean_t pcfFifoIsEmpty(const PCFFifoDesc_t* pFifo)
{
	return ( (pFifo->count > 0) ? enEPCFBoolean_False : enEPCFBoolean_True);
}

EnEPCFBoolean_t pcfFifoIsFull(const PCFFifoDesc_t* pFifo)
{
	return ( (pFifo->count < pFifo->size) ? enEPCFBoolean_False : enEPCFBoolean_True);
}
