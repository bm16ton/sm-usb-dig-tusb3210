BYTE code abromConfigurationDescriptorGroup[SIZEOF_BOOTCODE_CONFIG_DESC_GROUP] =
  {
    // CONFIGURATION DESCRIPTOR (9 bytes)
    SIZEOF_CONFIG_DESCRIPTOR,        // bLength
    DESC_TYPE_CONFIG,                // bDescriptorType
    SIZEOF_BOOTCODE_CONFIG_DESC_GROUP, 0x00, // wTotalLength
    0x01,                            // bNumInterfaces
    0x01,                            // bConfigurationValue
    0x00,                            // iConfiguration Description offset
    0xa0,                            // bmAttributes, bus power, support remote wake
    0x32,                            // Max. Power Consumption at 2mA unit

    // INTERFACE DESCRIPTOR (9 bytes)
    SIZEOF_INTERFACE_DESCRIPTOR,    // bLength
    DESC_TYPE_INTERFACE,            // bDescriptorType
    0x00,                           // bInterfaceNumber
    0x00,                           // bAlternateSetting
    2,                              // bNumEndpoints
    0xff,                           // bInterfaceClass: 3 = HID Device
    1,                              // bInterfaceSubClass: 1 = Boot Device
    1,                              // bInterfaceProtocol: 1 = Keyboard
    0x01,                           // iInterface
    /*
    // KEYBOARD HID DESCRIPTOR (9 bytes)
    0x09,                           // bLength of HID descriptor
    0x21,                           // HID Descriptor Type: 0x21 = Keyboard
    0x00,0x01,                      // HID Revision number 1.00
    0x00,                           // Target country, nothing specified (00h)
    0x01,                           // Number of HID classes to follow 
    0x22,                           // Report descriptor type
    SIZEOF_REPORT_DESCRIPTOR, 0x00, // Total length of report descriptor
    */
    // ENDPOINT #1 INPUT DESCRIPTOR, (7 bytes)
    SIZEOF_ENDPOINT_DESCRIPTOR,     // bLength
    DESC_TYPE_ENDPOINT,             // bDescriptorType
    0x81,                           // bEndpointAddress; bit7=1 for IN, bits 3-0=1 
    EP_DESC_ATTR_TYPE_BULK,          // bmAttributes, interrupt transfers
    0x40, 0x00,                     // wMaxPacketSize, 8 bytes
    0x00,                           // Polling interval: Every 10 ms

   // ENDPOINT #2 INPUT DESCRIPTOR, (7 bytes)
    SIZEOF_ENDPOINT_DESCRIPTOR,     // bLength
    DESC_TYPE_ENDPOINT,             // bDescriptorType
    0x01,                           // bEndpointAddress; bit7=1 for IN, bits 3-0=1 
    EP_DESC_ATTR_TYPE_BULK,          // bmAttributes, interrupt transfers
    0x40, 0x00,                     // wMaxPacketSize, 8 bytes
    0x00                           // Polling interval: Every 10 ms

  };

BYTE code abromDeviceDescriptor[SIZEOF_DEVICE_DESCRIPTOR] = {
  SIZEOF_DEVICE_DESCRIPTOR,       // Length of this descriptor (12h bytes)
  DESC_TYPE_DEVICE,               // Type code of this descriptor (01h)
  0x10,0x01,                      // Release of USB spec (Rev 1.1)
  0x00,                           // Device's base class code
  0,                              // Device's sub class code
  0,                              // Device's protocol type code
  EP0_MAX_PACKET_SIZE,            // End point 0's max packet size = 8
  0xFF,0xFF,                      // Vendor ID, UPDATED AT RUN-TIME
  0xFF, 0xFF,                     // Product ID, UPDATED AT RUN-TIME
  0x00,0x01,                      // Revision level of device, UPDATED AT RUN-TIME
  1,                              // Index of manufacturer name string desc, UPDATED AT RUN-TIME
  2,                              // Index of product name string desc, UPDATED AT RUN-TIME
  3,                              // Index of serial number string desc, UPDATED AT RUN-TIME
  1                               // Number of configurations supported
};
