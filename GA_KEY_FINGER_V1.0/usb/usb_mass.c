#include "usb.h"
#include "usb_mass.h"

unsigned char G_UMS=0;
unsigned char G_CMD=0;
unsigned char Bot_State;
unsigned short Data_Len;
Bulk_Only_CBW CBW;
Bulk_Only_CSW CSW;
unsigned int SCSI_LBA , SCSI_BlkLen;

extern unsigned char g_reboot,g_led_flag;
extern unsigned char G_XFA_Data[];

unsigned char Page00_Inquiry_Data[] =
  {
    0x00, /* PERIPHERAL QUALIFIER & PERIPHERAL DEVICE TYPE*/
    0x00,
    0x00,
    0x00,
    0x00 /* Supported Pages 00*/
  };
unsigned char Standard_Inquiry_Data[] =
  {
    0x00,          /* Direct Access Device */
    0x00,          /* RMB = 1: Removable Medium */
    0x02,          /* Version: No conformance claim to standard */
    0x02,

    0x1f,          /* Additional Length */
    0x00,          /* SCCS = 1: Storage Controller Component */
    0x00,
    0x00,
    /* Vendor Identification */
    'G', 'A', 'S', 'E', 'C', ' ', ' ', ' ',
    /* Product Identification */
    'G', 'A', 'F', 'K', 'E', 'Y', ' ', ' ', ' ',
    ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    /* Product Revision Level */
    '1', '.', '0', '0'
  };
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
unsigned char Mode_Sense6_data[] =
  {
    0x0b,
    0x00,
    0x00,
    0x08,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x01,
    0x00
  };

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/

unsigned char Mode_Sense10_data[] =
  {
    0x00,
    0x06,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
  };
unsigned char Scsi_Sense_Data[] =
  {
    0x70, /*RespCode*/
    0x00, /*SegmentNumber*/
    NO_SENSE, /* Sens_Key*/
    0x00,
    0x00,
    0x00,
    0x00, /*Information*/
    0x0A, /*AdditionalSenseLength*/
    0x00,
    0x00,
    0x00,
    0x00, /*CmdInformation*/
    NO_SENSE, /*Asc*/
    0x00, /*ASCQ*/
    0x00, /*FRUC*/
    0x00, /*TBD*/
    0x00,
    0x00 /*SenseKeySpecific*/
  };

  unsigned char Scsi_Sense_Data_A[] =
  {
    0x70, /*RespCode*/
    0x00, /*SegmentNumber*/
    0x02, /* Sens_Key*/
    0x00,
    0x00,
    0x00,
    0x00, /*Information*/
    0x0A, /*AdditionalSenseLength*/
    0x00,
    0x00,
    0x00,
    0x00, /*CmdInformation*/
    0x3A, /*Asc*/
    0x00, /*ASCQ*/
    0x0C, /*FRUC*/
    0x03, /*TBD*/
    0x00,
    0x00 /*SenseKeySpecific*/
  };
//unsigned char ReadCapacity10_Data[] =
//  {
    /* Last Logical Block */
 //   0,
 //   0,
 //   0x0f,
//    0xff,

    /* Block Length */
//    0,
//    0,
//    0x02,
//    0
//  };

unsigned char ReadCapacity10_Data[] =
  {
    /* Last Logical Block */
    0,
    0,
    0x00,
    0x00,

    /* Block Length */
    0,
    0,
    0x04,
    0
  };

unsigned char ReadFormatCapacity_Data[12]; 

unsigned  char ReadTOC_Data[] = 
{
	0x00,0x12,	// length
	0x01,// first track
	0x01,// last track
	
	0x00,// rsved
	0x14,// adr|cntl
	0x01,// track number
	0x00,// rsved
	0x00,0x00,0x02,0x00,

	0x00,// rsved
	0x14,// adr|cntl
	0xaa,// track number
	0x00,// rsved
	0x00,0x38,0x37,0x3b,
};

unsigned int Mass_Memory_Size[2];
unsigned int Mass_Block_Size[2];
unsigned int Mass_Block_Count[2];

unsigned int Max_Lun = MAX_LUN;
unsigned char TransferState = TXFR_IDLE;

//volatile unsigned int Block_Read_count = 0;
//volatile unsigned int Block_offset;
//volatile unsigned int Counter = 0;

//unsigned int   Idx;
unsigned char  Data_Buffer[0x400]; /* 512 bytes*/

unsigned int SW32(x)
{
	unsigned int i;
	
	i = (x&0xff000000)>> 24 | (x&0x00ff0000)>> 8 | (x&0x0000ff00)<< 8 | (x&0x000000ff)<< 24;
	
	return i;
}

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : MAL_Init
* Description    : Initializes the Media on the STM32
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
/*
unsigned short MAL_Init(unsigned char lun)
{

  unsigned short status = MAL_OK;

  switch (lun)
  {
    case 0:
      //status = MSD_Init();
      HAL_SF_Init();
      break;
    default:
      return MAL_FAIL;
  }
  return status;
  
}

*/

/*******************************************************************************
* Function Name  : MAL_Read
* Description    : Read sectors
* Input          : None
* Output         : None
* Return         : Buffer pointer
*******************************************************************************/
/*
unsigned short MAL_Read(unsigned char lun, unsigned int Memory_Offset, unsigned int *Readbuff, unsigned short Transfer_Length)
{

  switch (lun)
  {
    case 0:
      //MSD_ReadBlock((unsigned char*)Readbuff, Memory_Offset, Transfer_Length);
      HAL_SF_Init();
      HAL_SF_ReadData(Memory_Offset, Transfer_Length, (unsigned char*)Readbuff);
      break;
    default:
      return MAL_FAIL;
  }
  return MAL_OK;
  
}
*/
/*******************************************************************************
* Function Name  : MAL_GetStatus
* Description    : Get status
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
unsigned short MAL_GetStatus (unsigned char lun)
{
	//Mass_Block_Count[0] = 0x03FF;
	Mass_Block_Count[0] = 0;
	Mass_Block_Size[0] = 0x0400;
	Mass_Memory_Size[0] = Mass_Block_Count[0] * Mass_Block_Size[0];
	return MAL_OK;
}


/*******************************************************************************
* Function Name  : Read_Memory
* Description    : Handle the Read operation from the microSD card.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
/*
void Read_Memory(unsigned char lun, unsigned int Memory_Offset, unsigned int Transfer_Length)
{

  static unsigned int Offset, Length;

  if (TransferState == TXFR_IDLE )
  {
    Offset = Memory_Offset * Mass_Block_Size[lun];
    Length = Transfer_Length * Mass_Block_Size[lun];
    TransferState = TXFR_ONGOING;
  }

  if (TransferState == TXFR_ONGOING )
  {
    if (!Block_Read_count)
    {
      MAL_Read(lun ,
               Offset ,
               Data_Buffer,
               Mass_Block_Size[lun]);

      HAL_USB_BulkIn(4, (unsigned char *)Data_Buffer, BULK_MAX_PACKET_SIZE);

      Block_Read_count = Mass_Block_Size[lun] - BULK_MAX_PACKET_SIZE;
      Block_offset = BULK_MAX_PACKET_SIZE;
    }
    else
    {
      HAL_USB_BulkIn(4, (unsigned char *)Data_Buffer + Block_offset, BULK_MAX_PACKET_SIZE);

      Block_Read_count -= BULK_MAX_PACKET_SIZE;
      Block_offset += BULK_MAX_PACKET_SIZE;
    }

    Offset += BULK_MAX_PACKET_SIZE;
    Length -= BULK_MAX_PACKET_SIZE;

    CSW.dDataResidue -= BULK_MAX_PACKET_SIZE;
  }
  if (Length == 0)
  {
    Block_Read_count = 0;
    Block_offset = 0;
    Offset = 0;
    Bot_State = BOT_DATA_IN_LAST;
    TransferState = TXFR_IDLE;
  }


}
*/
/*******************************************************************************
* Function Name  : Set_Scsi_Sense_Data
* Description    : Set Scsi Sense Data routine.
* Input          : unsigned char Sens_Key
                   unsigned char Asc.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Set_Scsi_Sense_Data(unsigned char lun, unsigned char Sens_Key, unsigned char Asc)
{
  	Scsi_Sense_Data[2] = Sens_Key;
  	Scsi_Sense_Data[12] = Asc;
}

/*******************************************************************************
* Function Name  : Set_CSW
* Description    : Set the SCW with the needed fields.
* Input          : unsigned char CSW_Status this filed can be CSW_CMD_PASSED,CSW_CMD_FAILED,
*                  or CSW_PHASE_ERROR.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Set_CSW (unsigned char CSW_Status, unsigned char Send_Permission)
{
//  CSW.dSignature = BOT_CSW_SIGNATURE;
//  CSW.bStatus = CSW_Status;
//  CSW.dDataResidue = SW32(CSW.dDataResidue);

//  HAL_USB_BulkIn(2, ((unsigned char *)& CSW), CSW_DATA_LENGTH);

	USB_EP2_FIFO_32 = 0x55534253;
	USB_EP2_FIFO_32 = CSW.dTag;
	USB_EP2_FIFO_32 = 0x00000000;
	USB_EP2_FIFO_8 = CSW_Status;

	USB_INDEX = 0x2;
	USB_TXCSR = 0x0120;
		
	while(USB_TXCSR & 0x0100);
  	Bot_State = BOT_IDLE;
}

/*******************************************************************************
* Function Name  : Transfer_Data_Request
* Description    : Send the request response to the PC HOST.
* Input          : unsigned char* Data_Address : point to the data to transfer.
*                  unsigned short Data_Length : the nember of Bytes to transfer.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Transfer_Data_Request(unsigned char* Data_Pointer, unsigned short Data_Len)
{

	HAL_USB_BulkIn(2, Data_Pointer, Data_Len);
  	Bot_State = BOT_IDLE;//BOT_DATA_IN_LAST;//###
  	CSW.dDataResidue -= Data_Len;
  	CSW.bStatus = CSW_CMD_PASSED;
}

/*******************************************************************************
* Function Name  : Bot_Abort
* Description    : Stall the needed Endpoint according to the selected direction.
* Input          : Endpoint direction IN, OUT or both directions
* Output         : None.
* Return         : None.
*******************************************************************************/
void Bot_Abort(unsigned char Direction)
{
	switch (Direction)
	{
	case DIR_IN :
		usb_ep4_stall();
      		break;
	case DIR_OUT :
		usb_ep3_stall();
      		break;
    	case BOTH_DIR :
      		usb_ep4_stall();
     		usb_ep3_stall();
      		break;
	default:
		break;
  	}
}


/*******************************************************************************
* Function Name  : SCSI_Address_Management
* Description    : Test the received address.
* Input          : unsigned char Cmd : the command can be SCSI_READ10 or SCSI_WRITE10.
* Output         : None.
* Return         : Read\Write status (bool).
*******************************************************************************/
unsigned char SCSI_Address_Management(unsigned char lun , unsigned char Cmd , unsigned int LBA , unsigned int BlockNbr)
{

  if ((LBA + BlockNbr) > Mass_Block_Count[lun] )
  {
    if (Cmd == SCSI_WRITE10)
    {
      Bot_Abort(BOTH_DIR);
    }
    Bot_Abort(DIR_IN);
    Set_Scsi_Sense_Data(lun, ILLEGAL_REQUEST, ADDRESS_OUT_OF_RANGE);
    Set_CSW (CSW_CMD_FAILED, SEND_CSW_DISABLE);
    return 0;
  }


  if (CBW.dDataLength != BlockNbr * Mass_Block_Size[lun])
  {
    if (Cmd == SCSI_WRITE10)
    {
      Bot_Abort(BOTH_DIR);
    }
    else
    {
      Bot_Abort(DIR_IN);
    }
    Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, INVALID_FIELED_IN_COMMAND);
    Set_CSW (CSW_CMD_FAILED, SEND_CSW_DISABLE);
    return 0;
  }
  return 1;
}


/*******************************************************************************
* Function Name  : SCSI_Inquiry_Cmd
* Description    : SCSI Inquiry Command routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SCSI_Inquiry_Cmd(unsigned char lun)
{
  unsigned char* Inquiry_Data;
  unsigned short Inquiry_Data_Length;

//   if (CBW.CB[1] & 0x01)/*Evpd is set*/
//  {
//    Inquiry_Data = Page00_Inquiry_Data;
//    Inquiry_Data_Length = 5;
//  }
//  else
  {
    Inquiry_Data = Standard_Inquiry_Data;

    if (CBW.CB[4] <= STANDARD_INQUIRY_DATA_LEN)
      Inquiry_Data_Length = CBW.CB[4];
    else
      Inquiry_Data_Length = STANDARD_INQUIRY_DATA_LEN;

  }

  Transfer_Data_Request(Inquiry_Data, Inquiry_Data_Length);
   Set_CSW (CSW_CMD_PASSED, SEND_CSW_ENABLE);
}

/*******************************************************************************
* Function Name  : SCSI_ReadFormatCapacity_Cmd
* Description    : SCSI ReadFormatCapacity Command routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SCSI_ReadFormatCapacity_Cmd(unsigned char lun)
{

  if (MAL_GetStatus(lun) != 0 )
  {
    Set_Scsi_Sense_Data(CBW.bLUN, NOT_READY, MEDIUM_NOT_PRESENT);
    Set_CSW (CSW_CMD_FAILED, SEND_CSW_ENABLE);
    Bot_Abort(DIR_IN);
    return;
  }
  ReadFormatCapacity_Data[0]=0;
  ReadFormatCapacity_Data[1]=0;
  ReadFormatCapacity_Data[2]=0;
  ReadFormatCapacity_Data[3]=0x08;
  
  ReadFormatCapacity_Data[4] = (unsigned char)(Mass_Block_Count[lun] >> 24);
  ReadFormatCapacity_Data[5] = (unsigned char)(Mass_Block_Count[lun] >> 16);
  ReadFormatCapacity_Data[6] = (unsigned char)(Mass_Block_Count[lun] >>  8);
  ReadFormatCapacity_Data[7] = (unsigned char)(Mass_Block_Count[lun]);

  ReadFormatCapacity_Data[9] = (unsigned char)(Mass_Block_Size[lun] >>  16);
  ReadFormatCapacity_Data[10] = (unsigned char)(Mass_Block_Size[lun] >>  8);
  ReadFormatCapacity_Data[11] = (unsigned char)(Mass_Block_Size[lun]);
  Transfer_Data_Request(ReadFormatCapacity_Data, READ_FORMAT_CAPACITY_DATA_LEN);
   Set_CSW (CSW_CMD_PASSED, SEND_CSW_ENABLE);
}

/*******************************************************************************
* Function Name  : SCSI_ReadCapacity10_Cmd
* Description    : SCSI ReadCapacity10 Command routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SCSI_ReadCapacity10_Cmd(unsigned char lun)
{

  if (MAL_GetStatus(lun))
  {
    Set_Scsi_Sense_Data(CBW.bLUN, NOT_READY, MEDIUM_NOT_PRESENT);
    Set_CSW (CSW_CMD_FAILED, SEND_CSW_ENABLE);
    Bot_Abort(DIR_IN);
    return;
  }

  Transfer_Data_Request(ReadCapacity10_Data, READ_CAPACITY10_DATA_LEN);
  Set_CSW (CSW_CMD_PASSED, SEND_CSW_ENABLE);
}

/*******************************************************************************
* Function Name  : SCSI_ModeSense6_Cmd
* Description    : SCSI ModeSense6 Command routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SCSI_ModeSense6_Cmd (unsigned char lun)
{
  Transfer_Data_Request(Mode_Sense6_data, MODE_SENSE6_DATA_LEN);
   Set_CSW (CSW_CMD_PASSED, SEND_CSW_ENABLE);
}

/*******************************************************************************
* Function Name  : SCSI_ModeSense10_Cmd
* Description    : SCSI ModeSense10 Command routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SCSI_ModeSense10_Cmd (unsigned char lun)
{
  Transfer_Data_Request(Mode_Sense10_data, MODE_SENSE10_DATA_LEN);
   Set_CSW (CSW_CMD_PASSED, SEND_CSW_ENABLE);
}

/*******************************************************************************
* Function Name  : SCSI_RequestSense_Cmd
* Description    : SCSI RequestSense Command routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SCSI_RequestSense_Cmd(unsigned char lun)
{
	unsigned char Request_Sense_data_Length;

  	if (CBW.CB[4] <= REQUEST_SENSE_DATA_LEN)
  	{
		Request_Sense_data_Length = CBW.CB[4];
  	}
  	else
  	{
    		Request_Sense_data_Length = REQUEST_SENSE_DATA_LEN;
  	}

  	Transfer_Data_Request(Scsi_Sense_Data, Request_Sense_data_Length);
	 Set_CSW (CSW_CMD_PASSED, SEND_CSW_ENABLE);
}

/*******************************************************************************
* Function Name  : SCSI_Start_Stop_Unit_Cmd
* Description    : SCSI Start_Stop_Unit Command routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SCSI_Start_Stop_Unit_Cmd(unsigned char lun)
{
  	Set_CSW (CSW_CMD_PASSED, SEND_CSW_ENABLE);
}

/*******************************************************************************
* Function Name  : SCSI_Read10_Cmd
* Description    : SCSI Read10 Command routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SCSI_Read10_Cmd(unsigned char lun , unsigned int LBA , unsigned int BlockNbr)
{
	unsigned int i;
	unsigned int Offset;

	if (TransferState == TXFR_IDLE )
	{
	  Offset = LBA * Mass_Block_Size[lun];
//	  Length = BlockNbr * Mass_Block_Size[lun];
	  TransferState = TXFR_ONGOING;
	}
	
	if (TransferState == TXFR_ONGOING )
	{
		//HAL_SF_Init();//main 函数中放在usb初始化前, 否则必须在此初始化
		for(i=0;i<BlockNbr;i++)
		{					
			//HAL_SF_ReadData(Offset , Mass_Block_Size[lun], Data_Buffer);
			memset(Data_Buffer,0xff,Mass_Block_Size[lun]);
			HAL_USB_BulkIn(2,Data_Buffer,Mass_Block_Size[lun]);			
			Offset+=Mass_Block_Size[lun];
		}

		//Block_offset = 0;
		TransferState = TXFR_IDLE;

	}
	Set_CSW (CSW_CMD_PASSED, SEND_CSW_ENABLE);

}

/*******************************************************************************
* Function Name  : SCSI_Verify10_Cmd
* Description    : SCSI Verify10 Command routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SCSI_Verify10_Cmd(unsigned char lun)
{
  if ((CBW.dDataLength == 0) && !(CBW.CB[1] & BLKVFY))/* BLKVFY not set*/
  {
    Set_CSW (CSW_CMD_PASSED, SEND_CSW_ENABLE);
  }
  else
  {
    Bot_Abort(BOTH_DIR);
    Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, INVALID_FIELED_IN_COMMAND);
    Set_CSW (CSW_CMD_FAILED, SEND_CSW_DISABLE);
  }
}
/*******************************************************************************
* Function Name  : SCSI_Valid_Cmd
* Description    : Valid Commands routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SCSI_Valid_Cmd(unsigned char lun)
{
  if (CBW.dDataLength != 0)
  {
    Bot_Abort(BOTH_DIR);
    Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, INVALID_COMMAND);
    Set_CSW (CSW_CMD_FAILED, SEND_CSW_DISABLE);
  }
  else
    Set_CSW (CSW_CMD_PASSED, SEND_CSW_ENABLE);
}
/*******************************************************************************
* Function Name  : SCSI_Valid_Cmd
* Description    : Valid Commands routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SCSI_TestUnitReady_Cmd(unsigned char lun)
{
    Set_CSW (CSW_CMD_PASSED, SEND_CSW_ENABLE);
}

/*******************************************************************************
* Function Name  : SCSI_ReadToc_Cmd
* Description    : SCSI ReadToc Cmd.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SCSI_ReadToc_Cmd(unsigned char lun)
{
	unsigned char length = 0;

	length = CBW.CB[8];

	
	if(CBW.dDataLength < length)
    {
        length = CBW.dDataLength;
    }
   
    length = (length > 20) ? 20: length;

    Transfer_Data_Request(ReadTOC_Data, length);	
	Set_CSW (CSW_CMD_PASSED, SEND_CSW_ENABLE);//###
}

/*******************************************************************************
* Function Name  : SCSI_Invalid_Cmd
* Description    : Invalid Commands routine
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SCSI_Invalid_Cmd(unsigned char lun)
{
  if (CBW.dDataLength == 0)
  {
    Bot_Abort(DIR_IN);
  }
  else
  {
    if ((CBW.bmFlags & 0x80) != 0)
    {
      Bot_Abort(DIR_IN);
    }
    else
    {
      Bot_Abort(BOTH_DIR);
    }
  }
  Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, INVALID_COMMAND);
  Set_CSW (CSW_CMD_FAILED, SEND_CSW_DISABLE);
}

void Mass_Storage_In (void)
{
  switch (Bot_State)
  {
    case BOT_CSW_Send:
    case BOT_ERROR:
      Bot_State = BOT_IDLE;
      break;
    case BOT_DATA_IN:
      switch (CBW.CB[0])
      {
        case SCSI_READ10:
          SCSI_Read10_Cmd(CBW.bLUN , SCSI_LBA , SCSI_BlkLen);
          break;
      }
      break;
    case BOT_DATA_IN_LAST:
      Set_CSW (CSW_CMD_PASSED, SEND_CSW_ENABLE);
      break;

    default:
      break;
  }
}


void Command(void);

/*******************************************************************************
* Function Name  : CBW_Decode
* Description    : Decode the received CBW and call the related SCSI command
*                 routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void CBW_Decode(void)
{
  unsigned int Counter;
  unsigned short slength = 0,len1;
  unsigned char buf;

  for (Counter = 0; Counter < Data_Len; Counter++)
  {
    *((unsigned char *)&CBW + Counter) = g_b_MassComm[Counter];
  }
  
  CBW.dDataLength = SW32(CBW.dDataLength);

  CSW.dTag = CBW.dTag;
  CSW.dDataResidue = CBW.dDataLength;
  if (Data_Len != BOT_CBW_PACKET_LENGTH)
  {
    Bot_Abort(BOTH_DIR);
    /* reset the CBW.dSignature to desible the clear feature until receiving a Mass storage reset*/
    CBW.dSignature = 0;
    Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, PARAMETER_LIST_LENGTH_ERROR);
    Set_CSW (CSW_CMD_FAILED, SEND_CSW_DISABLE);
    return;
  }

  if ((CBW.CB[0] == SCSI_READ10 ) || (CBW.CB[0] == SCSI_WRITE10 ))
  {
    /* Calculate Logical Block Address */
    SCSI_LBA = (CBW.CB[2] << 24) | (CBW.CB[3] << 16) | (CBW.CB[4] <<  8) | CBW.CB[5];
    /* Calculate the Number of Blocks to transfer */
    SCSI_BlkLen = (CBW.CB[7] <<  8) | CBW.CB[8];
  }

  if (CBW.dSignature == BOT_CBW_SIGNATURE)
  {
    /* Valid CBW */
    if ((CBW.bLUN > Max_Lun) || (CBW.bCBLength < 1) || (CBW.bCBLength > 16))
    {
      Bot_Abort(BOTH_DIR);
      Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, INVALID_FIELED_IN_COMMAND);
      Set_CSW (CSW_CMD_FAILED, SEND_CSW_DISABLE);
    }
    else
    {
      switch (CBW.CB[0])
      {
        case SCSI_REQUEST_SENSE:
          SCSI_RequestSense_Cmd (CBW.bLUN);
		  break;

        case SCSI_INQUIRY:
			SCSI_Inquiry_Cmd(CBW.bLUN);
			break;

        case SCSI_START_STOP_UNIT:
			SCSI_Start_Stop_Unit_Cmd(CBW.bLUN);
			break;
        case SCSI_ALLOW_MEDIUM_REMOVAL:
			SCSI_Start_Stop_Unit_Cmd(CBW.bLUN);
		  	break;
        case SCSI_MODE_SENSE6:
          SCSI_ModeSense6_Cmd (CBW.bLUN);
          break;
        case SCSI_MODE_SENSE10:
          SCSI_ModeSense10_Cmd (CBW.bLUN);
          break;
        case SCSI_READ_FORMAT_CAPACITIES:
          SCSI_ReadFormatCapacity_Cmd(CBW.bLUN);
		  break;

        case SCSI_READ_CAPACITY10:
          SCSI_ReadCapacity10_Cmd(CBW.bLUN);
		  break;

        case SCSI_TEST_UNIT_READY:
		  	SCSI_TestUnitReady_Cmd(CBW.bLUN);
		  break;

        case SCSI_READ10:
          SCSI_Read10_Cmd(CBW.bLUN, SCSI_LBA , SCSI_BlkLen);
          break;
        case SCSI_VERIFY10:
          SCSI_Verify10_Cmd(CBW.bLUN);
          break;
        case SCSI_FORMAT_UNIT:
          SCSI_Format_Cmd(CBW.bLUN);
          break;
          /*Unsupported command*/
   		case SCSI_WRITE10:
          SCSI_Write10_Cmd(CBW.bLUN);
          break;
        case SCSI_MODE_SELECT10:
          SCSI_Mode_Select10_Cmd(CBW.bLUN);
          break;
        case SCSI_MODE_SELECT6:
          SCSI_Mode_Select6_Cmd(CBW.bLUN);
          break;

        case SCSI_SEND_DIAGNOSTIC:
          SCSI_Send_Diagnostic_Cmd(CBW.bLUN);
          break;
        case SCSI_READ6:
          SCSI_Read6_Cmd(CBW.bLUN);
          break;
        case SCSI_READ12:
          SCSI_Read12_Cmd(CBW.bLUN);
          break;
        case SCSI_READ16:
          SCSI_Read16_Cmd(CBW.bLUN);
          break;
        case SCSI_READ_CAPACITY16:
          SCSI_READ_CAPACITY16_Cmd(CBW.bLUN);
          break;
        case SCSI_WRITE6:
          SCSI_Write6_Cmd(CBW.bLUN);
          break;
        case SCSI_WRITE12:
          SCSI_Write12_Cmd(CBW.bLUN);
          break;
        case SCSI_WRITE16:
          SCSI_Write16_Cmd(CBW.bLUN);
          break;
        case SCSI_VERIFY12:
          SCSI_Verify12_Cmd(CBW.bLUN);
          break;
        case SCSI_VERIFY16:
          SCSI_Verify16_Cmd(CBW.bLUN);
	   break;
	case SCSI_READTOC:
	   SCSI_ReadToc_Cmd(CBW.bLUN);
          break;
	case SCSI_COMMAND:
	  {
	  	unsigned char cmd[6];
			//接收指令
		slength = 0;
		slength =  (CBW.CB[8] +(CBW.CB[7] << 8)) ;

#if 0
		if(slength>512&&(slength%512)==6)
		{
			usb_receiveData_DMA(cmd,g_b_MassComm,slength);
			g_APDU.CLA = cmd[0];
			g_APDU.INS = cmd[1];
			g_APDU.PP1 = cmd[2];
			g_APDU.PP2 = cmd[3];
			g_APDU.LEN[0] = cmd[4];
			g_APDU.LEN[1] = cmd[5];

			g_APDU.pInData=g_b_MassComm;
			g_APDU.pOutData=g_b_MassComm+8*1024;
			
			if(slength==4)
			{
				g_APDU.LC =0;
			}
			else if(slength==6)
			{
				g_APDU.LC=(cmd[4]<<8)+cmd[5];
			}
			else 
			{
				g_APDU.LC = slength - 6;	
			}
		}
			
		else
		{
			usb_receive(g_b_MassComm,slength);
			g_APDU.CLA = g_b_MassComm[0];
			g_APDU.INS = g_b_MassComm[1];
			g_APDU.PP1 = g_b_MassComm[2];
			g_APDU.PP2 = g_b_MassComm[3];
			g_APDU.LEN[0] = g_b_MassComm[4];
			g_APDU.LEN[1] = g_b_MassComm[5];

			g_APDU.pInData=g_b_MassComm+8;
			g_APDU.pOutData=g_b_MassComm+8*1024;
			
			if(slength==4)
			{
				g_APDU.LC =0;
			}
			else if(slength==6)
			{
				g_APDU.LC=(g_b_MassComm[4]<<8)+g_b_MassComm[5];
			}
			else 
			{
				g_APDU.LC = slength - 6;	
//				memcpy(g_APDU.pInData, g_b_MassComm+6, g_APDU.LC);
				memmove(g_APDU.pInData, g_b_MassComm+6, g_APDU.LC);
			}
		}
		
#else
				
		memset(g_b_MassComm, 0, 6);
		HAL_USB_BulkOut(1, g_b_MassComm, &slength,1);

		g_APDU.CLA = g_b_MassComm[0];
		g_APDU.INS = g_b_MassComm[1];
		g_APDU.PP1 = g_b_MassComm[2];
		g_APDU.PP2 = g_b_MassComm[3];
		g_APDU.LEN[0] = g_b_MassComm[4];
		g_APDU.LEN[1] = g_b_MassComm[5];

		g_APDU.pInData=g_b_MassComm;
		g_APDU.pOutData=g_b_MassComm+8*1024;
	
		if(slength==4)
		{
			g_APDU.LC =0;
		}
		else if(slength==6)
		{
			g_APDU.LC=(g_b_MassComm[4]<<8)+g_b_MassComm[5];
		}
		else 
		{
			g_APDU.LC = slength - 6;	
			//memcpy(g_APDU.pInData, g_b_MassComm+6, g_APDU.LC);
			memmove(g_APDU.pInData, g_b_MassComm+6, g_APDU.LC);
		}

#endif	
		Command();
		G_UMS = 0;
		G_CMD=1;
		Set_CSW (CSW_CMD_PASSED, SEND_CSW_ENABLE);
		if(g_led_flag==1)
		{
			g_led_flag=0;
			SPIDDR&=~0x08;
		}
		break;
	   }
	case SCSI_RESPONSE:
	  {		

		if(g_reboot==1)
			g_reboot=2;
		if(g_reboot==3)
			g_reboot=4;

		g_APDU.pOutData[g_APDU.RLE] = g_APDU.SW1;
		g_APDU.pOutData[g_APDU.RLE+1] = g_APDU.SW2;	
		usb_send_DMA_Test(g_APDU.pOutData,g_APDU.RLE+2);
//		Transfer_Data_Request(g_APDU.pOutData,g_APDU.RLE+2);
		G_UMS = 0;
		Set_CSW (CSW_CMD_PASSED, SEND_CSW_ENABLE);
		}
		if(g_led_flag==1)
		{
			g_led_flag=0;
			SPIDDR&=~0x08;
		}
          break;
        default:
        {
         	//Bot_Abort(BOTH_DIR);
			SCSI_BlkLen = (CBW.CB[7] <<  8) | CBW.CB[8];

			if(SCSI_BlkLen)
			{
				buf = 0;
				SCSI_BlkLen = 0;
				Transfer_Data_Request(&buf, 1);
			}
	          
	        Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, INVALID_COMMAND);
	        Set_CSW (CSW_CMD_FAILED, SEND_CSW_DISABLE);
	     }  
      }
    }
  }
  else
  {
    /* Invalid CBW */
    Bot_Abort(BOTH_DIR);
    Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, INVALID_COMMAND);
    Set_CSW (CSW_CMD_FAILED, SEND_CSW_DISABLE);
  }

}

/*******************************************************************************
* Function Name  : Mass_Storage_Out
* Description    : Mass Storage OUT transfer.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Mass_Storage_Out (void)
{
  unsigned char CMD;
  CMD = CBW.CB[0];

  switch (Bot_State)
  {
    case BOT_IDLE:
      CBW_Decode();
      break;
    case BOT_DATA_OUT:
      Bot_Abort(DIR_OUT);
      Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, INVALID_FIELED_IN_COMMAND);
      Set_CSW (CSW_PHASE_ERROR, SEND_CSW_DISABLE);
      break;
    default:
      Bot_Abort(BOTH_DIR);
      Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, INVALID_FIELED_IN_COMMAND);
      Set_CSW (CSW_PHASE_ERROR, SEND_CSW_DISABLE);
      break;
  }
}

