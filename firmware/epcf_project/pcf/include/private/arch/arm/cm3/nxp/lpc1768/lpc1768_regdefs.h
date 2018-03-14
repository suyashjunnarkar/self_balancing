/**
 * \file      lpc1768_regdefs.h
 * \brief     Register Defines
 * \copyright Copyright (c) 2014 <br> PhiRobotics Research Pvt Ltd
 * 
 * \par
 * For licensing information, see the file 'LICENSE' in the root folder of
 * this software module.
 * 
 * Review status: NO
 */

#ifndef __PCF_INCLUDE_PRIVATE_ARCH_ARM_CM3_NXP_LPC1768_LPC1768_REGDEFS_H
#define __PCF_INCLUDE_PRIVATE_ARCH_ARM_CM3_NXP_LPC1768_LPC1768_REGDEFS_H
 
/** Bit defines for PCONP register      */
// Bit 0 in PCONP is reserved

// Bit 5 in PCONP is reserved
#define PWR_SPI         BIT_MASK_8
#define PWR_RTC         BIT_MASK_9
#define PWR_SSP1        BIT_MASK_10

// Bit 11 in PCONP is reserved
#define PWR_CAN1        BIT_MASK_13
#define PWR_CAN2        BIT_MASK_14 
#define PWR_GPIO        BIT_MASK_15
#define PWR_RIT         BIT_MASK_16
#define PWR_MCPWM       BIT_MASK_17
#define PWR_QEI         BIT_MASK_18
// Bit 20 in PCONP is reserved
#define PWR_SSP0        BIT_MASK_21
#define PWR_I2S         BIT_MASK_27

// Bit 28 in PCONP is reserved
#define PWR_GPDMA       BIT_MASK(29)
#define PWR_ENET        BIT_MASK(30)
#define PWR_USB         BIT_MASK(31)


/** Bit defines for PCLKSEL registers   */
#define PCLK_DIV_WDT      0
#define PCLK_DIV_TIMER0     2
#define PCLK_DIV_TIMER1     4
#define PCLK_DIV_UART0      6
#define PCLK_DIV_UART1      8
// Bit 10:11 in PCLKSEL0 are reserved
#define PCLK_DIV_PWM1     12
#define PCLK_DIV_I2C0     14
#define PCLK_DIV_SPI      16
// Bit 18:19 in PCLKSEL0 are reserved
#define PCLK_DIV_SSP1     20
#define PCLK_DIV_DAC      22
#define PCLK_DIV_ADC      24
#define PCLK_DIV_CAN1     26
#define PCLK_DIV_CAN2     28
#define PCLK_DIV_ACF      30
#define PCLK_DIV_QEI      32
#define PCLK_DIV_GPIOINT    34
#define PCLK_DIV_PCB      36
#define PCLK_DIV_I2C1     38
// Bit 8:9 in PCLKSEL1 are reserved
#define PCLK_DIV_SSP0     42
#define PCLK_DIV_TIMER2     44
#define PCLK_DIV_TIMER3     46
#define PCLK_DIV_UART2      48
#define PCLK_DIV_UART3      50
#define PCLK_DIV_I2C2     52
#define PCLK_DIV_I2S      54
// Bit 24:25 in PCLKSEL1 are reserved
#define PCLK_DIV_RIT      58
#define PCLK_DIV_SYSCON     60
#define PCLK_DIV_MCPWM      62


/**
 * Bit definitions for CAN configuration registers
 * \addtogroup PF_CAN CAN
 * @{
 */
/** 
 * \brief Bit definitions for CAN Mode Register (CANMOD) 
 */
/** Bit definition for RM bit in MOD register   */ 
#define CAN_MOD_RM        BIT_MASK_0
/** Bit definition for LOM bit in MOD register    */
#define CAN_MOD_LOM       BIT_MASK_1
/** Bit definition for STM bit in MOD register    */
#define CAN_MOD_STM       BIT_MASK_2
/** Bit definition for TPM bit in MOD register    */
#define CAN_MOD_TPM       BIT_MASK_3
/** Bit definition for SM bit in MOD register   */
#define CAN_MOD_SM        BIT_MASK_4
/** Bit definition for RPM bit in MOD register    */
#define CAN_MOD_RPM       BIT_MASK_5
/** Bit definition for TM bit in MOD register   */
#define CAN_MOD_TM        BIT_MASK_7

/** 
 * \brief Bit definitions for CAN Command Register (CANCMR) 
 */
#define CAN_CMR_TR        BIT_MASK_0
#define CAN_CMR_AT        BIT_MASK_1
#define CAN_CMR_RRB       BIT_MASK_2
#define CAN_CMR_CDO       BIT_MASK_3
#define CAN_CMR_SRR       BIT_MASK_4
#define CAN_CMR_STB1      BIT_MASK_5
#define CAN_CMR_STB2      BIT_MASK_6
#define CAN_CMR_STB3      BIT_MASK_7

/** 
 * \brief Bit definitions for CAN Global Status Register (CANGSR) 
 */
#define CAN_GSR_RBS       BIT_MASK_0
#define CAN_GSR_DOS       BIT_MASK_1
#define CAN_GSR_TBS       BIT_MASK_2
#define CAN_GSR_TCS       BIT_MASK_3
#define CAN_GSR_RS        BIT_MASK_4
#define CAN_GSR_TS        BIT_MASK_5
#define CAN_GSR_ES        BIT_MASK_6
#define CAN_GSR_BS        BIT_MASK_7

/** 
 * \brief Bit definitions for CAN Controller Status Register (CANxSR) 
 */
#define CAN_SR_RBS        BIT_MASK_0
#define CAN_SR_DOS        BIT_MASK_1
#define CAN_SR_TBS1       BIT_MASK_2
#define CAN_SR_TCS1       BIT_MASK_3
#define CAN_SR_RS1        BIT_MASK_4
#define CAN_SR_TS1        BIT_MASK_5
#define CAN_SR_ES       BIT_MASK_6
#define CAN_SR_BS       BIT_MASK_7
#define CAN_SR_TBS2       BIT_MASK_10
#define CAN_SR_TCS2       BIT_MASK_11
#define CAN_SR_TS2        BIT_MASK_13
#define CAN_SR_TBS3       BIT_MASK_18
#define CAN_SR_TCS3       BIT_MASK_19
#define CAN_SR_TS3        BIT_MASK_21

/** 
 * \brief Bit definitions for CAN Receive Frame Status Register (CANxRFS) 
 */
#define CAN_RFS_INDEX_MASK    (BIT_MASK_0 | BIT_MASK_1 | BIT_MASK_2 | BIT_MASK_3 | BIT_MASK_4 | BIT_MASK_5 | BIT_MASK_6 | BIT_MASK_7 | BIT_MASK_8 | BIT_MASK_9)
#define CAN_RFS_BP        BIT_MASK_10     
#define CAN_RFS_DLC       (BIT_MASK_16 | BIT_MASK_17 | BIT_MASK_18 | BIT_MASK_19)
#define CAN_RFS_RTR       BIT_MASK_30
#define CAN_RFS_FF        BIT_MASK_31

/** 
 * \brief Bit definitions for CAN Transmit Frame Information Register (CANxTFI) 
 */
#define CAN_TFI_PRIO_MASK   (BIT_MASK_0 | BIT_MASK_1 | BIT_MASK_2 | BIT_MASK_3 | BIT_MASK_4 | BIT_MASK_5 | BIT_MASK_6 | BIT_MASK_7)
#define CAN_TFI_DLC       (BIT_MASK_16 | BIT_MASK_17 | BIT_MASK_18 | BIT_MASK_19)
#define CAN_TFI_RTR       BIT_MASK_30
#define CAN_TFI_FF        BIT_MASK_31

/** 
 * \brief Bit definitions for CAN Transmit Interrupt and Capture Register (CANxTFI) 
 */
#define CAN_ICR_RI        BIT_MASK_0
#define CAN_ICR_TI1       BIT_MASK_1
#define CAN_ICR_EI        BIT_MASK_2
#define CAN_ICR_DOI       BIT_MASK_3
#define CAN_ICR_WUI       BIT_MASK_4
#define CAN_ICR_EPI       BIT_MASK_5
#define CAN_ICR_ALI       BIT_MASK_6
#define CAN_ICR_BEI       BIT_MASK_7
#define CAN_ICR_IDI       BIT_MASK_8
#define CAN_ICR_TI2       BIT_MASK_9
#define CAN_ICR_TI3       BIT_MASK_10
#define CAN_ICR_ERRDIR      BIT_MASK_21



/** @} */

/*
 *  USB registers bit definitions
 */

/* Device Interrupt Bit Definitions */
#define USB_DEV_INT_FRAME           0x00000001
#define USB_DEV_INT_EP_FAST         0x00000002
#define USB_DEV_INT_EP_SLOW         0x00000004
#define USB_DEV_INT_STAT          0x00000008
#define USB_DEV_INT_CCEMTY          0x00000010
#define USB_DEV_INT_CDFULL          0x00000020
#define USB_DEV_INT_RxENDPKT        0x00000040
#define USB_DEV_INT_TxENDPKT        0x00000080
#define USB_DEV_INT_EP_RLZED        0x00000100
#define USB_DEV_INT_ERR             0x00000200

/* Rx & Tx Packet Length Definitions */
#define USB_PKT_LNGTH_MASK      0x000003FF
#define USB_PKT_DV              0x00000400
#define USB_PKT_RDY             0x00000800

/* USB Control Definitions */
#define USB_CTRL_RD_EN          0x00000001
#define USB_CTRL_WR_EN          0x00000002

/* Command Codes */
#define USB_CMD_SET_ADDR        0x00D00500
#define USB_CMD_CFG_DEV         0x00D80500
#define USB_CMD_SET_MODE        0x00F30500
#define USB_CMD_RD_FRAME        0x00F50500
#define USB_DAT_RD_FRAME        0x00F50200
#define USB_CMD_RD_TEST         0x00FD0500
#define USB_DAT_RD_TEST         0x00FD0200
#define USB_CMD_SET_DEV_STAT    0x00FE0500
#define USB_CMD_GET_DEV_STAT    0x00FE0500
#define USB_DAT_GET_DEV_STAT    0x00FE0200
#define USB_CMD_GET_ERR_CODE    0x00FF0500
#define USB_DAT_GET_ERR_CODE    0x00FF0200
#define USB_CMD_RD_ERR_STAT     0x00FB0500
#define USB_DAT_RD_ERR_STAT     0x00FB0200
#define USB_DAT_WR_BYTE(x)     (0x00000100 | ((x) << 16))
#define USB_CMD_SEL_EP(x)      (0x00000500 | ((x) << 16))
#define USB_DAT_SEL_EP(x)      (0x00000200 | ((x) << 16))
#define USB_CMD_SEL_EP_CLRI(x) (0x00400500 | ((x) << 16))
#define USB_DAT_SEL_EP_CLRI(x) (0x00400200 | ((x) << 16))
#define USB_CMD_SET_EP_STAT(x) (0x00400500 | ((x) << 16))
#define USB_CMD_CLR_BUF         0x00F20500
#define USB_DAT_CLR_BUF         0x00F20200
#define USB_CMD_VALID_BUF       0x00FA0500

/* Device Address Register Definitions */
#define USB_DEV_ADDR_MASK       0x7F
#define USB_DEV_EN              0x80

/* Device Configure Register Definitions */
#define USB_CONF_DVICE          0x01

/* Device Mode Register Definitions */
#define USB_AP_CLK              0x01
#define USB_INAK_CI             0x02
#define USB_INAK_CO             0x04
#define USB_INAK_II             0x08
#define USB_INAK_IO             0x10
#define USB_INAK_BI             0x20
#define USB_INAK_BO             0x40

/* Device Status Register Definitions */
#define USB_DEV_CON             0x01
#define USB_DEV_CON_CH          0x02
#define USB_DEV_SUS             0x04
#define USB_DEV_SUS_CH          0x08
#define USB_DEV_RST             0x10

/* Error Code Register Definitions */
#define USB_ERR_EC_MASK         0x0F
#define USB_ERR_EA              0x10

/* Error Status Register Definitions */
#define USB_ERR_PID             0x01
#define USB_ERR_UEPKT           0x02
#define USB_ERR_DCRC            0x04
#define USB_ERR_TIMOUT          0x08
#define USB_ERR_EOP             0x10
#define USB_ERR_B_OVRN          0x20
#define USB_ERR_BTSTF           0x40
#define USB_ERR_TGL             0x80

/* Endpoint Select Register Definitions */
#define USB_EP_SEL_F            0x01
#define USB_EP_SEL_ST           0x02
#define USB_EP_SEL_STP          0x04
#define USB_EP_SEL_PO           0x08
#define USB_EP_SEL_EPN          0x10
#define USB_EP_SEL_B_1_FULL     0x20
#define USB_EP_SEL_B_2_FULL     0x40

/* Endpoint Status Register Definitions */
#define USB_EP_STAT_ST          0x01
#define USB_EP_STAT_DA          0x20
#define USB_EP_STAT_RF_MO       0x40
#define USB_EP_STAT_CND_ST      0x80

/* Clear Buffer Register Definitions */
#define USB_CLR_BUF_PO          0x01


/* DMA Interrupt Bit Definitions */
#define USB_DMA_INT_EOT       0x01
#define USB_DMA_INT_NDD_REQ   0x02
#define USB_DMA_INT_SYS_ERR   0x04

#endif // __PCF_INCLUDE_PRIVATE_ARCH_ARM_CM3_NXP_LPC1768_LPC1768_REGDEFS_H
