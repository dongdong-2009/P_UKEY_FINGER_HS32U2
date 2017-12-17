// +FHDR -----------------------------------------------------------------------
// Copyright (c) 2008, Hongsi.
// Hongsi Confidential Proprietary
// 2009/7/15
//
// -----------------------------------------------------------------------------
// File Name: sm1.h
// Type: C Language 
//
// -----------------------------------------------------------------------------
// Header:
// This header file is definitions for SM1 Function of HS32U2.
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
#ifndef __SM1_H__
#define __SM1_H__

typedef unsigned int U32;
typedef unsigned char U8;

// ---------------------------------------------------------------------  
// Constant Definitions 
// ---------------------------------------------------------------------  

#define BUSY  		0x00000001

#define OPERATION_ENCODE	0x00
#define OPERATION_DECODE	0x01

#define MODE_ECB			0x00
#define MODE_CBC			0x01

#define KEY_NOT_CHANGE 		0x00
#define NEW_KEY 			0x01

// ---------------------------------------------------------------------  
// Register Definitions
// ---------------------------------------------------------------------  

#define SAEDINR  (U32 *)0x00b30000
#define SAEIVINR (U32 *)0x00b30010
#define SAEKINR  (U32 *)0x00b30020
#define SAEDOUTR (U32 *)0x00b30040
#define SAECSR   (*(volatile U32 *)0x00b30050)

// ---------------------------------------------------------------------  
// Function Declarations
// ---------------------------------------------------------------------  

void SM1_CRYPT(U8 *in, U32 bytes, U8 *key, U8 new_key, U8 *iv, U8 operation, U8 mode, U8 *out);

#endif

