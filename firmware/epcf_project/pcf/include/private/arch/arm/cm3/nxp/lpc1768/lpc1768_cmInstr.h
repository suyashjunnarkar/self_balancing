/**
 * \file      lpc1768_cmInstr.h
 * \brief     CM3 Cortex-M Core Instruction Access Header File
 * \copyright Copyright (c) 2014 <br> PhiRobotics Research Pvt Ltd
 * 
 * \par
 * For licensing information, see the file 'LICENSE' in the root folder of
 * this software module.
 * 
 * Review status: NO
 */

#ifndef __PCF_INCLUDE_PRIVATE_ARCH_ARM_CM3_NXP_LPC1768_LPC1768_INSTR_H
#define __PCF_INCLUDE_PRIVATE_ARCH_ARM_CM3_NXP_LPC1768_LPC1768_INSTR_H

#ifdef __GNUC__        //GNU Compiler

#if (_PCF_CORTEX_M3 >= 0x03)

/**
 * \brief		Reverse bit order of value
 * \details		This function reverses the bit order of the given value.
 * 
 * \param [in]    value  Value to reverse
 * \return               Reversed value
 */
static PCF_INLINE PCF_FORCE_INLINE uint32_t PF_RBIT(uint32_t value)
{
  uint32_t result;

   PCF_ASM volatile ("rbit %0, %1" : "=r" (result) : "r" (value) );
   return(result);
}

/**
 * \brief		LDR Exclusive (8 bit)
 * \details		This function performs a exclusive LDR command for 8 bit value.
 * 
 * \param [in]    ptr  Pointer to data
 * \return             value of type uint8_t at (*ptr)
 */
static PCF_INLINE PCF_FORCE_INLINE uint8_t PF_LDREXB(volatile uint8_t *addr)
{
    uint8_t result;

   PCF_ASM volatile ("ldrexb %0, [%1]" : "=r" (result) : "r" (addr) );
   return(result);
}

/**
 * \brief		LDR Exclusive (16 bit)
 * \details		This function performs a exclusive LDR command for 16 bit values.
 * 
 * \param [in]    ptr  Pointer to data
 * \return        value of type PFword at (*ptr)
 */
static PCF_INLINE PCF_FORCE_INLINE uint16_t PF_LDREXH(volatile uint16_t *addr)
{
	uint16_t result;

   PCF_ASM volatile ("ldrexh %0, [%1]" : "=r" (result) : "r" (addr) );
   return(result);
}

/**
 * \brief		LDR Exclusive (32 bit)
 * \details		This function performs a exclusive LDR command for 32 bit values.
 * 
 * \param [in]    ptr  Pointer to data
 * \return        value of type uint32_t at (*ptr)
 */
static PCF_INLINE PCF_FORCE_INLINE uint32_t PF_LDREXW(volatile uint32_t *addr)
{
    uint32_t result;

   PCF_ASM volatile ("ldrex %0, [%1]" : "=r" (result) : "r" (addr) );
   return(result);
}

/**
 * \brief		STR Exclusive (8 bit)
 * \details		This function performs a exclusive STR command for 8 bit values.
 * 
 * \param [in]  value  Value to store
 * \param [in]    ptr  Pointer to location
 * \return          0  Function succeeded
 * \return          1  Function failed
 */
static PCF_INLINE PCF_FORCE_INLINE uint32_t PF_STREXB(uint8_t value, volatile uint8_t *addr)
{
   uint32_t result;

   PCF_ASM volatile ("strexb %0, %2, [%1]" : "=r" (result) : "r" (addr), "r" (value) );
   return(result);
}

/**
 * \brief		STR Exclusive (16 bit)
 * \details		This function performs a exclusive STR command for 16 bit values.
 * 
 * \param [in]  value  Value to store
 * \param [in]    ptr  Pointer to location
 * \return          0  Function succeeded
 * \return          1  Function failed
 */
static PCF_INLINE PCF_FORCE_INLINE uint32_t PF_STREXH(uint16_t value, volatile uint16_t *addr)
{
   uint32_t result;

   PCF_ASM volatile ("strexh %0, %2, [%1]" : "=r" (result) : "r" (addr), "r" (value) );
   return(result);
}

/**
 * \brief		STR Exclusive (32 bit)
 * \details		This function performs a exclusive STR command for 32 bit values.
 * 
 * \param [in]  value  Value to store
 * \param [in]    ptr  Pointer to location
 * \return          0  Function succeeded
 * \return          1  Function failed
 */
static PCF_INLINE PCF_FORCE_INLINE uint32_t PF_STREXW(uint32_t value, volatile uint32_t *addr)
{
   uint32_t result;

   PCF_ASM volatile ("strex %0, %2, [%1]" : "=r" (result) : "r" (addr), "r" (value) );
   return(result);
}

/**
 * \brief		Remove the exclusive lock
 * \details		This function removes the exclusive lock which is created by LDREX.
 */
static PCF_INLINE PCF_FORCE_INLINE void PF_CLREX(void)
{
  PCF_ASM volatile ("clrex");
}

/**
 * \brief		Signed Saturate
 * \details		This function saturates a signed value.
 * 
 * \param [in]  value  Value to be saturated
 * \param [in]    sat  Bit position to saturate to (1..32)
 * \return             Saturated value
 */
#define PF_SSAT(ARG1,ARG2) \
({                          \
  uint32_t __RES, __ARG1 = (ARG1); \
  PCF_ASM ("ssat %0, %1, %2" : "=r" (__RES) :  "I" (ARG2), "r" (__ARG1) ); \
  __RES; \
 })

/**
 * \brief		Unsigned Saturate
 * \details		This function saturates an unsigned value.
 * 
 * \param [in]  value  Value to be saturated
 * \param [in]    sat  Bit position to saturate to (0..31)
 * \return             Saturated value
 */
#define PF_USAT(ARG1,ARG2) \
({                          \
  uint32_t __RES, __ARG1 = (ARG1); \
  PCF_ASM ("usat %0, %1, %2" : "=r" (__RES) :  "I" (ARG2), "r" (__ARG1) ); \
  __RES; \
 })

/**
 * \brief		Count leading zeros
 * \details		This function counts the number of leading zeros of a data value.
 * 
 * \param [in]  value  Value to count the leading zeros
 * \return             number of leading zeros in value
 */
static PCF_INLINE PCF_FORCE_INLINE uint8_t PF_CLZ(uint32_t value)
{
  uint8_t result;

  PCF_ASM volatile ("clz %0, %1" : "=r" (result) : "r" (value) );
  return(result);
}

#endif  // (_PCF_CORTEX_M3 >= 0x03)
#endif  // __GNUC__
#endif  // __PCF_INCLUDE_PRIVATE_ARCH_ARM_CM3_NXP_LPC1768_LPC1768_INSTR_H
