// +FHDR -----------------------------------------------------------------------
// Copyright (c) 2009, Hongsi.
// Hongsi Confidential Proprietary
// 2009/7/15
//
// -----------------------------------------------------------------------------
// File Name: des.h
// Type: C Language 
//
// -----------------------------------------------------------------------------
// Header:
// This header file is definitions for DES Function of HS32U2.
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
#define BUSY 0x00000001

#define OPERATION_ENCODE	0x00
#define OPERATION_DECODE	0x01

#define MODE_ECB			0x00
#define MODE_CBC			0x01

#define KEY_NOT_CHANGE		0x00
#define KEY_LENGTH_56		0x08
#define DES					0x08
#define KEY_LENGTH_112		0x10
#define TDES				0x10

// ---------------------------------------------------------------------  
// Register Definitions
// ---------------------------------------------------------------------  

#define DAEDINR  ( U32 *)0x00b20000
#define DAEKIN1R ( U32 *)0x00b20008
#define DAEKIN2R ( U32 *)0x00b20010
#define DAEKIN3R ( U32 *)0x00b20018
#define DAEIVINR ( U32 *)0x00b20020
#define DAEDOUTR ( U32 *)0x00b20028
#define DAECSR   (*(volatile U32 *)0x00b20030)

// ---------------------------------------------------------------------  
// Function Declarations
// ---------------------------------------------------------------------  

void DES_CRYPT(U32 *in, U32 bytes, U32 *key, U8 key_len, U32 *iv, U8 decrypt, U8 cbc, U32 *out);
