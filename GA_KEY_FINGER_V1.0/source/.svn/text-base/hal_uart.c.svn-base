#include "HAL_UART.h"

#include"string.h"
#include "stdio.h"
#include "stdarg.h"

void HAL_UART_Init(void)
{
	//œµÕ≥ ±÷”64/MHz //38400Hz 
	MCSCR |= SCI_ON;			
	SCIBDH=0x006A;      	//38400Hz.
	SCICR1=0x0028;         //SCICR1=0x00fc;
	SCICR2= 0x2c;//recv interrupt
		
}
unsigned short HAL_UART_WriteByte( unsigned char data)
{
	unsigned short tmp;
	unsigned short i =0;
	tmp = SCISR1; 
	SCIDRL = data;	
	tmp = SCISR1; 
	while(!(tmp & 0x0080))
	{
		tmp = SCISR1; 
		if((i++)== 322000)
		{
			return 1;
		}
	}	
	return 0;
}

void HAL_UART_SendData(unsigned char *data, unsigned short len)
{
	unsigned int i;
	unsigned short rv=0;
	
	for(i=0; i<len; i++)
	{		
		 HAL_UART_WriteByte(*(data+i));			
	}
	
}

void UART_printf(char *fmt,...)
{

	unsigned char temp[256];
	
	va_list arg_ptr;
//	unsigned char *string=pUARTData;
	unsigned char *string=temp;	
	va_start(arg_ptr, fmt);  
	vsprintf((char *)string,fmt,arg_ptr); 
    	HAL_UART_SendData(string,strlen((char *)string));
	va_end(arg_ptr);
}


void HAL_UART_SEND_ASC(unsigned char* pInData,unsigned short len)
{	
	unsigned char temp[4];
	unsigned char m;
	unsigned short i,len1;
	
	len1=2*len;
	for(i=0;i<len;i++)
	{
		m=(pInData[i]>>4)&0x0f;
		if(m>=0&&m<=9)
			m+=0x30;
		else
			m+=55;
		temp[0]=m;
		m=pInData[i]&0x0f;
		if(m>=0&&m<=9)
			m+=0x30;
		else
			m+=55;
		temp[1]=m;
		temp[2]=' ';
		HAL_UART_SendData(temp,3);
	}
	temp[0]=0x0a;
	HAL_UART_SendData(temp,1);
}



