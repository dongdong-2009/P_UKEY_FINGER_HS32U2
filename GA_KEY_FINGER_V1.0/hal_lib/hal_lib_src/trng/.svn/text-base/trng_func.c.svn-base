// +FHDR -----------------------------------------------------------------------
// Copyright (c) 2009, Hongsi.
// Hongsi Confidential Proprietary
// 2009/06/26 
//
// -----------------------------------------------------------------------------
// File Name: TRNG.c
// Type: C Language 
//
// -----------------------------------------------------------------------------
// Description:
// This code is Init TRNG function and Generate Random Data function for TRNG.
//
// -----------------------------------------------------------------------------
// Detailed Func Description:
// 1. Initialize TRNG.
// 2. Generate data.
//
// -----------------------------------------------------------------------------
// Revision History
// DATE         AUTHOR          DESCRIPTION
// 2009/06/26 			V1.0
// -FHDR -----------------------------------------------------------------------
 
// ---------------------------------------------------------------------  
// Include File Declarations 
// ---------------------------------------------------------------------  

#include "TRNG.h"

// ---------------------------------------------------------------------  
// Function Declarations 
// ---------------------------------------------------------------------  

// ---------------------------------------------------------------------  
// Func : TRNG_Init()
// Description : Initialize TRNG
// ---------------------------------------------------------------------  
// Input
// No
//-----------------------------------------------------------------
// Output
// No

void TRNG_Init()
{
	unsigned int TRNGd,flag,num;

	// Start TRNG work
	TRNGCSR = 0x00000001;
	flag = TRNGCSR;
	
	for(num=0;num<2;num++)
	{
		do{
		flag=TRNGCSR & TRNGDRY;    
		}while(!flag);
		TRNGd=TRNGDR;
	}
}

// ---------------------------------------------------------------------  
// Func : Get_Rand()
// Description : Generate Random Data
// ---------------------------------------------------------------------  
// Input
// No
//-----------------------------------------------------------------
// Output
// Return Random Data

unsigned long Get_Rand()
{
	unsigned int TRNGd,flag;

	flag = TRNGCSR;

	do{
	flag=TRNGCSR & TRNGDRY;    
	}while(!flag);

	TRNGd=TRNGDR;
	return(TRNGd);

}