/*Host computer side program to execute basic commands*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <libusb-1.0/libusb.h>
#include "commands.h"
#include "unistd.h"
#include <sys/time.h>
#include <time.h>

#define VID 0x0451
#define PID 0x3210

#define EP_OUT 0x01
#define EP_IN  0x81

int main(int argc, char *argv[])
{
  int i;
  struct stat s;
  int len;

  libusb_device **devs;
  libusb_device_handle *tusb_handle;
  int r;
  int num_bytes;
  ssize_t cnt;

  char ibuff[64]; // input buffer on host
  char obuff[64]; // output buffer on host
  
  // USB handling
  r = libusb_init(NULL);
  if (r < 0)
    return r;
  
  cnt = libusb_get_device_list(NULL, &devs);
  if (cnt < 0)
    return (int) cnt;
  
  tusb_handle = libusb_open_device_with_vid_pid(NULL, 0x0451, 0x3210);
  if(tusb_handle == NULL) {
    printf("No such device\n");
    return 0;
  }
      
  libusb_free_device_list(devs, 1);

  r = libusb_claim_interface(tusb_handle, 0); // claim bInterfaceNumber 0
  if(r<0) {
    printf("Cannot claim intefrace\n");
    return 0;
  }

  while(1)  {

  // Send CMD_5 and get the response from TUSB firmware// Send CMD_5 and get the response from TUSB firmware
  obuff[0] = CMD_03;
  obuff[1] = 0x01;
  r = libusb_bulk_transfer(tusb_handle, EP_OUT, obuff, 2, &num_bytes, 500);
  ibuff[0] = 0;
  r = libusb_bulk_transfer(tusb_handle, EP_IN, ibuff, 64, &num_bytes, 500);
  printf("CMD_04: Received %i bytes: 0x%02x\n", num_bytes, ibuff[0]);
  sleep(1);
  //test
  // Send CMD_5 and get the response from TUSB firmware// Send CMD_5 and get the response from TUSB firmware
  obuff[0] = CMD_04;
  obuff[1] = 0x01;
  r = libusb_bulk_transfer(tusb_handle, EP_OUT, obuff, 2, &num_bytes, 500);
  ibuff[0] = 0;
  r = libusb_bulk_transfer(tusb_handle, EP_IN, ibuff, 64, &num_bytes, 500);
  printf("CMD_04: Received %i bytes: 0x%02x\n", num_bytes, ibuff[0]);
  sleep(1);
  
  /*
  // Send CMD_5 and get the response from TUSB firmware
  obuff[0] = CMD_03;
  obuff[1] = 0x01;
  r = libusb_bulk_transfer(tusb_handle, EP_OUT, obuff, 2, &num_bytes, 500);
  ibuff[0] = 0;
  r = libusb_bulk_transfer(tusb_handle, EP_IN, ibuff, 64, &num_bytes, 500);
  printf("CMD_03: Received %i bytes: 0x%02x\n", num_bytes, ibuff[0]);
  sleep(1);
  
  // Send CMD_5 and get the response from TUSB firmware
  obuff[0] = CMD_04;
  obuff[1] = 0x01;
  r = libusb_bulk_transfer(tusb_handle, EP_OUT, obuff, 2, &num_bytes, 500);
  ibuff[0] = 0;
  r = libusb_bulk_transfer(tusb_handle, EP_IN, ibuff, 64, &num_bytes, 500);
  printf("CMD_04: Received %i bytes: 0x%02x\n", num_bytes, ibuff[0]);

  sleep(1);
  */
  }

  // Done
  i = libusb_release_interface(tusb_handle, 0);
  if(i<0) {
    printf("Cannot release intefrace\n");
    return 0;
  }

  libusb_close(tusb_handle);
  libusb_exit(NULL);
  
  return 0;
}
