// +FHDR -----------------------------------------------------------------------
// Copyright (c) 2009, Hongsi.
// Hongsi Confidential Proprietary
// 2009/7/15
//
// -----------------------------------------------------------------------------
// File Name: cgu.h
// Type: C Language 
//
// -----------------------------------------------------------------------------
// Header:
// This header file is definitions for CGU Function of HS32U2.
//
// -----------------------------------------------------------------------------
// Detailed Func Description:
// 1. Data Type Definitions.
// 2. Register Definitions.
// 3. Constant Definitions.
//
// -----------------------------------------------------------------------------
// Revision History
// DATE         AUTHOR          DESCRIPTION
// 2009/7/15 					V1.0
// -FHDR -----------------------------------------------------------------------

// ---------------------------------------------------------------------  
// Type Definitions 
// ---------------------------------------------------------------------  

typedef unsigned int U32;
typedef unsigned short U16;
typedef unsigned char U8;

// ---------------------------------------------------------------------  
// Register Definitions
// ---------------------------------------------------------------------

#define CGCR   		(* (volatile unsigned int * )0x00c30000)
#define MCSCR    	(* (volatile unsigned int * )0x00c30004) 

// ---------------------------------------------------------------------  
// Constant Definitions 
// ---------------------------------------------------------------------  
// 1. Clock Frequency Multiplier
// ---------------------------------------------------------------------  

#define CLOCK_OUT 	0x00000001
#define OSC_CLOSE	0x00000008

// for input clock <= 12 MHz
#define CLOCK_X1 	0x03190016
#define CLOCK_X2 	0x07190016
#define CLOCK_X8_3	0x0f290016		// 12 * 8/3 = 32MHz
#define CLOCK_X3 	0x0b190016
#define CLOCK_X7_2 	0x0d190016		// 12 * 7/2 = 42MHz
#define CLOCK_X4 	0x0f190016
#define CLOCK_X5 	0x13190016
#define CLOCK_X16_3	0x1f290016		// 12 * 16/3 = 64MHz
#define CLOCK_X6	0x17190016
#define CLOCK_X20_3	0x33290016		// 12 * 20/3 = 80MHz
#define CLOCK_X7	0x1b190016

// for input clock <= 8 MHz
#define CLOCK_X8	0x1f190016
#define CLOCK_X9	0x31190016
#define CLOCK_X10	0x33190016

// for input clock <= 6 MHz
#define CLOCK_X11	0x35190016
#define CLOCK_X12	0x37190016
#define CLOCK_X13	0x39190016
#define CLOCK_X14	0x3b190016

// for input clock <= 4 MH
#define CLOCK_X15	0x3d190016
#define CLOCK_X16	0x3f190016
#define CLOCK_X18	0x57190016
#define CLOCK_X20	0x73190016
#define CLOCK_X21	0x75190016

// ---------------------------------------------------------------------  
// 2. Module Clock Switch
// ---------------------------------------------------------------------  
// for settings of MCSCR

#define USB_FIFO_ON	0x00008000
#define BECCM_ON	0x00004000
#define HSPI_ON		0x00002000
#define USBI_ON		0x00000800
#define SCI_ON		0x00000400
#define PIT1_ON		0x00000200
#define PIT2_ON		0x00000100
#define WDT_ON		0x00000080
#define DMAC_ON		0x00000040
#define HAE_ON		0x00000020
#define SHA_ON		0x00000020
#define FAE_ON		0x00000010
#define SSF33_ON	0x00000010
#define CAE_ON		0x00000008
#define SM1_ON		0x00000008
#define DAE_ON		0x00000004
#define DES_ON		0x00000004
#define AAE_ON		0x00000002
#define AES_ON		0x00000002
#define REAE_ON		0x00000001
#define PK_RSA_ON	0x00000001
#define PK_ECC_ON	0x00000001
#define CLOSE_ALL	0x00000000


