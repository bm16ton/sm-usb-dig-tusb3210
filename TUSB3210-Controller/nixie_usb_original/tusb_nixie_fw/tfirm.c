#include <8052.h>
#include "types.h"
#include "usbdefs.h"
#include "tusb2136.h"
#include "descrip.h"
#include "usbiofun.h"
#include "commands.h"

#define MAX_MSP_XMT_BLOCK 124

/* Global variables */
BYTE deviceReady = FALSE;
BYTE bStatusAction;
BYTE bUsbDeviceAddress;
WORD wDeviceFeatures = 0;
WORD wBytesRemainingOnIEP0;
WORD wBytesRemainingOnOEP0;
PBYTE pbIEP0Buffer;
PBYTE pbOEP0Buffer;
BYTE bConfigurationNumber = 0;
BYTE bInterfaceNumber = 0;

BYTE bSuspended = FALSE;

BYTE gbIdleRateL;
BYTE gbIdleRateH;
BYTE gbProtocol=1; // default is report protocol

BOOL bHostAskMoreDataThanAvailable;

BOOL bCurrentBuffer;
#define X_BUFFER 0
#define Y_BUFFER 1

void usbReceiveDataPacketOnEP0(PBYTE pbBuffer);
void usbStallEndpoint0(void);
void usbSendZeroLengthPacketOnIEP0(void);
void usbSendNextPacketOnIEP0(void);
void usbSendDataPacketOnEP0(PBYTE pbBuffer);

/* Setup packet */
xdata at 0xff00 tDEVICE_REQUEST tSetupPacket;

/* Endpoint 0 descriptor */
xdata at 0xff80 tEDB0 tEndPoint0DescriptorBlock;

/* Endpoint descriptor blocks */
xdata at 0xff48 tEDB tInputEndPointDescriptorBlock[3];
xdata at 0xff08 tEDB tOutputEndPointDescriptorBlock[3];

/* EP0 Buffers */
xdata at 0xfef0 BYTE abOEP0Buffer[EP0_MAX_PACKET_SIZE];
xdata at 0xfef8 BYTE abIEP0Buffer[EP0_MAX_PACKET_SIZE];

/* Device descriptor */
xdata at 0xfe80 BYTE abDescriptor[SIZEOF_DEVICE_DESCRIPTOR];

/* EP1 Buffer addresses */
xdata at 0xfd80 BYTE pbOEP1XBufferAddress[EP_MAX_PACKET_SIZE];
xdata at 0xfdc0 BYTE pbOEP1YBufferAddress[EP_MAX_PACKET_SIZE];
xdata at 0xfe00 BYTE pbIEP1XBufferAddress[EP_MAX_PACKET_SIZE];
xdata at 0xfe40 BYTE pbIEP1YBufferAddress[EP_MAX_PACKET_SIZE];

/* ID bytes in internal mem */
BYTE ID1;
BYTE ID2;
BYTE FIRMWARE_VERSION;

/* OEP1 data save buffer in internl mem */
BYTE bOEP1RecieveLength;
BYTE bOEP1SaveBufferPosition;
idata BYTE abOEP1SaveBuffer[80];
idata BYTE abIEP1SaveBuffer[80];

BYTE total = 0;

void usbSendZeroLengthPacketOnIEP0(void) {
  wBytesRemainingOnIEP0 = NO_MORE_DATA;
  bStatusAction = STATUS_ACTION_NOTHING;
  tEndPoint0DescriptorBlock.bIEPBCNT = 0x00;
}

void usbSetEndpointHalt(void) {
  tInputEndPointDescriptorBlock[0].bEPCNF &= ~EPCNF_UBME;
  usbSendZeroLengthPacketOnIEP0();
}

void usbClearEndpointHalt(void) {
  tInputEndPointDescriptorBlock[0].bEPCNF |= EPCNF_UBME;  
  usbSendZeroLengthPacketOnIEP0();
}


void usbGetConfiguration(void) {
  wBytesRemainingOnIEP0 = 1;
  usbSendDataPacketOnEP0((PBYTE) &bConfigurationNumber);
}

void usbSetConfiguration(void) {
  usbStallOEP0;
  bConfigurationNumber = tSetupPacket.bValueL;
  usbSendZeroLengthPacketOnIEP0();
}

void usbSetIdle(void) {
  gbIdleRateL = tSetupPacket.bValueL;
  gbIdleRateH = tSetupPacket.bValueH;
  usbSendZeroLengthPacketOnIEP0();
}

void usbGetIdle(void) {
  wBytesRemainingOnIEP0 = 1;
  usbSendDataPacketOnEP0(&gbIdleRateH);
}

void usbSetInterface(void) {
  usbStallOEP0;                             // control write without data stage
  bInterfaceNumber = tSetupPacket.bIndexL;
  usbSendZeroLengthPacketOnIEP0();
}

void usbGetInterface(void) {
  wBytesRemainingOnIEP0 = 1;
  usbSendDataPacketOnEP0((PBYTE) &bInterfaceNumber);
}


void usbSetProtocol(void) {
  gbProtocol = tSetupPacket.bValueL;
  usbSendZeroLengthPacketOnIEP0();
}

void usbGetProtocol(void) {
  wBytesRemainingOnIEP0 = 1;
  usbSendDataPacketOnEP0(&gbProtocol);
}


void usbSetAddress(void) {
  if(tSetupPacket.bValueL < 128)
    {
      bFUNADR = tSetupPacket.bValueL;
      bUsbDeviceAddress = tSetupPacket.bValueL;
      bStatusAction = STATUS_ACTION_SET_ADDRESS;
      usbSendZeroLengthPacketOnIEP0();
    }
  else 
    usbStallEndpoint0();
}


void usbSetRemoteWakeup(void) {
  bUSBCTL |= USBCTL_RWE;
  wDeviceFeatures |= 0x0200;
  usbStallOEP0;
  usbSendZeroLengthPacketOnIEP0();
}

void usbClearRemoteWakeup(void) {
  bUSBCTL &= ~USBCTL_RWE;
  wDeviceFeatures &= ~0x0200;
  usbStallOEP0;
  usbSendZeroLengthPacketOnIEP0();
}

void usbSetReport(void) {
  wBytesRemainingOnOEP0 = 1;
}


void usbGetEndpointStatus(void) {
  WORD wEndpointStatus = 0x0100;
  if(tInputEndPointDescriptorBlock[0].bEPCNF & EPCNF_UBME)
    wEndpointStatus = 0x0000;
  
  wBytesRemainingOnIEP0 = 2;
  usbSendDataPacketOnEP0((PBYTE) &wEndpointStatus);
}

void usbGetDeviceStatus(void) {
  wBytesRemainingOnIEP0 = 2;
  usbSendDataPacketOnEP0((PBYTE) &wDeviceFeatures);
}

void usbGetInterfaceStatus(void) {
  WORD wStatusBuffer = 0x00;      
  usbStallOEP0;
  wBytesRemainingOnIEP0 = 2;
  usbSendDataPacketOnEP0((PBYTE) &wStatusBuffer);
}


void usbGetReportDescriptor(void) {
  usbClearOEP0ByteCount;
  wBytesRemainingOnIEP0 = SIZEOF_REPORT_DESCRIPTOR;
}


void usbGetConfigurationDescriptor(void) {
  BYTE bTemp;
  // Copy the DEVICE DESCRIPTOR from program "ROM" to XRAM
  for(bTemp=0;bTemp<SIZEOF_BOOTCODE_CONFIG_DESC_GROUP;bTemp++)
    abDescriptor[bTemp] = abromConfigurationDescriptorGroup[bTemp];

  abDescriptor[7] = 0x80;  

  usbClearOEP0ByteCount;
  wBytesRemainingOnIEP0 = SIZEOF_BOOTCODE_CONFIG_DESC_GROUP;
  usbSendDataPacketOnEP0((PBYTE)&abDescriptor);
}


void usbGetHIDDescriptor(void) {
  BYTE bTemp;
  // Copy the DEVICE DESCRIPTOR from program "ROM" to XRAM
  for(bTemp=0;bTemp<SIZEOF_DEVICE_DESCRIPTOR;bTemp++)
    abDescriptor[bTemp] = abromConfigurationDescriptorGroup[SIZEOF_CONFIG_DESCRIPTOR+SIZEOF_INTERFACE_DESCRIPTOR + bTemp];
  
  usbClearOEP0ByteCount;
  wBytesRemainingOnIEP0 = SIZEOF_KEYBD_HID_DESCRIPTOR;
  usbSendDataPacketOnEP0((PBYTE)&abDescriptor);
}

void usbGetDeviceDescriptor(void) {
  BYTE bTemp;

  for(bTemp=0;bTemp<SIZEOF_DEVICE_DESCRIPTOR;bTemp++)
    abDescriptor[bTemp] = abromDeviceDescriptor[bTemp];
  
  abDescriptor[OFFSET_DEVICE_DESCRIPTOR_CLASS] = 0xFF;
  abDescriptor[OFFSET_DEVICE_DESCRIPTOR_VID_L] = 0x51;
  abDescriptor[OFFSET_DEVICE_DESCRIPTOR_VID_H] = 0x04;
  abDescriptor[OFFSET_DEVICE_DESCRIPTOR_PID_L] = 0x10;
  abDescriptor[OFFSET_DEVICE_DESCRIPTOR_PID_H] = 0x32;
  abDescriptor[OFFSET_DEVICE_DESCRIPTOR_VER_L] = 0x00;
  abDescriptor[OFFSET_DEVICE_DESCRIPTOR_VER_H] = 0x01;
  
  abDescriptor[OFFSET_DEVICE_DESCRIPTOR_IMFG] = 0x00;
  abDescriptor[OFFSET_DEVICE_DESCRIPTOR_IPROD] = 0x00;
  abDescriptor[OFFSET_DEVICE_DESCRIPTOR_ISN] = 0x01;
  
  usbClearOEP0ByteCount;
  wBytesRemainingOnIEP0 = SIZEOF_DEVICE_DESCRIPTOR;
  usbSendDataPacketOnEP0((PBYTE)&abDescriptor);
  // Once the Device Descriptor has been sent, the device can essentially
  // function.  Thus we enable the deviceReady variable so that the main
  // code in keyboard.c knows that it can begin the service loop.
  deviceReady = TRUE;    
}


void usbGetStringDescriptor(void) {

  usbClearOEP0ByteCount;
  wBytesRemainingOnIEP0 = SIZEOF_DEVICE_DESCRIPTOR;
  usbSendDataPacketOnEP0((PBYTE)&abDescriptor);
}


void usbNonStandardRequest(void) {
  usbStallEndpoint0();
}

void usbStallEndpoint0(void) {
  tEndPoint0DescriptorBlock.bIEPCNFG |= EPCNF_STALL;
  tEndPoint0DescriptorBlock.bOEPCNFG |= EPCNF_STALL;
}

/* Compare structure */
typedef struct _tDEVICE_REQUEST_COMPARE
{
  BYTE    bmRequestType;              // See bit definitions below
  BYTE    bRequest;                   // See value definitions below
  BYTE    bValueL;                    // Meaning varies with request type
  BYTE    bValueH;                    // Meaning varies with request type
  BYTE    bIndexL;                    // Meaning varies with request type
  BYTE    bIndexH;                    // Meaning varies with request type
  BYTE    bLengthL;                   // Number of bytes of data to transfer (LSByte)
  BYTE    bLengthH;                   // Number of bytes of data to transfer (MSByte)
  BYTE    bCompareMask;
  VOID    (*pUsbFunction)(VOID);      // function pointer
} tDEVICE_REQUEST_COMPARE, *ptDEVICE_REQUEST_COMPARE;

/* Request compare list */

code tDEVICE_REQUEST_COMPARE tUsbRequestList[] =
  {
    // SET ENDPOINT FEATURE
    {USB_REQ_TYPE_OUTPUT | USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_ENDPOINT,
     USB_REQ_SET_FEATURE,
     FEATURE_ENDPOINT_STALL,0x00,
     0xff,0x00,
     0x00,0x00,
     0xf7,usbSetEndpointHalt},
    
    // CLEAR ENDPOINT FEATURE
    {USB_REQ_TYPE_OUTPUT | USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_ENDPOINT,
     USB_REQ_CLEAR_FEATURE,
     FEATURE_ENDPOINT_STALL,0x00,
     0xff,0x00,
     0x00,0x00,
     0xf7,usbClearEndpointHalt},


    // GET CONFIGURATION
    {USB_REQ_TYPE_INPUT | USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_DEVICE,
     USB_REQ_GET_CONFIGURATION,
     0x00,0x00,
     0x00,0x00,
     0x01,0x00,
     0xff,usbGetConfiguration},


    // SET CONFIGURATION This is needed for enumeration!
    {USB_REQ_TYPE_OUTPUT | USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_DEVICE,
     USB_REQ_SET_CONFIGURATION,
     0xff,0x00,
     0x00,0x00,
     0x00,0x00,
     0xdf,usbSetConfiguration},
    
    // GET DEVICE DESCRIPTOR
    {USB_REQ_TYPE_INPUT | USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_DEVICE,
     USB_REQ_GET_DESCRIPTOR,
     0xff,DESC_TYPE_DEVICE,                  // bValueL is index and bValueH is type
     0xff,0xff,
     0xff,0xff,
     0xd0,usbGetDeviceDescriptor},
    
    // GET CONFIGURATION DESCRIPTOR
    {USB_REQ_TYPE_INPUT | USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_DEVICE,
     USB_REQ_GET_DESCRIPTOR,
     0xff,DESC_TYPE_CONFIG,                  // bValueL is index and bValueH is type
     0xff,0xff,
     0xff,0xff,
     0xd0,usbGetConfigurationDescriptor},

    // GET HID DESCRIPTOR
    {USB_REQ_TYPE_INPUT | USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_INTERFACE,
     USB_REQ_GET_DESCRIPTOR,
     0xff,DESC_TYPE_HID,                  // bValueL is index and bValueH is type
     0xff,0xff,
     0xff,0xff,
     0xd0,usbGetHIDDescriptor},


    // GET STRING DESCRIPTOR
    {USB_REQ_TYPE_INPUT | USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_DEVICE,
     USB_REQ_GET_DESCRIPTOR,
     0xff,DESC_TYPE_STRING,                  // bValueL is index and bValueH is type
     0xff,0xff,
     0xff,0xff,
     0xd0,usbGetStringDescriptor},


    // GET REPORT DESCRIPTOR
    {USB_REQ_TYPE_INPUT | USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_INTERFACE,
     USB_REQ_GET_DESCRIPTOR,
     0xff,DESC_TYPE_REPORT,                 // bValueL is index and bValueH is type
     0xff,0xff,
     0xff,0xff,
     0xd0,usbGetReportDescriptor},


    // SET REPORT
    {USB_REQ_TYPE_OUTPUT | USB_REQ_TYPE_CLASS | USB_REQ_TYPE_INTERFACE,
     USB_REQ_SET_REPORT,
     0xff,0xFF,                 // bValueL is index and bValueH is type
     0xff,0xff,
     0xff,0xff,
     0xC0,usbSetReport},

    // SET IDLE
    {USB_REQ_TYPE_OUTPUT | USB_REQ_TYPE_CLASS | USB_REQ_TYPE_INTERFACE,
     USB_REQ_SET_IDLE,
     0xff,0xFF,                  // bValueL is index and bValueH is type
     0xff,0xff,
     0x00,0x00,
     0xc3,usbSetIdle},
    

    // SET PROTOCOL
    {USB_REQ_TYPE_OUTPUT | USB_REQ_TYPE_CLASS | USB_REQ_TYPE_INTERFACE,
     USB_REQ_SET_PROTOCOL,
     0xff,0xFF,                  // bValueL is index and bValueH is type
     0xff,0xff,
     0x00,0x00,
     0xc3,usbSetProtocol},


    // GET IDLE
    {USB_REQ_TYPE_INPUT | USB_REQ_TYPE_CLASS | USB_REQ_TYPE_INTERFACE,
     USB_REQ_GET_IDLE,
     0xff,0xFF,                  // bValueL is index and bValueH is type
     0xff,0xff,
     0x01,0x00,
     0xc3,usbGetIdle},


    // GET PROTOCOL
    {USB_REQ_TYPE_INPUT | USB_REQ_TYPE_CLASS | USB_REQ_TYPE_INTERFACE,
     USB_REQ_GET_PROTOCOL,
     0xff,0xFF,                  // bValueL is index and bValueH is type
     0xff,0xff,
     0x01,0x00,
     0xc3,usbGetProtocol},

    // GET INTERFACE
    {USB_REQ_TYPE_INPUT | USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_INTERFACE,
     USB_REQ_GET_INTERFACE,
     0x00,0x00,
     0xff,0xff,
     0x01,0x00,
     0xf3,usbGetInterface},
    
    // GET DEVICE STATUS
    {USB_REQ_TYPE_INPUT | USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_DEVICE,
     USB_REQ_GET_STATUS,
     0x00,0x00,
     0x00,0x00,
     0x02,0x00,
     0xff,usbGetDeviceStatus},
    
    // GET INTERFACE STATUS
    {USB_REQ_TYPE_INPUT | USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_INTERFACE,
     USB_REQ_GET_STATUS,
     0x00,0x00,
     0xff,0x00,
     0x02,0x00,
     0xf7,usbGetInterfaceStatus},
    
    // GET ENDPOINT STATUS
    {USB_REQ_TYPE_INPUT | USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_ENDPOINT,
     USB_REQ_GET_STATUS,
     0x00,0x00,
     0xff,0x00,
     0x02,0x00,
     0xf7,usbGetEndpointStatus},
    
    // SET ADDRESS
    {USB_REQ_TYPE_OUTPUT | USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_DEVICE,
     USB_REQ_SET_ADDRESS,
     0xff,0x00,
     0x00,0x00,
     0x00,0x00,
     0xdf,usbSetAddress},

    // SET DEVICE FEATURE
    {USB_REQ_TYPE_OUTPUT | USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_DEVICE,
     USB_REQ_SET_FEATURE,
     FEATURE_REMOTE_WAKEUP,0x00,           // feature selector
     0x00,0x00,
     0x00,0x00,
     0xff,usbSetRemoteWakeup}, // df, setDeviceFeature

    // CLEAR DEVICE FEATURE
    {USB_REQ_TYPE_OUTPUT | USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_DEVICE,
     USB_REQ_CLEAR_FEATURE,
     FEATURE_REMOTE_WAKEUP,0x00,
     0x00,0x00,
     0x00,0x00,
     0xff,usbClearRemoteWakeup},

    // SET INTERFACE FEATURE
    {USB_REQ_TYPE_OUTPUT | USB_REQ_TYPE_STANDARD | USB_REQ_TYPE_INTERFACE,
     USB_REQ_SET_INTERFACE,
     0xff,0x00,                      // alternative setting
     0xff,0x00,                      // interface number
     0x00,0x00,
     0xd7,usbSetInterface},
    
    // END OF LIST CATCH-ALL REQUEST: 
    // This will match any USB request sicne bCompareMask is 0x00.
    {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
     0x00,usbNonStandardRequest}
  };


void usbReset(void) {
  bFUNADR = 0x00;

  wBytesRemainingOnIEP0 = NO_MORE_DATA;
  wBytesRemainingOnOEP0 = NO_MORE_DATA;
  bStatusAction = STATUS_ACTION_NOTHING;

  pbIEP0Buffer = (PBYTE) 0x0000;
  pbOEP0Buffer = (PBYTE) 0x0000;

  bConfigurationNumber = 0;
  bInterfaceNumber = 0;

  tEndPoint0DescriptorBlock.bIEPCNFG = EPCNF_USBIE | EPCNF_UBME;
  tEndPoint0DescriptorBlock.bOEPCNFG = EPCNF_USBIE | EPCNF_UBME;

  tEndPoint0DescriptorBlock.bIEPBCNT  = EPBCNT_NAK;
  tEndPoint0DescriptorBlock.bOEPBCNT  = EPBCNT_NAK;

  //enable Input Endpoint 1 interrupt
  tInputEndPointDescriptorBlock[0].bEPCNF  = 0x00;
  tInputEndPointDescriptorBlock[0].bEPCNF   = EPCNF_USBIE | EPCNF_UBME;
  tInputEndPointDescriptorBlock[0].bEPBBAX  = (BYTE)(IEP1_X_BUFFER_ADDRESS >> 3 & 0x00ff);
  tInputEndPointDescriptorBlock[0].bEPBCTX  = EPBCT_NAK; //0x0000;
  tInputEndPointDescriptorBlock[0].bEPSIZXY = EP_MAX_PACKET_SIZE;
  tInputEndPointDescriptorBlock[0].bEPBCTX = EPBCT_NAK;

  // enable Output Endpoint 1 interrupt
  tOutputEndPointDescriptorBlock[0].bEPCNF = 0x00;
  //tOutputEndPointDescriptorBlock[0].bEPCNF |= EPCNF_USBIE | EPCNF_UBME | EPCNF_DBUF;
  tOutputEndPointDescriptorBlock[0].bEPCNF |= EPCNF_USBIE | EPCNF_UBME;
  tOutputEndPointDescriptorBlock[0].bEPBBAX = (BYTE)(OEP1_X_BUFFER_ADDRESS >> 3 & 0x00ff);
  tOutputEndPointDescriptorBlock[0].bEPBCTX = 0x00;
  tOutputEndPointDescriptorBlock[0].bEPBBAY = (BYTE)(OEP1_Y_BUFFER_ADDRESS >> 3 & 0x00ff);
  tOutputEndPointDescriptorBlock[0].bEPBCTY = 0x00;
  tOutputEndPointDescriptorBlock[0].bEPSIZXY = EP_MAX_PACKET_SIZE;

  bCurrentBuffer = X_BUFFER;
  bOEP1RecieveLength = 0x00;
  bOEP1SaveBufferPosition = 0x00;

  bUSBMSK = USBMSK_STPOW | USBMSK_SETUP | USBMSK_RSTR | USBMSK_RESR | USBMSK_SUSR;
  bHUBCNFG   |= (HUBCNFG_P3_FIXED | HUBCNFG_P1E | HUBCNFG_P2E | HUBCNFG_OCP);

  ID1 = 0x43;
  ID2 = 0x4d;
  FIRMWARE_VERSION = 0x00;
}


void SystemInitialization(void) {

  EA = DISABLE;

  bUSBCTL = 0x00;

  bMCNFG = (MCNFG_24MHZ | MCNFG_OVCE | MCNFG_XINT); // Set to 24Mhz

  //  bMCNFG = 0x80;


  EA = ENABLE;
  EX0 = ENABLE;
  
  usbReset();

  bUSBCTL = USBCTL_CONT;

}


void usbReceiveDataPacketOnEP0(PBYTE pbBuffer) {
  WORD wh = 0x00;
  WORD wl = 0x00;
  pbOEP0Buffer = pbBuffer;

  wh |= tSetupPacket.bLengthH;
  wh = (wh<<8);
  wl |= tSetupPacket.bLengthL;
  //wBytesRemainingOnOEP0 = (WORD)(tSetupPacket.bLengthH << 8) | (WORD)tSetupPacket.bLengthL;
  wBytesRemainingOnOEP0 = wh | wl;
  bStatusAction = STATUS_ACTION_DATA_OUT;
  usbClearOEP0ByteCount;            
}

void usbReceiveNextPacketOnOEP0(void) {
  BYTE bIndex,bByte;
  
  // First we must determine how many bytes were received in this data
  // packet.  We AND it with EPBCT_BYTECNT_MASK so that a NAK condition
  // will return "0 bytes."
  bByte = tEndPoint0DescriptorBlock.bOEPBCNT & EPBCT_BYTECNT_MASK;
  
  // If the number of bytes remaining to be received is greater than
  // or equal to the number of bytes received in this packet then
  // we handle the packet.  However, if we received more bytes than
  // we had expected we simply ignore the packet since it is
  // presumably erroneous.
  if(wBytesRemainingOnOEP0 >= (WORD)bByte)
    {
      // For each of the bytes received, we copy the value received to the
      // next position in the buffer we set aside for the OEP0 data.
      for(bIndex=0;bIndex<bByte;bIndex++)
	*pbOEP0Buffer++ = abOEP0Buffer[bIndex];
      
      // We now reduce the number of bytes remaining by the number of bytes
      // received in this packet.                              
      wBytesRemainingOnOEP0 -= (WORD)bByte;
      
      // If there are still more bytes to be received in additional packets (i.e.,
      // wBytesRemainingOnOEP0 is greater than zero), we clear the byte count and
      // reestablish bStatusAction to indicate that we are still in a DATA_OUT
      // condition.
      if(wBytesRemainingOnOEP0 > 0)
	{
	  usbClearOEP0ByteCount;        
	  bStatusAction = STATUS_ACTION_DATA_OUT;
	}
      else
	{
	  // If we aren't expecting any more data bytes, we terminate the OEP0
	  // transaction by stalling OEP0 and setting the bStatusAction condition
	  // to "Nothing."  Since in this firmware the only USB function that
	  // includes a subsequent data payload is the Set_Report function, we
	  // automatically update the keyboard LEDs with the new value.  If
	  // additional features are added that expect data payloads, calling
	  // the OEP0SetLeds() function when a Set_Report request was not
	  // received will cause no harm.
	  usbStallOEP0;
	  bStatusAction = STATUS_ACTION_NOTHING;        
	  //OEP0SetLEDs();
	}
    }

  else
    
    {
      // If the packet we received include more data than we expected, we ignore
      // the entire packet and abort the transfer.  This is accomplished by
      // stalling OEP0 and resetting the bStatusAction condition to "Nothing."
      usbStallOEP0;
      bStatusAction = STATUS_ACTION_NOTHING;
    }
}

void usbSendNextPacketOnIEP0(void) {
  BYTE bPacketSize,bIndex;
  
  // First check if there are bytes remaining to be transferred
  if(wBytesRemainingOnIEP0 != NO_MORE_DATA)
    {
      if(wBytesRemainingOnIEP0 > EP0_MAX_PACKET_SIZE)
	{
	  // More bytes are remaining than will fit in one packet
	  // there will be More IN Stage
	  bPacketSize = EP0_MAX_PACKET_SIZE;
	  wBytesRemainingOnIEP0 -= EP0_MAX_PACKET_SIZE;
	  bStatusAction = STATUS_ACTION_DATA_IN;
	}
      else if (wBytesRemainingOnIEP0 < EP0_MAX_PACKET_SIZE)
	{
	  // The remaining data will fit in one packet.
	  // This case will properly handle wBytesRemainingOnIEP0 == 0
	  bPacketSize = (BYTE)wBytesRemainingOnIEP0;
	  wBytesRemainingOnIEP0 = NO_MORE_DATA;  // No more data need to be Txed
	  bStatusAction = STATUS_ACTION_NOTHING;
	}
      else
	{
	  // wBytesRemainingOnIEP0 == EP0_MAX_PACKET_SIZE
	  bPacketSize = EP0_MAX_PACKET_SIZE;
	  if(bHostAskMoreDataThanAvailable == TRUE)
	    {
	      wBytesRemainingOnIEP0 = 0;
	      bStatusAction = STATUS_ACTION_DATA_IN;
	    }
	  else
	    { 
	      wBytesRemainingOnIEP0 = NO_MORE_DATA;
	      bStatusAction = STATUS_ACTION_NOTHING;
	    }
	}
      for(bIndex=0; bIndex<bPacketSize; bIndex++) 
	abIEP0Buffer[bIndex] = *pbIEP0Buffer++;
      
      tEndPoint0DescriptorBlock.bIEPBCNT = bPacketSize;   // & EPBCT_BYTECNT_MASK;
    }
  else
    {
      bStatusAction = STATUS_ACTION_NOTHING;
    }
}

void usbSendDataPacketOnEP0(PBYTE pbBuffer) {
  WORD wh = 0x00;
  WORD wl = 0x00;
  WORD wTemp;
  
  pbIEP0Buffer = pbBuffer;

  wh |= tSetupPacket.bLengthH;
  wh = (wh<<8);
  wl |= tSetupPacket.bLengthL;

  wTemp = wh | wl;
  
  // Limit transfer size to wLength if needed
  // this prevent USB device sending 'more than require' data back to host
  if(wBytesRemainingOnIEP0 >= wTemp)
    {
      wBytesRemainingOnIEP0 = wTemp;
      bHostAskMoreDataThanAvailable = FALSE;
    }
  else
    { 
      bHostAskMoreDataThanAvailable = TRUE;
    }
  
  usbSendNextPacketOnIEP0();
}

void usbDecodeAndProcessUsbRequest(void) { // from usb.c
  BYTE bMask,bResult,bTemp;
  BYTE *pbUsbRequestList;                 // save code space
  
  
  // We initialize the pbUsbRequestList pointer to the beginning of the
  // tUsbRequestList[] so that we can subsequently traverse the table
  // by incrementing the pbUsbRequestList pointer.
  pbUsbRequestList = (PBYTE) &tUsbRequestList[0];
  //pbUsbRequestList = tUsbRequestList;
  // Cycle indefinitely until we've found an entry in the tUsbRequestList[]
  // table.  Since the last entry in the table has a 0x00 mask, we'll
  // *always* find a match, so this cycle will always exit.
  while(1)
    {
      bResult = 0x00;
      bMask   = 0x80;
      
      // We cycle through fields 0 through 7, which correspond to the 8 fields
      // in each entry of tUsbRequestList.  If the given byte in the packet
      // we just receive is equal to the corresponding byte in the table, we
      // set that bit in the result, indicating a byte which matched.  Otherwise,
      // we don't set the bit which means that byte didn't match.
      for(bTemp = 0; bTemp < 8; bTemp++)
	{
	  if(*(pbEP0_SETUP_ADDRESS+bTemp) == *(pbUsbRequestList+bTemp)) 
	    bResult |= bMask;
	  bMask = bMask >> 1;
	}
      
      // At this point, bResult holds 8 bits which indicate whether each of the
      // bytes in the packet matched the corresponding bytes in the tUsbRequestList[]
      // table.  We then AND the mask value in the table with the result so that
      // we only are comparing the bits required in the mask.  If the resulting
      // value is equal to the mask, that means that all significant bytes match.
      // This is done since any bit that is clear in the mask is a "don't care", so
      // the AND makes sure we don't reject a "valid" comparison beause a don't 
      // care bit actually matched.
      if((*(pbUsbRequestList+bTemp) & bResult) == *(pbUsbRequestList+bTemp)) 
	break;
      // If we haven't found a matching entry yet, we advenced the pointer to point
      // to the next entry in the table, and keep looking.
      pbUsbRequestList += sizeof(tDEVICE_REQUEST_COMPARE);
    }
  
  // We check to see if any more setup packet(s) have been received and, if so, we
  // anbandon this one to hanlde the next one.
  if(bUSBSTA & (USBSTA_SETUP | USBSTA_STPOW) != 0x00) {
    return;
  }
  // If we've reached this point of the function, we've found the function that should
  // be called given the current request.  So we call it...
  ((ptDEVICE_REQUEST_COMPARE)pbUsbRequestList)->pUsbFunction();
}

void OEP0InterruptHandler(void) {
  // We clear the IEP0 byte count since we have nothing to send out.
  tEndPoint0DescriptorBlock.bIEPBCNT = 0x00;
  
  // We now handle the interrupt based on the bStatusAction condition.
  // If we are in a DATA_OUT condition, we call the usbReceiveNextPacketOnEP0
  // function to copy the data payload to its correct buffer.  If we are
  // not expecting any data on OEP0, we set the stall flag to stall the
  // endpoint and abort any additional data that may otherwise be
  // sent.
  if(bStatusAction == STATUS_ACTION_DATA_OUT) 
    usbReceiveNextPacketOnOEP0(); // Handle this data packet
  else 
    tEndPoint0DescriptorBlock.bOEPCNFG |= EPCNF_STALL; // We weren't expecting data
}

void IEP0InterruptHandler(void) {
  // We clear the OEP0 byte count since we are not expecting any data.
  tEndPoint0DescriptorBlock.bOEPBCNT = 0x00;
  
  // We now handle the interrupt based on the bStatusAction condition.
  // If we are in a DATA_IN condition, we call the usbSendNextPacketOnIEP0  
  // function to send the next data payload packet.  If we are in a
  // Set Address mode, we modify the address.  In any other case, we've
  // sent all teh data we had to send, so we stall the endpoint to indicate
  // there is no more data to send.
  if(bStatusAction == STATUS_ACTION_DATA_IN) 
    usbSendNextPacketOnIEP0(); // Send the next data packet
  /*
  else if(bStatusAction == STATUS_ACTION_SET_ADDRESS) 
    bFUNADR = bUsbDeviceAddress; // Set the device's address
  */
  else 
    tEndPoint0DescriptorBlock.bIEPCNFG |= EPCNF_STALL; // No more data to send
  //bIEPDCTX_1 = 0x02;
}

void OEP1InterruptHandler(void) {
  BYTE bSize, bTemp;

  BYTE xmt_size;
  BYTE rcv_size;

  bIEPDCTX_1 = 0x80;

  //Check if first packet

  if(bOEP1RecieveLength == 0x00) {
    bOEP1RecieveLength = pbOEP1XBufferAddress[1];    
    bSize = tOutputEndPointDescriptorBlock[0].bEPBCTX & EPBCT_BYTECNT_MASK;
    for(bTemp=0; bTemp<bSize; bTemp++) {
      abOEP1SaveBuffer[bOEP1SaveBufferPosition] = pbOEP1XBufferAddress[bTemp];
      
      bOEP1SaveBufferPosition++;
    }
    tOutputEndPointDescriptorBlock[0].bEPBCTX = 0x00;
  }

  else {

    bSize = tOutputEndPointDescriptorBlock[0].bEPBCTX & EPBCT_BYTECNT_MASK;
    for(bTemp=0; bTemp<bSize; bTemp++) {
      abOEP1SaveBuffer[bOEP1SaveBufferPosition] = pbOEP1XBufferAddress[bTemp];
      
      bOEP1SaveBufferPosition++;
    }
    tOutputEndPointDescriptorBlock[0].bEPBCTX = 0x00;
  }

  // Check if all data received

  if(bOEP1SaveBufferPosition < bOEP1RecieveLength)
    return; // All data not received

  bOEP1RecieveLength = 0x00;

  bOEP1SaveBufferPosition = 0x00;

  switch(abOEP1SaveBuffer[0]) {

  case CMD_01:
    fn_cmd_01();
    break;

  case CMD_02:
    fn_cmd_02();
    break;

  case CMD_03:
    fn_cmd_03();
    break;

  case CMD_04:
    fn_cmd_04();
    break;

  case CMD_05:
    fn_cmd_05();
    break;

  case CMD_06: // Send firmware data to host
    fn_cmd_06();
    break;

  case CMD_07:
    fn_cmd_07();
    break;

  case CMD_08:
    fn_cmd_08();
    break;

  default:
    break;
  }
  
  return;

}

void IEP1InterruptHandler() {
  return;
}

void SetupPacketInterruptHandler(void) { // From usb.c
  // Hardware clears STALL in both data endpoints once valid setup packet is
  // received.  NAK both data endpoints.
  tEndPoint0DescriptorBlock.bIEPBCNT  = EPBCNT_NAK;
  tEndPoint0DescriptorBlock.bOEPBCNT  = EPBCNT_NAK;
  
  bUSBSTA = USBSTA_SETUP; // from now, hardware will refer NAK bit in I/OEPBCNT
  
  // Copy the MSB of bmRequestType to DIR bit of USBCTL to indicate the
  // direction of the transfer.
  if((tSetupPacket.bmRequestType & USB_REQ_TYPE_INPUT) == USB_REQ_TYPE_INPUT)
    bUSBCTL |= USBCTL_DIR;
  else 
    bUSBCTL &= ~USBCTL_DIR;
  
  // Clear the bStatusAction to indicate that, at this point, nothing is 
  // happening (it may be set to DATA_OUT by specific functions that
  // expect a DATA packet following the setup packet).
  bStatusAction = STATUS_ACTION_NOTHING;
  
  // Call the function that determines which function should be called to
  // handle the specific USB request.
  usbDecodeAndProcessUsbRequest();
}


void usbISR(void) interrupt 0 {
  EA = DISABLE;

  switch (bVECINT) {
  
  case VECINT_OUTPUT_ENDPOINT0:
    bVECINT  = 0x00;
    OEP0InterruptHandler();
    break;

  case VECINT_INPUT_ENDPOINT0:
    bVECINT  = 0x00;
    IEP0InterruptHandler();
    break;

  case VECINT_OUTPUT_ENDPOINT1:
    bVECINT = 0x00;
    OEP1InterruptHandler();
    //bIEPDCTX_1 = 0x80;
    break;

  case VECINT_INPUT_ENDPOINT1:
    bVECINT = 0x00;
    //send_registers();
    //    IEP1InterruptHandler();
    break;

  case VECINT_STPOW_PACKET_RECEIVED:
    bVECINT  = 0x00;
    bUSBSTA = USBSTA_STPOW;
    SetupPacketInterruptHandler();
    break;

  case VECINT_SETUP_PACKET_RECEIVED: // All below taken from usb.c
    bVECINT  = 0x00;
    bUSBSTA = USBSTA_SETUP;
    SetupPacketInterruptHandler();
    break;

  case VECINT_RSTR_INTERRUPT:
    bVECINT  = 0x00;
    bUSBSTA = USBSTA_RSTR;
    usbReset();
    //send_registers();
    break;
    
  case VECINT_RESR_INTERRUPT:
    bVECINT = 0x00;
    bUSBSTA = USBSTA_RESR;
    bSuspended = FALSE;
    break;
    
  case VECINT_SUSR_INTERRUPT:
    bVECINT = 0x00;
    bUSBSTA = USBSTA_SUSR;
    bSuspended = TRUE;
    break;
    
  default:
    bVECINT = 0x00;
    break;
  }

  EA = ENABLE;

}

void main(void) {

  bPUR0 = 0x00;
  bPUR1 = 0x00;
  bPUR2 = 0xff;
  bPUR3 = 0x80;

  P3 = 0xff;
  P2 = 0xff;
  P1 = 0xff;

  IE &= 0xf5;

  P3_2 = 1; // rd\ signal to msp430

  SystemInitialization();

}
