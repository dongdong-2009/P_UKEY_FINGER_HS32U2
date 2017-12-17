// +FHDR -----------------------------------------------------------------------
// Copyright (c) 2009, Hongsi.
// Hongsi Confidential Proprietary
// 2009/7/15
//
// -----------------------------------------------------------------------------
// File Name: flash.h
// Type: C Language 
//
// -----------------------------------------------------------------------------
// Header:
// This header file is definitions for FLASH Function of HS32U2.
//
// -----------------------------------------------------------------------------
// Detailed Func Description:
// 1. Data Type Definitions.
// 2. Constant Definitions.
// 3. Register Definitions.
// 4. Function Declarations.
//
// -----------------------------------------------------------------------------
// Revision History
// DATE         AUTHOR          DESCRIPTION
// 2009/7/15 					V1.0
// -FHDR -----------------------------------------------------------------------


// ---------------------------------------------------------------------  
// Data Type Definitions 
// ---------------------------------------------------------------------  

typedef unsigned int     U32;
typedef unsigned short   U16;
typedef unsigned char    U8;

// ---------------------------------------------------------------------  
// Constant Definitions 
// ---------------------------------------------------------------------  

#define EFMSR_CCIF   0x80000000

// ---------------------------------------------------------------------  
// Register Definitions
// ---------------------------------------------------------------------  

#define EFMCR		(*(volatile U32 *)0x00d00000)
#define EFMSR		(*(volatile U32 *)0x00d00004)
#define EFMCMD		(*(volatile U32 *)0x00d00008)

// ---------------------------------------------------------------------  
// Function Declarations
// ---------------------------------------------------------------------  

void Erasescode(U32 *);

void Writescode(U32 *, U32);

void InitFlash();

void ReadFlash(U8 *,U32,U32);

void WriteFlash(U8 *,U32,U32);

void WriteFlashOnly(U8 *,U32,U32);

void PageeraseFlash(U32);
