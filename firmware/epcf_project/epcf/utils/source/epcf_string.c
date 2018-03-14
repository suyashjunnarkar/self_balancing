#include "pcf.h"

#define __EPCF_UTILS_STRING_INCLUDE PCF_CONDITIONAL_INCLUDE_FILE(EPCF_DIR_PATH/,utils/,include/,epcf_string.h)
#include __EPCF_UTILS_STRING_INCLUDE
#undef __EPCF_UTILS_STRING_INCLUDE

static uint8_t tokString[256];
static uint16_t is,len;

uint8_t* pcfStringTokenize(uint8_t* str, const uint8_t* token)
{
    uint16_t index2 = 0, loop = 0, temp, index=0;
    uint8_t result = 0;
    if((token == NULL))
    {
        return 0;
    }
	index++;
	is = index;
	if(str != NULL)
	{
		len = 0;
		is = 0;
		index = 0;
		while(str[len] != 0)
		{
			tokString[len] = str[len];
			len++;
		}
		tokString[len] = 0;
	}
  
    while(tokString[index] != 0)
    {
        loop = 0;
        index2 = index;
        while(1)
        {
            if(tokString[index2] != token[loop])
            {
                break;
            }
            loop++;
            index2++;
            if(tokString[index2] == 0)
                break;
            if(token[loop] == 0)
            {
                result = 1;
                break;
            }
        }
        if(result == 1)
        {
            for(temp = 0; temp < loop; temp++)
            {
                tokString[index+temp] = 0;
            }
            return &tokString[is];
        }
        index++;
			if(index >= len)
				return &tokString[is];
    }
		
    return 0;
}

uint32_t pcfStrLen(const uint8_t* str)
{
	uint32_t index = 0;
#if (PF_UTILS_DEBUG == 1)
	if(str == 0)
	{
		return 0;
	}	
#endif	// #if (PF_UTILS_DEBUG == 1)

	while(*(str + index) != 0)
	{
		index++;
	}
	
	return index;
}

uint32_t pcfStrCopy(uint8_t* dest, const uint8_t* src)
{
	uint32_t count = 0;
#if (PF_UTILS_DEBUG == 1)
	if((dest == 0) || (src == 0))
	{
		return 0;
	}	
#endif	// #if (PF_UTILS_DEBUG == 1)
	while(*(src+count) != 0)
	{
		*(dest+count) = *(src+count);
		count++;
	}
	return count;
}

int8_t pcfStrReverse(uint8_t * str)
{
	uint8_t i, j,ch;
#if (PF_UTILS_DEBUG == 1)
	if(str == 0)
	{
		return -2;
	}	
#endif	// #if (PF_UTILS_DEBUG == 1)	
	for (i = 0, j = pcfStrLen(str)-1; i<j; i++, j--) 
	{
		ch = str[i];
		str[i] = str[j];
		str[j] = ch;
	}
	
	return 0;
}
//const
int8_t pcfMemCopy(void* dest, const void* src, uint32_t num)
{
	uint32_t index;
#if (PF_UTILS_DEBUG == 1)
	if( (src == 0) || (dest == 0) || (num == 0) )
	{
		return -2; 		//enStatusInvArgs
	}	
#endif	// #if (PF_UTILS_DEBUG == 1)

	for(index = 0; index < num; index++)	
	{
		*(((uint8_t*)dest) + index) = *(((const uint8_t*)src) + index);
	}
	
	return 0;		//enStatusSuccess
}

int8_t pcfMemSet(void* ptr, uint8_t value, uint32_t num)
{
	uint32_t index;
#if (PF_UTILS_DEBUG == 1)
	if( (ptr == 0) || (num == 0) )
	{
		return -2; 
	}	
#endif	// #if (PF_UTILS_DEBUG == 1)

	for(index = 0; index < num; index++)	
	{
		*(((uint8_t*)ptr) + index) = value;
	}
	
	return 0;
}

EnEPCFBoolean_t pcfMemCompare( const void* ptr1, const void* ptr2, uint32_t num)
{
	uint32_t index;
#if (PF_UTILS_DEBUG == 1)
	if( (ptr1 == 0) || (ptr2 == 0) || (num == 0) )
	{
		return false;
	}	
#endif	// #if (PF_UTILS_DEBUG == 1)

	for(index = 0; index < num; index++)	
	{
		if( *(((const uint8_t*)ptr1) + index) != *(((const uint8_t*)ptr2) + index) )
		{
			return false;
		}
	}
	
	return true;
}

int8_t pcfFtoA(float x, uint8_t* str)
{
	short ie=0,precission=6,i, k;
 	double y=1;
 		
#if (PF_UTILS_DEBUG == 1)
	if(str == 0)
	{
		return -2;
	}	
#endif	// #if (PF_UTILS_DEBUG == 1)
	
	if( x < 0) 	/* if x negative, write minus and reverse */
 	{
 	  *str++ = '-';
 	  x = -x;
 	}

 	if(x!=0.0f)		//if (x<0.0) then increment by 10 till betwen 1.0 and 10.0
 	{
 		while(x < 1.0f)  
 		{
 		  x =x* 10.0f;
 		  ie--;
 		}
 	}
 	while(x >= 10.0f)	 //if x>10 then let's shift it down
 	{
 		x = x*(1.0f/10.0f);
 		ie++;
 	}
	/* rounding fraction part. add this fraction to get exact fraction value */
 	for(i = 1; i < precission; i++)	//find least significant digit
 	  y = y *(1.0f/10.0f); 		          //multiply by 1/10 is faster than divides
 	 
  	x = x+ y *(1.0f/2.0f);			      //add rounding
 	/* repair rounding  */
 	if(x >= 10.0f) 
 	{
		x = 1.0f; 
 		ie++;
 		precission++;
 	} 	
	
 	/*check and see if the number is less than 1.0*/
	if(ie<0)
 	{
 		*str++ = '0'; 
 		*str++ = '.';
 	
 		for(i = -1; i > ie; i--)
 			*str++ = '0';
 	}
 
 	for(i=0; i < precission; i++)   	//for each digit 
 	{
 		float b;
 		k = x;						    //k = most significant digit
 		*str++ = k + '0';			//output the char representation
  
		if(i==ie)
 			*str++ = '.';			  //output a decimal point
		
 		b =( float)k;                      
 		b = b*10.0f;							//multiply by 10 before subtraction to remove errors from limited number of bits in float. 
 		x = x*10.0f;
 		x = x - b;				      //subtract k from x		
 	}
	*str++ = '\0';
	return 0;
}

int8_t pcfAtoI(const uint8_t* str, uint32_t* num)
{
	uint32_t k = 0;
#if (PF_UTILS_DEBUG == 1)
	if( (str == 0) || (num == 0) )
	{
		return -2;
	}	
#endif	// #if (PF_UTILS_DEBUG == 1)
	
	while (*str) 
	{
			k = (k<<3)+(k<<1)+(*str)-'0';
			str++;
	}
	*num = k;
	
	return 0;
}

int8_t pcfAtoF(const uint8_t* str, float* num)
{
	float result=0;
	uint16_t sLen = pcfStrLen(str);
	uint8_t dotpos=0,i;
#if (PF_UTILS_DEBUG == 1)
	if( (str == 0) || (num == 0) )
	{
		return -2;
	}	
#endif	// #if (PF_UTILS_DEBUG == 1)	
	if((str[0] == '-') || (str[0] == '+'))
	{
		i=1;
	}
	else
	{
		i=0;
	}
	for(;i<sLen;i++)
	{
		if(str[i]=='.')
		{
			dotpos = sLen-i-1;
		}
		else
		{
			result = (result * 10.0f) + (str[i] - '0');
		}
	}
	while(dotpos--)
	{
		result /= 10.0f;
	}
	if(str[0] == '-')
	{
		result *= -1;
	}
	
	*num = result;
	
	return 0;
}

int8_t pcfItoA(long num, uint8_t* str)
{
	long i=0, sign;
#if (PF_UTILS_DEBUG == 1)
	if( (str == 0) || (num == 0) )
	{
		return -2;
	}	
#endif	// #if (PF_UTILS_DEBUG == 1)	
	
	sign = num;
	if (num < 0)  			// record sign
	{
		num = -num;         // make num positive
	}		
	do 
	{    
		// generate digits in reverse order
		str[i++] = num % 10 + '0';   // get next digit
	} while ((num /= 10) > 0);     	// delete it
			
	if (sign < 0)
	{
		str[i++] = '-';
	}
	str[i] = '\0';
	pcfStrReverse(str);
	
	return 0;
}

uint8_t pcfStrCat(uint8_t *dest, const uint8_t *src)
{
	uint32_t destCount=0, srcCount=0, index;

	while(*(dest + destCount) != 0)
	{
		destCount++;
	}

	while(*(src + srcCount) != 0)
	{
		srcCount++;
	}

	for(index=0; index<srcCount; index++)
	{
		*((dest+destCount)+ index) = *(src + index);
	}

	return 0;
}
