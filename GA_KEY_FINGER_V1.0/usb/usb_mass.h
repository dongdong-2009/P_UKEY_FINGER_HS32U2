#ifndef __MID_USB_MASS_H
#define __MID_USB_MASS_H

#define SCSI_FORMAT_UNIT                            0x04
#define SCSI_INQUIRY                                0x12
#define SCSI_MODE_SELECT6                           0x15
#define SCSI_MODE_SELECT10                          0x55
#define SCSI_MODE_SENSE6                            0x1A
#define SCSI_MODE_SENSE10                           0x5A
#define SCSI_ALLOW_MEDIUM_REMOVAL                   0x1E
#define SCSI_READ6                                  0x08
#define SCSI_READ10                                 0x28
#define SCSI_READ12                                 0xA8
#define SCSI_READ16                                 0x88

#define SCSI_READ_CAPACITY10                        0x25
#define SCSI_READ_CAPACITY16                        0x9E

#define SCSI_REQUEST_SENSE                          0x03
#define SCSI_START_STOP_UNIT                        0x1B
#define SCSI_TEST_UNIT_READY                        0x00
#define SCSI_WRITE6                                 0x0A
#define SCSI_WRITE10                                0x2A
#define SCSI_WRITE12                                0xAA
#define SCSI_WRITE16                                0x8A

#define SCSI_VERIFY10                               0x2F
#define SCSI_VERIFY12                               0xAF
#define SCSI_VERIFY16                               0x8F
#define SCSI_READTOC				0x43

#define SCSI_COMMAND				0xFE
#define SCSI_RESPONSE				0xFD

#define SCSI_SEND_DIAGNOSTIC                        0x1D
#define SCSI_READ_FORMAT_CAPACITIES                 0x23

#define NO_SENSE		                    0
#define RECOVERED_ERROR		                    1
#define NOT_READY		                    2
#define MEDIUM_ERROR		                    3
#define HARDWARE_ERROR		                    4
#define ILLEGAL_REQUEST		                    5
#define UNIT_ATTENTION		                    6
#define DATA_PROTECT		                    7
#define BLANK_CHECK		                    8
#define VENDOR_SPECIFIC		                    9
#define COPY_ABORTED		                    10
#define ABORTED_COMMAND		                    11
#define VOLUME_OVERFLOW		                    13
#define MISCOMPARE		                    14


#define INVALID_COMMAND                             0x20
#define INVALID_FIELED_IN_COMMAND                   0x24
#define PARAMETER_LIST_LENGTH_ERROR                 0x1A
#define INVALID_FIELD_IN_PARAMETER_LIST             0x26
#define ADDRESS_OUT_OF_RANGE                        0x21
#define MEDIUM_NOT_PRESENT 			    0x3A
#define MEDIUM_HAVE_CHANGED			    0x28

#define READ_FORMAT_CAPACITY_DATA_LEN               0x0C
#define READ_CAPACITY10_DATA_LEN                    0x08
#define MODE_SENSE10_DATA_LEN                       0x08
#define MODE_SENSE6_DATA_LEN                        0x0c
#define REQUEST_SENSE_DATA_LEN                      0x12
#define STANDARD_INQUIRY_DATA_LEN                   0x24
#define BLKVFY                                      0x04

typedef struct _Bulk_Only_CBW
{
  unsigned int dSignature;
  unsigned int dTag;
  unsigned int dDataLength;
  unsigned char  bmFlags;
  unsigned char  bLUN;
  unsigned char  bCBLength;
  unsigned char  CB[16];
}
Bulk_Only_CBW;

/* Bulk-only Command Status Wrapper */
typedef struct _Bulk_Only_CSW
{
  unsigned int dSignature;
  unsigned int dTag;
  unsigned int dDataResidue;
  unsigned char  bStatus;
}
Bulk_Only_CSW;

#define BOT_IDLE                      0       /* Idle state */
#define BOT_DATA_OUT                  1       /* Data Out state */
#define BOT_DATA_IN                   2       /* Data In state */
#define BOT_DATA_IN_LAST              3       /* Last Data In Last */
#define BOT_CSW_Send                  4       /* Command Status Wrapper */
#define BOT_ERROR                     5       /* error state */

#define BOT_CBW_SIGNATURE             0x55534243
#define BOT_CSW_SIGNATURE             0x55534253
#define BOT_CBW_PACKET_LENGTH         31

#define CSW_DATA_LENGTH               0x000D

/* CSW Status Definitions */
#define CSW_CMD_PASSED                0x00
#define CSW_CMD_FAILED                0x01
#define CSW_PHASE_ERROR               0x02

#define SEND_CSW_DISABLE              0
#define SEND_CSW_ENABLE               1

#define DIR_IN                        0
#define DIR_OUT                       1
#define BOTH_DIR                      2

#define MAL_OK   0
#define MAL_FAIL 1
#define MAX_LUN  0

#define TXFR_IDLE     0
#define TXFR_ONGOING  1

#define BULK_MAX_PACKET_SIZE	0x40

extern unsigned char G_UMS;
extern unsigned char G_CMD;

extern  unsigned char Page00_Inquiry_Data[];
extern  unsigned char Standard_Inquiry_Data[];
extern  unsigned char Standard_Inquiry_Data2[];
extern  unsigned char Standard_Inquiry_Data3[];
extern  unsigned char Mode_Sense6_data[];
extern  unsigned char Mode_Sense10_data[];
extern  unsigned char Scsi_Sense_Data[];
extern  unsigned char Scsi_Sense_Data_A[];
extern  unsigned char ReadCapacity10_Data[];
extern  unsigned char ReadFormatCapacity_Data[];
extern  unsigned char ReadTOC_Data[];
extern  unsigned char ReadTOC_Data1[];
extern  unsigned int Max_Lun;
extern  unsigned short Data_Len;

#define SCSI_Prevent_Removal_Cmd         SCSI_Valid_Cmd

/* Invalid (Unsupported) commands */
#define SCSI_Format_Cmd				SCSI_Invalid_Cmd
#define SCSI_READ_CAPACITY16_Cmd         SCSI_Invalid_Cmd
#define SCSI_Write10_Cmd              SCSI_Invalid_Cmd
#define SCSI_Write6_Cmd                  SCSI_Invalid_Cmd
#define SCSI_Write16_Cmd                 SCSI_Invalid_Cmd
#define SCSI_Write12_Cmd                 SCSI_Invalid_Cmd
#define SCSI_Read6_Cmd                   SCSI_Invalid_Cmd
#define SCSI_Read12_Cmd                  SCSI_Invalid_Cmd
#define SCSI_Read16_Cmd                  SCSI_Invalid_Cmd
#define SCSI_Send_Diagnostic_Cmd         SCSI_Invalid_Cmd
#define SCSI_Mode_Select6_Cmd            SCSI_Invalid_Cmd
#define SCSI_Mode_Select10_Cmd           SCSI_Invalid_Cmd
#define SCSI_Verify12_Cmd                SCSI_Invalid_Cmd
#define SCSI_Verify16_Cmd                SCSI_Invalid_Cmd

void Mass_Storage_Out (void);

#endif //__MID_USB_MASS_H

