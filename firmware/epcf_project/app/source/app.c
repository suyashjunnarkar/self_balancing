//
//  main.c
//  LED_Blink
//
//  Created by SuyashJ on 16/06/17.
//  Copyright © 2017 The Wolfkeeper. All rights reserved.
//

/**
 *  \file       app.c
 *  \brief      Source file for the application program
 *
 */

#include "pcf.h"
#include "appConfig.h"
#include "../pcf/include/private/arch/arm/cm3/nxp/lpc1768/lpc1768_regmap.h"

int main()
{
	int8_t status=0;
	
	status = appInit();
	if(status != 0)
	{
		while(1);
	}
	
	PINCON_TypeDef PINSELECT;
	GPIO_TypeDef LED;
	PINSELECT.PINSEL1=0x00000001;
	PINSELECT.PINMODE1=0xfffffffe;
	LED.FIODIR=0xfffffffe;
	LED.FIOSET=0xfffffffe;
	PINSELECT.PINSEL1-=1;
	PINSELECT.PINMODE1+=1;
	LED.FIODIR+=1;
	LED.FIOSET+=1;
	
	
	return 0;
}
