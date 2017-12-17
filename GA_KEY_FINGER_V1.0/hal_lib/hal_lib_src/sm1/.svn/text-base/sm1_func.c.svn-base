// +FHDR -----------------------------------------------------------------------
// Copyright (c) 2000, Hongsi.
// Hongsi Confidential Proprietary
// 2009/6/23 
//
// -----------------------------------------------------------------------------
// File Name: sm1_func.c
// Type: C Language 
//
// -----------------------------------------------------------------------------
// Description:
// This code is cryption function for SM1.
//
// -----------------------------------------------------------------------------
// Detailed Func Description:
// 1. Cryption Function
//
// -----------------------------------------------------------------------------
// Revision History
// DATE         AUTHOR          DESCRIPTION
// 2005/11/17 			V1.0
// -FHDR -----------------------------------------------------------------------


// ---------------------------------------------------------------------  
// Include File Declarations 
// ---------------------------------------------------------------------  

#include "sm1.h"

// ---------------------------------------------------------------------  
// Func : SM1_CRYPT()
// Description : Cryption for SM1
// ---------------------------------------------------------------------  
// Input
// in: 	 	Input data buffer. Plaintext to encrypt or crypto to decrypt.
// bytes: 	Length of input data in byte. Must be multiple of 16.
// key:	Key in byte format with the length of 16 bytes.
// new_key:	Flag to load key
// iv:		Initial value for CBC mode in byte format.
// decrypt:	Operation flag. 0 for encrypt, 1 for decrypt.
// cbc:		Operation flag. 0 for ECB, 1 for CBC,
//----------------------------------------------------------------------
// Output
// out: 	Output data buffer.

void SM1_CRYPT(U8 *in, U32 bytes, U8 *key, U8 new_key, U8 *iv, U8 decrypt, U8 cbc, U8 *out)
{

	register unsigned int *src, *dest;
	unsigned int tmp[4];
	
	U32 i, j;
	
	// Setup operation mode
	j = decrypt ? 0x02 :0x00;
	if(cbc) j |=  0x04;
	SAECSR = j;
	
	if (new_key)
	{
		memcpy((unsigned char *)tmp, key, 16);
		src = tmp;
		dest = SAEKINR;
		for(i=0;i<4;i++)
		{
			*dest = *src;
			dest++;
			src++;
		}
	}
	
	if(cbc)
	{
		memcpy((unsigned char *)tmp, iv, 16);
		src = tmp;
		dest = SAEIVINR;
		for(i=0;i<4;i++)
		{
			*dest = *src;
			dest++;
			src++;
		}
	}
	
	for(i=0;i<bytes;i+=16)
	{
		memcpy((unsigned char *)tmp, in+i, 16);
		dest = SAEDINR;
		src = tmp;
		for(j=0;j<4;j++)
		{
			*dest = *src;
			dest++;
			src++;
		}
		
		
		while(SAECSR & BUSY){};
		
		// get result
		dest = tmp;
		src = SAEDOUTR;
		for(j=0;j<4;j++)
		{
			*dest = *src;
			dest++;
			src++;
		}
		memcpy(out+i, (unsigned char *)tmp, 16);
	}
	return;
}
