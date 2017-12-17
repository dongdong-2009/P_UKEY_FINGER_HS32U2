// +FHDR -----------------------------------------------------------------------
// Copyright (c) 2000, Hongsi.
// Hongsi Confidential Proprietary
// 2009/6/24 
//
// -----------------------------------------------------------------------------
// File Name: sha_func.c
// Type: C Language 
//
// -----------------------------------------------------------------------------
// Description:
// This code is cryption function for SHA.
//
// -----------------------------------------------------------------------------
// Detailed Func Description:
// 1. HASH Function
//
// -----------------------------------------------------------------------------
// Revision History
// DATE         AUTHOR          DESCRIPTION
// 2005/11/17 			V1.0
// -FHDR -----------------------------------------------------------------------


// ---------------------------------------------------------------------  
// Include File Declarations 
// ---------------------------------------------------------------------  

#include "sha.h"

// ---------------------------------------------------------------------  
// Func : SHA_Hash()
// Description : Hash by SHA-1/SHA-224/SHA-256
// ---------------------------------------------------------------------  
// Input
// in: 	 	Input data buffer.Message to be hashed.
// bytes: 	Length of input data in byte. Must be multiple of 64.
// mode:	1/160: SHA-1; 224: SHA-224; 256: SHA-256
// init:	1: start a new process; 0: continue existing progress
//----------------------------------------------------------------------
// Output
// out: 	Output data buffer.

void SHA_HASH(U8 *in, U32 bytes, U8 mode, U8 init, U8 *out)
{

	register unsigned int *src, *dest;

	U32 i, j;
	
	// Setup operation mode
	HAECSR = (U32)mode;
	if(init)HAECSR = 0x00000004;
	
	for(i=0;i<bytes;i+=64)
	{
		src = (U32 *)&in[i];
		dest = HAEMINR;
		
		for(j=0;j<16;j++)
		{
			*dest = *src;
			dest++;
			src++;
		}
		
		while(HAECSR & BUSY){};
	}
	
	// get result
	dest = (U32 *)out;
	if(mode)
	{
		src = HAEDIGR;
		j = 8;
		if(mode & 0x10) j--;
	}
	else
	{
		src = H0;
		j = 5;
	}
	
	for(i=0;i<j;i++)
	{
		*dest = *src;
		dest++;
		src++;
	}
	
	return;
}
