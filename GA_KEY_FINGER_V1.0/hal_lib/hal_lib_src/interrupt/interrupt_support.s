// +FHDR -----------------------------------------------------------------------
// Copyright (c) 2009, Beijing Hongsi Electronic Technology Co., Ltd.
// HSEC Confidential Proprietary
// 2009/08/12
//
// HSEC is a trademark of Beijing Hongsi Electronic Technology Co., Ltd.
// -----------------------------------------------------------------------------
// File Name: interrupt_support.s
// Type: C Language 
//
// -----------------------------------------------------------------------------
// Description:
// This code is a sample for HS32U2 interrupt support
//
// -----------------------------------------------------------------------------
// Background Description:
// 
// -----------------------------------------------------------------------------
// Revision History
// DATE         AUTHOR          DESCRIPTION
// 2009/08/12 	Liu Yong		V1.0
// -FHDR -----------------------------------------------------------------------

    .file   "interrupt_support.s"
    .text
######################################################################
# Control register read routines
######################################################################
    .export Read_PSR, Read_VBR

Read_PSR:
    mfcr    r2,cr0
    rts

Read_VBR:
    mfcr    r2,cr1
    rts

######################################################################
# Control register write routines
######################################################################
    .export Write_PSR, Write_VBR

Write_PSR:
    mtcr    r2,cr0
    rts

Write_VBR:
    mtcr    r2,cr1
    rts

##########################################################################
# Disable_Ints function (disables interrupts by clearing PSR.IE and PSR.FE
##########################################################################
    .export Disable_Ints
Disable_Ints:
    mfcr    r1, cr0		# get PSR
    bclri   r1, 0x4		# disable fast interrupts
    bclri   r1, 0x6		# disable normal interrupts
    mtcr    r1, cr0		# make it so by stashing it back into PSR
    jmp     r15

##########################################################################
# Enable_Ints function (enables interrupts by setting PSR.IE and PSR.FE
##########################################################################
    .export Enable_Ints
Enable_Ints:
    mfcr    r1, cr0		# get PSR	
    bseti   r1, 0x4		# enable fast interrupts
    bseti   r1, 0x6		# enable normal interrupts
    mtcr    r1, cr0		# put changes back into PSR
    jmp     r15

##########################################################################
# Set_Alternate_Stack function (plug memory address into alt SP)
##########################################################################
	.export Set_Alternate_Stack
Set_Alternate_Stack:
	mtcr	r2, cr6		# move address from function argument into SS0
	mfcr	r3, cr0		# get PSR
	bseti	r3, 1		# set AF bit to use alternate registers
	mtcr	r3, cr0		# put PSR back
	mfcr	r0, cr6		# copy address into alternate SP
	mfcr	r3, cr0		# get PSR back
	bclri	r3, 1		# clear AF bit to use normal registers
	mtcr	r3, cr0		# put back into PSR
	jmp		r15			# return

