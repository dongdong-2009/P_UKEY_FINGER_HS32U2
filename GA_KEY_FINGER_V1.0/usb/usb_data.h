#ifndef __USB_DATA_H_
#define __USB_DATA_H_

#ifndef NULL
#define NULL 0
#endif

typedef struct _apdu{
	unsigned char rfu[2];
	unsigned char CLA;
	unsigned char INS;
	unsigned char PP1;
	unsigned char PP2;
	unsigned char LEN[2];
//	unsigned char pInData[1024];
//	unsigned char pOutData[1024];
	unsigned char *pInData;
	unsigned char *pOutData;
	unsigned char SW1;
	unsigned char SW2;
	unsigned int LC;
	unsigned int  RLE;
}APDU;

#endif