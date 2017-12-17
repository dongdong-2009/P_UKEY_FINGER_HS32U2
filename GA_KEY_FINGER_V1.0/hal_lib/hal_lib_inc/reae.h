// +FHDR -----------------------------------------------------------------------
// Copyright (c) 2009, Hongsi.
// Hongsi Confidential Proprietary
// 2009/06/17 
//
// -----------------------------------------------------------------------------
// File Name: reae.h
// Type: C Language 
//
// -----------------------------------------------------------------------------
// Header:
// This header file is various definition for REAE.
//
// -----------------------------------------------------------------------------
// Detailed Func Description:
// 1. Data Type Definitions.
// 2. Register Definitions.
// 3. Constant Definitions.
// 4. Function Declarations.
//
// -----------------------------------------------------------------------------
// Revision History
// DATE         AUTHOR          DESCRIPTION
// 2009/06/17 			V1.0
// -FHDR -----------------------------------------------------------------------


#pragma once

// ---------------------------------------------------------------------  
// Data Type Definitions 
// ---------------------------------------------------------------------  

typedef unsigned char U8;
typedef unsigned short U16;
typedef unsigned int  U32;

// ---------------------------------------------------------------------  
// Constant Definitions 
// ---------------------------------------------------------------------  

//------------------------------------------------------
// RSA for 2048

//#define RSA_MAXLONG 68
//#define RSA_HALFLONG 36

#define RSA_MAXLONG 64
#define RSA_HALFLONG 32

//RSA for 1024
#define RSA_MAXLONG1024		32
#define RSA_HALFLONG1024	16

#define REAEBUSY  	0x00000001
#define CMDFULL  	0x00000002
 
// ---------------------------------------------------------------------  
// Register Definitions
// ---------------------------------------------------------------------  

//------------------------------------------------------
// Clock Gen
#define CGCR        (* (volatile unsigned int * )0x00c30000)
#define MCSCR    (* (volatile unsigned int * )0x00c30004) 

//------------------------------------------------------
// REAE
#define REAEDRP       ( unsigned int *)(0x00B00000)     /* REAE Data Memory Pointer*/
#define REAECSR       (*( unsigned int *)(0x00B00800))  /* REAE Software Reset and Status Register*/
#define REAEMLR       (*( unsigned int *)(0x00B00804))  /* REAE Segments Register*/
#define REAEMPR       (*( unsigned int *)(0x00B00808))  /* REAE Montgomery Para Register*/
#define REAECMDR      (*( unsigned int *)(0x00B0080C))  /* REAE Control Register*/


//------------------------------------------------------
// TRNG
#define RNGDR  (*(volatile unsigned int *)0x00ca0000)
#define RNGCSR (*(volatile unsigned int *)0x00ca0004)
#define RNGCDR (*(volatile unsigned int *)0x00ca0008)
 
// ---------------------------------------------------------------------  
// Function Declarations
// ---------------------------------------------------------------------  

U32 Get_Rand_Rsa();
void Create_rand_data (U32 * , U32);
void AEmodN_for_RSA (U32 *,U32 *,U32 *,U32 *,U32);
void RSA_Get_Key_new(U32 *,U32 *,U32 *,U32);
void RSA_Get_Key_For_CRT(U32 *,U32 *,U32 *,U32 *,U32 *,U32 *,U32 *,U32);
void RSA_bigint_mod_e_CRT(U32 *, U32 *,U32 *,U32 *,U32 *,U32 *,U32 *,U32);

U32 GetMP (U32);
void GetR2 (U32,U32,U32);
void GetInverse(U32 *, U32 *, U32 *,U32);
int Create_prime (U32 *, U32);
void NN_Assign (U32 *, U32 *,U32);
int NN_Cmp (U32 *, U32 *,U32);
int NN_Zero (U32 *,U32);
void NN_RShift (U32 *,U32 *,U32,U32);
U32 NN_Add (U32 *, U32 *, U32 *,U32);
U32 NN_Sub (U32 *, U32 *, U32 *,U32);
void NN_Mod(U32 *, U32 *, U32, U32 *, U32);
void NN_Div(U32 *, U32 *, U32 *, U32, U32 *, U32);
U32 NN_Digits(U32 *, U32);
U32 NN_DigitBits(U32);
void NN_AssignZero(U32 *, U32);
U32 NN_LShift(U32 *, U32 *, U32, U32);
void NN_DigitDiv(U32 *, U32 [2], U32);
U32 NN_SubDigitMult(U32 *, U32 *, U32, U32 *, U32);
void NN_DigitMult(U32 [2], U32, U32);
int NN_Gcd (U32 *, U32 *,U32 digits);












