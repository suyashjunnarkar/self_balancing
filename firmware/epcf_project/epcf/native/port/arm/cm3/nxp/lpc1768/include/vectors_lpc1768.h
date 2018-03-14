#ifndef __PCF_INCLUDED_NATIVE_PORT_ARM32_CM3_LPC_VECTORS_LPC1768_H
#define __PCF_INCLUDED_NATIVE_PORT_ARM32_CM3_LPC_VECTORS_LPC1768_H

void NMI_Handler (void);
void HardFault_Handler (void);
void MemManage_Handler (void);
void BusFault_Handler (void);
void UsageFault_Handler (void);
void SVC_Handler (void);
void DebugMon_Handler (void);
void PendSV_Handler (void);
void SysTick_Handler (void);

void WDT_IRQHandler (void);
void TIMER0_IRQHandler (void);
void TIMER1_IRQHandler (void);
void TIMER2_IRQHandler (void);
void TIMER3_IRQHandler (void);
void UART0_IRQHandler (void);
void UART1_IRQHandler (void);
void UART2_IRQHandler (void);
void UART3_IRQHandler (void);
void PWM_IRQHandler (void);
void I2C0_IRQHandler (void);
void I2C1_IRQHandler (void);
void I2C2_IRQHandler (void);
void SPI_IRQHandler (void);
void SSP0_IRQHandler (void);
void SSP1_IRQHandler (void);
void PLL0_IRQHandler (void);
void RTC_IRQHandler (void);
void EINT0_IRQHandler (void);
void EINT1_IRQHandler (void);
void EINT2_IRQHandler (void);
void EINT3_IRQHandler (void);
void ADC_IRQHandler (void);
void BOD_IRQHandler (void);
void USB_IRQHandler (void);
void CAN_IRQHandler (void);
void DMA_IRQHandler (void);
void I2S_IRQHandler (void);
void ENET_IRQHandler (void);
void RIT_IRQHandler (void);
void MCPWM_IRQHandler (void);
void QEI_IRQHandler (void);

#endif /* __PCF_INCLUDED_NATIVE_PORT_ARM32_CM3_LPC_VECTORS_LPC1768_H 		*/

