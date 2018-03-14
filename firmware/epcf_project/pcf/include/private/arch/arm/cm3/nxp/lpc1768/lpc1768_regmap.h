/**
 * \file		lpc1768_regmap.h
 * \brief		Describe the Register Map of LPC1768.
 * \copyright 	Copyright (c) 2014 <br> PhiRobotics Research Pvt Ltd.
 * 
 * \par			For licensing information, see the file 'LICENSE' in the root folder of	this software module.
 *
 * Review status: NO
 *
 */
#ifndef __PCF_INCLUDE_PRIVATE_ARCH_ARM_CM3_NXP_LPC1768_LPC1768_REGMAP_H
#define __PCF_INCLUDE_PRIVATE_ARCH_ARM_CM3_NXP_LPC1768_LPC1768_REGMAP_H

/**
 * \ingroup native
 * \defgroup LPCxx Peripherals
 * @{
 * 	
 * 	\brief  LPC1768 Reg Map
 */

 /** Macros defined for defining register read/write access                                          */
#define _RW                 volatile
#define _R                  volatile const
#define _W                  volatile

 
/** \brief IRQ interrupt source definition */
typedef enum
{
/******  Cortex-M3 Processor Exceptions Numbers ***************************************************/
  Reset_IRQn                    = -15,      /**< 1 Reset Vector, invoked on PowerUp and warm reset*/
  NonMaskableInt_IRQn           = -14,      /**< 2 Non Maskable Interrupt                         */
  HardFault_IRQn                = -13,      /**< 3  Hard Fault, all classes of Fault              */
  MemoryManagement_IRQn         = -12,      /**< 4 Cortex-M3 Memory Management Interrupt          */
  BusFault_IRQn                 = -11,      /**< 5 Cortex-M3 Bus Fault Interrupt                  */
  UsageFault_IRQn               = -10,      /**< 6 Cortex-M3 Usage Fault Interrupt                */
  SVCall_IRQn                   = -5,       /**< 11 Cortex-M3 SV Call Interrupt                   */
  DebugMonitor_IRQn             = -4,       /**< 12 Cortex-M3 Debug Monitor Interrupt             */
  PendSV_IRQn                   = -2,       /**< 14 Cortex-M3 Pend SV Interrupt                   */
  SysTick_IRQn                  = -1,       /**< 15 Cortex-M3 System Tick Interrupt               */

/******  LPC17xx Specific Interrupt Numbers *******************************************************/
  WDT_IRQn                      = 0,        /**< Watchdog Timer Interrupt                         */
  TIMER0_IRQn                   = 1,        /**< Timer0 Interrupt                                 */
  TIMER1_IRQn                   = 2,        /**< Timer1 Interrupt                                 */
  TIMER2_IRQn                   = 3,        /**< Timer2 Interrupt                                 */
  TIMER3_IRQn                   = 4,        /**< Timer3 Interrupt                                 */
  UART0_IRQn                    = 5,        /**< UART0 Interrupt                                  */
  UART1_IRQn                    = 6,        /**< UART1 Interrupt                                  */
  UART2_IRQn                    = 7,        /**< UART2 Interrupt                                  */
  UART3_IRQn                    = 8,        /**< UART3 Interrupt                                  */
  PWM1_IRQn                     = 9,        /**< PWM1 Interrupt                                   */
  I2C0_IRQn                     = 10,       /**< I2C0 Interrupt                                   */
  I2C1_IRQn                     = 11,       /**< I2C1 Interrupt                                   */
  I2C2_IRQn                     = 12,       /**< I2C2 Interrupt                                   */
  SPI_IRQn                      = 13,       /**< SPI Interrupt                                    */
  SSP0_IRQn                     = 14,       /**< SSP0 Interrupt                                   */
  SSP1_IRQn                     = 15,       /**< SSP1 Interrupt                                   */
  PLL0_IRQn                     = 16,       /**< PLL0 Lock (Main PLL) Interrupt                   */
  RTC_IRQn                      = 17,       /**< Real Time Clock Interrupt                        */
  EINT0_IRQn                    = 18,       /**< External Interrupt 0 Interrupt                   */
  EINT1_IRQn                    = 19,       /**< External Interrupt 1 Interrupt                   */
  EINT2_IRQn                    = 20,       /**< External Interrupt 2 Interrupt                   */
  EINT3_IRQn                    = 21,       /**< External Interrupt 3 Interrupt                   */
  ADC_IRQn                      = 22,       /**< A/D Converter Interrupt                          */
  BOD_IRQn                      = 23,       /**< Brown-Out Detect Interrupt                       */
  USB_IRQn                      = 24,       /**< USB Interrupt                                    */
  CAN_IRQn                      = 25,       /**< CAN Interrupt                                    */
  DMA_IRQn                      = 26,       /**< General Purpose DMA Interrupt                    */
  I2S_IRQn                      = 27,       /**< I2S Interrupt                                    */
  ENET_IRQn                     = 28,       /**< Ethernet Interrupt                               */
  RIT_IRQn                      = 29,       /**< Repetitive Interrupt Timer Interrupt             */
  MCPWM_IRQn                    = 30,       /**< Motor Control PWM Interrupt                      */
  QEI_IRQn                      = 31,       /**< Quadrature Encoder Interface Interrupt           */
  PLL1_IRQn                     = 32,       /**< PLL1 Lock (USB PLL) Interrupt                    */
  USBActivity_IRQn              = 33,       /**< USB Activity Interrupt 						  */
  CANActivity_IRQn              = 34,       /**< CAN Activity Interrupt 						  */
} IRQn_Type;

/**		\brief  Structure type to access the Nested Vectored Interrupt Controller (NVIC).	*/
typedef struct
{
  _RW uint32_t ISER[8];                 /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register           */
       uint32_t RESERVED0[24];
  _RW uint32_t ICER[8];                 /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register         */
       uint32_t RSERVED1[24];
  _RW uint32_t ISPR[8];                 /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register          */
       uint32_t RESERVED2[24];
  _RW uint32_t ICPR[8];                 /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register        */
       uint32_t RESERVED3[24];
  _RW uint32_t IABR[8];                 /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register           */
       uint32_t RESERVED4[56];
  _RW uint8_t  IP[240];                 /*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
       uint32_t RESERVED5[644];
  _W  uint32_t STIR;                    /*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register     */
}  NVIC_Type;

/**	\brief  Structure type to access the System Control Block (SCB).	*/
typedef struct
{
  _R  uint32_t CPUID;                   /*!< Offset: 0x000 (R/ )  CPU ID Base Register                                  */
  _RW uint32_t ICSR;                    /*!< Offset: 0x004 (R/W)  Interrupt Control State Register                      */
  _RW uint32_t VTOR;                    /*!< Offset: 0x008 (R/W)  Vector Table Offset Register                          */
  _RW uint32_t AIRCR;                   /*!< Offset: 0x00C (R/W)  Application Interrupt / Reset Control Register        */
  _RW uint32_t SCR;                     /*!< Offset: 0x010 (R/W)  System Control Register                               */
  _RW uint32_t CCR;                     /*!< Offset: 0x014 (R/W)  Configuration Control Register                        */
  _RW uint8_t  SHP[12];                 /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  _RW uint32_t SHCSR;                   /*!< Offset: 0x024 (R/W)  System Handler Control and State Register             */
  _RW uint32_t CFSR;                    /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register                    */
  _RW uint32_t HFSR;                    /*!< Offset: 0x02C (R/W)  Hard Fault Status Register                            */
  _RW uint32_t DFSR;                    /*!< Offset: 0x030 (R/W)  Debug Fault Status Register                           */
  _RW uint32_t MMFAR;                   /*!< Offset: 0x034 (R/W)  Mem Manage Address Register                           */
  _RW uint32_t BFAR;                    /*!< Offset: 0x038 (R/W)  Bus Fault Address Register                            */
  _RW uint32_t AFSR;                    /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register                       */
  _R  uint32_t PFR[2];                  /*!< Offset: 0x040 (R/ )  Processor Feature Register                            */
  _R  uint32_t DFR;                     /*!< Offset: 0x048 (R/ )  Debug Feature Register                                */
  _R  uint32_t ADR;                     /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register                            */
  _R  uint32_t MMFR[4];                 /*!< Offset: 0x050 (R/ )  Memory Model Feature Register                         */
  _R  uint32_t ISAR[5];                 /*!< Offset: 0x060 (R/ )  ISA Feature Register                                  */
} SCB_Type;

/** \brief  Structure type to access the System Timer (SysTick).	*/
typedef struct
{
  _RW uint32_t CTRL;                    /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
  _RW uint32_t LOAD;                    /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register       */
  _RW uint32_t VAL;                     /*!< Offset: 0x008 (R/W)  SysTick Current Value Register      */
  _R  uint32_t CALIB;                   /*!< Offset: 0x00C (R/ )  SysTick Calibration Register        */
} SysTick_Type;

/** \brief  Structure type to access the Instrumentation Trace Macrocell Register (ITM). */
typedef struct
{
  _W  union
  {
    _W  uint8_t    u8;                  /*!< Offset: 0x000 ( /W)  ITM Stimulus Port 8-bit                   */
    _W  uint16_t   u16;                 /*!< Offset: 0x000 ( /W)  ITM Stimulus Port 16-bit                  */
    _W  uint32_t   u32;                 /*!< Offset: 0x000 ( /W)  ITM Stimulus Port 32-bit                  */
  }  PORT [32];                          /*!< Offset: 0x000 ( /W)  ITM Stimulus Port Registers               */
       uint32_t RESERVED0[864];
  _RW uint32_t TER;                     /*!< Offset:       (R/W)  ITM Trace Enable Register                 */
       uint32_t RESERVED1[15];
  _RW uint32_t TPR;                     /*!< Offset:       (R/W)  ITM Trace Privilege Register              */
       uint32_t RESERVED2[15];
  _RW uint32_t TCR;                     /*!< Offset:       (R/W)  ITM Trace Control Register                */
       uint32_t RESERVED3[29];
  _RW uint32_t IWR;                     /*!< Offset:       (R/W)  ITM Integration Write Register            */
  _RW uint32_t IRR;                     /*!< Offset:       (R/W)  ITM Integration Read Register             */
  _RW uint32_t IMCR;                    /*!< Offset:       (R/W)  ITM Integration Mode Control Register     */
       uint32_t RESERVED4[43];
  _RW uint32_t LAR;                     /*!< Offset:       (R/W)  ITM Lock Access Register                  */
  _RW uint32_t LSR;                     /*!< Offset:       (R/W)  ITM Lock Status Register                  */
       uint32_t RESERVED5[6];
  _R  uint32_t PID4;                    /*!< Offset:       (R/ )  ITM Peripheral Identification Register #4 */
  _R  uint32_t PID5;                    /*!< Offset:       (R/ )  ITM Peripheral Identification Register #5 */
  _R  uint32_t PID6;                    /*!< Offset:       (R/ )  ITM Peripheral Identification Register #6 */
  _R  uint32_t PID7;                    /*!< Offset:       (R/ )  ITM Peripheral Identification Register #7 */
  _R  uint32_t PID0;                    /*!< Offset:       (R/ )  ITM Peripheral Identification Register #0 */
  _R  uint32_t PID1;                    /*!< Offset:       (R/ )  ITM Peripheral Identification Register #1 */
  _R  uint32_t PID2;                    /*!< Offset:       (R/ )  ITM Peripheral Identification Register #2 */
  _R  uint32_t PID3;                    /*!< Offset:       (R/ )  ITM Peripheral Identification Register #3 */
  _R  uint32_t CID0;                    /*!< Offset:       (R/ )  ITM Component  Identification Register #0 */
  _R  uint32_t CID1;                    /*!< Offset:       (R/ )  ITM Component  Identification Register #1 */
  _R  uint32_t CID2;                    /*!< Offset:       (R/ )  ITM Component  Identification Register #2 */
  _R  uint32_t CID3;                    /*!< Offset:       (R/ )  ITM Component  Identification Register #3 */
} ITM_Type;


/**	\brief  Structure type to access the Interrupt Type Register.	*/
typedef struct
{
       uint32_t RESERVED0;
  _R  uint32_t ICTR;                    /*!< Offset: 0x004 (R/ )  Interrupt Control Type Register */
#if ((defined __CM3_REV) && (__CM3_REV >= 0x200))
  _RW uint32_t ACTLR;                   /*!< Offset: 0x008 (R/W)  Auxiliary Control Register      */
#else
       uint32_t RESERVED1;
#endif
} InterruptType_Type;


/**	\brief  Structure type to access the Memory Protection Unit (MPU).	*/
typedef struct
{
  _R  uint32_t TYPE;                    /*!< Offset: 0x000 (R/ )  MPU Type Register                              */
  _RW uint32_t CTRL;                    /*!< Offset: 0x004 (R/W)  MPU Control Register                           */
  _RW uint32_t RNR;                     /*!< Offset: 0x008 (R/W)  MPU Region RNRber Register                     */
  _RW uint32_t RBAR;                    /*!< Offset: 0x00C (R/W)  MPU Region Base Address Register               */
  _RW uint32_t RASR;                    /*!< Offset: 0x010 (R/W)  MPU Region Attribute and Size Register         */
  _RW uint32_t RBAR_A1;                 /*!< Offset: 0x014 (R/W)  MPU Alias 1 Region Base Address Register       */
  _RW uint32_t RASR_A1;                 /*!< Offset: 0x018 (R/W)  MPU Alias 1 Region Attribute and Size Register */
  _RW uint32_t RBAR_A2;                 /*!< Offset: 0x01C (R/W)  MPU Alias 2 Region Base Address Register       */
  _RW uint32_t RASR_A2;                 /*!< Offset: 0x020 (R/W)  MPU Alias 2 Region Attribute and Size Register */
  _RW uint32_t RBAR_A3;                 /*!< Offset: 0x024 (R/W)  MPU Alias 3 Region Base Address Register       */
  _RW uint32_t RASR_A3;                 /*!< Offset: 0x028 (R/W)  MPU Alias 3 Region Attribute and Size Register */
} MPU_Type;


/**	\brief  Structure type to access the Core Debug Register (CoreDebug).	*/
typedef struct
{
  _RW uint32_t DHCSR;                   /*!< Offset: 0x000 (R/W)  Debug Halting Control and Status Register    */
  _W  uint32_t DCRSR;                   /*!< Offset: 0x004 ( /W)  Debug Core Register Selector Register        */
  _RW uint32_t DCRDR;                   /*!< Offset: 0x008 (R/W)  Debug Core Register Data Register            */
  _RW uint32_t DEMCR;                   /*!< Offset: 0x00C (R/W)  Debug Exception and Monitor Control Register */
} CoreDebug_Type;

// includeing the core reg map Address Macro
#include "../../../../arm/cm3/nxp/lpc1768/lpc1768_cm3.h"       /* Cortex-M3 processor and core peripherals           */

/******************************************************************************/
/*                Device Specific Peripheral registers structures             */
/******************************************************************************/

/*------------- System Control (SC) ------------------------------------------*/
/** \brief System Control (SC) register structure definition */
typedef struct
{
  _RW uint32_t FLASHCFG;               /* Flash Accelerator Module           */
       uint32_t RESERVED0[31];
  _RW uint32_t PLL0CON;                /* Clocking and Power Control         */
  _RW uint32_t PLL0CFG;
  _R  uint32_t PLL0STAT;
  _W  uint32_t PLL0FEED;
       uint32_t RESERVED1[4];
  _RW uint32_t PLL1CON;
  _RW uint32_t PLL1CFG;
  _R  uint32_t PLL1STAT;
  _W  uint32_t PLL1FEED;
       uint32_t RESERVED2[4];
  _RW uint32_t PCON;
  _RW uint32_t PCONP;
       uint32_t RESERVED3[15];
  _RW uint32_t CCLKCFG;
  _RW uint32_t USBCLKCFG;
  _RW uint32_t CLKSRCSEL;
  _RW uint32_t	CANSLEEPCLR;
  _RW uint32_t	CANWAKEFLAGS;
       uint32_t RESERVED4[10];
  _RW uint32_t EXTINT;                 /* External Interrupts                */
       uint32_t RESERVED5;
  _RW uint32_t EXTMODE;
  _RW uint32_t EXTPOLAR;
       uint32_t RESERVED6[12];
  _RW uint32_t RSID;                   /* Reset                              */
       uint32_t RESERVED7[7];
  _RW uint32_t SCS;                    /* Syscon Miscellaneous Registers     */
  _RW uint32_t IRCTRIM;                /* Clock Dividers                     */
  _RW uint32_t PCLKSEL0;
  _RW uint32_t PCLKSEL1;
       uint32_t RESERVED8[4];
  _RW uint32_t USBIntSt;               /* USB Device/OTG Interrupt Register  */
  _RW uint32_t DMAREQSEL;
  _RW uint32_t CLKOUTCFG;              /* Clock Output Configuration         */
 } SC_TypeDef;

/*------------- Pin Connect Block (PINCON) -----------------------------------*/
/** \brief Pin Connect Block (PINCON) register structure definition */
typedef struct
{
  _RW uint32_t PINSEL0;
  _RW uint32_t PINSEL1;
  _RW uint32_t PINSEL2;
  _RW uint32_t PINSEL3;
  _RW uint32_t PINSEL4;
  _RW uint32_t PINSEL5;
  _RW uint32_t PINSEL6;
  _RW uint32_t PINSEL7;
  _RW uint32_t PINSEL8;
  _RW uint32_t PINSEL9;
  _RW uint32_t PINSEL10;
       uint32_t RESERVED0[5];
  _RW uint32_t PINMODE0;
  _RW uint32_t PINMODE1;
  _RW uint32_t PINMODE2;
  _RW uint32_t PINMODE3;
  _RW uint32_t PINMODE4;
  _RW uint32_t PINMODE5;
  _RW uint32_t PINMODE6;
  _RW uint32_t PINMODE7;
  _RW uint32_t PINMODE8;
  _RW uint32_t PINMODE9;
  _RW uint32_t PINMODE_OD0;
  _RW uint32_t PINMODE_OD1;
  _RW uint32_t PINMODE_OD2;
  _RW uint32_t PINMODE_OD3;
  _RW uint32_t PINMODE_OD4;
  _RW uint32_t I2CPADCFG;
} PINCON_TypeDef;

/*------------- General Purpose Input/Output (GPIO) --------------------------*/
/** \brief General Purpose Input/Output (GPIO) register structure definition */
typedef struct
{
  union {
    _RW uint32_t FIODIR;
    struct {
      _RW uint16_t FIODIRL;
      _RW uint16_t FIODIRH;
    };
    struct {
      _RW uint8_t  FIODIR0;
      _RW uint8_t  FIODIR1;
      _RW uint8_t  FIODIR2;
      _RW uint8_t  FIODIR3;
    };
  };
  uint32_t RESERVED0[3];
  union {
    _RW uint32_t FIOMASK;
    struct {
      _RW uint16_t FIOMASKL;
      _RW uint16_t FIOMASKH;
    };
    struct {
      _RW uint8_t  FIOMASK0;
      _RW uint8_t  FIOMASK1;
      _RW uint8_t  FIOMASK2;
      _RW uint8_t  FIOMASK3;
    };
  };
  union {
    _RW uint32_t FIOPIN;
    struct {
      _RW uint16_t FIOPINL;
      _RW uint16_t FIOPINH;
    };
    struct {
      _RW uint8_t  FIOPIN0;
      _RW uint8_t  FIOPIN1;
      _RW uint8_t  FIOPIN2;
      _RW uint8_t  FIOPIN3;
    };
  };
  union {
    _RW uint32_t FIOSET;
    struct {
      _RW uint16_t FIOSETL;
      _RW uint16_t FIOSETH;
    };
    struct {
      _RW uint8_t  FIOSET0;
      _RW uint8_t  FIOSET1;
      _RW uint8_t  FIOSET2;
      _RW uint8_t  FIOSET3;
    };
  };
  union {
    _W  uint32_t FIOCLR;
    struct {
      _W  uint16_t FIOCLRL;
      _W  uint16_t FIOCLRH;
    };
    struct {
      _W  uint8_t  FIOCLR0;
      _W  uint8_t  FIOCLR1;
      _W  uint8_t  FIOCLR2;
      _W  uint8_t  FIOCLR3;
    };
  };
} GPIO_TypeDef;

/** \brief General Purpose Input/Output interrupt (GPIOINT) register structure definition */
typedef struct
{
  _R  uint32_t IntStatus;
  _R  uint32_t IO0IntStatR;
  _R  uint32_t IO0IntStatF;
  _W  uint32_t IO0IntClr;
  _RW uint32_t IO0IntEnR;
  _RW uint32_t IO0IntEnF;
       uint32_t RESERVED0[3];
  _R  uint32_t IO2IntStatR;
  _R  uint32_t IO2IntStatF;
  _W  uint32_t IO2IntClr;
  _RW uint32_t IO2IntEnR;
  _RW uint32_t IO2IntEnF;
} GPIOINT_TypeDef;

/*------------- Timer (TIM) --------------------------------------------------*/
/** \brief Timer (TIM) register structure definition */
typedef struct
{
  _RW uint32_t IR;
  _RW uint32_t TCR;
  _RW uint32_t TC;
  _RW uint32_t PR;
  _RW uint32_t PC;
  _RW uint32_t MCR;
  _RW uint32_t MR0;
  _RW uint32_t MR1;
  _RW uint32_t MR2;
  _RW uint32_t MR3;
  _RW uint32_t CCR;
  _R  uint32_t CR0;
  _R  uint32_t CR1;
       uint32_t RESERVED0[2];
  _RW uint32_t EMR;
       uint32_t RESERVED1[12];
  _RW uint32_t CTCR;
} TIM_TypeDef;

/*------------- Pulse-Width Modulation (PWM) ---------------------------------*/
/** \brief Pulse-Width Modulation (PWM) register structure definition */
typedef struct
{
  _RW uint32_t IR;
  _RW uint32_t TCR;
  _RW uint32_t TC;
  _RW uint32_t PR;
  _RW uint32_t PC;
  _RW uint32_t MCR;
  _RW uint32_t MR0;
  _RW uint32_t MR1;
  _RW uint32_t MR2;
  _RW uint32_t MR3;
  _RW uint32_t CCR;
  _R  uint32_t CR0;
  _R  uint32_t CR1;
  _R  uint32_t CR2;
  _R  uint32_t CR3;
       uint32_t RESERVED0;
  _RW uint32_t MR4;
  _RW uint32_t MR5;
  _RW uint32_t MR6;
  _RW uint32_t PCR;
  _RW uint32_t LER;
       uint32_t RESERVED1[7];
  _RW uint32_t CTCR;
} PWM_TypeDef;

/*------------- Universal Asynchronous Receiver Transmitter (UART) -----------*/
/** \brief  Universal Asynchronous Receiver Transmitter (UART) register structure definition */
typedef struct
{
  union {
  _R  uint8_t  RBR;
  _W  uint8_t  THR;
  _RW uint8_t  DLL;
       uint32_t RESERVED0;
  };
  union {
  _RW uint8_t  DLM;
  _RW uint32_t IER;
  };
  union {
  _R  uint32_t IIR;
  _W  uint8_t  FCR;
  };
  _RW uint8_t  LCR;
       uint8_t  RESERVED1[7];
  _R  uint8_t  LSR;
       uint8_t  RESERVED2[7];
  _RW uint8_t  SCR;
       uint8_t  RESERVED3[3];
  _RW uint32_t ACR;
  _RW uint8_t  ICR;
       uint8_t  RESERVED4[3];
  _RW uint8_t  FDR;
       uint8_t  RESERVED5[7];
  _RW uint8_t  TER;
} UART_TypeDef;

/** \brief  Universal Asynchronous Receiver Transmitter 1 (UART1) register structure definition */
typedef struct
{
  union {
  _R  uint8_t  RBR;
  _W  uint8_t  THR;
  _RW uint8_t  DLL;
       uint32_t RESERVED0;
  };
  union {
  _RW uint8_t  DLM;
  _RW uint32_t IER;
  };
  union {
  _R  uint32_t IIR;
  _W  uint8_t  FCR;
  };
  _RW uint8_t  LCR;
       uint8_t  RESERVED1[3];
  _RW uint8_t  MCR;
       uint8_t  RESERVED2[3];
  _R  uint8_t  LSR;
       uint8_t  RESERVED3[3];
  _R  uint8_t  MSR;
       uint8_t  RESERVED4[3];
  _RW uint8_t  SCR;
       uint8_t  RESERVED5[3];
  _RW uint32_t ACR;
       uint32_t RESERVED6;
  _RW uint32_t FDR;
       uint32_t RESERVED7;
  _RW uint8_t  TER;
       uint8_t  RESERVED8[27];
  _RW uint8_t  RS485CTRL;
       uint8_t  RESERVED9[3];
  _RW uint8_t  ADRMATCH;
       uint8_t  RESERVED10[3];
  _RW uint8_t  RS485DLY;
} UART1_TypeDef;

/*------------- Serial Peripheral Interface (SPI) ----------------------------*/
/** \brief  Serial Peripheral Interface (SPI) register structure definition */
typedef struct
{
  _RW uint32_t SPCR;
  _R  uint32_t SPSR;
  _RW uint32_t SPDR;
  _RW uint32_t SPCCR;
       uint32_t RESERVED0[3];
  _RW uint32_t SPINT;
} SPI_TypeDef;

/*------------- Synchronous Serial Communication (SSP) -----------------------*/
/** \brief  Synchronous Serial Communication (SSP) register structure definition */
typedef struct
{
  _RW uint32_t CR0;
  _RW uint32_t CR1;
  _RW uint32_t DR;
  _R  uint32_t SR;
  _RW uint32_t CPSR;
  _RW uint32_t IMSC;
  _RW uint32_t RIS;
  _RW uint32_t MIS;
  _RW uint32_t ICR;
  _RW uint32_t DMACR;
} SSP_TypeDef;

/*------------- Inter-Integrated Circuit (I2C) -------------------------------*/
/** \brief  Inter-Integrated Circuit (I2C) register structure definition */
typedef struct
{
  _RW uint32_t I2CONSET;
  _R  uint32_t I2STAT;
  _RW uint32_t I2DAT;
  _RW uint32_t I2ADR0;
  _RW uint32_t I2SCLH;
  _RW uint32_t I2SCLL;
  _W  uint32_t I2CONCLR;
  _RW uint32_t MMCTRL;
  _RW uint32_t I2ADR1;
  _RW uint32_t I2ADR2;
  _RW uint32_t I2ADR3;
  _R  uint32_t I2DATA_BUFFER;
  _RW uint32_t I2MASK0;
  _RW uint32_t I2MASK1;
  _RW uint32_t I2MASK2;
  _RW uint32_t I2MASK3;
} I2C_TypeDef;

/*------------- Inter IC Sound (I2S) -----------------------------------------*/
/** \brief  Inter IC Sound (I2S) register structure definition */
typedef struct
{
  _RW uint32_t I2SDAO;
  _RW uint32_t I2SDAI;
  _W  uint32_t I2STXFIFO;
  _R  uint32_t I2SRXFIFO;
  _R  uint32_t I2SSTATE;
  _RW uint32_t I2SDMA1;
  _RW uint32_t I2SDMA2;
  _RW uint32_t I2SIRQ;
  _RW uint32_t I2STXRATE;
  _RW uint32_t I2SRXRATE;
  _RW uint32_t I2STXBITRATE;
  _RW uint32_t I2SRXBITRATE;
  _RW uint32_t I2STXMODE;
  _RW uint32_t I2SRXMODE;
} I2S_TypeDef;

/*------------- Repetitive Interrupt Timer (RIT) -----------------------------*/
/** \brief  Repetitive Interrupt Timer (RIT) register structure definition */
typedef struct
{
  _RW uint32_t RICOMPVAL;
  _RW uint32_t RIMASK;
  _RW uint8_t  RICTRL;
       uint8_t  RESERVED0[3];
  _RW uint32_t RICOUNTER;
} RIT_TypeDef;

/*------------- Real-Time Clock (RTC) ----------------------------------------*/
/** \brief  Real-Time Clock (RTC) register structure definition */
typedef struct
{
  _RW uint8_t  ILR;
       uint8_t  RESERVED0[7];
  _RW uint8_t  CCR;
       uint8_t  RESERVED1[3];
  _RW uint8_t  CIIR;
       uint8_t  RESERVED2[3];
  _RW uint8_t  AMR;
       uint8_t  RESERVED3[3];
  _R  uint32_t CTIME0;
  _R  uint32_t CTIME1;
  _R  uint32_t CTIME2;
  _RW uint8_t  SEC;
       uint8_t  RESERVED4[3];
  _RW uint8_t  MIN;
       uint8_t  RESERVED5[3];
  _RW uint8_t  HOUR;
       uint8_t  RESERVED6[3];
  _RW uint8_t  DOM;
       uint8_t  RESERVED7[3];
  _RW uint8_t  DOW;
       uint8_t  RESERVED8[3];
  _RW uint16_t DOY;
       uint16_t RESERVED9;
  _RW uint8_t  MONTH;
       uint8_t  RESERVED10[3];
  _RW uint16_t YEAR;
       uint16_t RESERVED11;
  _RW uint32_t CALIBRATION;
  _RW uint32_t GPREG0;
  _RW uint32_t GPREG1;
  _RW uint32_t GPREG2;
  _RW uint32_t GPREG3;
  _RW uint32_t GPREG4;
  _RW uint8_t  RTC_AUXEN;
       uint8_t  RESERVED12[3];
  _RW uint8_t  RTC_AUX;
       uint8_t  RESERVED13[3];
  _RW uint8_t  ALSEC;
       uint8_t  RESERVED14[3];
  _RW uint8_t  ALMIN;
       uint8_t  RESERVED15[3];
  _RW uint8_t  ALHOUR;
       uint8_t  RESERVED16[3];
  _RW uint8_t  ALDOM;
       uint8_t  RESERVED17[3];
  _RW uint8_t  ALDOW;
       uint8_t  RESERVED18[3];
  _RW uint16_t ALDOY;
       uint16_t RESERVED19;
  _RW uint8_t  ALMON;
       uint8_t  RESERVED20[3];
  _RW uint16_t ALYEAR;
       uint16_t RESERVED21;
} RTC_TypeDef;

/*------------- Watchdog Timer (WDT) -----------------------------------------*/
/** \brief  Watchdog Timer (WDT) register structure definition */
typedef struct
{
  _RW uint8_t  WDMOD;
       uint8_t  RESERVED0[3];
  _RW uint32_t WDTC;
  _W  uint8_t  WDFEED;
       uint8_t  RESERVED1[3];
  _R  uint32_t WDTV;
  _RW uint32_t WDCLKSEL;
} WDT_TypeDef;

/*------------- Analog-to-Digital Converter (ADC) ----------------------------*/
/** \brief  Analog-to-Digital Converter (ADC) register structure definition */
typedef struct
{
  _RW uint32_t ADCR;
  _RW uint32_t ADGDR;
       uint32_t RESERVED0;
  _RW uint32_t ADINTEN;
  _R  uint32_t ADDR[8];
  _R  uint32_t ADSTAT;
  _RW uint32_t ADTRM;
} ADC_TypeDef;

/*------------- Digital-to-Analog Converter (DAC) ----------------------------*/
/** \brief  Digital-to-Analog Converter (DAC) register structure definition */
typedef struct
{
  _RW uint32_t DACR;
  _RW uint32_t DACCTRL;
  _RW uint16_t DACCNTVAL;
} DAC_TypeDef;

/*------------- Motor Control Pulse-Width Modulation (MCPWM) -----------------*/
/** \brief  Motor Control Pulse-Width Modulation (MCPWM) register structure definition */
typedef struct
{
  _R  uint32_t MCCON;
  _W  uint32_t MCCON_SET;
  _W  uint32_t MCCON_CLR;
  _R  uint32_t MCCAPCON;
  _W  uint32_t MCCAPCON_SET;
  _W  uint32_t MCCAPCON_CLR;
  _RW uint32_t MCTIM0;
  _RW uint32_t MCTIM1;
  _RW uint32_t MCTIM2;
  _RW uint32_t MCPER0;
  _RW uint32_t MCPER1;
  _RW uint32_t MCPER2;
  _RW uint32_t MCPW0;
  _RW uint32_t MCPW1;
  _RW uint32_t MCPW2;
  _RW uint32_t MCDEADTIME;
  _RW uint32_t MCCCP;
  _RW uint32_t MCCR0;
  _RW uint32_t MCCR1;
  _RW uint32_t MCCR2;
  _R  uint32_t MCINTEN;
  _W  uint32_t MCINTEN_SET;
  _W  uint32_t MCINTEN_CLR;
  _R  uint32_t MCCNTCON;
  _W  uint32_t MCCNTCON_SET;
  _W  uint32_t MCCNTCON_CLR;
  _R  uint32_t MCINTFLAG;
  _W  uint32_t MCINTFLAG_SET;
  _W  uint32_t MCINTFLAG_CLR;
  _W  uint32_t MCCAP_CLR;
} MCPWM_TypeDef;

/*------------- Quadrature Encoder Interface (QEI) ---------------------------*/
/** \brief  Quadrature Encoder Interface (QEI) register structure definition */
typedef struct
{
  _W  uint32_t QEICON;
  _R  uint32_t QEISTAT;
  _RW uint32_t QEICONF;
  _R  uint32_t QEIPOS;
  _RW uint32_t QEIMAXPOS;
  _RW uint32_t CMPOS0;
  _RW uint32_t CMPOS1;
  _RW uint32_t CMPOS2;
  _R  uint32_t INXCNT;
  _RW uint32_t INXCMP;
  _RW uint32_t QEILOAD;
  _R  uint32_t QEITIME;
  _R  uint32_t QEIVEL;
  _R  uint32_t QEICAP;
  _RW uint32_t VELCOMP;
  _RW uint32_t FILTER;
       uint32_t RESERVED0[998];
  _W  uint32_t QEIIEC;
  _W  uint32_t QEIIES;
  _R  uint32_t QEIINTSTAT;
  _R  uint32_t QEIIE;
  _W  uint32_t QEICLR;
  _W  uint32_t QEISET;
} QEI_TypeDef;

/*------------- Controller Area Network (CAN) --------------------------------*/
/** \brief  Controller Area Network Acceptance Filter RAM (CANAF_RAM)structure definition */
typedef struct
{
  _RW uint32_t mask[512];              /* ID Masks                           */
} CANAF_RAM_TypeDef;

/** \brief  Controller Area Network Acceptance Filter(CANAF) register structure definition */
typedef struct                          /* Acceptance Filter Registers        */
{
  _RW uint32_t AFMR;
  _RW uint32_t SFF_sa;
  _RW uint32_t SFF_GRP_sa;
  _RW uint32_t EFF_sa;
  _RW uint32_t EFF_GRP_sa;
  _RW uint32_t ENDofTable;
  _R  uint32_t LUTerrAd;
  _R  uint32_t LUTerr;
  _RW uint32_t FCANIE;
  _RW uint32_t FCANIC0;
  _RW uint32_t FCANIC1;
} CANAF_TypeDef;

/** \brief  Controller Area Network Central (CANCR) register structure definition */
typedef struct                          /* Central Registers                  */
{
  _R  uint32_t CANTxSR;
  _R  uint32_t CANRxSR;
  _R  uint32_t CANMSR;
} CANCR_TypeDef;

/** \brief  Controller Area Network Controller (CAN) register structure definition */
typedef struct                          /* Controller Registers               */
{
  _RW uint32_t MOD;
  _W  uint32_t CMR;
  _RW uint32_t GSR;
  _R  uint32_t ICR;
  _RW uint32_t IER;
  _RW uint32_t BTR;
  _RW uint32_t EWL;
  _R  uint32_t SR;
  _RW uint32_t RFS;
  _RW uint32_t RID;
  _RW uint32_t RDA;
  _RW uint32_t RDB;
  _RW uint32_t TFI1;
  _RW uint32_t TID1;
  _RW uint32_t TDA1;
  _RW uint32_t TDB1;
  _RW uint32_t TFI2;
  _RW uint32_t TID2;
  _RW uint32_t TDA2;
  _RW uint32_t TDB2;
  _RW uint32_t TFI3;
  _RW uint32_t TID3;
  _RW uint32_t TDA3;
  _RW uint32_t TDB3;
} CAN_TypeDef;

/*------------- General Purpose Direct Memory Access (GPDMA) -----------------*/
/** \brief  General Purpose Direct Memory Access (GPDMA) register structure definition */
typedef struct                          /* Common Registers                   */
{
  _R  uint32_t DMACIntStat;
  _R  uint32_t DMACIntTCStat;
  _W  uint32_t DMACIntTCClear;
  _R  uint32_t DMACIntErrStat;
  _W  uint32_t DMACIntErrClr;
  _R  uint32_t DMACRawIntTCStat;
  _R  uint32_t DMACRawIntErrStat;
  _R  uint32_t DMACEnbldChns;
  _RW uint32_t DMACSoftBReq;
  _RW uint32_t DMACSoftSReq;
  _RW uint32_t DMACSoftLBReq;
  _RW uint32_t DMACSoftLSReq;
  _RW uint32_t DMACConfig;
  _RW uint32_t DMACSync;
} GPDMA_TypeDef;

/** \brief  General Purpose Direct Memory Access Channel (GPDMACH) register structure definition */
typedef struct                          /* Channel Registers                  */
{
  _RW uint32_t DMACCSrcAddr;
  _RW uint32_t DMACCDestAddr;
  _RW uint32_t DMACCLLI;
  _RW uint32_t DMACCControl;
  _RW uint32_t DMACCConfig;
} GPDMACH_TypeDef;

/*------------- Universal Serial Bus (USB) -----------------------------------*/
/** \brief  Universal Serial Bus (USB) register structure definition */
typedef struct
{
  _R  uint32_t HcRevision;             /* USB Host Registers                 */
  _RW uint32_t HcControl;
  _RW uint32_t HcCommandStatus;
  _RW uint32_t HcInterruptStatus;
  _RW uint32_t HcInterruptEnable;
  _RW uint32_t HcInterruptDisable;
  _RW uint32_t HcHCCA;
  _R  uint32_t HcPeriodCurrentED;
  _RW uint32_t HcControlHeadED;
  _RW uint32_t HcControlCurrentED;
  _RW uint32_t HcBulkHeadED;
  _RW uint32_t HcBulkCurrentED;
  _R  uint32_t HcDoneHead;
  _RW uint32_t HcFmInterval;
  _R  uint32_t HcFmRemaining;
  _R  uint32_t HcFmNumber;
  _RW uint32_t HcPeriodicStart;
  _RW uint32_t HcLSTreshold;
  _RW uint32_t HcRhDescriptorA;
  _RW uint32_t HcRhDescriptorB;
  _RW uint32_t HcRhStatus;
  _RW uint32_t HcRhPortStatus1;
  _RW uint32_t HcRhPortStatus2;
       uint32_t RESERVED0[40];
  _R  uint32_t Module_ID;

  _R  uint32_t OTGIntSt;               /* USB On-The-Go Registers            */
  _RW uint32_t OTGIntEn;
  _W  uint32_t OTGIntSet;
  _W  uint32_t OTGIntClr;
  _RW uint32_t OTGStCtrl;
  _RW uint32_t OTGTmr;
       uint32_t RESERVED1[58];

  _R  uint32_t USBDevIntSt;            /* USB Device Interrupt Registers     */
  _RW uint32_t USBDevIntEn;
  _W  uint32_t USBDevIntClr;
  _W  uint32_t USBDevIntSet;

  _W  uint32_t USBCmdCode;             /* USB Device SIE Command Registers   */
  _R  uint32_t USBCmdData;

  _R  uint32_t USBRxData;              /* USB Device Transfer Registers      */
  _W  uint32_t USBTxData;
  _R  uint32_t USBRxPLen;
  _W  uint32_t USBTxPLen;
  _RW uint32_t USBCtrl;
  _W  uint32_t USBDevIntPri;

  _R  uint32_t USBEpIntSt;             /* USB Device Endpoint Interrupt Regs */
  _RW uint32_t USBEpIntEn;
  _W  uint32_t USBEpIntClr;
  _W  uint32_t USBEpIntSet;
  _W  uint32_t USBEpIntPri;

  _RW uint32_t USBReEp;                /* USB Device Endpoint Realization Reg*/
  _W  uint32_t USBEpInd;
  _RW uint32_t USBMaxPSize;

  _R  uint32_t USBDMARSt;              /* USB Device DMA Registers           */
  _W  uint32_t USBDMARClr;
  _W  uint32_t USBDMARSet;
       uint32_t RESERVED2[9];
  _RW uint32_t USBUDCAH;
  _R  uint32_t USBEpDMASt;
  _W  uint32_t USBEpDMAEn;
  _W  uint32_t USBEpDMADis;
  _R  uint32_t USBDMAIntSt;
  _RW uint32_t USBDMAIntEn;
       uint32_t RESERVED3[2];
  _R  uint32_t USBEoTIntSt;
  _W  uint32_t USBEoTIntClr;
  _W  uint32_t USBEoTIntSet;
  _R  uint32_t USBNDDRIntSt;
  _W  uint32_t USBNDDRIntClr;
  _W  uint32_t USBNDDRIntSet;
  _R  uint32_t USBSysErrIntSt;
  _W  uint32_t USBSysErrIntClr;
  _W  uint32_t USBSysErrIntSet;
       uint32_t RESERVED4[15];

  union {
  _R  uint32_t I2C_RX;                 /* USB OTG I2C Registers              */
  _W  uint32_t I2C_TX;
  };
  _R  uint32_t I2C_STS;
  _RW uint32_t I2C_CTL;
  _RW uint32_t I2C_CLKHI;
  _W  uint32_t I2C_CLKLO;
       uint32_t RESERVED5[824];

  union {
  _RW uint32_t USBClkCtrl;             /* USB Clock Control Registers        */
  _RW uint32_t OTGClkCtrl;
  };
  union {
  _R  uint32_t USBClkSt;
  _R  uint32_t OTGClkSt;
  };
} USB_TypeDef;

/*------------- Ethernet Media Access Controller (EMAC) ----------------------*/
/** \brief  Ethernet Media Access Controller (EMAC) register structure definition */
typedef struct
{
  _RW uint32_t MAC1;                   /* MAC Registers                      */
  _RW uint32_t MAC2;
  _RW uint32_t IPGT;
  _RW uint32_t IPGR;
  _RW uint32_t CLRT;
  _RW uint32_t MAXF;
  _RW uint32_t SUPP;
  _RW uint32_t TEST;
  _RW uint32_t MCFG;
  _RW uint32_t MCMD;
  _RW uint32_t MADR;
  _W  uint32_t MWTD;
  _R  uint32_t MRDD;
  _R  uint32_t MIND;
       uint32_t RESERVED0[2];
  _RW uint32_t SA0;
  _RW uint32_t SA1;
  _RW uint32_t SA2;
       uint32_t RESERVED1[45];
  _RW uint32_t Command;                /* Control Registers                  */
  _R  uint32_t Status;
  _RW uint32_t RxDescriptor;
  _RW uint32_t RxStatus;
  _RW uint32_t RxDescriptorNumber;
  _R  uint32_t RxProduceIndex;
  _RW uint32_t RxConsumeIndex;
  _RW uint32_t TxDescriptor;
  _RW uint32_t TxStatus;
  _RW uint32_t TxDescriptorNumber;
  _RW uint32_t TxProduceIndex;
  _R  uint32_t TxConsumeIndex;
       uint32_t RESERVED2[10];
  _R  uint32_t TSV0;
  _R  uint32_t TSV1;
  _R  uint32_t RSV;
       uint32_t RESERVED3[3];
  _RW uint32_t FlowControlCounter;
  _R  uint32_t FlowControlStatus;
       uint32_t RESERVED4[34];
  _RW uint32_t RxFilterCtrl;           /* Rx Filter Registers                */
  _RW uint32_t RxFilterWoLStatus;
  _RW uint32_t RxFilterWoLClear;
       uint32_t RESERVED5;
  _RW uint32_t HashFilterL;
  _RW uint32_t HashFilterH;
       uint32_t RESERVED6[882];
  _R  uint32_t IntStatus;              /* Module Control Registers           */
  _RW uint32_t IntEnable;
  _W  uint32_t IntClear;
  _W  uint32_t IntSet;
       uint32_t RESERVED7;
  _RW uint32_t PowerDown;
       uint32_t RESERVED8;
  _RW uint32_t Module_ID;
} EMAC_TypeDef;



/******************************************************************************/
/*                         Peripheral memory map                              */
/******************************************************************************/
/* Base addresses                                                             */
#define FLASH_BASE        (0x00000000UL)
#define RAM_BASE          (0x10000000UL)
#ifdef __LPC17XX_REV00
#define AHBRAM0_BASE      (0x20000000UL)
#define AHBRAM1_BASE      (0x20004000UL)
#else
#define AHBRAM0_BASE      (0x2007C000UL)
#define AHBRAM1_BASE      (0x20080000UL)
#endif
#define GPIO_BASE         (0x2009C000UL)
#define APB0_BASE         (0x40000000UL)
#define APB1_BASE         (0x40080000UL)
#define AHB_BASE          (0x50000000UL)
#define CM3_BASE          (0xE0000000UL)

/* APB0 peripherals                                                           */
#define WDT_BASE          (APB0_BASE + 0x00000)
#define TIM0_BASE         (APB0_BASE + 0x04000)
#define TIM1_BASE         (APB0_BASE + 0x08000)
#define UART0_BASE        (APB0_BASE + 0x0C000)
#define UART1_BASE        (APB0_BASE + 0x10000)
#define PWM1_BASE         (APB0_BASE + 0x18000)
#define I2C0_BASE         (APB0_BASE + 0x1C000)
#define SPI_BASE          (APB0_BASE + 0x20000)
#define RTC_BASE          (APB0_BASE + 0x24000)
#define GPIOINT_BASE      (APB0_BASE + 0x28080)
#define PINCON_BASE       (APB0_BASE + 0x2C000)
#define SSP1_BASE         (APB0_BASE + 0x30000)
#define ADC_BASE          (APB0_BASE + 0x34000)
#define CANAF_RAM_BASE    (APB0_BASE + 0x38000)
#define CANAF_BASE        (APB0_BASE + 0x3C000)
#define CANCR_BASE        (APB0_BASE + 0x40000)
#define CAN1_BASE         (APB0_BASE + 0x44000)
#define CAN2_BASE         (APB0_BASE + 0x48000)
#define I2C1_BASE         (APB0_BASE + 0x5C000)

/* APB1 peripherals                                                           */
#define SSP0_BASE         (APB1_BASE + 0x08000)
#define DAC_BASE          (APB1_BASE + 0x0C000)
#define TIM2_BASE         (APB1_BASE + 0x10000)
#define TIM3_BASE         (APB1_BASE + 0x14000)
#define UART2_BASE        (APB1_BASE + 0x18000)
#define UART3_BASE        (APB1_BASE + 0x1C000)
#define I2C2_BASE         (APB1_BASE + 0x20000)
#define I2S_BASE          (APB1_BASE + 0x28000)
#define RIT_BASE          (APB1_BASE + 0x30000)
#define MCPWM_BASE        (APB1_BASE + 0x38000)
#define QEI_BASE          (APB1_BASE + 0x3C000)
#define SC_BASE           (APB1_BASE + 0x7C000)

/* AHB peripherals                                                            */
#define EMAC_BASE         (AHB_BASE  + 0x00000)
#define GPDMA_BASE        (AHB_BASE  + 0x04000)
#define GPDMACH0_BASE     (AHB_BASE  + 0x04100)
#define GPDMACH1_BASE     (AHB_BASE  + 0x04120)
#define GPDMACH2_BASE     (AHB_BASE  + 0x04140)
#define GPDMACH3_BASE     (AHB_BASE  + 0x04160)
#define GPDMACH4_BASE     (AHB_BASE  + 0x04180)
#define GPDMACH5_BASE     (AHB_BASE  + 0x041A0)
#define GPDMACH6_BASE     (AHB_BASE  + 0x041C0)
#define GPDMACH7_BASE     (AHB_BASE  + 0x041E0)
#define USB_BASE          (AHB_BASE  + 0x0C000)

/* GPIOs                                                                      */
#define GPIO0_BASE        (GPIO_BASE + 0x00000)
#define GPIO1_BASE        (GPIO_BASE + 0x00020)
#define GPIO2_BASE        (GPIO_BASE + 0x00040)
#define GPIO3_BASE        (GPIO_BASE + 0x00060)
#define GPIO4_BASE        (GPIO_BASE + 0x00080)

/******************************************************************************/
/*                         Peripheral declaration                             */
/******************************************************************************/
#define PERIPH_SC                ((SC_TypeDef        *) SC_BASE       )
#define PERIPH_GPIO0             ((GPIO_TypeDef      *) GPIO0_BASE    )
#define PERIPH_GPIO1             ((GPIO_TypeDef      *) GPIO1_BASE    )
#define PERIPH_GPIO2             ((GPIO_TypeDef      *) GPIO2_BASE    )
#define PERIPH_GPIO3             ((GPIO_TypeDef      *) GPIO3_BASE    )
#define PERIPH_GPIO4             ((GPIO_TypeDef      *) GPIO4_BASE    )
#define PERIPH_WDT               ((WDT_TypeDef       *) WDT_BASE      )
#define PERIPH_TIMER0            ((TIM_TypeDef       *) TIM0_BASE     )
#define PERIPH_TIMER1            ((TIM_TypeDef       *) TIM1_BASE     )
#define PERIPH_TIMER2            ((TIM_TypeDef       *) TIM2_BASE     )
#define PERIPH_TIMER3            ((TIM_TypeDef       *) TIM3_BASE     )
#define PERIPH_RIT               ((RIT_TypeDef       *) RIT_BASE      )
#define PERIPH_UART0             ((UART_TypeDef      *) UART0_BASE    )
#define PERIPH_UART1             ((UART1_TypeDef     *) UART1_BASE    )
#define PERIPH_UART2             ((UART_TypeDef      *) UART2_BASE    )
#define PERIPH_UART3             ((UART_TypeDef      *) UART3_BASE    )
#define PERIPH_PWM1              ((PWM_TypeDef       *) PWM1_BASE     )
#define PERIPH_I2C0              ((I2C_TypeDef       *) I2C0_BASE     )
#define PERIPH_I2C1              ((I2C_TypeDef       *) I2C1_BASE     )
#define PERIPH_I2C2              ((I2C_TypeDef       *) I2C2_BASE     )
#define PERIPH_I2S               ((I2S_TypeDef       *) I2S_BASE      )
#define PERIPH_SPI               ((SPI_TypeDef       *) SPI_BASE      )
#define PERIPH_RTC               ((RTC_TypeDef       *) RTC_BASE      )
#define PERIPH_GPIOINT           ((GPIOINT_TypeDef   *) GPIOINT_BASE  )
#define PERIPH_PINCON            ((PINCON_TypeDef    *) PINCON_BASE   )
#define PERIPH_SSP0              ((SSP_TypeDef       *) SSP0_BASE     )
#define PERIPH_SSP1              ((SSP_TypeDef       *) SSP1_BASE     )
#define PERIPH_ADC               ((ADC_TypeDef       *) ADC_BASE      )
#define PERIPH_DAC               ((DAC_TypeDef       *) DAC_BASE      )
#define PERIPH_CANAF_RAM         ((CANAF_RAM_TypeDef *) CANAF_RAM_BASE)
#define PERIPH_CANAF             ((CANAF_TypeDef     *) CANAF_BASE    )
#define PERIPH_CANCR             ((CANCR_TypeDef     *) CANCR_BASE    )
#define PERIPH_CAN1              ((CAN_TypeDef       *) CAN1_BASE     )
#define PERIPH_CAN2              ((CAN_TypeDef       *) CAN2_BASE     )
#define PERIPH_MCPWM             ((MCPWM_TypeDef     *) MCPWM_BASE    )
#define PERIPH_QEI               ((QEI_TypeDef       *) QEI_BASE      )
#define PERIPH_EMAC              ((EMAC_TypeDef      *) EMAC_BASE     )
#define PERIPH_GPDMA             ((GPDMA_TypeDef     *) GPDMA_BASE    )
#define PERIPH_GPDMACH0          ((GPDMACH_TypeDef   *) GPDMACH0_BASE )
#define PERIPH_GPDMACH1          ((GPDMACH_TypeDef   *) GPDMACH1_BASE )
#define PERIPH_GPDMACH2          ((GPDMACH_TypeDef   *) GPDMACH2_BASE )
#define PERIPH_GPDMACH3          ((GPDMACH_TypeDef   *) GPDMACH3_BASE )
#define PERIPH_GPDMACH4          ((GPDMACH_TypeDef   *) GPDMACH4_BASE )
#define PERIPH_GPDMACH5          ((GPDMACH_TypeDef   *) GPDMACH5_BASE )
#define PERIPH_GPDMACH6          ((GPDMACH_TypeDef   *) GPDMACH6_BASE )
#define PERIPH_GPDMACH7          ((GPDMACH_TypeDef   *) GPDMACH7_BASE )
#define PERIPH_USB               ((USB_TypeDef       *) USB_BASE      )


/** GPIO Port 0 Register addresses.		*/
/** These addresses are used as base addresses and port-wise offset will be added to for each port operation.	*/
#define GPIO_IODIR_BASE				0x2009C000
#define GPIO_MASK_BASE				0x2009C010
#define GPIO_PIN_BASE				0x2009C014
#define GPIO_SET_BASE				0x2009C018
#define GPIO_CLEAR_BASE				0x2009C01C

/** @} */
#endif	// __PCF_INCLUDE_PRIVATE_ARCH_ARM_CM3_NXP_LPC1768_LPC1768_REGMAP_H
