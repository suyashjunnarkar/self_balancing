#ifndef __EPCF_INCLUDED_PERIPHERAL_TYPES_H
#define __EPCF_INCLUDED_PERIPHERAL_TYPES_H

/** \brief Enumeration for boolean value 	*/
typedef enum
{
    enEPCFBoolean_False  = 0, 	/**< False value	*/
    enEPCFBoolean_True   = 1,  	/**< True value 	*/
	enEPCFBoolean_Max			/**< Special value for boundary checking	*/
}EnEPCFBoolean_t;

/** User Callback     */
typedef void (*epcfCallbackWithArg_fp)(uint32_t uArg);
typedef void (*epcfCallback_fp)(void);

/** \brief  Enumeration for units of time  		*/
typedef enum
{
    enEPCFTimeUnit_ns,		/**< nanoseconds unit     	*/
    enEPCFTimeUnit_us,		/**< microseconds unit   	*/
	enEPCFTimeUnit_ms,		/**< milliseconds unit    	*/
	enEPCFTimeUnit_s,		/**< seconds unit   		*/
    enEPCFTimeUnit_Max		/**< Special value for boundary checking    */
}EnEPCFTimeUnit_t;

/** \brief Structure to define time value.
    For example To set time as 0.25 microseconds, set time unit to enEPCFTimeUnit_ns and set count value as 250.
*/
typedef struct
{
	uint32_t 			count;			//magnitude of time
	EnEPCFTimeUnit_t	unit;			//unit of time
}EPCFTime_t;

#endif /* __EPCF_INCLUDED_PERIPHERAL_TYPES_H */
