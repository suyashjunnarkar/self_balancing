/**
 *  \file       app_config.c
 *  \brief      Configuration settings
 *
 */

#include "pcf.h"
#include "appConfig.h"

EPCFSysClkDevice_t *myClock;

EPCFSysClkCfg_t myClockCfg =
{
    100000000,
    12000000,
    enEPCFPllClkSrcMainOSC
};

int8_t appInit(void)
{
    myClock = epcfCreateSysClk(&myClockCfg);
    if(myClock == NULL)
    {
        APP_DEBUG("Error in creating SysClk!");
        return -1;
    }
    
    return 0;
}
