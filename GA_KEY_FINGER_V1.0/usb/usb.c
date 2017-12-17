#include "usb.h"
#include "usb_mass.h"

DEVICE_REQUEST g_req;

unsigned char status_ep1 = 0x00;
unsigned char status_ep2 = 0x00;
unsigned char status_ep3 = 0x00;
unsigned char status_ep4 = 0x00;
unsigned char status_ep1_int = 0x00;
unsigned char g_bIsConfiged=0;

extern unsigned char G_XFA_Data[];
//unsigned char g_b_MassComm[COMMUNICATION_BUF_LEN];
unsigned char *g_b_MassComm=G_XFA_Data;
APDU g_APDU;

const unsigned char DeviceDescriptor[SIZ_DEVICE_DESC] =//复合设备
  {
    0x12,                       /*bLength */
    USB_DEVICE_DESCRIPTOR_TYPE, /*bDescriptorType*/
    0x00,                       /*bcdUSB */
    0x02,
    0x00,                       /*bDeviceClass*/
    0x00,                       /*bDeviceSubClass*/
    0x00,                       /*bDeviceProtocol*/
    0x40,                       /*bMaxPacketSize40???????????????????????????????????????*/
    0x48,                       /*idVendor (0x8888)*/
    0x57,
    0x16,                       /*idProduct = 0x1010*/
    0x39,
    0x01,                       /*bcdDevice rel. 1.00*/
    0x00,
    0x01,                          /*Index of string descriptor describing
                                              manufacturer */
    0x02,                          /*Index of string descriptor describing
                                             product*/
    0x03,                          /*Index of string descriptor describing the
                                             device serial number */
    0x01                        /*bNumConfigurations*/
  };/* DeviceDescriptor */
const unsigned char ConfigDescriptor[] =	
  {
    0x09, /* bLength: Configuation Descriptor size */
    USB_CONFIGURATION_DESCRIPTOR_TYPE, /* bDescriptorType: Configuration */
    SIZ_CONFIG_DESC,
    /* wTotalLength: Bytes returned */
    0x00,
    0x02,         /*bNumInterfaces: 1 interface*/
    0x01,         /*bConfigurationValue: Configuration value*/
    0x00,         /*iConfiguration: Index of string descriptor describing
                                 the configuration*/
    0x80,         /*bmAttributes: 总线供电*/
    0x32,         /*MaxPower 400 mA: this current is used for detecting Vbus*/

   
	/******************** Descriptor of MASS STORGE ********************/
    /******************** Descriptor of Mass Storage interface ********************/
    /* 09 */
    0x09,   /* bLength: Interface Descriptor size */
    USB_INTERFACE_DESCRIPTOR_TYPE,   /* bDescriptorType: */
    /*      Interface descriptor type */
    0x00,   /* bInterfaceNumber: Number of Interface */
    0x00,   /* bAlternateSetting: Alternate setting */
    0x02,   /* bNumEndpoints*/
    0x08,   /* bInterfaceClass: MASS STORAGE Class */
    0x06,   /* bInterfaceSubClass : SCSI transparent*/
    0x50,   /* nInterfaceProtocol */
    0x05,   /* iInterface: */
    /* 18 */

    0x07,   /*Endpoint descriptor length = 7*/
    0x05,   /*Endpoint descriptor type */
    0x03,   /*Endpoint address (IN, address 4) */
    0x02,   /*Bulk endpoint type */
    0x40,   /*Maximum packet size (64 bytes) */
    0x00,
    0x00,   /*Polling interval in milliseconds */

    /* 25 */
    0x07,   /*Endpoint descriptor length = 7 */
    0x05,   /*Endpoint descriptor type */
    0x84,   /*Endpoint address (OUT, address 5) */
    0x02,   /*Bulk endpoint type */
    0x40,   /*Maximum packet size (64 bytes) */
	0x00,
	0x00 ,    /*Polling interval in milliseconds*/

   /************** Descriptor of interface ****************/
    /* 09 */
    0x09,         /*bLength: Interface Descriptor size*/
    USB_INTERFACE_DESCRIPTOR_TYPE,/*bDescriptorType: Interface descriptor type*/
    0x01,         /*bInterfaceNumber: Number of Interface*/
    0x00,         /*bAlternateSetting: Alternate setting*/
    0x03,         /*bNumEndpoints*/
    0x0b,// CCID           
    0x00,         /*bInterfaceSubClass : 1=BOOT, 0=no boot*/
    0x00,         /*nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse*/
    0x04,            /*iInterface: Index of string descriptor*/  //??????????
    /******************** Descriptor of CCID ********************/
    /* 18 */

    0x36,         /*bLength: HID Descriptor size*/
    0x21, /*bDescriptorType: CCID*/
    0x10,         /* release number */
    0x01,
    0x00,         /*bCountryCode: Hardware target country*/
    0x07,         /*bNumDescriptors: Number of  class descriptors to follow*/
   
   	0x03, 0x00, 0x00, 0x00, // protocol T=0	and T=1
   	0xfc, 0x0d, 0x00, 0x00, // clock 3.58M ???
   	0xfc, 0x0d, 0x00, 0x00, // max clock14.32M???
   	0x01,	// num clock  ???


	0x80, 0x25, 0x00, 0x00, // data rate 9600bps ???
   	0x00, 0xc2, 0x01, 0x00, // max data rate???
   	0x00, 	// num data rate???



	0x00, 0x02, 0x00, 0x00, // max FSD	Information Field Size for CCID T=1	 ???
//	0xbe, 0x04, 0x02, 0x00,


	0x07, 0x00, 0x00, 0x00, // synch protocol
	0x00, 0x00, 0x00, 0x00, // mechanical level

	0xbe, 0x04, 0x02, 0x00, // feature

	0x00, 0x02, 0x00, 0x00, // message length 261+10
	0xff,	// echo response
	0xff,	// envelope
	0x80, 0x40, // lcd support???
	0x01,		// pin support???
	0x01,		// busy slot???

    /******************** Descriptor of  in endpoint ********************/
    /* 27 */
    0x07,          /*bLength: Endpoint Descriptor size*/
    USB_ENDPOINT_DESCRIPTOR_TYPE, /*bDescriptorType:*/

    0x01,          /*bEndpointAddress: Endpoint Address (IN)*/

    0x02,          /*bmAttributes: Bulk endpoint type*/
    0x40,          /*wMaxPacketSize: 64 Byte max */
    0x00,
    0x00,          /*bInterval: Polling Interval (10 ms)*/
    /* 34 */
    /******************** Descriptor of out endpoint ********************/
    /* 27 */
    0x07,          /*bLength: Endpoint Descriptor size*/
    USB_ENDPOINT_DESCRIPTOR_TYPE, /*bDescriptorType:*/

    0x82,          /*bEndpointAddress: Endpoint Address (OUT)*/
    0x02,          /*bmAttributes: Bulk endpoint type*/
    0x40,          /*wMaxPacketSize: 64 Byte max */
    0x00,
    0x00,          /*bInterval: Polling Interval (10 ms)*/
    /* 34 */

	// IN endpoint	 //Interrupt-IN Endpoint ICC插拔卡中断
	0x07, // length
	0x05, // type
	0x81, // endpoint addr
	0x03, // attribute 
	0x08, // max packet	lo
	0x00, // max packet	hi
	0x01 // interval


  }; /* ConfigDescriptor */


/* USB Configuration Descriptor */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor */
const unsigned char ConfigDescriptor2[] =	
  {
    0x09, /* bLength: Configuation Descriptor size */
    USB_CONFIGURATION_DESCRIPTOR_TYPE, /* bDescriptorType: Configuration */
    SIZ_CONFIG2_DESC,
    /* wTotalLength: Bytes returned */
    0x00,
    0x01,         /*bNumInterfaces: 1 interface*/
    0x01,         /*bConfigurationValue: Configuration value*/
    0x00,         /*iConfiguration: Index of string descriptor describing
                                 the configuration*/
    0x80,         /*bmAttributes: 总线供电*/
    0x32,         /*MaxPower 400 mA: this current is used for detecting Vbus*/

   /************** Descriptor of interface ****************/
    /* 09 */
    0x09,   /* bLength: Interface Descriptor size */
    USB_INTERFACE_DESCRIPTOR_TYPE,   /* bDescriptorType: */
    /*      Interface descriptor type */
    0x00,   /* bInterfaceNumber: Number of Interface */
    0x00,   /* bAlternateSetting: Alternate setting */
    0x02,   /* bNumEndpoints*/
    0x08,   /* bInterfaceClass: MASS STORAGE Class */
    0x06,   /* bInterfaceSubClass : SCSI transparent*/
    0x50,   /* nInterfaceProtocol */
    0x00,   /* iInterface: */

    /******************** Descriptor of out endpoint ********************/
     0x07,   /*Endpoint descriptor length = 7*/
    0x05,   /*Endpoint descriptor type */
    0x01,   /*Endpoint address (IN, address 4) */
    0x02,   /*Bulk endpoint type */
    0x00,   /*Maximum packet size (64 bytes) */
    0x02,
    0x00,   /*Polling interval in milliseconds */

    /* 25 */
    0x07,   /*Endpoint descriptor length = 7 */
    0x05,   /*Endpoint descriptor type */
    0x82,   /*Endpoint address (OUT, address 5) */
    0x02,   /*Bulk endpoint type */
    0x00,   /*Maximum packet size (64 bytes) */
	0x02,
	0x00 ,    /*Polling interval in milliseconds*/


  }; /* ConfigDescriptor */


const unsigned char ReportDescriptor[SIZ_REPORT_DESC] =
  {	
    0x05, 0xFF,                    // USAGE_PAGE(User define)  
    0x09, 0xFF,                    // USAGE(User define)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x05, 0x01,                    // USAGE_PAGE(1)
    0x19, 0x00,                    //   USAGE_MINIMUM(0)
    0x29, 0xFF,                    //   USAGE_MAXIMUM(255)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0xFF,                    //   LOGICAL_MAXIMUM (255)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x95, 0x40,                    //   REPORT_COUNT (64)
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
    0x05, 0x02,                    // USAGE_PAGE(2)
    0x19, 0x00,                    //   USAGE_MINIMUM (0)
    0x29, 0xFF,                    //   USAGE_MAXIMUM (255)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0xFF,                    //   LOGICAL_MAXIMUM (255)
    0x95, 0x08,                    //   REPORT_COUNT (8)
    0x75, 0x40,                    //   REPORT_SIZE (64)
    0x91, 0x02,                    //   OUTPUT (Data,Var,Abs)
    0xc0                           // END_COLLECTION		
  }; /* ReportDescriptor */

/* USB String Descriptors (optional) */
const unsigned char StringLangID[SIZ_STRING_LANGID] =
  {
    SIZ_STRING_LANGID,
    USB_STRING_DESCRIPTOR_TYPE,
    0x09,
    0x04
  }; /* LangID = 0x0409: U.S. English */

const unsigned char StringVendor[SIZ_STRING_VENDOR] =
  {
    SIZ_STRING_VENDOR, 3,
    'C', 0, 
    'U', 0, 
    'P', 0
  };

const unsigned char StringProduct[SIZ_STRING_PRODUCT] =
  {
    SIZ_STRING_PRODUCT, 3, 
    'Z', 0,
    'H', 0, 
    'I', 0, 
    ' ', 0,
    'F', 0,
    'U', 0, 
    ' ', 0, 
    'T', 0,
    'O', 0,
    'N', 0,
    'G', 0
    };

const unsigned char StringSerial[SIZ_STRING_SERIAL] =
  {
    10,3,
    '1',0,
    '.',0,
    '0',0,
    '0',0
  };

const unsigned char DevQualifier[]=
{
	0x0a,
	DSCR_QUALIFIER,
	0x10,0x01,
	0x00,
	0x00,
	0x00,
	USB_EP0_SIZE,
	0x00,
	0x00
	//bNumConfigurations: 1 configuration
};

const unsigned char ReaderName[32] = 
{
	24,3,
    'R', 0,
    '2', 0,
    ' ',0,
     '0', 0,
    '0', 0, 
    '1', 0, 
    ' ', 0,
	'0', 0,
    '0', 0, 
    '0', 0, 
    '1', 0
};

const unsigned char UMASSName[40] = 
{
    40,3,
    'M', 0, 
    'a', 0,
    's', 0, 
    's', 0,
    ' ', 0,
    'S', 0,
    't',0,
     'o', 0,
    'r', 0, 
    'a', 0, 
    'g', 0,
	'e', 0,
    ' ', 0, 
    'D', 0, 
    'e', 0,
    'v', 0,
    'i', 0, 
    'c', 0, 
    'e', 0
};


static unsigned char Response_To_GET_CLOCK_FREQUENCIES[] = {0xfc, 0x0d, 0x00, 0x00};
static unsigned char Response_To_GET_DATA_RATES[] = {0x80, 0x25, 0x00, 0x00};

#define SWAP(x)   ((((x) & 0xFF) << 8) | (((x) >> 8) & 0xFF))

void HAL_USB_Init()
{
	USBICR = 0x00060013;

	// enable Interrupt
	USB_INTRTXE = EP0_INTR ;//| EP4_INTR;
	USB_INTRRXE =  EP1_INTR;//EP3_INTR |
	USB_INTRUSBE = 0x07;	
	
	// clear register 
	USB_FADDR = 0x00;	
	USB_INDEX = 0x0;		
	USB_CSR0 = 0x0000;
	
	USB_INDEX = 0x1;
	USB_RxFIFOsz = 0x16;
	USB_RxFIFOadd = 0x0800;
	
	USB_INDEX = 0x2;
	USB_TxFIFOsz = 0x16;
	USB_TxFIFOadd = 0x0801;	 
	
	// config RX endpoint and TX endpoint
//	USB_INDEX = 0x3;
//	USB_RxFIFOsz = 0x16;
////	USB_RXMAXP = 0x0002;
//	USB_RxFIFOadd = 0x0800;		// USB_ENDPOINT0_MAXP/8
//	
//	USB_INDEX = 0x4;
////	USB_TXMAXP = 0x0002;	
//	USB_TxFIFOsz = 0x16;
//	USB_TxFIFOadd = 0x0801;	 

	USB_INDEX = 0x0;
	
	// set high speed mode
	USB_POWER = 0x60;
}

void usb_read_ep0_fifo(unsigned char *dst,unsigned short length)
{
	unsigned short i;
	for(i=0;i<length;i++)
	{
		*(dst+i) = USB_EP0_FIFO_8;
	}
}

void usb_write_ep0_fifo(unsigned char *src,unsigned short length)
{
	unsigned short i;
	if(length > 64)
	{ 
		for(i = 0; i < 64; i++)
		{
			USB_EP0_FIFO_8 = *(src+i);
		}
		USB_CSR0 = USB_CSR0 | 0x0200;
		
		while(!(USB_INTRTX & 0x0100));
		
		for(; i < length; i++)
		{
			USB_EP0_FIFO_8 = *(src+i);
		}
		USB_CSR0 = USB_CSR0 | 0x0A00;
	}
	else
	{
		for(i = 0; i < length; i++)
		{
			USB_EP0_FIFO_8 = *(src+i);
		}
		USB_CSR0 = USB_CSR0 | 0x0A00;			
	}
}

void usb_ep0_send_stall(void)
{
	USB_CSR0 |= 0x2000; //send stall
}

void usb_ep1_stall(void)
{
	USB_INDEX = 1;
	USB_RXCSR |= 0x2000;
}

void usb_ep2_stall(void)
{
	USB_INDEX = 2;
	USB_TXCSR |= 0x2000;
}

void usb_ep3_stall(void)
{
	USB_INDEX = 3;
	USB_RXCSR |= 0x2000;
}

void usb_ep4_stall(void)
{
	USB_INDEX = 4;
	USB_TXCSR |= 0x2000;
}

void usb_read_ep1_fifo(unsigned char *dst,unsigned short *length)
{
	unsigned short len = 0, i;

	while(1)
	{
		//if(USB_INTRRX & EP1_INTR)    // ep1 routine
		{
			USB_INDEX = 0x1;
			
			if(USB_RXCSR & 0x0100)
			{
				i = USB_RXCOUNT;
				len = ((i>>8) | (i<<8));
							
				for(i = 0; i < len; i++)
				{
					dst[i] = USB_EP1_FIFO_8;
				}
				
				USB_RXCSR = USB_RXCSR & 0xfeff;
				
				*length = len;
				return;
			}
			
			*length = 0;				
		}          // end if(USB_INTRRX & 0x0200)
	}   // end while(1)
}

void usb_write_ep2_fifo(unsigned char *src,unsigned short length)
{
	unsigned short i;
	
	for(i = 0; i < length; i++)
	{
		USB_EP2_FIFO_8 = src[i];
	}
	
	USB_INDEX = 2;
	USB_TXCSR = 0x0120;

	while((USB_TXCSR &0x0100 ));
	//while(!(USB_INTRTX & EP2_INTR));
}

void usb_write_ep1_int(unsigned char *src,unsigned short length)
{
	unsigned short i;
	
	for(i = 0; i < length; i++)
	{
		USB_EP1_FIFO_8 = src[i];
	}
	
	USB_INDEX = 1;
	USB_TXCSR = 0x0120;
	
	while(!(USB_INTRTX & EP1_INTR));
}

void usb_read_ep3_fifo(unsigned char *dst,unsigned short *length)
{
	unsigned short len = 0, i;
	while(1)
	{
			USB_INDEX = 0x3;
			
			if(USB_RXCSR & 0x0100)
			{
				//i = USB_RXCOUNT;
				//len = ((i>>8) | (i<<8));
				len = *length;
								
				for(i = 0; i < len; i++)
				{
					dst[i] = USB_EP3_FIFO_8;
				}
				
				USB_RXCSR = USB_RXCSR & 0xfeff;

				//*length = len;
				return;
			}	
			
			//*length = 0;		
	}   // end while(1)
}

void usb_write_ep4_fifo(unsigned char *src,unsigned short length)
{
	unsigned short i;
	
	for(i = 0; i < length; i++)
	{
		USB_EP4_FIFO_8 = src[i];
	}
	
	USB_INDEX = 4;
	USB_TXCSR = 0x0120;
	
	while((USB_TXCSR &0x0100 ));//未开中断用查询状态方式
	//while(!(USB_INTRTX & EP4_INTR));//使用查中断发包有问题
}

void usb_get_status(void)
{
	unsigned char status[2] = {0x00, 0x00};
	switch(g_req.wIndex)
	{
	case 0:
		usb_write_ep0_fifo(status,2);
		USB_CSR0 |= 0x0A00;	//finishing load data into fifo
		//set TxPktRdy bit and set DataEnd bit
		break;
		
	case 0x0001:
		//	case 0x0100:
		status[0] = status_ep1;
		usb_write_ep0_fifo(status,2);
		USB_CSR0 |= 0x0A00;	//finishing load data into fifo
		break;
	case 0x0081:
		//	case 0x0100:
		status[0] = status_ep1_int;
		usb_write_ep0_fifo(status,2);
		USB_CSR0 |= 0x0A00;	//finishing load data into fifo
		break;	
	case 0x0082:
		//	case 0x8200:
		status[0] = status_ep2;
		usb_write_ep0_fifo(status,2);
		USB_CSR0 |= 0x0A00;	//finishing load data into fifo
		break;
	case 0x0003:
		//	case 0x8200:
		status[0] = status_ep3;
		usb_write_ep0_fifo(status,2);
		USB_CSR0 |= 0x0A00;	//finishing load data into fifo
		break;
	case 0x0084:
		//	case 0x8200:
		status[0] = status_ep4;
		usb_write_ep0_fifo(status,2);
		USB_CSR0 |= 0x0A00;	//finishing load data into fifo
		break;		
	default:
		USB_CSR0 |= 0x2000; //send stall
		break;
	}
}

void usb_clear_feature(void)
{
    switch(g_req.wIndex)
	{
	case 0x0001:
		//	case 0x0100:
		status_ep1 = 0x00;
		break;
	case 0x0081:
		//	case 0x0100:
		status_ep1_int = 0x00;
		break;	
	case 0x0082:
		//	case 0x8200:
		status_ep2 = 0x00;
		break;
	case 0x0003:
		//	case 0x0100:
		status_ep3 = 0x00;
		break;
		
	case 0x0084:
		//	case 0x8200:
		status_ep4 = 0x00;
		break;	
	default:
		break;
	}
	USB_CSR0 |= 0x4800;	//set the ServicedRxPktRdy and DataEnd bit
}

void usb_set_feature(void)
{
    switch(g_req.wIndex)
	{
	case 0x0001:
		//	case 0x0100:
		status_ep1 = 0x01;
		break;
	case 0x0081:
		//	case 0x0100:
		status_ep1_int = 0x01;
		break;	
	case 0x0082:
		//	case 0x8200:
		status_ep2 = 0x01;
		break;
	case 0x0003:
		//	case 0x0100:
		status_ep3 = 0x01;
		break;
		
	case 0x0084:
		//	case 0x8200:
		status_ep4 = 0x01;
		break;	
	default:
		break;
	}
	//USB_CSR0 |= 0x2000; //send stall
	USB_CSR0 |= 0x4800;	//set the ServicedRxPktRdy and DataEnd bit
}

void usb_get_description(void)
{
	unsigned char bRequestType;
	unsigned char bRequest;
	unsigned short wValue;
	unsigned char wValue_bIndex;
	unsigned short wLength;
	unsigned short wRecLen;
	unsigned short wRecdDataLen=0;
	unsigned char i = 0;
	
	USB_CSR0 |= 0x4000;	//set the ServicedRxPktRdy

	bRequestType = g_req.bmRequestType;
	bRequest = g_req.bRequest;
	wValue = (g_req.wValue>>8);
	wValue_bIndex = (g_req.wValue & 0xff);
	wLength = g_req.wLength;	

	if(wValue == USB_DEVICE_DESCRIPTOR_TYPE)
	{
		
		wLength = (wLength > DeviceDescriptor[0]) ? DeviceDescriptor[0] : wLength;		
		usb_write_ep0_fifo((unsigned char *)DeviceDescriptor, wLength);
		
		
	}
	else if(wValue == USB_CONFIGURATION_DESCRIPTOR_TYPE)
	{
		wLength = (wLength > ConfigDescriptor2[2]) ? ConfigDescriptor2[2] : wLength;
		usb_write_ep0_fifo((unsigned char *)ConfigDescriptor2, wLength);
	}
	else if(wValue == USB_STRING_DESCRIPTOR_TYPE)
	{
		switch(wValue_bIndex)
		{
		case 0: // language string
			//if(wLength > StringLangID[0])
			//	wLength = StringLangID[0];

			wLength = (wLength > StringLangID[0]) ? StringLangID[0] : wLength;
			usb_write_ep0_fifo((unsigned char *)StringLangID, wLength);
			break;
		
		case 1:// serial string
			//if(wLength > StringVendor[0])
			//	wLength = StringVendor[0];

			wLength = (wLength > StringVendor[0]) ? StringVendor[0] : wLength;
			usb_write_ep0_fifo((unsigned char *)StringVendor, wLength);	
			//usb_write_ep0_fifo(serialnumString, wLength);
			break;
		
		case 2:// prduct string	
			//if(wLength > StringProduct[0])
			//	wLength = StringProduct[0];
			
			wLength = (wLength > ReaderName[0]) ? ReaderName[0] : wLength;
			usb_write_ep0_fifo((unsigned char *)ReaderName, wLength);
		
			
			break;
		
		case 3:// mfr string
			//if(wLength > StringSerial[0])
			//	wLength = StringSerial[0];

			wLength = (wLength > StringSerial[0]) ? StringSerial[0] : wLength;
			usb_write_ep0_fifo((unsigned char *)StringSerial, wLength);
			break;
		case 4:
			wLength = (wLength > ReaderName[0]) ? ReaderName[0] : wLength;
			usb_write_ep0_fifo((unsigned char *)ReaderName, wLength);
			break;
		case 5:
			wLength = (wLength > UMASSName[0]) ? UMASSName[0] : wLength;
			usb_write_ep0_fifo((unsigned char *)UMASSName, wLength);
			break;		
		default:
			usb_ep0_send_stall();
			return;
		}//end of "switch(wValue_bIndex)"		
	}
	else if(wValue == USB_DEVICE_QUALIFIER_DESCRIPTOR_TYPE)
	{
		wLength = (wLength > DevQualifier[0]) ? DevQualifier[0] : wLength;
		usb_write_ep0_fifo((unsigned char *)DevQualifier, wLength);
	}
	else
	{
		usb_ep0_send_stall();
		return;
	}

	USB_CSR0 |= 0x0a00;  //set TxPktRdy and set DataEnd bit
	USBICR = 0x00060013;
}

void usb_get_configuration(void)
{
	usb_write_ep0_fifo(&g_bIsConfiged,1);
	USB_CSR0 |= 0x0A00;	//finishing load data into fifo
				//set TxPktRdy bit and set DataEnd bit
}

void usb_set_address(void)
{
	unsigned char	i;

	USB_CSR0 |= 0x4000;	//set the ServicedRxPktRdy

	while(!(USB_INTRTX & 0x0100));

	USB_FADDR = (unsigned char)g_req.wValue;

	i = (unsigned char)g_req.wValue;
	usb_write_ep0_fifo(&i,1);
	USB_CSR0 |= 0x0A00;	//finishing load data into fifo
				//set TxPktRdy bit and set DataEnd bit
}

void usb_set_configuration(void)
{
//	USB_INDEX = 0x1;   // out rx
//	USB_RXMAXP = 0x4000;
//	USB_RXCSR = 0x0000;
//											
//	USB_INDEX = 0x2;  // in  tx
//	USB_TXMAXP = 0x4000;
//	USB_TXCSR = 0x0020;
			
	USB_INDEX = 0x1;   // out rx
	USB_RXMAXP = 0x0002;
	USB_RXCSR = 0x0000;
											
	USB_INDEX = 0x2;  // in  tx
	USB_TXMAXP = 0x0002;
	USB_TXCSR = 0x0020;
	
	g_bIsConfiged = (unsigned char)g_req.wValue;

	USB_INDEX = 0x0;
	
	USB_CSR0 = USB_CSR0 | 0x4800;
}

void usb_get_interface(void)
{
	unsigned char i = 0;
	usb_write_ep0_fifo(&i,1);
	USB_CSR0 |= 0x0A00;	//finishing load data into fifo
				//set TxPktRdy bit and set DataEnd bit
}
void usb_set_interface(void)
{
	USB_CSR0 |= 0x4800;
}

void reserved(void)
{
	usb_ep0_send_stall();
}

void (*StandardDeviceRequest[])(void) =
{
	usb_get_status,
	usb_clear_feature,
	reserved,
	usb_set_feature,
	reserved,
	usb_set_address,
	usb_get_description,
	reserved,
	usb_get_configuration,
	usb_set_configuration,
	usb_get_interface,
	usb_set_interface,
};

void usb_control_transfer_handler(void)
{
	unsigned char ret = 0;	
	unsigned char data[19] = 
	{
		0x6b, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x40, 0x54, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,0x76
	};

	unsigned char ICinplug[2] = {0x50, 0x03};
	unsigned char ICoutplug[2] = {0x50, 0x02};

		
	if((g_req.bmRequestType&0x60) == SETUP_TYPE_CLASS)
	{
		
		if(g_req.bmRequestType == 0xa1)
		{
			if(g_req.bRequest == 0x02)
			{
				usb_write_ep0_fifo(Response_To_GET_CLOCK_FREQUENCIES, 4);

				//if(!g_AU9541)
				//{
					//HAL_UART_WriteData(0, data, 19);
					//g_AU9541 = 1;
					usb_write_ep1_int((unsigned char *)ICinplug, 2);
				//}
			
			}
			else if(g_req.bRequest == 0x03)
			{
				usb_write_ep0_fifo(Response_To_GET_DATA_RATES, 4);
			}
			else if(g_req.bRequest == 0xfe)
	    		{
	    		
	    			/*ret = Max_Lun;
				USB_CSR0 |= 0x4000;
		    		usb_write_ep0_fifo(&ret,1);
				USB_CSR0 |= 0x0a00;  //set TxPktRdy and set DataEnd bit
				USBICR = 0x00060013;
				*/				
				ret = Max_Lun;
				usb_write_ep0_fifo(&ret,1);

				
	    		}
			else
			{
				USB_CSR0 = USB_CSR0 | 0x6000;
			}			
		}
		else
		{
			USB_CSR0 = USB_CSR0 | 0x6000;
		}    		
	}
	else 
    {
		StandardDeviceRequest[g_req.bRequest]();
	}
}

#pragma interrupt on
void usb_IrqHandle(void)
{
	unsigned char usb_count0;
	unsigned char EpIndex_reg;
	unsigned int i;
	unsigned char setupbuf[8];
	unsigned short len, offset;
	unsigned char intrusb_reg;
	unsigned short intrtx_reg, intrrx_reg, usb_csr0;//, intrrx_reg
	unsigned short relen;
	
	intrusb_reg = USB_INTRUSB;
	usb_csr0 = USB_CSR0;


	if(intrusb_reg & 0x04)
	{
		HAL_USB_Init();
		return;
	}
	else if(intrusb_reg & 0x02)//resume
	{
		return;
	}
	else if(intrusb_reg & 0x01)//suspend
	{
		return;
	}

		
	intrtx_reg = USB_INTRTX;

	EpIndex_reg = USB_INDEX;
	USB_INDEX = 0x0;									 
	
	if((intrtx_reg & 0x0100) && (usb_csr0 & 0x0100))   //ep0 接收中断
	{
		usb_count0 = USB_COUNT0;
		if(usb_count0 == 8)  //setup end
		{
			for(i=0;i<8;i++)
				setupbuf[i] = USB_EP0_FIFO_8;
			memcpy((unsigned char *)&g_req, setupbuf, 8);			

			g_req.wValue = SWAP(g_req.wValue);
			g_req.wIndex = SWAP(g_req.wIndex);
			g_req.wLength = SWAP(g_req.wLength);
			usb_control_transfer_handler();
		}
		
	}

	// 通过ep3接收
	intrrx_reg = USB_INTRRX;
	
	if(intrrx_reg & EP1_INTR)
	{	
		USB_INDEX = 0x1;
		if(USB_RXCSR & 0x0100)
		{
			if(!G_UMS)
			{
				Data_Len = 31;
//  				HAL_USB_BulkOut(1, g_b_MassComm, &Data_Len,1);
				usb_receive(g_b_MassComm,Data_Len);
				G_UMS = 1;				
			}	
		}			
	}
	USB_INDEX = EpIndex_reg;	
}
#pragma interrupt off

void HAL_USB_BulkInStall(void)
{
	U32 i=0;   
	USB_INDEX =  0x1; 
	while (USB_TXCSR & 0x0100){}  //等待可以被写数据,等待fifo为空
	
    // stall it
	USB_TXCSR |= 0x1000;
    
        while(1)
	{	
        
		if((++i)>0x80)
		{
			break;
		}	
	}

    // clear stall status
    USB_TXCSR &= ~0x1000;
}


void HAL_USB_BulkOutStall(void) 
{
	USB_INDEX =  0x1;
	USB_RXCSR |= 0x2000;
}

asm void usb_send_SM1(unsigned char *data_buf_g, unsigned int data_len_g)
{
	subi    r0,28
	stm     r10
	
	lrw		r14, USB_SEND_FIFO
	lrw		r13, DMA_SAR_ADDR
	lrw		r11, USB_INDEX_ADDR
	lrw		r10, USB_TXCSR_ADDR

	mov		r4, r2
	mov		r5, r14
	lrw		r6, 512
	lrw		r7, 0x00002001	
	subu	r4, r6
	
_package_loop:
	addu	r4, r6	
	stq		r13
	
_wait_DMA:
	ld.w	r12, (r13, 12)
	btsti	r12, 16
	bf		_wait_DMA
	
	bgeni	r12, 16
	st.w	r12, (r13, 12)
	
	movi	r12, 2
	st.b	r12, (r11, 0)
	
	movi	r12, 32
	bseti	r12, 8
	st.h	r12, (r10, 0)

_wait_USB:
	ld.h	r12, (r10, 0)
	btsti	r12, 8
	bt		_wait_USB
	
	subu	r3, r6
	cmphs	r3, r6
	bt		_package_loop
	
_exit:
	ldm     r10
	addi    r0,28
	
	jmp		r15	
}

void usb_send(unsigned char *data_buf, unsigned int len)
{
	unsigned int i;
	unsigned int j;
	
	for(i = 0; i < (len >> 9); i++)
	{
		for(j = 0; j < 512; j++)
		{
			USB_EP2_FIFO_8 = data_buf[j + (i << 9)];
		}
		
		USB_INDEX = 0x2;
		USB_TXCSR = 0x0120;		
		while(USB_TXCSR & 0x0100);
	}
	
	if(len & 0x000001FF)
	{
		for(j = 0; j < (len & 0x000001FF); j++)
		{
			USB_EP2_FIFO_8 = data_buf[j + (i << 9)];
		}
		
		USB_INDEX = 0x2;
		USB_TXCSR = 0x0120;		
		while(USB_TXCSR & 0x0100);
	}
}



asm void usb_receive_SM1(unsigned char *data_buf_g, unsigned int data_len_g)
{
	subi    r0,16
	subi    r0,16
	stm     r9
	
	lrw		r14, USB_RECEIVE_FIFO
	lrw		r13, DMA_SAR_ADDR
	lrw		r11, USB_INDEX_ADDR
	lrw		r10, USB_RXCSR_ADDR

	mov		r4, r14
	mov		r5, r2
	lrw		r6, 512
	lrw		r7, 0x00000101
	subu	r5, r6
	
_package_loop:	
	addu	r5, r6
	
_wait_data:
	movi	r12, 1
	st.b	r12, (r11, 0)
	ld.h	r12, (r10, 0)
	btsti	r12, 8
	bf		_wait_data
	
	stq		r13
	
_wait_DMA:
	//ld.h	r12, (r10, 2)
	ld.w	r12, (r13, 12)
	btsti	r12, 16
	bf		_wait_DMA
	
	bgeni	r12, 16
	st.w	r12, (r13, 12)
	
	ld.h	r12, (r10, 0)
	not		r12
	bseti	r12, 8
	not		r12
	st.h	r12, (r10, 0)
	
	subu	r3, r6
	cmphs	r3, r6
	bt		_package_loop
	
_exit:
	ldm     r9
	addi    r0,16
	addi    r0,16
	jmp		r15	
}

void usb_receive(unsigned char *data_buf, unsigned int len)
{
	unsigned int i;
	unsigned int j;
	if(len)
	{
		while(1)
		{
//			if(USB_INTRRX & 0x0200)    // ep1 routine
			{
				USB_INDEX = 0x1;
				
				if(USB_RXCSR & 0x0100)
				{
					for(j = 0; j < len; j++)
					{
						data_buf[j] = USB_EP1_FIFO_8;
					}
//					if(flag==1)
					{
						USB_RXCSR = USB_RXCSR & 0xfeff;
					}					
					break;
				}				
			}        // end if(USB_INTRRX & 0x0200)
		
		}    // end while(1)
	}
#if 0
	for(i = 0; i < (len >> 9); i++)
	{
		while(1)
		{
//			if(USB_INTRRX & 0x0200)    // ep1 routine
			{
				USB_INDEX = 0x1;
				
				if(USB_RXCSR & 0x0100)
				{
					for(j = 0; j < 512; j++)
					{
						data_buf[j + (i << 9)] = USB_EP1_FIFO_8;
					}	
					
						USB_RXCSR = USB_RXCSR & 0xfeff;
					
					break;
				}				
			}          // end if(USB_INTRRX & 0x0200)
		}        // end while(1)
	}
	
	if(len & 0x000001FF)
	{
		while(1)
		{
//			if(USB_INTRRX & 0x0200)    // ep1 routine
			{
				USB_INDEX = 0x1;
				
				if(USB_RXCSR & 0x0100)
				{
					for(j = 0; j < (len & 0x000001FF); j++)
					{
						data_buf[j + (i << 9)] = USB_EP1_FIFO_8;
					}
					if(flag==1)
					{
						USB_RXCSR = USB_RXCSR & 0xfeff;
					}
						
					
					break;
				}				
			}        // end if(USB_INTRRX & 0x0200)
		
		}    // end while(1)
	}   // end if(len & 0x00000200)

#endif
	
}
void HAL_USB_BulkOut(unsigned char Endpoint, unsigned char *pBuf, unsigned short *plen,unsigned char flag)
{

#if 0
	unsigned short ulLen, ulLenReceived, ulLenTmp,len;
	unsigned char EpIndex_reg;
	unsigned int i=0;

	EpIndex_reg = USB_INDEX;
	
	//receive the first packet
	USB_INDEX = Endpoint;
	
	while (!(USB_RXCSR & 0x0100) ){}
	
	if(*plen == 0)
	{
		ulLenTmp = USB_RXCOUNT;
		len = ((ulLenTmp>>8) | (ulLenTmp<<8));
	}
	else
	{
		len = *plen;
	}
	
	
	
	while (len > BULK_BUF_MAXLEN)
	{
		ulLenTmp = BULK_BUF_MAXLEN;
		
		if(Endpoint == 1)
			usb_read_ep1_fifo(pBuf+i, &ulLenTmp);
		else
			usb_read_ep3_fifo(pBuf+i, &ulLenTmp);
			
		len -= BULK_BUF_MAXLEN;
		i += BULK_BUF_MAXLEN;
	}
	
	//发送剩余数据到主机
	if(len>0)
	{
		ulLenTmp = len;
		
		if(Endpoint == 1)
			usb_read_ep1_fifo(pBuf+i, &ulLenTmp);
		else
			usb_read_ep3_fifo(pBuf+i, &ulLenTmp);
			
		i+=len;

	}
		
	USB_INDEX =  EpIndex_reg;

	*plen = i;
#else

	unsigned short len1=0,len2=0;
	len1 =*plen %512;
	len2 = *plen - len1;
 	if(len2>0)
 	{
		usb_receive_SM1(pBuf, len2);
 	}
	usb_receive(pBuf+len2,len1);

#endif
	return;	
}



void HAL_USB_BulkIn(unsigned char Endpoint, unsigned char *pBuf, unsigned short len)
{
#if 0
	unsigned char EpIndex_reg;
	unsigned int i=0;
	
	EpIndex_reg = USB_INDEX;
				
	while (len > BULK_BUF_MAXLEN)
	{
		if(Endpoint == 2)
			usb_write_ep2_fifo(pBuf+i, BULK_BUF_MAXLEN);
		else
			usb_write_ep4_fifo(pBuf+i, BULK_BUF_MAXLEN);
			
		len -= BULK_BUF_MAXLEN;
		//pBuf += BULK_BUF_MAXLEN;	
		i += BULK_BUF_MAXLEN;
	}
	
	//发送剩余数据到主机
	if(len>0)
	{
		if(Endpoint == 2)
			usb_write_ep2_fifo(pBuf+i, len);
		else
			usb_write_ep4_fifo(pBuf+i, len);

	}
	
	USB_INDEX =  EpIndex_reg;

#else
	unsigned int len1=0,len2=0;
	len1 =len %512;
	len2 = len - len1;
 	if(len2>0)
 	{
		usb_send_SM1(pBuf, len2);
 	}

	usb_send(pBuf+len2,len1);
#endif
} 


void usb_receive_DMA1(unsigned char *buf, unsigned int len)
{
	unsigned int i, j;
	
	for(i = 0; i < (len >> 9); i++)
	{
	//USB_RXCSR = USB_RXCSR & 0xFEFF;
		while(1)
		{
			//if(USB_INTRRX & 0x0200)    // ep1 routine
			//{
				USB_INDEX = 0x1;
				
				if(USB_RXCSR & 0x0100)
				{
					DMA_SAR = 0x00900024;
					DMA_DAR = (unsigned int)buf + (i << 9);
					DMA_TCR = 512;
					//DMA_DCSR = 0x00008101;	//源为2字节，目的为4字节				
					DMA_DCSR = 0x00008501;	//源为2字节，目的为2字节		
					while(!(DMA_DCSR & 0x00010000));
					DMA_DCSR = 0x00010000;						
					
					break;
				}				
			//}          // end if(USB_INTRRX & 0x0200)
		}        // end while(1)
		USB_RXCSR = USB_RXCSR & 0xFEFF;
	}
	
	len &= 0x000001FF;

	if(len)
	{
	//USB_RXCSR = USB_RXCSR & 0xFEFF;
		while(1)
		{
			//if(USB_INTRRX & 0x0200)    // ep1 routine
			//{
				USB_INDEX = 0x1;
				
				if(USB_RXCSR & 0x0100)
				{
					DMA_SAR = 0x00900024;
					DMA_DAR = (unsigned int)buf + (i << 9);
					DMA_TCR = len;
					//DMA_DCSR = 0x00008101;	
					DMA_DCSR = 0x00008501;		//源为2字节，目的为2字节				
					
					while(!(DMA_DCSR & 0x00010000));
					DMA_DCSR = 0x00010000;									
					
					break;
				}				
			//}        // end if(USB_INTRRX & 0x0200)
		}    // end while(1)
		USB_RXCSR = USB_RXCSR & 0xfeff;
	}   // end if(len & 0x00000200)

}



void usb_receiveData_DMA(unsigned char *bufhead, unsigned char *bufdata, unsigned int len)
{
	unsigned int i;

	
	USB_INDEX = 0x1;
	USB_RXCSR = USB_RXCSR & 0xFEFF;
	while(!(USB_RXCSR&0x0100))
	{
		USB_INDEX = 0x1;
	}
	
	for(i=0; i<6; i++)
	{
		bufhead[i] = USB_EP1_FIFO_8;
	}
	
	usb_receive_DMA1(bufdata, 506);
	usb_receive_DMA1(bufdata+506, len-512);
	/*len = len - 6;
	if(len)
	{
		if(len>506)
		{
		usb_receive_DMA1(bufdata, 506);
		usb_receive_DMA1(bufdata+506, len-512);
		}
		else
		{
		usb_receive_DMA1(bufdata, len);
		}
	}*/
	
}



void usb_send_DMA_Test(unsigned char *buf,unsigned int len)
{
	unsigned int i, j;
	unsigned int len1 = len;;
	//len = CBW[8] + (CBW[9] << 8) + (CBW[10] << 16) + (CBW[11] << 24);
	for(i = 0; i < (len >> 9); i++)
	{
		DMA_SAR = (unsigned int)buf + (i << 9);
		DMA_DAR = 0x00900028;
		DMA_TCR = 512;
		DMA_DCSR = 0x00002001;
		while(!(DMA_DCSR & 0x00010000));
		DMA_DCSR = 0x00010000;
		
		USB_INDEX = 0x2;
		USB_TXCSR = 0x0120;
		//while(!(USB_INTRTX & 0x0400));
		while(USB_TXCSR & 0x0100);
		
	}
	if(len%512)
		usb_send(buf + (i << 9),len%512);
#if 0	
	//if(len)
	//{
		len &= 0x000001FF;
		if(len-2)
		{
			DMA_SAR = (unsigned int)buf + (i << 9);
			DMA_DAR = 0x00900028;
			DMA_TCR = len-2;
			DMA_DCSR = 0x00002001;
			while(!(DMA_DCSR & 0x00010000));
			DMA_DCSR = 0x00010000;
			
		}
	//}
	
	USB_EP2_FIFO_8 = buf[len1-2];//发状态字
	USB_EP2_FIFO_8 = buf[len1-1];
	USB_INDEX = 0x2;
	USB_TXCSR = 0x0120;
	while(USB_TXCSR & 0x0100);
#endif
	
}


