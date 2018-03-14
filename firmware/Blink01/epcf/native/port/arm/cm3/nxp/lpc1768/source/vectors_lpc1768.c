#include "pcf.h"

#define __EPCF_VECTOR_LPC1768_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_NATIVE_PATH/	\
		,port/PCF_ARCH_NAME/PCF_ARCH_VARIANT/PCF_ARCH_DEVICE_VENDOR/,PCF_ARCH_DEVICE/include/,vectors_lpc1768.h)
#include __EPCF_VECTOR_LPC1768_INCLUDE
#undef __EPCF_VECTOR_LPC1768_INCLUDE

/*
 * The next data are defined by the linker script.
 */
extern unsigned long _stext;		/* Label to indicate start of text section */
extern unsigned long _etext;		/* Label to indicate end of text section */
extern unsigned long _sdata;		/* Label to indicate start of data section */
extern unsigned long _edata;		/* Label to indicate end of data section */
extern unsigned long _sbss;			/* Label to indicate start of bss section */
extern unsigned long _ebss;			/* Label to indicate end of bss section */
extern unsigned long _estack;		/* Label to indicate start of stack section */

/* This is the main */
extern int main (void);

/* Reset Handler		*/
void ResetHandler(void);

/*
 * This is our vector table.
 */
extern void (* const gVectors[])(void);
__attribute__ ((section(".vectors"), used))
void (* const gVectors[])(void) =
{
   (void (*)(void))((unsigned long)&_estack),
   ResetHandler,
   NMI_Handler,
   HardFault_Handler,
   MemManage_Handler,
   BusFault_Handler,
   UsageFault_Handler,
   0, 0, 0, 0,
   SVC_Handler,
   DebugMon_Handler,
   0,
   PendSV_Handler,
   SysTick_Handler,

   WDT_IRQHandler,
   TIMER0_IRQHandler,
   TIMER1_IRQHandler,
   TIMER2_IRQHandler,
   TIMER3_IRQHandler,
   UART0_IRQHandler,
   UART1_IRQHandler,
   UART2_IRQHandler,
   UART3_IRQHandler,
   PWM_IRQHandler,
   I2C0_IRQHandler,
   I2C1_IRQHandler,
   I2C2_IRQHandler,
   SPI_IRQHandler,
   SSP0_IRQHandler,
   SSP1_IRQHandler,
   PLL0_IRQHandler,
   RTC_IRQHandler,
   EINT0_IRQHandler,
   EINT1_IRQHandler,
   EINT2_IRQHandler,
   EINT3_IRQHandler,
   ADC_IRQHandler,
   BOD_IRQHandler,
   USB_IRQHandler,
   CAN_IRQHandler,
   DMA_IRQHandler,
   I2S_IRQHandler,
   ENET_IRQHandler,
   RIT_IRQHandler,
   MCPWM_IRQHandler,
   QEI_IRQHandler
}; /* gVectors */


/*  This function is used for the C runtime initialisation,                
 *  for handling the .data and .bss segments.
 *
 */
void __attribute__((noreturn)) ResetHandler (void)
{
   uint32_t *pSrc;
   uint32_t *pDest;

   /*
    * Set the "Vector Table Offset Register". From the ARM
    * documentation, we got the following information:
    *
    * Use the Vector Table Offset Register to determine:
    *  - if the vector table is in RAM or code memory
    *  - the vector table offset.
    */
   *((uint32_t*)0xE000ED08) = (uint32_t)&_stext;

   /*
    * Copy the initialized data of the ".data" segment
    * from the flash to the are in the ram.
    */
   pSrc  = &_etext;
   pDest = &_sdata;
   while(pDest < &_edata)
   {
      *pDest++ = *pSrc++;
   }

   /*
    * Clear the ".bss" segment.
    */
   pDest = &_sbss;
   while(pDest < &_ebss)
   {
      *pDest++ = 0;
   }

   /*
    * And now the main function can be called.
    * Scotty, energie...
    */
   main();

   /*
    * In case there are problems with the
    * "warp drive", stop here.
    */
   while(1) {};

} /* ResetHandler */

/*
 * And here are the weak interrupt handlers.
 *
 */
void __attribute__((weak, noreturn)) NMI_Handler (void) { while(1); }
void __attribute__((weak, noreturn)) HardFault_Handler (void) { while(1); }
void __attribute__((weak, noreturn)) MemManage_Handler (void) { while(1); }
void __attribute__((weak, noreturn)) BusFault_Handler (void) { while(1); }
void __attribute__((weak, noreturn)) UsageFault_Handler (void) { while(1); }
void __attribute__((weak, noreturn)) SVC_Handler (void) { while(1); }
void __attribute__((weak, noreturn)) DebugMon_Handler (void) { while(1); }
void __attribute__((weak, noreturn)) PendSV_Handler (void) { while(1); }
void __attribute__((weak, noreturn)) SysTick_Handler (void) { while(1); }

void __attribute__((weak, noreturn)) WDT_IRQHandler (void) { while(1); }
void __attribute__((weak, noreturn)) TIMER0_IRQHandler (void) { while(1); }
void __attribute__((weak, noreturn)) TIMER1_IRQHandler (void) { while(1); }
void __attribute__((weak, noreturn)) TIMER2_IRQHandler (void) { while(1); }
void __attribute__((weak, noreturn)) TIMER3_IRQHandler (void) { while(1); }
void __attribute__((weak, noreturn)) UART0_IRQHandler (void) { while(1); }
void __attribute__((weak, noreturn)) UART1_IRQHandler (void) { while(1); }
void __attribute__((weak, noreturn)) UART2_IRQHandler (void) { while(1); }
void __attribute__((weak, noreturn)) UART3_IRQHandler (void) { while(1); }
void __attribute__((weak, noreturn)) PWM_IRQHandler (void) { while(1); }
void __attribute__((weak, noreturn)) I2C0_IRQHandler (void) { while(1); }
void __attribute__((weak, noreturn)) I2C1_IRQHandler (void) { while(1); }
void __attribute__((weak, noreturn)) I2C2_IRQHandler (void) { while(1); }
void __attribute__((weak, noreturn)) SPI_IRQHandler (void) { while(1); }
void __attribute__((weak, noreturn)) SSP0_IRQHandler (void) { while(1); }
void __attribute__((weak, noreturn)) SSP1_IRQHandler (void) { while(1); }
void __attribute__((weak, noreturn)) PLL0_IRQHandler (void) { while(1); }
void __attribute__((weak, noreturn)) RTC_IRQHandler (void) { while(1); }
void __attribute__((weak, noreturn)) EINT0_IRQHandler (void) { while(1); }
void __attribute__((weak, noreturn)) EINT1_IRQHandler (void) { while(1); }
void __attribute__((weak, noreturn)) EINT2_IRQHandler (void) { while(1); }
void __attribute__((weak, noreturn)) EINT3_IRQHandler (void) { while(1); }
void __attribute__((weak, noreturn)) ADC_IRQHandler (void) { while(1); }
void __attribute__((weak, noreturn)) BOD_IRQHandler (void) { while(1); }
void __attribute__((weak, noreturn)) USB_IRQHandler (void) { while(1); }
void __attribute__((weak, noreturn)) CAN_IRQHandler (void) { while(1); }
void __attribute__((weak, noreturn)) DMA_IRQHandler (void) { while(1); }
void __attribute__((weak, noreturn)) I2S_IRQHandler (void) { while(1); }
void __attribute__((weak, noreturn)) ENET_IRQHandler (void) { while(1); }
void __attribute__((weak, noreturn)) RIT_IRQHandler (void) { while(1); }
void __attribute__((weak, noreturn)) MCPWM_IRQHandler (void) { while(1); }
void __attribute__((weak, noreturn)) QEI_IRQHandler (void) { while(1); }
