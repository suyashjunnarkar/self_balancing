/**
 * \file  pcf_string.h
 * \brief String library utility functions
 */

#ifndef __PCF_INCLUDED_UTILS_STRING_H
#define __PCF_INCLUDED_UTILS_STRING_H

/**
 * \brief Copies the values of \a num bytes from the location pointed by \a src directly to the memory block pointed by \a dest.
 *
 * \param 	dest    Pointer to the destination array where the content is to be copied.
 * \param 	src     Pointer to the source of data to be copied. 
 * \param 	num     Number of bytes to copy.
 *
 * \return return status. Refer to "../common/status.h" header file for the appropriate status codes.
 */
int8_t pcfMemCopy(void* dest, const void* src, uint32_t num);

/**
 * \brief Sets the first \a num bytes of the block of memory pointed by \a ptr to the specified \a value. 
 *
 * \param 	ptr 	Pointer to the block of memory to fill.
 * \param 	value 	Value to be set. 
 * \param 	num 	Number of bytes to be set to the \a value.
 *
 * \return return status. Refer to "../common/status.h" header file for the appropriate status codes.
 */
int8_t pcfMemSet(void* ptr, uint8_t value, uint32_t num); 

/**
 * \brief Compares the first \a num bytes of the block of memory pointed by \a ptr1 to the first \a num bytes pointed by \a ptr2, 
 *        and returns \a enPCFBooleanTrue if all values are equal else \a enPCFBooleanFalse.
 *
 * \param 	ptr1 	Pointer to block of memory.
 * \param 	ptr2 	Pointer to block of memory.
 * \param 	num     Number of bytes to compare.
 *
 * \return enPCFBooleanTrue if \a num bytes in both the buffers are equal.
 *         enPCFBooleanFalse if any one among \a num bytes in both the buffers is not equal.
 */
EnEPCFBoolean_t pcfMemCompare(const void* ptr1, const void* ptr2, uint32_t num);

/**
 * \brief Calculate length of a C string. The length of a C string is determined by the terminating null-character.
 *        A C string is as long as the number of characters between the beginning of the string 
 *        and the terminating null character (without including the terminating null character itself).
 *
 * \param 	str 	C string.
 *
 * \return 			Length of the string.
 */
uint32_t pcfStrLen(const uint8_t* str);

/**
 * \brief Copies string from \a src to \a dest buffer. The string copy terminates at null value.
 *
 * \param 	dest 	Destination buffer pointer to copy string.
 * \param 	src 	Source buffer to copy string from.
 *
 * \return 			Number of bytes copied.
 */
uint32_t pcfStrCopy(uint8_t* dest, const uint8_t* src);
/**
 * TODO: Add the Description of the Function.
 * \brief
 *
 * \param   dest
 * \param   src
 *
 * \return
 */
uint8_t pcfStrCat(uint8_t *dest, const uint8_t *src);

/**
 * \brief Reverses the order of letters in the \a str. The reversed string will be stored in the same string.
 *
 * \param 	str 	String to be reversed.
 *
 * \return return status. Refer to "../common/status.h" header file for the appropriate status codes.
 */
int8_t pcfStrReverse(uint8_t* str);

/**
 * \brief Function breaks a character string, pointed to by string, into a sequence of tokens.
 *        The first time function is called, it returns a pointer to the first token in string.
 *        In subsequent calls with str equal to NULL, function returns a pointer to the next token in the string.
 *
 * \param 	str 	pointer to the string.
 *
 * \param 	token 	tokens in string pointed to by this parameter.
 *
 * \return 			Returns a pointer to token in string.
 */ 
uint8_t* pcfStringTokenize(uint8_t* str, const uint8_t* token);

/**
 * \brief Function converts the floating-point value to a string.
 *
 * \param 	x 		floating-point value to convert in string format.
 * \param 	str 	Pointer to buffer where converted string will be loaded.
 *
 * \return return status. Refer to "../common/status.h" header file for the appropriate status codes.
 */
int8_t pcfFtoA(float x, uint8_t* str);

/**
 * \brief Function converts the integer value to a string.
 *
 * \param 	num 	Integer number to convert in string 
 * \param 	str 	Pointer to buffer where converted string will be loaded.
 *
 * \return return status. Refer to "../common/status.h" header file for the appropriate status codes.
 */
int8_t pcfItoA(long num, uint8_t* str);

/**
 * \brief Function converts the string to a floating-point value.
 *
 * \param 	str 	Float number in string format to convert.
 * \param 	num 	Pointer to float variable where converted number will be loaded.
 *
 * \return return status. Refer to "../common/status.h" header file for the appropriate status codes.
 */
int8_t pcfAtoF(const uint8_t* str, float* num);

/**
 * \brief Function converts the string to a integer value.
 *
 * \param 	str 	Integer number in string format to convert.
 * \param 	num 	Pointer to variable where the converted number will be loaded.
 *
 * \return return status. Refer to "../common/status.h" header file for the appropriate status codes.
 */
int8_t pcfAtoI(const uint8_t* str, uint32_t* num);

#endif		//__PCF_INCLUDED_UTILS_STRING_H
