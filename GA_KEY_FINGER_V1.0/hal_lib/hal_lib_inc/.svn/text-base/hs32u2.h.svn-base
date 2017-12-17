// +FHDR -----------------------------------------------------------------------
// Copyright (c) 2009, Hongsi.
// Hongsi Confidential Proprietary
// 2009/071/17 
//
// -----------------------------------------------------------------------------
// File Name: ssx14.h
// Type: C Language 
//
// -----------------------------------------------------------------------------
// Header:
// This header file is various definition for HS32U2.
//
// -----------------------------------------------------------------------------
// Detailed Func Description:
// 1. Register Definitions.
// 2. Constant Definitions.
// 3. Function Declarations.
//
// -----------------------------------------------------------------------------
// Revision History
// DATE         AUTHOR          DESCRIPTION
// 2009/07/17 			V1.0
// -FHDR -----------------------------------------------------------------------

#define SCI_BASE	    0x00cc0000
#define SCIBDH          (*(volatile unsigned  short *)(SCI_BASE+0x0000))
#define SCIBDL          (*(volatile unsigned  char *)(SCI_BASE+0x0001))
#define SCICR1          (*(volatile unsigned  short *)(SCI_BASE+0x0002))
#define SCICR2          (*(volatile unsigned  char *)(SCI_BASE+0x0003))
#define SCISR1          (*(volatile unsigned  char *)(SCI_BASE+0x0004))
#define SCISR2          (*(volatile unsigned  char *)(SCI_BASE+0x0005))
#define SCIDRH          (*(volatile unsigned  short *)(SCI_BASE+0x0006))
#define SCIDRL          (*(volatile unsigned  char *)(SCI_BASE+0x0007))
#define SCIPURD         (*(volatile unsigned  char *)(SCI_BASE+0x0008))
#define SCIPORT         (*(volatile unsigned  char *)(SCI_BASE+0x0009))
#define SCIDDR          (*(volatile unsigned  char *)(SCI_BASE+0x000A))
#define SCIRESERV0B     (*(volatile unsigned  char *)(SCI_BASE+0x000B))


#define SPIPORT		(* (volatile unsigned char * )0x00cb0007)
#define SPIDDR		(* (volatile unsigned char * )0x00cb0008)
#define RCR   (*(unsigned char *)0x00c40000)

#pragma once
 
// ---------------------------------------------------------------------  
// Register Definitions
// ---------------------------------------------------------------------  


// ---------------------------------------------------------------------  
// Function Declarations
// ---------------------------------------------------------------------  

//------------------------------------------------------
// FLASH : Write and Read Flash Memory
void flash();

//------------------------------------------------------
// SSF33 : Encrypt and Decrypt with 128 bits
void ssf33();

//------------------------------------------------------
// DES : Encrypt and Decrypt with 64 bits
void des();

//------------------------------------------------------
// TRNG : True Raandom Number Generator
void trng();

//------------------------------------------------------
// RSA : Encrypt and Decrypt with 1024 bits
void rsa();

//------------------------------------------------------
// USB : USB Transfer
void usb();





   


