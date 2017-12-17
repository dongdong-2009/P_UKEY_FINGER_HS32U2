// +FHDR -----------------------------------------------------------------------
// Copyright (c) 2009, Hongsi.
// Hongsi Confidential Proprietary
// 2009/7/15
//
// -----------------------------------------------------------------------------
// File Name: ssf33.h
// Type: C Language 
//
// -----------------------------------------------------------------------------
// Header:
// This header file is definitions for SSF33 Function of HS32U2.
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

typedef unsigned int U32;
typedef unsigned char U8;

// ---------------------------------------------------------------------  
// Constant Definitions 
// ---------------------------------------------------------------------  

#define BUSY  0x00000001

#define OPERATION_ENCODE	0x00
#define OPERATION_DECODE	0x01

#define MODE_ECB			0x00
#define MODE_CBC			0x01

// ---------------------------------------------------------------------  
// Register Definitions
// ---------------------------------------------------------------------  

#define FAEDINR  ( U32 *)0x00b40000
#define FAEKINR  ( U32 *)0x00b40010
#define FAEIVINR ( U32 *)0x00b40020
#define FAEDOUTR ( U32 *)0x00b40030
#define FAECSR   (*( U32 *)0x00b40040)

// ---------------------------------------------------------------------  
// Function Declarations
// ---------------------------------------------------------------------  
#define SSF33_ENCKEY(key,keyout) ((void (*)())(0x0003F000))(key,keyout)
#define SSF33_DECKEY(key,keyout) ((void (*)())(0x0003F964))(key,keyout)	    
void SSX33_GENERATE_KEY(U32 *x, U32 *key);
void SSF33_CRYPT(U8 *in, U32 bytes, U32 * key, U8 *iv, U8 operation, U8 mode, U8 *out);