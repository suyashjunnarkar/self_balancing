/********************************************************************************
* \file				lpc1768_cmFunc.h													
* \brief			CM3 Cortex-M Core Function Access Header File
* \copyright	Copyright (c) 2014 <br> PhiRobotics Research Pvt Ltd
* 
* \par
* For licensing information, see the file 'LICENSE' in the root folder of
* this software module.
* 
* Review status: NO
******************************************************************************/

#ifndef __PCF_INCLUDE_PRIVATE_ARCH_ARM_CM3_NXP_LPC1768_LPC1768_FUNC_H
#define __PCF_INCLUDE_PRIVATE_ARCH_ARM_CM3_NXP_LPC1768_LPC1768_FUNC_H

#ifdef __GNUC__						/*------------------ GNU Compiler ---------------------*/
/* GNU gcc specific functions */

/**
 * \brief		Enable IRQ Interrupts
 * \details		This function enables IRQ interrupts by clearing the I-bit in the CPSR.
 * 
 * \note		Can only be executed in Privileged modes.
 */
static PCF_INLINE PCF_FORCE_INLINE void __enable_irq(void)
{
  PCF_ASM volatile ("cpsie i");
}

/**
 * \brief		Disable IRQ Interrupts
 * \details		This function disables IRQ interrupts by setting the I-bit in the CPSR.
 * 
 * \note		Can only be executed in Privileged modes.
 */
static PCF_INLINE PCF_FORCE_INLINE void __disable_irq(void)
{
  PCF_ASM volatile ("cpsid i");
}

/**
 * \brief		Get Control Register
 * \details		This function returns the content of the Control Register.
 * 
 * \return               Control Register value
 */
static PCF_INLINE PCF_FORCE_INLINE uint32_t __get_CONTROL(void)
{
  uint32_t result;

  PCF_ASM volatile ("MRS %0, control" : "=r" (result) );
  return(result);
}

/**
 * \brief		Set Control Register
 * \details		This function writes the given value to the Control Register.
 * 
 * \param [in]    control  Control Register value to set
 */
static PCF_INLINE PCF_FORCE_INLINE void __set_CONTROL(uint32_t control)
{
  PCF_ASM volatile ("MSR control, %0" : : "r" (control) );
}

/**
 * \brief  		Get ISPR Register
 * \details		This function returns the content of the ISPR Register.
 * 
 * \return               ISPR Register value
 */
static PCF_INLINE PCF_FORCE_INLINE uint32_t __get_IPSR(void)
{
  uint32_t result;

  PCF_ASM volatile ("MRS %0, ipsr" : "=r" (result) );
  return(result);
}

/**
 * \brief		Get APSR Register
 * \details		This function returns the content of the APSR Register.
 * 
 * \return               APSR Register value
 */
static PCF_INLINE PCF_FORCE_INLINE uint32_t __get_APSR(void)
{
  uint32_t result;

  PCF_ASM volatile ("MRS %0, apsr" : "=r" (result) );
  return(result);
}

/**
 * \brief  		Get xPSR Register
 * \details		This function returns the content of the xPSR Register.
 * 
 * \return               xPSR Register value
 */
static PCF_INLINE PCF_FORCE_INLINE uint32_t __get_xPSR(void)
{
  uint32_t result;

  PCF_ASM volatile ("MRS %0, xpsr" : "=r" (result) );
  return(result);
}

/**
 * \brief		Get Process Stack Pointer
 * \details		This function returns the current value of the Process Stack Pointer (PSP).
 * 
 * \return               PSP Register value
 */
static PCF_INLINE PCF_FORCE_INLINE uint32_t __get_PSP(void)
{
  register uint32_t result;

  PCF_ASM volatile ("MRS %0, psp\n"  : "=r" (result) );
  return(result);
}
 
/**
 * \brief		Set Process Stack Pointer
 * \details		This function assigns the given value to the Process Stack Pointer (PSP).
 * 
 * \param [in]    topOfProcStack  Process Stack Pointer value to set
 */
static PCF_INLINE PCF_FORCE_INLINE void __set_PSP(uint32_t topOfProcStack)
{
  PCF_ASM volatile ("MSR psp, %0\n" : : "r" (topOfProcStack) );
}

/**
 * \brief		Get Main Stack Pointer
 * \details		This function returns the current value of the Main Stack Pointer (MSP).
 * 
 * \return               MSP Register value
 */
static PCF_INLINE PCF_FORCE_INLINE uint32_t __get_MSP(void)
{
  register uint32_t result;

  PCF_ASM volatile ("MRS %0, msp\n" : "=r" (result) );
  return(result);
}
 
/**
 * \brief		Set Main Stack Pointer
 * \details		This function assigns the given value to the Main Stack Pointer (MSP).
 * 
 * \param [in]    topOfMainStack  Main Stack Pointer value to set
 */
static PCF_INLINE PCF_FORCE_INLINE void __set_MSP(uint32_t topOfMainStack)
{
  PCF_ASM volatile ("MSR msp, %0\n" : : "r" (topOfMainStack) );
}

/**
 * \brief  		Get Priority Mask
 * \details		This function returns the current state of the priority mask bit from the Priority Mask Register.
 * 
 * \return               Priority Mask value
 */
static PCF_INLINE PCF_FORCE_INLINE uint32_t __get_PRIMASK(void)
{
  uint32_t result;

  PCF_ASM volatile ("MRS %0, primask" : "=r" (result) );
  return(result);
}

/**
 * \brief		Set Priority Mask
 * \details	    This function assigns the given value to the Priority Mask Register.
 * 
 * \param [in]    priMask  Priority Mask
 */
static PCF_INLINE PCF_FORCE_INLINE void __set_PRIMASK(uint32_t priMask)
{
  PCF_ASM volatile ("MSR primask, %0" : : "r" (priMask) );
}
 
#if       (PCF_CORTEX_M3 >= 0x03)

/**
 * \brief  		Enable FIQ
 * \details		This function enables FIQ interrupts by clearing the F-bit in the CPSR.
 * 
 * \note		Can only be executed in Privileged modes.
 */
static PCF_INLINE PCF_FORCE_INLINE void __enable_fault_irq(void)
{
  PCF_ASM volatile ("cpsie f");
}

/**
 * \brief		Disable FIQ
 * \details		This function disables FIQ interrupts by setting the F-bit in the CPSR.
 * 
 * \note		Can only be executed in Privileged modes.
 */
static PCF_INLINE PCF_FORCE_INLINE void __disable_fault_irq(void)
{
  PCF_ASM volatile ("cpsid f");
}

/**
 * \brief		Get Base Priority
 * \details		This function returns the current value of the Base Priority register.
 * 
 * \return               Base Priority register value
 */
static PCF_INLINE PCF_FORCE_INLINE uint32_t __get_BASEPRI(void)
{
  uint32_t result;
  
  PCF_ASM volatile ("MRS %0, basepri_max" : "=r" (result) );
  return(result);
}

/**
 * \brief		Set Base Priority
 * \details		This function assigns the given value to the Base Priority register.
 * 
 * \param [in]    basePri  Base Priority value to set
 */
static PCF_INLINE PCF_FORCE_INLINE void __set_BASEPRI(uint32_t value)
{
  PCF_ASM volatile ("MSR basepri, %0" : : "r" (value) );
}

/**
 * \brief		Get Fault Mask
 * \details		This function returns the current value of the Fault Mask register.
 * 
 * \return               Fault Mask register value
 */
static PCF_INLINE PCF_FORCE_INLINE uint32_t __get_FAULTMASK(void)
{
  uint32_t result;
  
  PCF_ASM volatile ("MRS %0, faultmask" : "=r" (result) );
  return(result);
}

/**
 * \brief		Set Fault Mask
 * \details		This function assigns the given value to the Fault Mask register.
 * 
 * \param [in]    faultMask  Fault Mask value to set
 */
static PCF_INLINE PCF_FORCE_INLINE void __set_FAULTMASK(uint32_t faultMask)
{
  PCF_ASM volatile ("MSR faultmask, %0" : : "r" (faultMask) );
}

#endif /* (__PCF_CORTEX_M3 >= 0x03) */

#if       (__PCF_CORTEX_M3 == 0x04)

/**
 * \brief		Get FPSCR
 * \details		This function returns the current value of the Floating Point Status/Control register.
 * 
 * \return               Floating Point Status/Control register value
 */
static PCF_INLINE PCF_FORCE_INLINE uint32_t __get_FPSCR(void)
{
#if (__FPU_PRESENT == 1)
  uint32_t result;

  PCF_ASM volatile ("MRS %0, fpscr" : "=r" (result) );
  return(result);
#else
   return(0);
#endif
}

/**
 * \brief		Set FPSCR
 * \details		This function assigns the given value to the Floating Point Status/Control register.
 * 
 * \param [in]    fpscr  Floating Point Status/Control value to set
 */
static PCF_INLINE PCF_FORCE_INLINE void __set_FPSCR(uint32_t fpscr)
{
#if (__FPU_PRESENT == 1)
  PCF_ASM volatile ("MSR fpscr, %0" : : "r" (fpscr) );
#endif
}

#endif // (__PCF_CORTEX_M3 == 0x04)

#endif // (__GNU__)

#endif // __PCF_INCLUDE_PRIVATE_ARCH_ARM_CM3_NXP_LPC1768_LPC1768_FUNC_H
