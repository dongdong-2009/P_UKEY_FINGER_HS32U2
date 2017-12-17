// +FHDR -----------------------------------------------------------------------
// Copyright (c) 2000, Hongsi.
// Hongsi Confidential Proprietary
// 2009/6/23 
//
// -----------------------------------------------------------------------------
// File Name: aes_func.c
// Type: C Language 
//
// -----------------------------------------------------------------------------
// Description:
// This code is cryption function for AES.
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

#include "aes.h"

// ---------------------------------------------------------------------  
// Func : AES_CRYPT()
// Description : Cryption for AES
// ---------------------------------------------------------------------  
// Input
// in: 	 	Input data buffer. Plaintext to encrypt or crypto to decrypt.
// bytes: 	Length of input data in byte. Must be multiple of 16.
// key:	Key in byte format
// key_len:	The length of the key in bit. 0 for not key extension
// iv:		Initial value for CBC mode in byte format.
// decrypt:	Operation flag. 0 for encrypt, 1 for decrypt.
// cbc:		Operation flag. 0 for ECB, 1 for CBC,
//----------------------------------------------------------------------
// Output
// out: 	Output data buffer.

void AES_CRYPT(U8 *in, U32 bytes, U8 *key, U8 key_len, U8 *iv, U8 decrypt, U8 cbc, U8 *out)
{

	register unsigned int *src, *dest;

	U32 i, j;
	
	// Setup operation mode
	i = 0;	
	if (decrypt) i |= 0x80;
	if (cbc) i |= 0x40;
	if (key_len>KEY_LENGTH_128)
	{
		if (key_len > KEY_LENGTH_128) i |= key_len;
	}
	
	if(!key_len) i |=  AAECSR & 0x38;

	AAECSR = i;
	
	if (key_len)
	{
		// extend the key
		j = key_len;
		if(key_len<KEY_LENGTH_256) j += 8;
		src = (U32 *)key;
		dest = AAEKINR;
		j >>= 2;
		for(i=0;i<j;i++)
		{
			*dest = *src;
			dest++;
			src++;
		}
	}
	
	if(cbc)
	{
		src = (U32 *)iv;
		dest = AAEIVINR;
		for(i=0;i<4;i++)
		{
			*dest = *src;
			dest++;
			src++;
		}
	}
	
	// if decrypt wait for key extension
	if(decrypt)
	{
		do{}while(AAECSR & KBUSY);
	}
	
	for(i=0;i<bytes;i+=16)
	{
		
		dest = AAEDINR;
		src = (U32 *)(in+i);
		for(j=0;j<4;j++)
		{
			*dest = *src;
			dest++;
			src++;
		}
		
		do{}while(AAECSR & BUSY);
		
		// get result
		dest = (U32 *)(out+i);
		src = AAEDOUTR;
		for(j=0;j<4;j++)
		{
			*dest = *src;
			dest++;
			src++;
		}
	
	}
	return;
}
