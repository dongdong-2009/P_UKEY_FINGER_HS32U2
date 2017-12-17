// +FHDR -----------------------------------------------------------------------
// Copyright (c) 2000, Hongsi.
// Hongsi Confidential Proprietary
// 2009/6/23 
//
// -----------------------------------------------------------------------------
// File Name: des_func.c
// Type: C Language 
//
// -----------------------------------------------------------------------------
// Description:
// This code is cryption function for DES.
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

#include "des.h"

// ---------------------------------------------------------------------  
// Func : DES_CRYPT()
// Description : Cryption for DES
// ---------------------------------------------------------------------  
// Input
// in: 	 	Input data buffer. Plaintext to encrypt or crypto to decrypt.
// bytes: 	Length of input data in byte. Must be multiple of 16.
// key:	Key in byte format
// key_len:	The length of the key in bit. 56/64 for DES, 112/128 for 3DES
// iv:		Initial value for CBC mode in byte format.
// decrypt:	Operation flag. 0 for encrypt, 1 for decrypt.
// cbc:		Operation flag. 0 for ECB, 1 for CBC,
//----------------------------------------------------------------------
// Output
// out: 	Output data buffer.

void DES_CRYPT(U32 *in, U32 bytes, U32 *key, U8 key_len, U32 *iv, U8 decrypt, U8 cbc, U32 *out)
{

	register unsigned int *src, *dest;

	U32 i, j;
	
	// Setup operation mode
	i = DAECSR;
	i &= 0xfffffff9;
	if(decrypt) i |= 0x02;
	if(cbc) i |= 0x04;
	if(key_len)
	{
		i &= 0xffffffef;
		if(key_len==KEY_LENGTH_112) i |= 0x10;
	}
	
	DAECSR = i;
	
	if(key_len)
	{
		src = (U32 *)key;
		dest = DAEKIN1R;
		for(i=0;i<(key_len>>2);i++)
		{
			*dest = *src;
			dest++;
			src++;
		}
	}
	
	if(cbc)
	{
		src = (U32 *)iv;
		dest = DAEIVINR;
		for(i=0;i<2;i++)
		{
			*dest = *src;
			dest++;
			src++;
		}
	}
	
	for(i=0;i<bytes;i+=8)
	{
		
		dest = DAEDINR;
		src = (U32 *)(in+(i/4));
		for(j=0;j<2;j++)
		{
			*dest = *src;
			dest++;
			src++;
		}
		
		do{}while(DAECSR & BUSY);
		
		// get result
		dest = (U32 *)(out+(i/4));
		src = DAEDOUTR;
		for(j=0;j<2;j++)
		{
			*dest = *src;
			dest++;
			src++;
		}
	}
}
