// +FHDR -----------------------------------------------------------------------
// Copyright (c) 2009, Hongsi.
// Hongsi Confidential Proprietary
// 20096/07/21 
//
// -----------------------------------------------------------------------------
// File Name: init_int.c
// Type: C Language 
//
// -----------------------------------------------------------------------------
// Description:
// This code is a function for Interrupt Vector Initialization.
//
// -----------------------------------------------------------------------------
// Detailed Func Description:
// 1. Interrupt Vector Initialization Function.
// 
// -----------------------------------------------------------------------------
// Revision History
// DATE         AUTHOR          DESCRIPTION
// 2009/07/21 			V1.0
// -FHDR -----------------------------------------------------------------------


// ---------------------------------------------------------------------  
// Variables Declarations 
// ---------------------------------------------------------------------  
// r2 : 1st arg of Fnuction;
// r3 : 2st arg of Fnuction;
// r4 : 3st arg of Fnuction;
// r5 : 4st arg of Fnuction;
#include "interrupt.h"
#include "Hs32u2.h"

#include "HAL_USB.h"
#include "Global_Var.h"

void request_init()
{
	void isr_uart_IRQ();
	
	// ---------------------------------------------------------------------  
	// Initializes the INTC module
	// ---------------------------------------------------------------------  
	Disable_Interrupts;
	//Clear_VBR;
	INTC_ISCR = 0x00000000;
	INTC_NIER |= 0x00000004;
	INTC_PLSR4_7 = 0x00000200;

	// Set uart Interrupt
	Init_Int(0x807c00,0x807e00,isr_uart_IRQ,34);

	Enable_Interrupts;
}

#pragma interrupt on
void isr_uart_IRQ()
{

	return;
}

#pragma interrupt off

void Timer_init()
{
	void isr_timer_IRQ();
	
	Disable_Interrupts;

	PIT1_PCSR = 0x0f12; 			//PIT ferquency divider & mode
	// Initializes the INTC module
	INTC_ISCR = 0x00000000; 		//Initialize control register
	INTC_NIER |= 0x00000002;		//Enable interrupu level 2 (bit2 = 1)
	INTC_PLSR32_35 = 0x01000000;	//PIT1 interrupt at int32, level = 2
	
	// Set uart Interrupt
	Init_Int(0x807c00,0x807e00,isr_timer_IRQ,33);

	Enable_Interrupts;
}

#pragma interrupt on
void isr_timer_IRQ()
{	
	//Disable_Interrupts;
	
	PIT1_PCSR &=~0x0009; //PIT disable		
	//MID_DISP_SmallPic(SMALLPIC_ZHONGGUOYINLIAN);
	g_refresh = 1;
	//Enable_Interrupts;
	return;
}
#pragma interrupt off

void Timer_Enable(unsigned short timer)
{
	PIT1_PMR = timer; //Timer counter value

	// Enable Interrupt
	PIT1_PCSR |=0x0009; //PIT enabled		
}
void Timer_Disable(void)
{
	PIT1_PCSR &=~0x0009;	
}
