// +FHDR -----------------------------------------------------------------------
// Copyright (c) 2000, Hongsi.
// Hongsi Confidential Proprietary
// 2009/6/23 
//
// -----------------------------------------------------------------------------
// File Name: ssf33_func.c
// Type: C Language 
//
// -----------------------------------------------------------------------------
// Description:
// This code includes key process function and cryption function for SSF33.
//
// -----------------------------------------------------------------------------
// Detailed Func Description:
// 1. Key Process Function
// 2. Cryption Function
//
// -----------------------------------------------------------------------------
// Revision History
// DATE         AUTHOR          DESCRIPTION
// 2005/11/17 			V1.0
// -FHDR -----------------------------------------------------------------------


// ---------------------------------------------------------------------  
// Include File Declarations 
// ---------------------------------------------------------------------  

#include "ssf33.h"

// ---------------------------------------------------------------------  
// Function Declarations 
// ---------------------------------------------------------------------  

// ---------------------------------------------------------------------  
// Func : SSX33_ENCKEY()
// Description : Dummy function for SSF33 Encrypt Key
// ---------------------------------------------------------------------  
// Input
// x: 		128-bit key seed
//-----------------------------------------------------------------
// Output
// key: 	128-bit key

//void SSF33_ENCKEY (U32 *x, U32 *key)
//{
//	U32 i;
//	
//	memcpy(key, x, 16);
//}

// ---------------------------------------------------------------------  
// Function Declarations 
// ---------------------------------------------------------------------  

// ---------------------------------------------------------------------  
// Func : SSX33_DECKEY()
// Description : Dummy function for SSF33 Decrypt Key
// ---------------------------------------------------------------------  
// Input
// x: 		128-bit key seed
//-----------------------------------------------------------------
// Output
// key: 	128-bit key

//void SSF33_DECKEY (U32 *x, U32 *key)
//{
//	U32 i;
//	
//	memcpy(key, x, 16);
//}

// ---------------------------------------------------------------------  
// Func : SSF33_CRYPT()
// Description : Cryption for SSF33
// ---------------------------------------------------------------------  
// Input
// in: 	 	Input data buffer. Plaintext to encrypt or crypto to decrypt.
// bytes: 	Length of input data in byte. Must be multiple of 16.
// w_key:	Key of SSF33 in unsigned integer format with the length of 128 bits.
// b_iv:	Initial value for CBC mode in byte format.
// decrypt:	Operation flag. 0 for encrypt, 1 for decrypt.
// cbc:		Operation flag. 0 for ECB, 1 for CBC,
//----------------------------------------------------------------------
// Output
// out: 	Output data buffer.

void SSF33_CRYPT(U8 *in, U32 bytes, U32 *key, U8 *iv, U8 decrypt, U8 cbc, U8 *out)
{

	register unsigned int *src, *dest;

	U32 i, j;
	
	// Setup operation mode
	i = decrypt ? 1 : 0;
	j = cbc ? 1 : 0;
	FAECSR = i<<1;
	FAECSR |= j<<2;
	
	src = key;
	dest = FAEKINR;
	for(i=0;i<4;i++)
	{
		*dest = *src;
		dest++;
		src++;
	}
	
	if(cbc)
	{
		src = (U32 *)iv;
		dest = FAEIVINR;
		for(i=0;i<4;i++)
		{
			*dest = *src;
			dest++;
			src++;
		}
	}
	
	for(i=0;i<bytes;i+=16)
	{
		dest = FAEDINR;
		src = (U32 *)(in+i);
		for(j=0;j<4;j++)
		{
			*dest = *src;
			dest++;
			src++;
		}
		
		
		do{}while(FAECSR & BUSY);
		
		// get result
		dest = (U32 *)(out+i);
		src = FAEDOUTR;
		for(j=0;j<4;j++)
		{
			*dest = *src;
			dest++;
			src++;
		}
	}
	return;
}
