// DEVICE_REQUEST Structure
typedef struct _tDEVICE_REQUEST
{
  BYTE    bmRequestType;              // See bit definitions below
  BYTE    bRequest;                   // See value definitions below
  BYTE    bValueL;                    // Meaning varies with request type
  BYTE    bValueH;                    // Meaning varies with request type
  BYTE    bIndexL;                    // Meaning varies with request type
  BYTE    bIndexH;                    // Meaning varies with request type
  BYTE    bLengthL;                   // Number of bytes of data to transfer (LSByte)
  BYTE    bLengthH;                   // Number of bytes of data to transfer (MSByte)
} tDEVICE_REQUEST, *ptDEVICE_REQUEST;

// device descriptor structure
typedef struct _tDEVICE_DESCRIPTOR
{
  BYTE    bLength;                // Length of this descriptor (12h bytes)
  BYTE    bDescriptorType;        // Type code of this descriptor (01h)
  WORD    bcdUsb;                 // Release of USB spec (0210h = rev 2.10)
  BYTE    bDeviceClass;           // Device's base class code
  BYTE    bDeviceSubClass;        // Device's sub class code
  BYTE    bDeviceProtocol;        // Device's protocol type code
  BYTE    bMaxPacketSize0;        // End point 0's max packet size (8/16/32/64)
  WORD    wIdVendor;              // Vendor ID for device
  WORD    wIdProduct;             // Product ID for device
  WORD    wBcdDevice;             // Revision level of device
  BYTE    wManufacturer;          // Index of manufacturer name string desc
  BYTE    wProduct;               // Index of product name string desc
  BYTE    wSerialNumber;          // Index of serial number string desc
  BYTE    bNumConfigurations;     // Number of configurations supported
} tDEVICE_DESCRIPTOR, *ptDEVICE_DESCRIPTOR;

#define EP_DESC_ATTR_TYPE_INT   0x03
#define EP_DESC_ATTR_TYPE_BULK  0x02

// configuration descriptor structure
typedef struct _tCONFIG_DESCRIPTOR
{
  BYTE    bLength;                // Length of this descriptor (9h bytes)
  BYTE    bDescriptorType;        // Type code of this descriptor (02h)
  WORD    wTotalLength;           // Size of this config desc plus all interface,
  // endpoint, class, and vendor descriptors
  BYTE    bNumInterfaces;         // Number of interfaces in this config
  BYTE    bConfigurationValue;    // Value to use in SetConfiguration command
  BYTE    bConfiguration;         // Index of string desc describing this config
  BYTE    bAttributes;            // See CFG_DESC_ATTR_xxx values below
  BYTE    bMaxPower;              // Power used by this config in 2mA units
} tCONFIG_DESCRIPTOR, *ptCONFIG_DESCRIPTOR;

// interface descriptor structure
typedef struct _tINTERFACE_DESCRIPTOR
{
  BYTE    bLength;                // Length of this descriptor (9h bytes)
  BYTE    bDescriptorType;        // Type code of this descriptor (04h)
  BYTE    bInterfaceNumber;       // Zero based index of interface in the configuration
  BYTE    bAlternateSetting;      // Alternate setting number of this interface
  BYTE    bNumEndpoints;          // Number of endpoints in this interface
  BYTE    bInterfaceClass;        // Interface's base class code
  BYTE    bInterfaceSubClass;     // Interface's sub class code
  BYTE    bInterfaceProtocol;     // Interface's protocol type code
  BYTE    bInterface;             // Index of string desc describing this interface
} tINTERFACE_DESCRIPTOR, *ptINTERFACE_DESCRIPTOR;

// endpoint descriptor structure
typedef struct _tENDPOINT_DESCRIPTOR
{
  BYTE    bLength;                // Length of this descriptor (7h bytes)
  BYTE    bDescriptorType;        // Type code of this descriptor (05h)
  BYTE    bEndpointAddress;       // See EP_DESC_ADDR_xxx values below
  BYTE    bAttributes;            // See EP_DESC_ATTR_xxx value below
  WORD    wMaxPacketSize;         // Max packet size of endpoint
  BYTE    bInterval;              // Polling interval of endpoint in milliseconds
} tENDPOINT_DESCRIPTOR, *tpENDPOINT_DESCRIPTOR;

#define usbClearOEP0ByteCount tEndPoint0DescriptorBlock.bOEPBCNT = 0x00
#define usbStallOEP0          tEndPoint0DescriptorBlock.bOEPCNFG |= EPCNF_STALL

/*----------------------------------------------------------------------------+
  | Constant Definition                                                         |
  +----------------------------------------------------------------------------*/
#define USB_SPEC_REV_BCD        0x0101  /*BCD coded rev level of USB spec*/
#define SIZEOF_DEVICE_REQUEST   0x08

//  Bit definitions for DEVICE_REQUEST.bmRequestType
//  Bit 7:   Data direction
#define USB_REQ_TYPE_OUTPUT     0x00    // 0 = Host sending data to device
#define USB_REQ_TYPE_INPUT      0x80    // 1 = Device sending data to host

//  Bit 6-5: Type
#define USB_REQ_TYPE_MASK       0x60    // Mask value for bits 6-5
#define USB_REQ_TYPE_STANDARD   0x00    // 00 = Standard USB request
#define USB_REQ_TYPE_CLASS      0x20    // 01 = Class specific
#define USB_REQ_TYPE_VENDOR     0x40    // 10 = Vendor specific

//  Bit 4-0: Recipient
#define USB_REQ_TYPE_RECIP_MASK 0x1F    // Mask value for bits 4-0
#define USB_REQ_TYPE_DEVICE     0x00    // 00000 = Device
#define USB_REQ_TYPE_INTERFACE  0x01    // 00001 = Interface
#define USB_REQ_TYPE_ENDPOINT   0x02    // 00010 = Endpoint
#define USB_REQ_TYPE_OTHER      0x03    // 00011 = Other

//  Values for DEVICE_REQUEST.bRequest
// Standard Device Requests
#define USB_REQ_GET_STATUS              0
#define USB_REQ_CLEAR_FEATURE           1
#define USB_REQ_SET_FEATURE             3
#define USB_REQ_SET_ADDRESS             5
#define USB_REQ_GET_DESCRIPTOR          6
#define USB_REQ_SET_DESCRIPTOR          7
#define USB_REQ_GET_CONFIGURATION       8
#define USB_REQ_SET_CONFIGURATION       9
#define USB_REQ_GET_INTERFACE           10
#define USB_REQ_SET_INTERFACE           11
#define USB_REQ_SYNCH_FRAME             12

// HID CLASS Requests
#define USB_REQ_GET_REPORT              0x01
#define USB_REQ_GET_IDLE                0x02
#define USB_REQ_SET_REPORT              0x09
#define USB_REQ_SET_IDLE                0x0A
#define USB_REQ_SET_PROTOCOL            0x0B
#define USB_REQ_GET_PROTOCOL            0x03

//  Descriptor Type Values
#define DESC_TYPE_DEVICE                1       // Device Descriptor (Type 1)
#define DESC_TYPE_CONFIG                2       // Configuration Descriptor (Type 2)
#define DESC_TYPE_STRING                3       // String Descriptor (Type 3)
#define DESC_TYPE_INTERFACE             4       // Interface Descriptor (Type 4)
#define DESC_TYPE_ENDPOINT              5       // Endpoint Descriptor (Type 5)
#define DESC_TYPE_HID                   0x21    // HID Descriptor (Type 0x21)
#define DESC_TYPE_REPORT                0x22    // Report Descriptor (Type 0x22)
#define DESC_TYPE_PHYSICAL              0x23    // Physical Descriptor (Type 0x23)
#define DESC_TYPE_HUB                   0x29    // Hub Descriptor (Type 6

#define FEATURE_ENDPOINT_STALL          0       // Endpoint stall (Type 0)
#define FEATURE_REMOTE_WAKEUP           1       // Remote wakeup (Type 1)

// DEVICE_DESCRIPTOR structure
#define SIZEOF_DEVICE_DESCRIPTOR        0x12
#define OFFSET_DEVICE_DESCRIPTOR_CLASS  0x04
#define OFFSET_DEVICE_DESCRIPTOR_VID_L  0x08
#define OFFSET_DEVICE_DESCRIPTOR_VID_H  0x09
#define OFFSET_DEVICE_DESCRIPTOR_PID_L  0x0A
#define OFFSET_DEVICE_DESCRIPTOR_PID_H  0x0B
#define OFFSET_DEVICE_DESCRIPTOR_VER_L  0x0C
#define OFFSET_DEVICE_DESCRIPTOR_VER_H  0x0D
#define OFFSET_DEVICE_DESCRIPTOR_IMFG   0x0E
#define OFFSET_DEVICE_DESCRIPTOR_IPROD  0x0F
#define OFFSET_DEVICE_DESCRIPTOR_ISN    0x10

#define OFFSET_CONFIG_DESCRIPTOR_POWER  0x07
#define OFFSET_CONFIG_DESCRIPTOR_CURT   0x08


//  CONFIG_DESCRIPTOR structure
#define SIZEOF_CONFIG_DESCRIPTOR 0x09
#define SIZEOF_REPORT_DESCRIPTOR 0x3F

//  INTERFACE_DESCRIPTOR structure
#define SIZEOF_INTERFACE_DESCRIPTOR 0x09

//  KEYBOARD HID DESCRIPTOR structure
#define SIZEOF_KEYBD_HID_DESCRIPTOR 0x09

//  ENDPOINT_DESCRIPTOR structure
#define SIZEOF_ENDPOINT_DESCRIPTOR 0x07
