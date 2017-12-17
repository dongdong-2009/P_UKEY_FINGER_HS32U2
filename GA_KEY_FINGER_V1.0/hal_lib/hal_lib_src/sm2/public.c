#include "HS_types.h"



T_VOID memsetw(T_U32 *pData, T_U32 value, T_U32 len)
{
	while(len-- != 0)
	{
		pData[len] = value;
	}
}

T_VOID memcpyw(T_U32 *dst, const T_U32 *src, T_S32 count)
{
    while( count-- > 0 )
    {
        *dst++ = *src++;
    }
}


T_S32 memcmpw(const T_U32 *str1, const T_U32 *str2, T_U32 wordlength)
{
	if (!wordlength)
    {
        return 0;
    }

    while (--wordlength && *str1 == *str2)
    {
        str1++;
        str2++;
    }

    return((T_S32)(*str1 - *str2));
}
/*
T_VOID memcpy(T_U8 *dst, const T_U8 *src, T_S32 count)
{
    while( count-- > 0 )
    {
        *dst++ = *src++;
    }
}
*/
T_VOID memrcpyw(T_U32 *dst, const T_U32 *src, T_U32 count)
{
	src = src + count-1;
    while( count-- > 0 )
    {
        *dst++ = *src--;
    }
}
