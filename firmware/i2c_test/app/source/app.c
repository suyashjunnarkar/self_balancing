/**
 *  \file       app.c
 *  \brief      Source file for the application program
 *
 */
//#define _PCF_INTERNAL_DEBUG

#include "pcf.h"
#include "appConfig.h"

extern EPCFGpioDevice_t *myGpio;
extern EPCFGpioDevice_t *LED;
extern EPCFGpioDevice_t *myLED;
extern EPCFGpioDevice_t *Switch;
extern EPCFUartDevice_t *myUART;
extern EPCFI2cDevice_t *i2cDevice; 

EPCFUartCfg_t uart_Config; 

int slaveAddress = 0;	/*ENTER SLAVE ADDRESS HERE*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

int main()
{
    int8_t status1=0;
	int8_t status2=0;
	int8_t Switch_Status=0;
    status1 = appInit();
    APP_DEBUG("ZHALO MI CHALU\n");
    if(status1 == 0)
    {
        APP_DEBUG("App configuration success\n");
    }
    else
    {
        APP_DEBUG("Error in App configuration!\n");
        while(1);
    }

    
    for(int i=0;i <3; i++) {
    	for (uint32_t i=0; i<5000000; i++);
    	epcf_gpio_set(LED);	
    	for (uint32_t i=0; i<5000000; i++);
    	epcf_gpio_clear(LED);	
    }
    
    int8_t status_UART = 0;

    while(1)
    {	

		// for (uint32_t i=0; i<5000000; i++);
		// epcf_gpio_set(myLED);	
		// epcf_uart_write(myUART, (uint8_t*)dataPointer, 4 ,timeOut);
		// for (uint32_t i=0; i<5000000; i++);
		// epcf_gpio_clear(myLED);	
	
	    char p[] = "Hello World \n";
		status_UART = serialPrint(p);
		

		if(status_UART == EPCF_STATUS_BUSY)
		{
			int k = 0;
			while(k<3) {
				for (uint32_t i=0; i<5000000; i++);
				epcf_gpio_set(LED);	
				for (uint32_t i=0; i<5000000; i++);
				epcf_gpio_clear(LED);		
				k++;
			}
			
		}
		else if (status_UART == EPCF_STATUS_NO_MEMORY)
		{
			int k = 0;
			while(k<3) {
				for (uint32_t i=0; i<5000000; i++);
				epcf_gpio_set(myGpio);	
				for (uint32_t i=0; i<5000000; i++);
				epcf_gpio_clear(myGpio);		
				k++;
			}
			APP_DEBUG("No Memory\n");
			while(1);
		}
		else if (status_UART == EPCF_STATUS_SUCCESS)
		{
			int k = 0;
			while(k<3) {
				for (uint32_t i=0; i<5000000; i++);
				epcf_gpio_set(myLED);	
				for (uint32_t i=0; i<5000000; i++);
				epcf_gpio_clear(myLED);		
				k++;
			}
		}




		// EPCFTime_t I2CTimeOut = {5, enEPCFTimeUnit_s,};

		// //I2C write
		// char d[] = "x";
		// int status_I2C = epcf_i2c_write(i2cDevice,enEPCFBoolean_True, slaveAddress, &d, sizeof(d), enEPCFBoolean_True, I2CTimeOut);
		// //Check 2nd last parameter again.

		// if(status_I2C == EPCF_STATUS_BUSY)
		// {
		// 	int k = 0;
		// 	while(k<3) {
		// 		for (uint32_t i=0; i<5000000; i++);
		// 		epcf_gpio_set(LED);	
		// 		for (uint32_t i=0; i<5000000; i++);
		// 		epcf_gpio_clear(LED);		
		// 		k++;
		// 	}
			
		// }
		// else if (status_I2C == EPCF_STATUS_NO_MEMORY)
		// {
		// 	int k = 0;
		// 	while(k<3) {
		// 		for (uint32_t i=0; i<5000000; i++);
		// 		epcf_gpio_set(myGpio);	
		// 		for (uint32_t i=0; i<5000000; i++);
		// 		epcf_gpio_clear(myGpio);		
		// 		k++;
		// 	}
		// 	APP_DEBUG("No Memory\n");
		// 	while(1);
		// }
		// else if (status_I2C == EPCF_STATUS_SUCCESS)
		// {
		// 	int k = 0;
		// 	while(k<3) {
		// 		for (uint32_t i=0; i<5000000; i++);
		// 		epcf_gpio_set(myLED);	
		// 		for (uint32_t i=0; i<5000000; i++);
		// 		epcf_gpio_clear(myLED);		
		// 		k++;
		// 	}
		// }

  //       Switch_Status = epcf_gpio_read(Switch);
		
  //       if(Switch_Status == 1)
  //       {
		// 	status1 = epcf_gpio_set(LED);
		// 	status2 = epcf_gpio_clear(myGpio);
		// 	if((status1 ==0) || (status2==0))
		// 	{
		// 		APP_DEBUG("LED On\n");
		// 	}
		// 	else
		// 	{
		// 		APP_DEBUG("Error\n");
		// 	}
		// }
	 // if(Switch_Status == 0)
	 // {
		// 	status1 = epcf_gpio_clear(LED);
		//  	status2 = epcf_gpio_set(myGpio);
		// 	if((status1 ==0) || (status2==0))
		// 	{
		// 		APP_DEBUG("LED Off\n");
		// 	}
		// 	else
		// 	{
		// 		APP_DEBUG("Error\n");
		//  	}
		// }
	}

	
    return 0;
}

