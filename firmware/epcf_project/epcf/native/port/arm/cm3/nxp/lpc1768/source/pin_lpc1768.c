#include "pcf.h"

#define __EPCF_PIN_LPC1768_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_NATIVE_PATH/	\
		,port/PCF_ARCH_NAME/PCF_ARCH_VARIANT/PCF_ARCH_DEVICE_VENDOR/,PCF_ARCH_DEVICE/include/,pin_lpc1768.h)
#include __EPCF_PIN_LPC1768_INCLUDE
#undef __EPCF_PIN_LPC1768_INCLUDE

#define __EPCF_GPIO_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_PATH/	\
		,peripheral/include/,gpio/,gpio.h)
#include __EPCF_GPIO_INCLUDE
#undef __EPCF_GPIO_INCLUDE

/** Port-wise offsets to add with base addresses for port read/write operations.		*/
#define _P_NATIVE_PORT_OFFSET			0x20
/*
#define _P_NATIVE_PORT_0				0x00
#define _P_NATIVE_PORT_1				(_P_NATIVE_PORT_0 + _P_NATIVE_PORT_OFFSET)
#define _P_NATIVE_PORT_2				(_P_NATIVE_PORT_1 + _P_NATIVE_PORT_OFFSET)
#define _P_NATIVE_PORT_3				(_P_NATIVE_PORT_2 + _P_NATIVE_PORT_OFFSET)
#define _P_NATIVE_PORT_4				(_P_NATIVE_PORT_3 + _P_NATIVE_PORT_OFFSET)
*/
#define _P_NATIVE_PORT_0				(0 * _P_NATIVE_PORT_OFFSET)
#define _P_NATIVE_PORT_1				(1 * _P_NATIVE_PORT_OFFSET)
#define _P_NATIVE_PORT_2				(2 * _P_NATIVE_PORT_OFFSET)
#define _P_NATIVE_PORT_3				(3 * _P_NATIVE_PORT_OFFSET)
#define _P_NATIVE_PORT_4				(4 * _P_NATIVE_PORT_OFFSET)

static int8_t _epcfGpioFunctionSelect(uint32_t port, uint32_t pins, uint8_t altFunction);
static int8_t _epcfGpioModeSelect(uint32_t port, uint32_t pins, EnEPCFGpioPinMode_t mode);
static int8_t _epcfGpioOpenDrain(uint32_t port, uint32_t pin, EnEPCFGpioOpenDrain_t openDrain);
static int8_t _epcfGpioSetDirection(uint32_t port, uint32_t pins, EnEPCFGpioDirection_t direction);

static const uint8_t _port_Array[5] = {
	_P_NATIVE_PORT_0,
	_P_NATIVE_PORT_1,
	_P_NATIVE_PORT_2,
	_P_NATIVE_PORT_3,
	_P_NATIVE_PORT_4
};
static const uint32_t _pin_Array[] =
{
	0x00000001,
	0x00000002,
	0x00000004,
	0x00000008,
	0x00000010,
	0x00000020,
	0x00000040,
	0x00000080,
	0x00000100,
	0x00000200,
	0x00000400,
	0x00000800,
	0x00001000,
	0x00002000,
	0x00004000,
	0x00008000,
	0x00010000,
	0x00020000,
	0x00040000,
	0x00080000,
	0x00100000,
	0x00200000,
	0x00400000,
	0x00800000,
	0x01000000,
	0x02000000,
	0x04000000,
	0x08000000,
	0x10000000,
	0x20000000,
	0x40000000,
	0x80000000,
};

//return values:
//0 : success
//-1: error
int8_t epcfPinInit(EPCFPinCfg_t *pConfig)
{
	int8_t status;

	//if((pConfig->portPin.port / PCF_NATIVE_PORT_OFFSET) >= GPIO_MAX_PORT)
	if( (pConfig->portPin.port) >= EPCF_LPC1768_MAX_PORT)
		return -1;

	status = _epcfGpioSetDirection(_port_Array[pConfig->portPin.port], _pin_Array[pConfig->portPin.pin], pConfig->direction);
	status = _epcfGpioFunctionSelect(_port_Array[pConfig->portPin.port], _pin_Array[pConfig->portPin.pin], pConfig->altFunction);
	status = _epcfGpioModeSelect(_port_Array[pConfig->portPin.port], _pin_Array[pConfig->portPin.pin], pConfig->mode);
	status = _epcfGpioOpenDrain(_port_Array[pConfig->portPin.port], _pin_Array[pConfig->portPin.pin], pConfig->openDrain);

	return status;
}

static int8_t _epcfGpioFunctionSelect(uint32_t port, uint32_t pin, uint8_t altFunction)
{
	uint16_t pinIndex;

	altFunction &= 0x03;

	switch(port)
	{
		case _P_NATIVE_PORT_0:
			for(pinIndex = 0; pinIndex < 16; pinIndex++)
			{
				if( (pin & (1 << pinIndex)) == (uint32_t)(1 << pinIndex) )
				{
					PERIPH_PINCON->PINSEL0 &= ~(3 << (pinIndex*2));
					PERIPH_PINCON->PINSEL0 |= (altFunction << (pinIndex*2));
				}
			}

			for(pinIndex = 16; pinIndex < 32; pinIndex++)
			{
				if( (pin & (1 << pinIndex)) == (uint32_t)(1 << pinIndex) )
				{
					PERIPH_PINCON->PINSEL1 &= ~(3 << ((pinIndex*2)-32));
					PERIPH_PINCON->PINSEL1 |= (altFunction << ((pinIndex*2)-32));
				}
			}
			break;

		case _P_NATIVE_PORT_1:
			for(pinIndex = 0; pinIndex < 16; pinIndex++)
			{
				if( (pin & (1 << pinIndex)) == (uint32_t)(1 << pinIndex) )
				{
					PERIPH_PINCON->PINSEL2 &= ~(3 << (pinIndex*2));
					PERIPH_PINCON->PINSEL2 |= (altFunction << (pinIndex*2));
				}
			}

			for(pinIndex = 16; pinIndex < 32; pinIndex++)
			{
				if( (pin & (1 << pinIndex)) == (uint32_t)(1 << pinIndex) )
				{
					PERIPH_PINCON->PINSEL3 &= ~(3 << ((pinIndex*2)-32));
					PERIPH_PINCON->PINSEL3 |= (altFunction << ((pinIndex*2)-32));
				}
			}
			break;

		case _P_NATIVE_PORT_2:
			for(pinIndex = 0; pinIndex < 16; pinIndex++)
			{
				if( (pin & (1 << pinIndex)) == (uint32_t)(1 << pinIndex) )
				{
					PERIPH_PINCON->PINSEL4 &= ~(3 << (pinIndex*2));
					PERIPH_PINCON->PINSEL4 |= (altFunction << (pinIndex*2));
				}
			}

			for(pinIndex = 16; pinIndex < 32; pinIndex++)
			{
				if( (pin & (1 << pinIndex)) == (uint32_t)(1 << pinIndex) )
				{
					PERIPH_PINCON->PINSEL5 &= ~(3 << ((pinIndex*2)-32));
					PERIPH_PINCON->PINSEL5 |= (altFunction << ((pinIndex*2)-32));
				}
			}
			break;

		case _P_NATIVE_PORT_3:
			for(pinIndex = 0; pinIndex < 16; pinIndex++)
			{
				if( (pin & (1 << pinIndex)) == (uint32_t)(1 << pinIndex) )
				{
					PERIPH_PINCON->PINSEL6 &= ~(3 << (pinIndex*2));
					PERIPH_PINCON->PINSEL6 |= (altFunction << (pinIndex*2));
				}
			}

			for(pinIndex = 16; pinIndex < 32; pinIndex++)
			{
				if( (pin & (1 << pinIndex)) == (uint32_t)(1 << pinIndex) )
				{
					PERIPH_PINCON->PINSEL7 &= ~(3 << ((pinIndex*2)-32));
					PERIPH_PINCON->PINSEL7 |= (altFunction << ((pinIndex*2)-32));
				}
			}
			break;

		case _P_NATIVE_PORT_4:
			for(pinIndex = 0; pinIndex < 16; pinIndex++)
			{
				if( (pin & (1 << pinIndex)) == (uint32_t)(1 << pinIndex) )
				{
					PERIPH_PINCON->PINSEL8 &= ~(3 << (pinIndex*2));
					PERIPH_PINCON->PINSEL8 |= (altFunction << (pinIndex*2));
				}
			}

			for(pinIndex = 16; pinIndex < 32; pinIndex++)
			{
				if( (pin & (1 << pinIndex)) == (uint32_t)(1 << pinIndex) )
				{
					PERIPH_PINCON->PINSEL9 &= ~(3 << ((pinIndex*2)-32));
					PERIPH_PINCON->PINSEL9 |= (altFunction << ((pinIndex*2)-32));
				}
			}
			break;

		default:
			return -1;
	}
	return 0;
}

//return values:
//0 : success
//-1: Invalid port
static int8_t _epcfGpioModeSelect(uint32_t port, uint32_t pin, EnEPCFGpioPinMode_t mode)
{
	uint16_t pinIndex;

	mode &= 0x03;

	switch(port)
	{
		case _P_NATIVE_PORT_0:
			for(pinIndex = 0; pinIndex < 16; pinIndex++)
			{
				if( (pin & (1 << pinIndex)) == (uint32_t)(1 << pinIndex) )
				{
					PERIPH_PINCON->PINMODE0 &= ~(3 << (pinIndex*2));
					PERIPH_PINCON->PINMODE0 |= (mode << (pinIndex*2));
				}
			}

			for(pinIndex = 16; pinIndex < 32; pinIndex++)
			{
				if( (pin & (1 << pinIndex)) == (uint32_t)(1 << pinIndex) )
				{
					PERIPH_PINCON->PINMODE1 &= ~(3 << ((pinIndex*2)-32));
					PERIPH_PINCON->PINMODE1 |= (mode << ((pinIndex*2)-32));
				}
			}
			break;

		case _P_NATIVE_PORT_1:
			for(pinIndex = 0; pinIndex < 16; pinIndex++)
			{
				if( (pin & (1 << pinIndex)) == (uint32_t)(1 << pinIndex) )
				{
					PERIPH_PINCON->PINMODE2 &= ~(3 << (pinIndex*2));
					PERIPH_PINCON->PINMODE2 |= (mode << (pinIndex*2));
				}
			}

			for(pinIndex = 16; pinIndex < 32; pinIndex++)
			{
				if( (pin & (1 << pinIndex)) == (uint32_t)(1 << pinIndex) )
				{
					PERIPH_PINCON->PINMODE3 &= ~(3 << ((pinIndex*2)-32));
					PERIPH_PINCON->PINMODE3 |= (mode << ((pinIndex*2)-32));
				}
			}
			break;

		case _P_NATIVE_PORT_2:
			for(pinIndex = 0; pinIndex < 16; pinIndex++)
			{
				if( (pin & (1 << pinIndex)) == (uint32_t)(1 << pinIndex) )
				{
					PERIPH_PINCON->PINMODE4 &= ~(3 << (pinIndex*2));
					PERIPH_PINCON->PINMODE4 |= (mode << (pinIndex*2));
				}
			}

			for(pinIndex = 16; pinIndex < 32; pinIndex++)
			{
				if( (pin & (1 << pinIndex)) == (uint32_t)(1 << pinIndex) )
				{
					PERIPH_PINCON->PINMODE5 &= ~(3 << ((pinIndex*2)-32));
					PERIPH_PINCON->PINMODE5 |= (mode << ((pinIndex*2)-32));
				}
			}
			break;

		case _P_NATIVE_PORT_3:
			for(pinIndex = 0; pinIndex < 16; pinIndex++)
			{
				if( (pin & (1 << pinIndex)) == (uint32_t)(1 << pinIndex) )
				{
					PERIPH_PINCON->PINMODE6 &= ~(3 << (pinIndex*2));
					PERIPH_PINCON->PINMODE6 |= (mode << (pinIndex*2));
				}
			}

			for(pinIndex = 16; pinIndex < 32; pinIndex++)
			{
				if( (pin & (1 << pinIndex)) == (uint32_t)(1 << pinIndex) )
				{
					PERIPH_PINCON->PINMODE7 &= ~(3 << ((pinIndex*2)-32));
					PERIPH_PINCON->PINMODE7 |= (mode << ((pinIndex*2)-32));
				}
			}
			break;

		case _P_NATIVE_PORT_4:
			for(pinIndex = 0; pinIndex < 16; pinIndex++)
			{
				if( (pin & (1 << pinIndex)) == (uint32_t)(1 << pinIndex) )
				{
					PERIPH_PINCON->PINMODE8 &= ~(3 << (pinIndex*2));
					PERIPH_PINCON->PINMODE8 |= (mode << (pinIndex*2));
				}
			}

			for(pinIndex = 16; pinIndex < 32; pinIndex++)
			{
				if( (pin & (1 << pinIndex)) == (uint32_t)(1 << pinIndex) )
				{
					PERIPH_PINCON->PINMODE9 &= ~(3 << ((pinIndex*2)-32));
					PERIPH_PINCON->PINMODE9 |= (mode << ((pinIndex*2)-32));
				}
			}
			break;

		default:
			return -1;
	}
	return 0;
}

//return values:
//0 : success
//-1: Invalid port
static int8_t _epcfGpioOpenDrain(uint32_t port, uint32_t pin, EnEPCFGpioOpenDrain_t openDrain)
{
	switch(port)
	{
		case _P_NATIVE_PORT_0:
			if(openDrain)
			{
				PERIPH_PINCON->PINMODE_OD0 |= pin;
			}
			else
			{
				PERIPH_PINCON->PINMODE_OD0 &= ~pin;
			}
			break;

		case _P_NATIVE_PORT_1:
			if(openDrain)
			{
				PERIPH_PINCON->PINMODE_OD1 |= pin;
			}
			else
			{
				PERIPH_PINCON->PINMODE_OD1 &= ~pin;
			}
			break;

		case _P_NATIVE_PORT_2:
			if(openDrain)
			{
				PERIPH_PINCON->PINMODE_OD2 |= pin;
			}
			else
			{
				PERIPH_PINCON->PINMODE_OD2 &= ~pin;
			}
			break;

		case _P_NATIVE_PORT_3:
			if(openDrain)
			{
				PERIPH_PINCON->PINMODE_OD3 |= pin;
			}
			else
			{
				PERIPH_PINCON->PINMODE_OD3 &= ~pin;
			}
			break;

		case _P_NATIVE_PORT_4:
			if(openDrain)
			{
				PERIPH_PINCON->PINMODE_OD4 |= pin;
			}
			else
			{
				PERIPH_PINCON->PINMODE_OD4 &= ~pin;
			}
			break;

		default:
			return -1;
	}

	return 0;
}

//input
//port -> Value from _port_Array[];
// pin -> Value from _pin_Array[];
static int8_t _epcfGpioSetDirection(uint32_t port, uint32_t pin, EnEPCFGpioDirection_t direction)
{
	if(direction == enEPCFGpioDirection_Output)	//output
	{
		*((volatile uint32_t*)(GPIO_IODIR_BASE + port)) |= pin;
	}
	else
	{
		*((volatile uint32_t*)(GPIO_IODIR_BASE + port)) &= ~pin;
	}

	return 0;
}
