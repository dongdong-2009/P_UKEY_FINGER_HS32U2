// +FHDR -----------------------------------------------------------------------
// Copyright (c) 2008, Hongsi.
// Hongsi Confidential Proprietary
// 2009/07/17 
//
// -----------------------------------------------------------------------------
// File Name: flash_func.c
// Type: C Language 
//
// -----------------------------------------------------------------------------
// Description:
// This code is Write data and Read data with Flash.
//
// -----------------------------------------------------------------------------
// Detailed Func Description:
// 1. Initialize Flash Function
// 2. Read Data by Byte Function
// 3. Write Data by Byte Function
// 4. Write Data without Page Erase Function
// 5. Page Erase Function
//
// Note:
// Write FLASH functions in this file are universal to fit unligned address and 
// the data ont in DWORD format.
//
// You can write your own code for faster performances if you write whole FLASH
// pages or DWORD aligned data by calling Write routain directly.
// -----------------------------------------------------------------------------
// Revision History
// DATE         AUTHOR          DESCRIPTION
// 2009/07/17  			        V1.0
// -FHDR -----------------------------------------------------------------------
 
// ---------------------------------------------------------------------  
// Include File Declarations 
// ---------------------------------------------------------------------  

#include "flash.h"
#include "interrupt.h"

// ---------------------------------------------------------------------  
// Element Function Declarations 
// --------------------------------------------------------------------- 

U32 sram_erase[20];
U32 sram_write[15];

void (*Write)(unsigned int *, unsigned int);
void (*Erase)(U32 *faddr);

// ---------------------------------------------------------------------  
// User Function Declarations 
// ---------------------------------------------------------------------  

// ---------------------------------------------------------------------  
// Func : InitFlash()
// Description : Control Flash Operation. (Faster Reading)
// ---------------------------------------------------------------------  
// Input
// No
//-----------------------------------------------------------------
// Output
// No
// ---------------------------------------------------------------------  

	
void InitFlash(void)
{
	// for system clock lower than 40 MHz
	//EFMCR=0x00000201;
	
	// lift the flash operation code into ram

	memcpy(sram_erase, Erasescode, 70);
	memcpy(sram_write, Writescode, 50);
	
	Erase = (void (*)(U32 *))sram_erase;
	Write = (void (*)(U32 *, U32))sram_write;	
		 	
}

// ---------------------------------------------------------------------  
// Func : ReadFlash()
// Description : Read Flash by Byte
// ---------------------------------------------------------------------  
// Input
// addr : read start address
// length : read data length by Byte
//-----------------------------------------------------------------
// Output
// buffer : output data 
// ---------------------------------------------------------------------  

void ReadFlash(U8 *buffer, U32 addr, U32 length)
{
	register U32 i;
	
	for(i=0;i<length;i++)
	{
		*(buffer+i)=(*(U8 *)(addr+i));
	}
	
}

// ---------------------------------------------------------------------  
// Func : WriteFlash()
// Description : Write Flash by Byte with Page Erase. Page span is 
// allowed. The most length for one call is 2048 bytes.
// ---------------------------------------------------------------------  
// Input
// buffer : data to be written 
// addr : write start address
// length : write data length
//-----------------------------------------------------------------
// Output
// No
// ---------------------------------------------------------------------  


void WriteFlash(unsigned char *data_buf, unsigned int addr, unsigned int len)
{
	U32 addr_start,addr_end;
	// the following addresses are DWORD aligned
	U32 head_page_addr,tail_page_addr, head_page_offset;
	// page buffer
    U32 mem[512];
    // a pointer
	U8 *memtp;	
	
	register U32 i, j;
	 
	U32 n, flash_addr, data_length, data_offset;
	
	Disable_Interrupts;
	
	data_length = len;
	
	// the two addesses define an area of new DWORD
	// in this area no FLASH data need to copy in
	
	// start address aligned forward
	// |    |    | XX | XX | XX | XX | XX | XX |
	//                 --->
	// |    |    | xx | xx |      XXXXXXXX     | 
	addr_start = (addr + 0x3) & 0x3FFFC;
	
	// end address aligned backward
	// | XX | XX | XX | XX | XX | XX |    |    | 
	//                      <---
	// |      XXXXXXXX     | xx | xx |    |    | 
	addr_end = (addr + len - 1) & 0x3FFFC;
	
	// page address to determine spaces to be erased
	head_page_addr = addr & 0x3F800;
	tail_page_addr = addr_end & 0x3F800;
	
	// relative address to the head page of the new data start point
	head_page_offset = addr & 0x07FF;
	
	if(head_page_addr == tail_page_addr)     // within 1 page
	{
		// copy FLASH data in the page before the new DWORD area
		flash_addr = head_page_addr;
		n = (addr_start - flash_addr) >> 2;
		
		for(i = 0; i < n; i ++,	flash_addr +=4)
		{
			mem[i] = *(unsigned int *)flash_addr;
		}
		
		// copy FLASH data int the page after new DWORD area
		flash_addr = addr_end;
		n = ((addr_end & 0x7fc)>>2);
		for(i = n; i < 512; i ++,	flash_addr +=4)
		{
			mem[i] = *(unsigned int *)flash_addr;
		}
		
		// write new data into page buffer, maybe overwrite some FLASH bytes
		memtp = (unsigned char *)(mem) + head_page_offset;
	
		for(i = 0; i < len; i++)
		{
			*(memtp + i) = *(data_buf + i);
		}
		
		// erase one FLASH page
		Erase((unsigned int *)head_page_addr);
		
		// write the data in page buffer into one FLASH page
		for(i = 0; i < 512; i++)
		{
			if(mem[i] ^ 0xffffffff) Write((unsigned int *)head_page_addr + i, mem[i]);
		}
	}
	else         // span pages (in 2 pages)
	{	
		// copy FLASH data in the 1st page before the new DWORD area
		flash_addr = head_page_addr;
		n = (addr_start - head_page_addr) >> 2;
		
		for(i = 0; i < n; i ++, flash_addr += 4)
		{
			mem[i] = *(unsigned int *)flash_addr;
		}
		
		// write new data in the 1st page to the page buffer
		memtp = (unsigned char *)(mem)+ head_page_offset;
		n = tail_page_addr - addr;
		// number of the remained bytes for the page 2
		data_length -= n;			
		data_offset = n;
		
		// write new bytes in the page 1
		for(i = 0; i < n; i++)
		{
			*(memtp + i) = *(data_buf + i);
		}
		
		// erase one flash page
		Erase((unsigned int *)addr_start);
		
		// write page buffer into the page 1
		for(i = 0; i < 512; i++)
		{
			if(mem[i] ^ 0xffffffff) Write((unsigned int *)head_page_addr + i, mem[i]);
		}
		
		// copy flash data to be reserved in the page 2
		flash_addr = addr_end;
		n = ((addr_end & 0x7fc)>>2);
		for(i = n; i < 512; i ++,	flash_addr +=4)
		{
			mem[i] = *(unsigned int *)flash_addr;
		}
		
		// write new bytes into the page buffer
		memtp = (unsigned char *)mem;
		
		for(i = 0, j = data_offset; i < data_length; i++, j++)
		{
			*(memtp + i) = *(data_buf + j);
		}	
		
		// erase the 2nd page
		Erase((unsigned int *)addr_end);
		
		// write the 2nd page
		for(i = 0; i < 512; i++)
		{
			if(mem[i] ^ 0xffffffff) Write((unsigned int *)tail_page_addr + i, mem[i]);
		}		
	}
	
	Enable_Interrupts;
	
}
// ---------------------------------------------------------------------  
// Func : WriteFlashOnly()
// Description : Write Flash by Byte without Page Erase in one Page.
// ---------------------------------------------------------------------  
// Input
// buffer : data to be written 
// addr : write start address
// length : write data length
//-----------------------------------------------------------------
// Output
// No
// ---------------------------------------------------------------------  

void WriteFlashOnly(unsigned char *data_buf, unsigned int addr, unsigned int len)
{
	unsigned int addr_offset;
	unsigned int addr_start;
	unsigned int addr_end;
	
	// the buffer only for 2048 bytes
    U32 mem[512];
    
    // a byte typt pointer
	unsigned char *memtp;
	
	unsigned int i, n;
	
	Disable_Interrupts;
	
	// get unaligned offset of the memory address
	addr_offset = addr & 0x3;
	
	// address ends
	addr_start = addr & 0x3FFFC;
	addr_end = (addr + len - 1) & 0x3FFFC;
	
	// get exsting bytes for aligning
	mem[0] = *(unsigned int *)addr_start;
	
	mem[(addr_end - addr_start) >> 2] = *(unsigned int *)addr_end;
	
	memtp = (unsigned char *)mem;
	for(i = 0; i < len; i++)
	{
		*(memtp + addr_offset + i) = *(data_buf + i);
	}
	
	n = (addr_end - addr_start) >> 2;
	
	for(i = 0; i <= n; i++)
	{
		Write((unsigned int *)addr_start + i, mem[i]);
	}
	
	Enable_Interrupts;
}

// ---------------------------------------------------------------------  
// Func : PageeraseFlash()
// Description : Erase Flash for 2048 bytes
// ---------------------------------------------------------------------  
// Input
// addr : start address for page
//-----------------------------------------------------------------
// Output
// No 
// ---------------------------------------------------------------------  

void PageEraseFlash(U32 addr)
{
	U32 *page_address;
	
	Disable_Interrupts;
	
	page_address = (U32 *)(addr & 0x3f800);
    Erase(page_address);
    
    Enable_Interrupts;		
}

void writeonebyte(unsigned int addr,unsigned char status)
{
	unsigned int addr1,temp,temp1=0xffffffff;
	unsigned char i,offset;

	temp=*(unsigned int*)(addr & 0x0003fffc);
	addr1=addr & 0x0003fffc;
	
	offset=addr&0x03;
	offset=3-offset;
	temp1&=status;
	temp1|=0xffffff00;
	for(i=0;i<offset*8;i++)
	{
		temp1=(temp1<<1)|0x01;
	}
	temp&=temp1;
	Write((unsigned int*)addr1,temp);
	
}

