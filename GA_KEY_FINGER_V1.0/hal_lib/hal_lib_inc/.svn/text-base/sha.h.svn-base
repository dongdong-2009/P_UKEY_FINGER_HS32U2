// +FHDR -----------------------------------------------------------------------
// Copyright (c) 2009, Hongsi.
// Hongsi Confidential Proprietary
// 2009/7/15
//
// -----------------------------------------------------------------------------
// File Name:sha.h
// Type: C Language 
//
// -----------------------------------------------------------------------------
// Header:
// This header file is various definition for HAE Function.
//
// -----------------------------------------------------------------------------
// Detailed Func Description:
// 1. Data Type Definitions.
// 2. Constant Definitions.
// 3. Register Definitions.
// 4. Function Declarations.
// -----------------------------------------------------------------------------
// Revision History
// DATE         AUTHOR          DESCRIPTION
// 2009/7/15 					V1.0
// -FHDR -----------------------------------------------------------------------

// ---------------------------------------------------------------------  
// Data Type Definitions 
// ---------------------------------------------------------------------  

typedef unsigned char U8;
typedef unsigned int U32;

// ---------------------------------------------------------------------
// Constant Definitions 
// ---------------------------------------------------------------------
#define BUSY 0x00000001

#define SHA_1	0x00
#define SHA_224	0x30
#define SHA_256	0x20

#define SHA_GO_ON 	0x00
#define SHA_INIT 	0x01

// --------------------------------------------------------------------- 
// Register Definitions
// ---------------------------------------------------------------------
#define HAEDIGR ( U32 *)0x00b50000
#define H0      ( U32 *)0x00b5000c
#define HAECSR  (*(volatile U32 *)0x00b50020)
#define HAEMINR ( U32 *)0x00b50040

// ---------------------------------------------------------------------  
// Function Declarations
// ---------------------------------------------------------------------  

void SHA_HASH(U8 *in, U32 bytes, U8 mode, U8 init, U8 *out);
