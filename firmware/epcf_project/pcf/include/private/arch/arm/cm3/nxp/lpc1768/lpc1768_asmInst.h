/**
 * \file     	lpc1768_asmInst.h															
 * \brief    	Cortex m3 Instruction Set
 * \copyright	Copyright (c) 2014 <br> PhiRobotics Research Pvt Ltd
 * 
 * \par
 * For licensing information, see the file 'LICENSE' in the root folder of
 * this software module.
 * 
 * Review status: NO
 */
 
#ifndef __PCF_INCLUDE_PRIVATE_ARCH_ARM_CM3_NXP_LPC1768_LPC1768_ASMINST_H
#define __PCF_INCLUDE_PRIVATE_ARCH_ARM_CM3_NXP_LPC1768_LPC1768_ASMINST_H

//#define __ASM            __asm
//#define __INLINE         __inline
//
//
//static __INLINE __ASM uint32_t __REV16(uint32_t value)
//{
//  rev16 r0, r0
//  bx lr
//}

/**
 *  \brief      No Operation
 *  \details    No Operation does nothing. This instruction can be used for code alignment purposes.
 */
static PCF_INLINE PCF_FORCE_INLINE void __NOP(void)
{
  PCF_ASM volatile ("nop");
}

/**
 *  \brief      Wait For Interrupt
 *  \details    Wait For Interrupt is a hint instruction that suspends execution until one of a number of events occurs.
 */
static PCF_INLINE PCF_FORCE_INLINE void __WFI(void)
{
  PCF_ASM volatile ("wfi");
}

/**
 *  \brief      Wait For Event
 *  \details    Wait For Event is a hint instruction that permits the processor to enter
 *              a low-power state until one of a number of events occurs.
 */
static PCF_INLINE PCF_FORCE_INLINE void __WFE(void)
{
  PCF_ASM volatile ("wfe");
}

/**
 *  \brief      Send Event
 *  \details    Send Event is a hint instruction. It causes an event to be signaled to the CPU.
 */
static PCF_INLINE PCF_FORCE_INLINE void __SEV(void)
{
  PCF_ASM volatile ("sev");
}

/**
 *  \brief      Instruction Synchronization Barrier
 *  \details    Instruction Synchronization Barrier flushes the pipeline in the processor,
 *              so that all instructions following the ISB are fetched from cache or
 *              memory, after the instruction has been completed.
 */
static PCF_INLINE PCF_FORCE_INLINE void __ISB(void)
{
  PCF_ASM volatile ("isb");
}

/**
 *  \brief      Data Synchronization Barrier
 *  \details    This function acts as a special kind of Data Memory Barrier.
 *              It completes when all explicit memory accesses before this instruction complete.
 */
static PCF_INLINE PCF_FORCE_INLINE void __DSB(void)
{
  PCF_ASM volatile ("dsb");
}

/**
 *  \brief      Data Memory Barrier
 *  \details    This function ensures the apparent order of the explicit memory operations before
 *              and after the instruction, without ensuring their completion.
 */
static PCF_INLINE PCF_FORCE_INLINE void __DMB(void)
{
  PCF_ASM volatile ("dmb");
}

/**
 *  \brief      Reverse byte order (32 bit)
 *  \details    This function reverses the byte order in integer value.
 *
 *  \param [in]    value  Value to reverse
 *
    \return               Reversed value
 */
static PCF_INLINE PCF_FORCE_INLINE uint32_t __REV(uint32_t value)
{
  uint32_t result;
  PCF_ASM volatile ("rev %0, %1" : "=r" (result) : "r" (value) );
  return(result);
}

/**
 *  \brief      Reverse byte order (16 bit)
 *  \details    This function reverses the byte order in two unsigned short values.
 *
 *  \param [in]    value  Value to reverse
 *  \return               Reversed value
 */
static PCF_INLINE PCF_FORCE_INLINE uint32_t __REV16(uint32_t value)
{
  uint32_t result;
  PCF_ASM volatile ("rev16 %0, %1" : "=r" (result) : "r" (value) );
  return(result);
}

/**
 *  \brief      Reverse byte order in signed short value
 *  \details    This function reverses the byte order in a signed short value with sign extension to integer.
 *
 *  \param [in]    value  Value to reverse
 *  \return               Reversed value
 */
static PCF_INLINE PCF_FORCE_INLINE int32_t __REVSH(int32_t value)
{
  uint32_t result;
  PCF_ASM volatile ("revsh %0, %1" : "=r" (result) : "r" (value) );
  return(result);
}

#endif //__PCF_INCLUDE_PRIVATE_ARCH_ARM_CM3_NXP_LPC1768_LPC1768_ASMINST_H



