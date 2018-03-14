/**
 * \file    can_lpc1768_config.h
 * \brief   Native CAN Driver Configuration for LPC1768.
 *
 */
#ifndef __EPCF_INCLUDED_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_CAN_CAN_LPC1768_CONFIG_H
#define __EPCF_INCLUDED_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_CAN_CAN_LPC1768_CONFIG_H

/** \brief Maximum ports available for CAN module				*/
#define CAN_MAX_CHANNEL		2
#define CAN_MAX_BAUDRATE   1000000
/** \brief ARCH SPECIFIC Configuration macros       */
#define CAN1_CH             CAN1
#define CAN2_CH             CAN2

#define CAN0_CHANNEL        PERIPH(CAN0_CH)
#define CAN1_CHANNEL        PERIPH(CAN1_CH)
#define CAN_PCLK_DIV        2

#define CAN_INT_HANDLER    PCF_CONCATE(CAN,_IRQHandler)


#define PWR_CAN1       		(1<<13)
#define PWR_CAN2       		(1<<14)
#define	PWR_CAN_CH(X)		PCF_CONCATE(PWR_,X)
#define PCLK_DIV(X)         PCF_CONCATE(PCLK_DIV_,X)
#define PERIPH(X)			PCF_CONCATE(PERIPH_,X)
#define POWER_ON(X) 		PERIPH_SC->PCONP |= X
#define POWER_OFF(X) 		PERIPH_SC->PCONP &= ~(X)
#define IRQ_NUM(X)			PCF_CONCATE(X,_IRQn)

/**
 * Bit definitions for CAN configuration registers
 * @{
 */
/** 
 * \brief Bit definitions for CAN Mode Register (CANMOD) 
 */
/** Bit definition for RM bit in MOD register		*/ 
#define CAN_MOD_RM				BIT_MASK(0)/** Bit definition for LOM bit in MOD register		*/
#define CAN_MOD_LOM				BIT_MASK(1)
/** Bit definition for STM bit in MOD register		*/
#define CAN_MOD_STM				BIT_MASK(2)
/** Bit definition for TPM bit in MOD register		*/
#define CAN_MOD_TPM				BIT_MASK(3)
/** Bit definition for SM bit in MOD register		*/
#define CAN_MOD_SM				BIT_MASK(4)
/** Bit definition for RPM bit in MOD register		*/
#define CAN_MOD_RPM				BIT_MASK(5)
/** Bit definition for TM bit in MOD register		*/
#define CAN_MOD_TM				BIT_MASK(7)

/** 
 * \brief Bit definitions for CAN Command Register (CANCMR) 
 */
#define CAN_CMR_TR				BIT_MASK(0)
#define CAN_CMR_AT				BIT_MASK(1)
#define CAN_CMR_RRB				BIT_MASK(2)
#define CAN_CMR_CDO				BIT_MASK(3)
#define CAN_CMR_SRR				BIT_MASK(4)
#define CAN_CMR_STB1			BIT_MASK(5)
#define CAN_CMR_STB2			BIT_MASK(6)
#define CAN_CMR_STB3			BIT_MASK(7)

/** 
 * \brief Bit definitions for CAN Global Status Register (CANGSR) 
 */
#define CAN_GSR_RBS				BIT_MASK(0)
#define CAN_GSR_DOS				BIT_MASK(1)
#define CAN_GSR_TBS				BIT_MASK(2)
#define CAN_GSR_TCS				BIT_MASK(3)
#define CAN_GSR_RS				BIT_MASK(4)
#define CAN_GSR_TS				BIT_MASK(5)
#define CAN_GSR_ES				BIT_MASK(6)
#define CAN_GSR_BS				BIT_MASK(7)

/** 
 * \brief Bit definitions for CAN Controller Status Register (CANxSR) 
 */
#define CAN_SR_RBS				BIT_MASK(0)
#define CAN_SR_DOS				BIT_MASK(1)
#define CAN_SR_TBS1				BIT_MASK(2)
#define CAN_SR_TCS1				BIT_MASK(3)
#define CAN_SR_RS1				BIT_MASK(4)
#define CAN_SR_TS1				BIT_MASK(5)
#define CAN_SR_ES				BIT_MASK(6)
#define CAN_SR_BS				BIT_MASK(7)
#define CAN_SR_RBS2				BIT_MASK(8)
#define CAN_SR_DOS2				BIT_MASK(9)
#define CAN_SR_TBS2				BIT_MASK(10)
#define CAN_SR_TCS2				BIT_MASK(11)
#define CAN_SR_RS2				BIT_MASK(12)
#define CAN_SR_TS2				BIT_MASK(13)
#define CAN_SR_ES2				BIT_MASK(14)
#define CAN_SR_BS2				BIT_MASK(15)
#define CAN_SR_RBS3				BIT_MASK(16)
#define CAN_SR_DOS3				BIT_MASK(17)
#define CAN_SR_TBS3				BIT_MASK(18)
#define CAN_SR_TCS3				BIT_MASK(19)
#define CAN_SR_TS3				BIT_MASK(21)
#define CAN_SR_ES3				BIT_MASK(22)
#define CAN_SR_BS3				BIT_MASK(23)
/** 
 * \brief Bit definitions for CAN Receive Frame Status Register (CANxRFS) 
 */
#define CAN_RFS_INDEX_MASK		(BIT_MASK(0) | BIT_MASK(1) | BIT_MASK(2) | BIT_MASK(3) | BIT_MASK(4) | BIT_MASK(5) | BIT_MASK(6) | BIT_MASK(7) | BIT_MASK(8) | BIT_MASK(9))
#define CAN_RFS_BP				BIT_MASK(10)			
#define CAN_RFS_DLC				(BIT_MASK(16) | BIT_MASK(17) | BIT_MASK(18) | BIT_MASK(19))
#define CAN_RFS_RTR				BIT_MASK(30)
#define CAN_RFS_FF				BIT_MASK(31)

/** 
 * \brief Bit definitions for CAN Transmit Frame Information Register (CANxTFI) 
 */
#define CAN_TFI_PRIO_MASK		(BIT_MASK(0)| BIT_MASK(1) | BIT_MASK(2) | BIT_MASK(3) | BIT_MASK(4) | BIT_MASK(5) | BIT_MASK(6)| BIT_MASK(7))
#define CAN_TFI_DLC				(BIT_MASK(16) | BIT_MASK(17) | BIT_MASK(18) | BIT_MASK(19))
#define CAN_TFI_RTR				BIT_MASK(30)
#define CAN_TFI_FF				BIT_MASK(31)

/** 
 * \brief Bit definitions for CAN Transmit Interrupt and Capture Register (CANxTFI) 
 */
#define CAN_ICR_RI				BIT_MASK(0)
#define CAN_ICR_TI1				BIT_MASK(1)
#define CAN_ICR_EI				BIT_MASK(2)
#define CAN_ICR_DOI				BIT_MASK(3)
#define CAN_ICR_WUI				BIT_MASK(4)
#define CAN_ICR_EPI				BIT_MASK(5)
#define CAN_ICR_ALI				BIT_MASK(6)
#define CAN_ICR_BEI				BIT_MASK(7)
#define CAN_ICR_IDI				BIT_MASK(8)
#define CAN_ICR_TI2				BIT_MASK(9)
#define CAN_ICR_TI3				BIT_MASK(10)
#define CAN_ICR_ERRDIR			BIT_MASK(21)
#endif      // __EPCF_INCLUDED_NATIVE_PORT_ARM32_CM3_NXP_LPC1768_CAN_CAN_LPC1768_CONFIG_H
