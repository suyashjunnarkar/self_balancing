/**
 *  \file       uart_x86_32.c
 *  \brief      Source file if uart channel for windows 32 bit platform and x86(32 bit) architecture
 *
 *  This file can be modified and need some editing like proper variable names, return values etc.
 *
 */

#include "epcf.h"
#include <stdlib.h>
#include <sys/ioctl.h> //ioctl() call defenitions

#define __EPCF_PRIVATE_UART_H_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_PATH/,peripheral/,uart/,uart_hidden.h)
#include  __EPCF_PRIVATE_UART_H_INCLUDE
#undef __EPCF_PRIVATE_UART_H_INCLUDE

#define __EPCF_UTILS_UART_H_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_PATH/,utils/,include/,epcf_string.h)
#include  __EPCF_UTILS_UART_H_INCLUDE
#undef __EPCF_UTILS_UART_H_INCLUDE


#define DEBUG_PRINT(...)        printf(__VA_ARGS__)

struct termios TtyN;    // For TTY New settings
static int32_t Fd;    // File Descriptor
static uint32_t Txcnt=0, Rxcnt=0;
static char Rxbuf[256]={0}, Txbuf[256]={0};  // Check weather this is needed or not
static uint32_t uartDeviceCount = UART_MAX_CHANNEL;

//look tables
static uint32_t baudRateMap[7] = {B2400,B4800,B9600,B19200,B38400,B57600,B115200};
static uint32_t databitMap[4] = {CS5,CS6,CS7,CS8};

//static uint32_t parityBitsMap[2] = {PARENB | PARODD,PARENB};
//static uint8_t stopBitsMap[2] = {~CSTOPB, CSTOPB};

//look tables Accessing
#define DATABITS_MAP(X)    (databitMap[X-5])
//#define STOPBITS_MAP(x)    (x==1 && x==2) ?( (x==1) ? (TtyN.c_cflag &= ~CSTOPB): (TtyN.c_cflag |= CSTOPB) ) : (0)
//#define PARITYBITS_MAP(x)  (x <0 && x >3) ?( (x==0) ? (TtyN.c_cflag &= ~PARENB): (TtyN.c_cflag |= parityBitsMap[x]) ): (0)

static int8_t _epcfNativeUartOpen(EPCFUartCfg_t *pConfig);
static int8_t _epcfNativeUartWriteByte(EPCFUartDevice_t* pUartDevice, uint8_t data, EPCFTime_t timeout);
int8_t controlModemLines(bool dtr, bool rts);


int8_t epcfNativeUartInit(EPCFUartDevice_t* pUartDevice, EPCFUartCfg_t *pConfig)
{
    int8_t status = 0;
	status = _epcfNativeUartOpen(pConfig);
	if(status != 0)
		return -1;

	uartDeviceCount--;
	return 0;
}


//return values
// 1 : success with Warning: Could not Set tc Attributes
// 0 : success
//-1 : unable to Initilized
//-4 : invalid parity agrs
//-5 : invalid stopbits agrs
static int8_t _epcfNativeUartOpen(EPCFUartCfg_t *pConfig)
{
    struct termios ttyo;        // For Old TTY settings
    uint8_t portname[20]={0};
    pcfMemSet(portname, 0, sizeof(portname));
    pcfStrCopy(portname, (const uint8_t*)"/dev/tty");

    if (((EPCFUartLinuxCfg_t*)(pConfig->hardwareCfg))->isUSBdevice == enEPCFBoolean_True)
    {
    	pcfStrCat(portname, "USB");
    }

    sprintf(&portname[pcfStrLen(portname)], "%d", (uint32_t)pConfig->uartId);
    DEBUG_PRINT("Portname = %s\n", portname);
    pcfMemSet (&TtyN, 0, sizeof(TtyN));

    /* Setting other Port Stuff */
    /*
        CS8    : 8n1 (8bit,no parity,1 stopbit)
        CLOCAL : local connection, no modem contol
        CREAD  : enable receiving characters
    */

    TtyN.c_cflag    &= ~CRTSCTS;    // Hardware flow control Disabled
    TtyN.c_cflag    &= ~CSIZE;      // Character Size mask
    switch(pConfig->parity)
    {
        default:
        case 0:
            TtyN.c_cflag    &= ~PARENB;                     // Disable Parity
            break;
        case 1:
            TtyN.c_cflag    |= PARENB | PARODD;
            break;
        case 2:
            TtyN.c_cflag    |= PARENB;
            break;
    }
    switch(pConfig->stopBits)
    {
        default:
        case 1:
            TtyN.c_cflag    &= ~CSTOPB;
            break;
        case 2:
            TtyN.c_cflag    |= CSTOPB;
            break;
    }
    TtyN.c_cflag    |= CREAD | CLOCAL;
    TtyN.c_cflag    |= DATABITS_MAP(pConfig->dataBits);

    TtyN.c_cc[VMIN]   =  0;     // read doesn't block
    TtyN.c_cc[VTIME]  =  1;     // 0.5 seconds read timeou

    cfsetospeed (&TtyN, (speed_t)(baudRateMap[pConfig->baudrate]));    // Set Output Speed (Baudrate)
    cfsetispeed (&TtyN, (speed_t)(baudRateMap[pConfig->baudrate]));    // Set Input Speed (Baudrate)

    TtyN.c_iflag |= IGNPAR;    // Ignore Parity Errors
    TtyN.c_oflag = 0;          //
    TtyN.c_lflag = 0;          // Non-canonical mode No Echo. Most Important.

    Fd = open(portname, O_RDWR);        //( portname, O_RDWR| O_NONBLOCK | O_NDELAY );
    DEBUG_PRINT("Initialized with File Descriptor %d",(int32_t)Fd);
    if ((int32_t) Fd < 0 )
    {
        DEBUG_PRINT("\n !!!!! ERROR: Unable to Initialize the Port %s\n",portname);
        return EPCF_STATUS_ERROR;
    }

    tcgetattr(Fd, &ttyo);     // Copy Old Settings.
    tcflush(Fd, TCIFLUSH);    // Flush Input before setting the new attribute values
    if (tcsetattr ( Fd, TCSANOW, &TtyN) != 0)
    {
        DEBUG_PRINT("!!!!! Warning: Could not Set tc Attributes \n");
        return EPCF_STATUS_ERROR; // 1
    }

    //ioctl(Fd,TIOCMBIC,TIOCM_DTR);//Set DTR pin
    controlModemLines(0,0);
    return EPCF_STATUS_SUCCESS;
}

int8_t controlModemLines(bool DTR, bool RTS)
{
	int32_t status=0;
	ioctl(Fd, TIOCMGET, &status) ;
	if ( DTR == 1 )      /* set the DTR line */
		status |= TIOCM_DTR;    //ioctl(Fd,TIOCMBIS,TIOCM_RTS);//Set RTS pin
	else
		status &= ~TIOCM_DTR;   //ioctl(Fd,TIOCMBIC,TIOCM_RTS);//Clear RTS pin
	if (RTS == 1 )      /* set the RTS line */
		status |= TIOCM_RTS;
	else
		status &= ~TIOCM_RTS;

	ioctl(Fd, TIOCMSET, &status);
	usleep(10000);                  // 10 MilliSeconds
	return EPCF_STATUS_SUCCESS;
}
//return valuesError in Initializing LED!
// 1 : success with Warning: Could not Set tc Attributes
// 0 : success
//-1 : unable to Initilized
//-4 : invalid parity agrs
//-5 : invalid stopbits agrs
int8_t epcfNativeUartClose(EPCFUartDevice_t* pUartDevice)
{
    if(epcfNativeUartTxBufferFlush(pUartDevice) == -1)
    {
        return EPCF_STATUS_ERROR;
    }
    
    if(epcfNativeUartRxBufferFlush(pUartDevice) == -1)
    {
        return EPCF_STATUS_ERROR;
    }

    if(close(Fd))
    {
        DEBUG_PRINT("!!!!! Error: Could not Purge Comm Port \n");
        return EPCF_STATUS_ERROR;
    }
    return EPCF_STATUS_SUCCESS;
}

//return values
// 0 : success
//-1 : error
//-2 : 
int32_t epcfNativeUartWrite(EPCFUartDevice_t* pUartDevice, const uint8_t* pdata, uint32_t size, EPCFTime_t timeout)
{
    uint32_t wrbytes=0;
    
    tcflush(Fd, TCOFLUSH);
    if ( tcsetattr (Fd, TCSANOW, &TtyN) != 0)
    {
        DEBUG_PRINT("!!!!! Warning: Could not Set tc Attributes \n");
    }

    wrbytes  = write(Fd, pdata, size);
    if(wrbytes == size)
    {
        Txcnt = wrbytes;
        return wrbytes;
    }
    else 
    {
        return EPCF_STATUS_ERROR;
    }
}

int32_t epcfNativeUartWriteBlocking(EPCFUartDevice_t* pUartDevice, const uint8_t* pdata, uint32_t size, EPCFTime_t timeout)
{
	return EPCF_STATUS_NOT_SUPPORTED;
}

//return values
// 0 : success
int32_t epcfNativeUartWriteString(EPCFUartDevice_t* pUartDevice, const uint8_t* pdata, EPCFTime_t timeout)
{
    Txcnt= 0;
    while(*pdata != '\0')
    {
        _epcfNativeUartWriteByte(pUartDevice, *pdata++, timeout);
        Txcnt++;
    }
    return EPCF_STATUS_SUCCESS;
}

uint32_t epcfNativeUartGetDeviceCount()
{
    return uartDeviceCount;
}

static int8_t _epcfNativeUartWriteByte(EPCFUartDevice_t* pUartDevice, uint8_t data, EPCFTime_t timeout)
{
    return epcfNativeUartWrite(pUartDevice, &data, 1, timeout);
}

int32_t epcfNativeUartRead(EPCFUartDevice_t* pUartDevice, uint8_t* uartReadData, uint32_t maxsize, EPCFTime_t timeout)
{
    int32_t byteread=0;
    uint32_t bytetoread=maxsize, rdbytes;
    uint16_t retries=10,attempt=0;

    pcfMemSet(uartReadData, 0, maxsize);
    rdbytes = 0;

    while((attempt<retries) && (rdbytes < maxsize))         // 10 Attempts are made to collect all the data
    {
        byteread = read(Fd, uartReadData, bytetoread);
        if(byteread == 0)
        {
            attempt++;              // Read Failed : 0 data bytes are received
        }
        else
        {
            uartReadData += byteread;
            rdbytes += byteread;
            bytetoread -= byteread;
        }
    }
    
    Rxcnt = rdbytes;
    tcflush( Fd, TCIFLUSH );
    if(rdbytes < maxsize)
    {
        return EPCF_STATUS_ERROR;
    }
    return rdbytes;
}

int8_t epcfNativeUartTxBufferFlush(EPCFUartDevice_t* pUartDevice)
{
    tcflush(Fd, TCOFLUSH);
    if ( tcsetattr ( Fd, TCSANOW, &TtyN) != 0)
    {
        DEBUG_PRINT("!!!!! Warning: Could not Set tc Attributes \n");
        return EPCF_STATUS_ERROR;
    }
    //pcfMemSet(Txbuf, 0, sizeof(Txbuf));
    Txcnt = 0;
    return EPCF_STATUS_SUCCESS;
}

int8_t epcfNativeUartRxBufferFlush(EPCFUartDevice_t* pUartDevice)
{
    tcflush( Fd, TCIFLUSH );
    if ( tcsetattr ( Fd, TCSANOW, &TtyN) != 0)
    {
        DEBUG_PRINT("!!!!! Warning: Could not Set tc Attributes \n");
        return EPCF_STATUS_ERROR;
    }
    //pcfMemSet(Rxbuf, 0, sizeof(Rxbuf));
    Rxcnt = 0;
    return EPCF_STATUS_SUCCESS;
}

int32_t epcfNativeUartGetTxBufferCount(EPCFUartDevice_t* pUartDevice)
{
    return EPCF_STATUS_NOT_SUPPORTED;
}

int32_t epcfNativeUartGetRxBufferCount(EPCFUartDevice_t* pUartDevice)
{
    return EPCF_STATUS_NOT_SUPPORTED;
}
