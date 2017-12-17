// +FHDR -----------------------------------------------------------------------
// Copyright (c) 2009, Hongsi.
// Hongsi Confidential Proprietary
// 2009/7/15
//
// -----------------------------------------------------------------------------
// File Name:interrupt.h
// Type: C Language 
//
// -----------------------------------------------------------------------------
// Header:
// This header file is definitions for Interrupt Controller.
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

/*=============================================================*/

/* Bit positions and macros common to both boards            */

/*=============================================================*/

//------------------------------------------------------
// INTC
#define INTC_ISCR        (*(unsigned int *)(0x00c50000))   
#define INTC_NIER        (*(unsigned int *)(0x00c50010))   
#define INTC_PLSR32_35   (*(unsigned int *)(0x00c50060))
#define INTC_PLSR4_7   	 (*(unsigned int *)(0x00c50044))  
#define INTC_PLSR36_39   (*(unsigned int *)(0x00c50064))   

//------------------------------------------------------
// PIT1
#define PIT1_PCSR       (*(unsigned short *)(0x00c80000))  
#define PIT1_PMR        (*(unsigned short *)(0x00c80002))  


/* Bit names for general use */

#define bit31    0x80000000

#define bit30    0x40000000

#define bit29    0x20000000

#define bit28    0x10000000

#define bit27    0x08000000

#define bit26    0x04000000

#define bit25    0x02000000

#define bit24    0x01000000

#define bit23    0x00800000

#define bit22    0x00400000

#define bit21    0x00200000

#define bit20    0x00100000

#define bit19    0x00080000

#define bit18    0x00040000

#define bit17    0x00020000

#define bit16    0x00010000

#define bit15    0x00008000

#define bit14    0x00004000

#define bit13    0x00002000

#define bit12    0x00001000

#define bit11    0x00000800

#define bit10    0x00000400

#define bit09    0x00000200

#define bit08    0x00000100

#define bit07    0x00000080

#define bit06    0x00000040

#define bit05    0x00000020

#define bit04    0x00000010

#define bit03    0x00000008

#define bit02    0x00000004

#define bit01    0x00000002

#define bit00    0x00000001

/* Processor Status Register (PSR) bits */

#define PSR_S    bit31        /* Supervisor/user mode. 1 = supervisor */

#define PSR_SP    bit29+bit28    /* Spare bits - write 0 */

#define U3    bit27        /* Hardware Accelerator Control bits */

#define U2    bit26

#define U1    bit25

#define U0    bit24

/* Vector number */

#define PSR_VEC bit22+bit21+bit20+bit19+bit18+bit17+bit16

#define TM    bit15+bit14    /* Trace mode bits */

#define TP    bit13        /* Trace pending */

#define TCTL    bit12     /* Translation control bit for external mem */

#define SC    bit10        /* Spare Control */

#define MM    bit09        /* Misalignment Exception Mask */

#define EE    bit08        /* Exception Enable */

#define IC    bit07        /* Interrupt Control */

#define IE    bit06        /* Interrupt Enable */

#define FE    bit04        /* Fast Interrupt Enable */

#define AF    bit01        /* Alternate File Enable */

#define C    bit00        /* Condition Control/Carry bit */

/* Macros and functions for controlling interrupts */

extern void Write_PSR(unsigned long);

extern unsigned long Read_PSR(void);

#define Enable_Interrupts    Write_PSR(Read_PSR() | EE | IE | FE )

#define Clear_VBR	Write_VBR(Read_VBR() & 0)

#define Disable_Interrupts    Write_PSR(Read_PSR() & ~EE & ~IE & ~FE )

