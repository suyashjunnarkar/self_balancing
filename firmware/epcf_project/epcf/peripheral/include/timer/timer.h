/**
 * \file  timer.h
 * \brief This file is used to configure a Timer device
 */

#ifndef __EPCF_PERIPHERAL_INCLUDE_TIMER_TIMER_H
#define __EPCF_PERIPHERAL_INCLUDE_TIMER_TIMER_H

/** \brief	Timer device    */
typedef struct EPCFTimerDevice EPCFTimerDevice_t;

/** \brief  Enumeration for Channel number  */
typedef enum
{
	enEPCFTimerChannel_0 = 0,	/**< Channel number 0		*/
	enEPCFTimerChannel_1,		/**< Channel number 1		*/
	enEPCFTimerChannel_2,		/**< Channel number 2		*/
	enEPCFTimerChannel_3,		/**< Channel number 3		*/
	enEPCFTimerChannel_4,		/**< Channel number 4		*/
	enEPCFTimerChannel_5,		/**< Channel number 5		*/
	enEPCFTimerChannel_6,		/**< Channel number 6		*/
	enEPCFTimerChannel_7,		/**< Channel number 7		*/
	enEPCFTimerChannel_8,		/**< Channel number 8		*/
	enEPCFTimerChannel_9,		/**< Channel number 9		*/
	enEPCFTimerChannel_10,		/**< Channel number 10		*/
	enEPCFTimerChannel_11,		/**< Channel number 11		*/
	enEPCFTimerChannel_12,		/**< Channel number 12		*/
	enEPCFTimerChannel_13,		/**< Channel number 13		*/
	enEPCFTimerChannel_14,		/**< Channel number 14		*/
	enEPCFTimerChannel_15,		/**< Channel number 15		*/
	enEPCFTimerChannel_Max		/**< Special value for boundary checking	*/
}EnEPCFTimerChannel_t;

/** \brief  Enumeration for Timer width  */
typedef enum
{
    enEPCFTimerWidth_8 = 0,		/**< 8-bit timer.Timer count MIN=0x00, MAX=0xFF                                 */
    enEPCFTimerWidth_16,		/**< 16-bit timer.Timer count MIN=0x0000, MAX=0xFFFF                            */
	enEPCFTimerWidth_32,		/**< 32-bit timer.Timer count MIN=0x00000000, MAX=0xFFFFFFFF                    */
	enEPCFTimerWidth_64,		/**< 64-bit timer.Timer count MIN=0x0000000000000000, MAX=0xFFFFFFFFFFFFFFFF    */
    enEPCFTimerWidth_Max		/**< Special value for boundary checking    */
}EnEPCFTimerWidth_t;

/** \brief  Enumeration for Timer mode  */
typedef enum
{
	enEPCFTimerMode_Timer = 0,	/**< Configure Timer in timer mode			*/
	enEPCFTimerMode_Counter,	/**< Configure Timer in counter mode		*/
	enEPCFTimerMode_Max			/**< Special value for boundary checking	*/
}EnEPCFTimerMode_t;

/** \brief Enumeration for compare match action             */
typedef enum
{
    enEPCFTimerCompareAction_None = 0,       /**< Take no action on compare match            */
    enEPCFTimerCompareAction_Reset,          /**< Reset the timer on compare match           */
    enEPCFTimerCompareAction_Stop,           /**< Stop the timer on compare match            */
    enEPCFTimerCompareAction_StopReset,      /**< Reset and stop the timer on compare match  */
    enEPCFTimerCompareAction_Max             /**< Special value for boundary checking        */
}EnEPCFTimerCompareAction_t;

/** \brief Enumeration for pin compare match action             */
typedef enum
{
	enEPCFTimerPinAction_None = 0,			/**< Take no action on compare match      */
	enEPCFTimerPinAction_Clear,				/**< Set pin Low on compare match     	  */
	enEPCFTimerPinAction_Set,				/**< Set pin High on compare match        */
	enEPCFTimerPinAction_toggle,			/**< Toggle pin state compare match       */
	enEPCFTimerPinAction_Max				/**< Special value for boundary checking  */
}EnEPCFTimerPinAction;

/** \brief Enumeration for input pin polarity	*/
typedef enum
{
	enEPCFTimer_None = 0,		/**< Do nothing				*/
	enEPCFTimer_RisingEdge,		/**< Capture input on rising edge of input pin						*/
	enEPCFTimer_FallingEdge,    /**< Capture input on falling edge of input pin						*/
	enEPCFTimer_BothEdge,		/**< Capture input on both rising and falling edge of input pin		*/
	enEPCFTimer_Max,            /**< Special value for boundary checking	*/
}EnEPCFTimerInputPolarity_t;

/** \brief Enumeration for interrupt source	*/
typedef enum
{
	enEPCFTimer_Overflow                = 0,    /**< Interrupt for timer counter overflow			*/
	enEPCFTimerCompareMatchChannel_0,		    /**< Interrupt for compare match channel 0			*/
	enEPCFTimerCompareMatchChannel_1,		    /**< Interrupt for compare match channel 1			*/
	enEPCFTimerCompareMatchChannel_2,		    /**< Interrupt for compare match channel 2			*/
	enEPCFTimerCompareMatchChannel_3,		    /**< Interrupt for compare match channel 3			*/
	enEPCFTimerCompareMatchChannel_4,		    /**< Interrupt for compare match channel 4			*/
	enEPCFTimerCompareMatchChannel_5,		    /**< Interrupt for compare match channel 5			*/
	enEPCFTimerInputCaptureChannel_0,		    /**< Interrupt for input capture channel 0			*/
	enEPCFTimerInputCaptureChannel_1,		    /**< Interrupt for input capture channel 1			*/
	enEPCFTimerInputCaptureChannel_2,		    /**< Interrupt for input capture channel 2			*/
	enEPCFTimerInputCaptureChannel_3,		    /**< Interrupt for input capture channel 3			*/
	enEPCFTimerInputCaptureChannel_4,		    /**< Interrupt for input capture channel 4			*/
	enEPCFTimerInputCaptureChannel_5,		    /**< Interrupt for input capture channel 5			*/
	enEPCFTimerInterruptSource_Max,			    /**< Special value for boundary checking			*/
}EnEPCFTimerInterruptSource_t;

/** \brief Enumeration for current state of timer */
typedef enum
{
    enEPCFTimerState_Stopped = 0,   /**< Timer is stopped, no user callback will get called		 */
    enEPCFTimerState_Running,       /**< Timer is running (operational), user callback(s) will get called at respective period */
    enEPCFTimerState_Max            /**< Special value for boundary checking 		*/
}EnEPCFTimerState_t;

/** \brief Timer configuration structure
	Example to configure timer in timer mode:
	
	EPCFTimerCfg_t timerConfig = 
	{
		0,							// timer id 0
		enEPCFTimerWidth_8,			// 8-bit timer width
		{250,enEPCFTimeUnit_ns},	// resolution set to 0.25 microseconds
		enEPCFTimerTypePeriodic,	// set periodic timer
		enEPCFTimerModeTimer,		// set in timer mode
		enEPCFBooleanTrue,			// enable interrupt
		NULL						// No hardware specific config
	};
*/
typedef struct 
{
	uint8_t 				timerId;			/**< Timer Id. Refer to platform specific header file for appropriate timer id	*/
													 
	EnEPCFTimerWidth_t		timerWidth;     	/**< Specifies the width of the timer			*/
	
    EPCFTime_t				resolution;     	/**< Specifies the resolution for the timer. Resolution defines the smallest time that
													 can be measured by the timer.You can define maximum period of timer by setting appropriate
													 resolution value.
													 Timer period = resolution x (2^timerWidth).
													 For example: Consider an 8-bit timer with resolution = 0.25 microseconds.
																  Then,the maximum period of the timer is equal to 0.25 x 256 = 64 microseconds.
																  To set 0.25 microseconds as the resolution, set time unit to enEPCFTimeUnit_ns
																  and set 250 as the count.
													 Refer to platform specific header file for supported values of resolution.
													 Refer to "../../common/types.h" header file for the definition of \link EPCFTime_t \endlink structure.		*/
	
	EnEPCFTimerMode_t		mode;				/**< Specifies timer mode	*/

    EnEPCFBoolean_t			interruptEnable;	/**< Specifies to enable timer interrupt or not
													 enEPCFBooleanTrue  = To enable timer interrupt
													 enEPCFBooleanFalse = To disable timer interrupt	*/
    
    void*                   hardwareCfg;		/**< Hardware platform specific configuration, Pass NULL for default configuration		*/
}EPCFTimerCfg_t;


/**
 * \brief This function is used to create a timer. Call this function in beginning to initialize the timer.
 *        This function allocates memory for the device using malloc() function call and returns a pointer to the device. Pass this device pointer 
 *        while calling timer functions.
 *
 * \param pTimerConfig Pointer to the timer configuration structure.
 *
 * \return On success, it return the pointer to timer device. 
 *         On error, it returns NULL.
 */
extern EPCFTimerDevice_t* epcf_timer_createNative(EPCFTimerCfg_t* pTimerConfig);

#ifdef	EPCF_SUPPORT_EXTENDED_TIMER

/** \brief  uart controller structure    */
typedef struct EPCFTimerController EPCFTimerController_t;

/**
 *  \brief This function is used to create a timer device in extended mode.
 *  	  	Before calling this function, user should create an adapter for communication between host and extended device.
 *        	For detail explaination, see ../../../../extended/adapter/adapter.h
 *        	Then, user should create a controller for controlling extended device from host.
 *  	  	Call this function in beginning to initialize the timer.
 *        	This function allocates memory for the device using malloc() function call and returns a pointer to the device. Pass this device pointer 
 *        	while calling timer functions.
 *
 *  \param pTimerController Pointer to the timer controller structure.
 *  \param pTimerConfig Pointer to the timer configuration structure.
 *
 *  \return On success, it return the pointer to timer device. 
 *         On error, it returns NULL.
 */
extern EPCFTimerDevice_t* epcf_timer_createExtended(EPCFTimerController_t* pTimerController, EPCFTimerCfg_t* pTimerConfig);

/**
 *  \brief This function is used to get the total number of available timer devices in extended mode.
 *  
 *  \param pTimerController Pointer to the timer controller structure.
 *
 *  \return Returns the number of available timer devices.
 */
extern uint8_t epcf_timer_extGetDeviceCount(EPCFTimerController_t* pTimerController);

#endif

/**
 * \brief This function is used to start the timer. The timer starts counting and will run according to the configuration. 
 *		  It can be stopped by a call to the function EPCF_TIMER_STOP.
 *
 * \param pTimerDevice Pointer to the timer device.
 *
 * \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_timer_start(EPCFTimerDevice_t* pTimerDevice);

/**
 * \brief This function is used to stop the running timer. The timer counting is stopped and can be started again by a
 *        call to the function EPCF_TIMER_START.
 *
 * \param pTimerDevice Pointer to the timer device.
 *
 * \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_timer_stop(EPCFTimerDevice_t* pTimerDevice);

/**
 * \brief This function is used to reset the timer. The timer count will be set to the initial value.
 * 
 * \param pTimerDevice Pointer to the timer device.
 *
 * \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_timer_reset(EPCFTimerDevice_t* pTimerDevice);

/**
 * \brief This function is used to get the current state of the timer.
 *		  Timer can be started by a call to the function EPCF_TIMER_START.
 *		  Timer can be stopped by a call to the function EPCF_TIMER_STOP.
 * 
 * \param pTimerDevice Pointer to the timer device.
 *
 * \return return timer state
 */
extern EnEPCFTimerState_t epcf_timer_getState(EPCFTimerDevice_t* pTimerDevice);

/**
 * \brief This function is used to read the current time value.
 *
 * \param pTimerDevice Pointer to the timer device.
 * \param time         Pointer to EPCFTime_t variable to get time value.
 * 						this function give time value in micro seconds
 *
 * \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_timer_getTime(EPCFTimerDevice_t* pTimerDevice,EPCFTime_t* time);

/**
 * \brief This function is used to set input polarity of capture signal for getting counter value in counter mode.
 *		  This function will return error if timer is configured in timer mode.
 *
 * \param pTimerDevice Pointer to the timer device.
 * \param channel Compare channel.
 * \param inputPolarity Set the input pin polarity to trigger the capture.
 *
 * \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_timer_setCounter(EPCFTimerDevice_t* pTimerDevice,EnEPCFTimerChannel_t channel,EnEPCFTimerInputPolarity_t inputPolarity);

/**
 * \brief This function is used to read the current timer count in both timer and counter mode.
 *
 * \param pTimerDevice Pointer to the timer device.
 * \param count Pointer to the uint32_t variable to get timer count.
 *
 * \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_timer_getCounterValue(EPCFTimerDevice_t* pTimerDevice, uint32_t* count);

/**
 * \brief This function is used to attach a timer callback for the specific timer interrupt source.
 *
 * \param pTimerDevice 		Pointer to the timer device.
 * \param interruptSource	Interrupt source for the callback.
 * \param callback         	User callback to be called at the specified interrupt source
 * \param priority         	Callback priority 
 *
 * \return return callbackId.
 *
 * \note Call this function before starting the timer device. To attach a callback if timer has already started: 
 *       1. Stop the timer.
 *       2. Reset the timer
 *       3. Detach the callback.
 *       4. Start the timer again.
 */
extern int8_t epcf_timer_attachCallback(EPCFTimerDevice_t* pTimerDevice,EnEPCFTimerInterruptSource_t interruptSource,epcfCallback_fp callback);

/**
 * \brief This function is used to detach the timer callback for the specific timer interrupt source.
 *
 * \param pTimerDevice 		Pointer to the timer device.
 * \param callbackId		callbackId returned by EPCF_TIMER_ATTACH_CALLBACK function.
 *
 * \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 *
 * \note Call this function before starting the timer device. To detach the callback if timer has already started: 
 *       1. Stop the timer.
 *       2. Reset the timer
 *       3. Detach the callback.
 *       4. Start the timer again.
 */
extern int8_t epcf_timer_detachCallback(EPCFTimerDevice_t* pTimerDevice,EnEPCFTimerInterruptSource_t interruptSource);

/**
 * \brief This function is used to set the compare time. Compare channel can be used to trigger an event after the specified time. A compare action
 *		  and an interrupt can be associated to that  event.
 *        A user callback is called if there is a callback attached for this interrupt source. The maximum value that should be passed
 *        to this function is equal to the period of the timer.
 *        Timer period = resolution x (2^timerWidth).
 *        For example: Consider an 8-bit timer with resolution = 0.25 microseconds and configured as a periodic type.
 *                     If time count == 5 and unit is equal to enEPCFTimeUnit_us, then user callback will be called after every 5 microseconds.
 * 
 * \param pTimerDevice 	Pointer to the timer device.
 * \param channel      	Compare channel.
 * \param compareAction	Specifies the timer action on compare match
 *                     	This parameter can be a value of EnEPCFTimerCompareAction_t.
 * \param pinAction		Specify the output pin action
 *						This parameter can be a value of EnEPCFTimerPinAction.
 * \param time         	Compare time value for the channel
 * 
 * \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 * 
 * \note Call this function before starting the timer. To set compare time for a new channel or to update the compare time: 
 *       1. Stop the timer.
 *       2. Reset the timer
 *       3. Detach the callback.
 *       4. Start the timer again.
 */
extern int8_t epcf_timer_setCompareTime(EPCFTimerDevice_t* pTimerDevice,EnEPCFTimerChannel_t channel,EnEPCFTimerCompareAction_t compareAction,EnEPCFTimerPinAction pinAction,EPCFTime_t time);

/**
 * \brief This function is used to set input polarity of the input capture channel. An input capture channel can be used to get width of
		  the input signal. It can also be used to generate an interrupt and a user callback is called if there is a
 * 		  callback attached for this interrupt source.
 *        For example: Consider a configuration in which timer resolution = 0.25 microseconds and input capture channel is configured
 * 					   to detect falling clock edge on channel0.
 *                     If the signal is in high state when the timer has started and comes to a low state after 5 microseconds.
 *					   Then, an interrupt will be generated after 5 microseconds. Use EPCF_TIMER_GET_INPUT_CAPTURE_TIME function
 *					   to get width of the signal.
 *
 * \param pTimerDevice 	Pointer to the timer device.
 * \param channel      	Input Capture channel.
 * \param inputPolarity Set the input pin polarity to trigger the capture
 *
 * \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 *
 * \note Call this function before starting the timer. To set input capture time for a new channel or to update the input capture time: 
 *       1. Stop the timer.
 *       2. Reset the timer
 *       3. Detach the callback.
 *       4. Start the timer again.
 */
extern int8_t epcf_timer_setInputCapture(EPCFTimerDevice_t* pTimerDevice,EnEPCFTimerChannel_t channel,EnEPCFTimerInputPolarity_t inputPolarity);

/**
 * \brief This function is used to read the input capture time for the specified channel.
 *
 * \param pTimerDevice Pointer to the timer device.
 * \param channel      Input Capture channel.
 * \param time		   Pointer to the EPCFTime_t variable to get input capture time value.
 *
 * \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_timer_getInputCaptureTime(EPCFTimerDevice_t* pTimerDevice,EnEPCFTimerChannel_t channel,EPCFTime_t* time);

/**
 * \brief This function is used to close the timer. It will free the memory allocated by the timer device.
 *
 * \param pTimerDevice Pointer to the timer device.
 *
 * \return return status. Refer to "../../common/status.h" header file for the appropriate status codes.
 */
extern int8_t epcf_timer_close(EPCFTimerDevice_t* pTimerDevice);

/**
 * \brief This function is used to get the total number of available timer devices.
 *
 * \return Returns the number of available timer devices.
 */
extern uint8_t epcf_timer_getDeviceCount();

#ifdef EPCF_USING_MT_ENV
//ToDo: Adding support for EPCF_USING_MT_ENV
//ToDo: Add comment for function description
extern int8_t epcf_timer_lock(EPCFTimerDevice_t* pTimerDevice);
extern int8_t epcf_timer_unlock(EPCFTimerDevice_t* pTimerDevice);

#endif	//EPCF_USING_MT_ENV

#endif      //__EPCF_PERIPHERAL_INCLUDE_TIMER_TIMER_H
