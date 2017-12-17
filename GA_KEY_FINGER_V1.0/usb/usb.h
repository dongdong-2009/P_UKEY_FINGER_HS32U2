#ifndef __HAL_USB_H
#define __HAL_USB_H

#include "cgu.h"
#include "Hs32u2.h"
#include "usb_data.h"

// Common USB registers
#define USB_FADDR (*(volatile unsigned char *)0x00900000)
#define USB_POWER (*(volatile unsigned char *)0x00900001)
#define USB_INTRTX (*(volatile unsigned short *)0x00900002)
#define USB_INTRRX (*(volatile unsigned short *)0x00900004)
#define USB_INTRTXE (*(volatile unsigned short *)0x00900006)
#define USB_INTRRXE (*(volatile unsigned short *)0x00900008)
#define USB_INTRUSB (*(volatile unsigned char *)0x0090000A)
#define USB_INTRUSBE (*(volatile unsigned char *)0x0090000B)
#define USB_FRAME (*(volatile unsigned short *)0x0090000C)
#define USB_INDEX (*(volatile unsigned char *)0x0090000E)

// Indexed registers - Peripheral mode
#define USB_CSR0 (*(volatile unsigned short *)0x00900012)
#define USB_COUNT0 (*(volatile unsigned char *)0x00900018)

#define USB_TXMAXP (*(volatile unsigned short *)0x00900010)
#define USB_TXCSR (*(volatile unsigned short *)0x00900012)
#define USB_RXMAXP (*(volatile unsigned short *)0x00900014)
#define USB_RXCSR (*(volatile unsigned short *)0x00900016)
#define USB_RXCOUNT (*(volatile unsigned short *)0x00900018)

// FIFOs
#define USB_EP0_FIFO_8 (*(volatile unsigned char *)0x00900020)
#define USB_EP0_FIFO_16 (*(volatile unsigned short *)0x00900020)
#define USB_EP0_FIFO_32 (*(volatile unsigned int *)0x00900020)

#define USB_EP1_FIFO_8 (*(volatile unsigned char *)0x00900024)
#define USB_EP1_FIFO_16 (*(volatile unsigned short *)0x00900024)
#define USB_EP1_FIFO_32 (*(volatile unsigned int *)0x00900024)

#define USB_EP2_FIFO_8 (*(volatile unsigned char *)0x00900028)
#define USB_EP2_FIFO_16 (*(volatile unsigned short *)0x00900028)
#define USB_EP2_FIFO_32 (*(volatile unsigned int *)0x00900028)

#define USB_EP3_FIFO_8 (*(volatile unsigned char *)0x0090002C)
#define USB_EP3_FIFO_16 (*(volatile unsigned short *)0x0090002C)
#define USB_EP3_FIFO_32 (*(volatile unsigned int *)0x0090002C)

#define USB_EP4_FIFO_8 (*(volatile unsigned char *)0x00900030)
#define USB_EP4_FIFO_16 (*(volatile unsigned short *)0x00900030)
#define USB_EP4_FIFO_32 (*(volatile unsigned int *)0x00900030)


// USBI extern registers	
#define USBICR (*(volatile unsigned int *)0x00900400)

// DYNAMIC FIFO SIZING
#define USB_TxFIFOsz (*(volatile unsigned char *)0x00900062)
#define USB_RxFIFOsz (*(volatile unsigned char *)0x00900063)
#define USB_TxFIFOadd (*(volatile unsigned short *)0x00900064)
#define USB_RxFIFOadd (*(volatile unsigned short *)0x00900066)

#define	USB_RECEIVE_FIFO	0x00900024
#define	USB_SEND_FIFO		0x00900028
#define 	DMA_SAR_ADDR		0x00D10000
#define 	DMA_DAR_ADDR		0x00D10004
#define 	DMA_TCR_ADDR		0x00D10008
#define 	DMA_DCSR_ADDR		0x00D1000C
#define 	USB_INDEX_ADDR		0x0090000E
#define 	USB_TXCSR_ADDR		0x00900012
#define 	USB_RXCSR_ADDR		0x00900016
#define	USB_RXCOUNT_ADDR	0x00900018

#define DMA_SAR (*(volatile unsigned int *)0x00D10000)
#define DMA_DAR (*(volatile unsigned int *)0x00D10004)
#define DMA_TCR (*(volatile unsigned int *)0x00D10008)
#define DMA_DCSR (*(volatile unsigned int *)0x00D1000C)

#define EP0_INTR 0x0100
#define EP1_INTR 0x0200
#define EP2_INTR 0x0400
#define EP3_INTR 0x0800
#define EP4_INTR 0x1000

#define USB_EP0_SIZE 		64
#define BULK_BUF_MAXLEN     0x200

#define DSCR_DEVICE         1   // Descriptor type: Device  //
#define DSCR_CONFIG         2   // Descriptor type: Configuration
#define DSCR_STRING         3   // Descriptor type: String
#define DSCR_INTRFC         4   // Descriptor type: Interface
#define DSCR_ENDPNT         5   // Descriptor type: Endpoint
#define DSCR_QUALIFIER		6


#define SETUP_MASK					0x60	//Used to mask off request type
#define SETUP_STANDARD_REQUEST	0		//Standard Request
#define SETUP_CLASS_REQUEST		0x20	//Class Request
#define SETUP_VENDOR_REQUEST		0x40	//Vendor Request
#define SETUP_RESERVED_REQUEST 	0x60	//Reserved or illegal request
#define SC_MASS_STORAGE_RESET   0xff
#define SC_GET_MAX_LUN          0xfe

#define VENDORREQ_READ 			0xf1
#define VENDORREQ_WRITE 			0xf0
#define USBS_DATA_READY  			1
#define USBS_NONE        				2
#define USBS_RECEIVING  				3
#define USBS_RECEIVED    			4
#define USBS_BUSY        				5

#define SETUP_TYPE_VENDOROUT 	0x40
#define VENDORREQ_RESET		0xf2
#define SETUP_TYPE_VENDORIN 	0xc0
#define SETUP_TYPE_CLASS     	0x20

#define USB_DEVICE_DESCRIPTOR_TYPE		0x01
#define USB_CONFIGURATION_DESCRIPTOR_TYPE	0x02
#define USB_STRING_DESCRIPTOR_TYPE		0x03
#define USB_INTERFACE_DESCRIPTOR_TYPE		0x04
#define USB_ENDPOINT_DESCRIPTOR_TYPE		0x05
#define USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE	0x06
#define USB_OTHER_SPEED_CONFIGURATION_DESCRIPTOR_TYPE	0x07
#define USB_INTERFACE_POWER_DESCRIPTOR_TYPE	0x08


#define SIZ_DEVICE_DESC                18
#define SIZ_CONFIG_DESC           	  116
#define SIZ_CONFIG2_DESC		   32 
#define SIZ_REPORT_DESC                39
#define SIZ_STRING_LANGID              4
#define SIZ_STRING_VENDOR            8
#define SIZ_STRING_PRODUCT           24 
#define SIZ_STRING_SERIAL           10

typedef struct _device_request
{
	unsigned char bmRequestType;
	unsigned char bRequest;
	unsigned short wValue;
	unsigned short wIndex;
	unsigned short wLength;
} DEVICE_REQUEST; 

#define  	COMMUNICATION_BUF_LEN	0xc00

//extern unsigned char g_b_MassComm[COMMUNICATION_BUF_LEN];
extern unsigned char *g_b_MassComm;
extern APDU g_APDU;

void usb_receive(unsigned char *data_buf, unsigned int len);
void HAL_USB_BulkOut(unsigned char Endpoint, unsigned char *pBuf, unsigned short *plen,unsigned char flag);
void HAL_USB_BulkIn(unsigned char Endpoint, unsigned char *pBuf, unsigned short len);
void usb_IrqHandle(void);	

void usb_ep1_stall(void);
void usb_ep2_stall(void);
void usb_ep3_stall(void);
void usb_ep4_stall(void);


#endif //__HAL_USB_H
