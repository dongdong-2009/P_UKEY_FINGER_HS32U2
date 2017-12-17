/*------------------------------------------------------------------------------*

	main.c
	
	MCORE EABI C Project Stationery using the Debugger Channel for I/O.
	
 *------------------------------------------------------------------------------*/

#include "hs32u2.h"
#include "interrupt.h"
#include "cgu.h"
#include "usb.h"
#include "usb_mass.h"
#include "app_cmd.h"
#include "xFA_SDK.h"


unsigned char g_reboot,g_led_flag;

void Chip_Reset(unsigned char flag)
{
	unsigned int i;

	unsigned char buf[16];

	if(flag==1)
	{
		buf[0] = 0xff;
		WriteFlash(buf, 0x00004003, 1);
	}
		
	for(i=0x50000;i>0;i--){};
	USB_POWER = 0x00;
	RCR = 0x80;
	return;
}

void clock_setup(unsigned int clock_parameter)
{
    CGCR = clock_parameter;
    while(!(MCSCR & 0x00010000)) CGCR = clock_parameter;
	
    while(CGCR != clock_parameter)
    {
        CGCR = clock_parameter;
        while(!(MCSCR & 0x00010000));
    } 
}

void interrupt_config(void)
{
    Disable_Interrupts;
	//Clear_VBR;
	INTC_ISCR = 0x00000000;
	INTC_NIER |= 0x00000002;			//设定有效的中断优先级为1、2、3	
	INTC_PLSR36_39 = 0x00000001;		//USB中断优先级设为1
	
	// Set USB Interrupt
	Init_Int(0x807c00, 0x807e00, usb_IrqHandle, 33);	

	Enable_Interrupts;
}
void GVAR_Init(void)
{
//	G_UMS = 0;	
}
void main()
{
	unsigned int timer;
	unsigned short ret;
	
	clock_setup(CLOCK_X16_3 | OSC_CLOSE);
	
	MCSCR = USB_FIFO_ON | USBI_ON | SM1_ON |SSF33_ON| HSPI_ON|PK_ECC_ON|DMAC_ON;  //打开HSPI的时钟
	
	HAL_Flash_Interface_Init();

//	HAL_UART_Init();
//	UART_printf("test key\r\n");

	hal_alg_init();

	interrupt_config();
	HAL_USB_Init();
	xFA_Init();
	cos_init(0);		
	
	//LED灯控制
	SPIPORT &= ~0x08;//设置输出
	SPIDDR|=0x08;

	g_reboot=0;
	g_led_flag=1;
	timer=0x50000;

	while(1)
	{	
		if(G_UMS)
		{
			Mass_Storage_Out();
			G_UMS = 0;
		}
//		if(G_CMD)
//		{
//			Command();
//			G_CMD=0;
//		}
		if(g_reboot==2)
		{
			Chip_Reset(1);
		}
		if(g_reboot==4)
		{
			Chip_Reset(0);
		}
		if(g_led_flag==0)
		{
			timer--;
			if(timer==0)
			{
				timer=0x50000;
				g_led_flag=1;
				SPIDDR|=0x08;
			}
		}
		
			
	}

}


