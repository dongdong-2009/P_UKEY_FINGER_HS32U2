// +FHDR -----------------------------------------------------------------------
// Copyright (c) 2008, Hongsi.
// Hongsi Confidential Proprietary
// 2009/7/15
//
// -----------------------------------------------------------------------------
// File Name: aes.h
// Type: C Language 
//
// -----------------------------------------------------------------------------
// Header:
// This header file is definitions for AES Function of HS32U2.
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
#define KBUSY 0x00000002

#define OPERATION_ENCODE	0x00
#define OPERATION_DECODE	0x01

#define MODE_ECB			0x00
#define MODE_CBC			0x01

#define KEY_NOT_CHANGE		0x00
#define KEY_LENGTH_128		0x08
#define AES_128				0x08
#define KEY_LENGTH_192		0x10
#define AES_192				0x10
#define KEY_LENGTH_256		0x20
#define AES_256				0x20


// ---------------------------------------------------------------------  
// Register Definitions
// ---------------------------------------------------------------------  

#define AAEDINR  ( U32 *)0x00b10000
#define AAEIVINR ( U32 *)0x00b10010
#define AAEDOUTR ( U32 *)0x00b10020
#define AAECSR   (*(volatile U32 *)0x00b10030)
#define AAEKINR  ( U32 *)0x00b10040

// ---------------------------------------------------------------------  
// Function Declarations
// ---------------------------------------------------------------------  

void AES_CRYPT(U8 *in, U32 bytes, U8 *key, U8 key_len, U8 *iv, U8 operation, U8 mode, U8 *out);