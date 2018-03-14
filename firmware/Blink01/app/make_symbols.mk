PCF_DIR                 = ../pcf
EPCF_DIR                = ../epcf
APP_PATH                = ./source

PERIPHERAL_SRC          = $(EPCF_DIR)/peripheral/source
UART                    = $(PERIPHERAL_SRC)/uart
TIMER                   = $(PERIPHERAL_SRC)/timer
GPIO                    = $(PERIPHERAL_SRC)/gpio
EXTINT			        = $(PERIPHERAL_SRC)/extInt
ADC                     = $(PERIPHERAL_SRC)/adc
I2C 			        = $(PERIPHERAL_SRC)/i2c
CAN 			        = $(PERIPHERAL_SRC)/can
SYSCLK                  = $(PERIPHERAL_SRC)/sysClk
WDT				        = $(PERIPHERAL_SRC)/wdt
PWM				        = $(PERIPHERAL_SRC)/pwm
SPI				        = $(PERIPHERAL_SRC)/spi
UTILS                   = $(EPCF_DIR)/utils/source

LPC1768_SRC             = $(EPCF_DIR)/native/port/arm/cm3/nxp/lpc1768/source
UART_LPC1768            = $(LPC1768_SRC)/uart
TIMER_LPC1768           = $(LPC1768_SRC)/timer
GPIO_LPC1768            = $(LPC1768_SRC)/gpio
EXTINT_LPC1768 	        = $(LPC1768_SRC)/extInt
PWM_LPC1768             = $(LPC1768_SRC)/pwm
I2C_LPC1768 	        = $(LPC1768_SRC)/i2c
CAN_LPC1768 	        = $(LPC1768_SRC)/can
ADC_LPC1768             = $(LPC1768_SRC)/adc
SYSCLK_LPC1768          = $(LPC1768_SRC)/sysClk
WDT_LPC1768 	        = $(LPC1768_SRC)/wdt
SPI_LPC1768 	        = $(LPC1768_SRC)/spi

X86                     = $(EPCF_DIR)/native/port/x86
UART_X86_WINDOWS        = $(X86)/uart/pcf_windows
UART_X86_LINUX          = $(X86)/uart/pcf_linux

EXTENDED                = $(EPCF_DIR)/extended
ADAPTER                 = $(EXTENDED)/adapter
PACKET                  = $(EXTENDED)/packet

EXTENDED_CONTROLLER     = $(EXTENDED)/controller
GPIO_CONTROLLER         = $(EXTENDED_CONTROLLER)/gpio
UART_CONTROLLER         = $(EXTENDED_CONTROLLER)/uart
TIMER_CONTROLLER        = $(EXTENDED_CONTROLLER)/timer

