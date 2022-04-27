/*Host side program to send time information to the TUSB controller*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <libusb-1.0/libusb.h>
#include "commands.h"
#include "unistd.h"
#include <sys/time.h>
#include <time.h>
#include <string.h>

#define VID 0x0451
#define PID 0x3210

#define EP_OUT 0x01
#define EP_IN  0x81

int main(int argc, char *argv[])
{
  int i;
  struct stat s;
  int len;

  //String to hold time 
  char time_str[20];
  char day[20];
  char month[20];
  char date[20];
  //char six_dig_time[20];
  int year;
  libusb_device **devs;
  libusb_device_handle *tusb_handle;
  int r;
  int num_bytes;
  int h, m, sec;
  //Digits displayed by individual Nixies
  int nixies[6];
  ssize_t cnt;

  char ibuff[64]; // input buffer on host
  char obuff[64]; // output buffer on host

  //Variables to keep track of time
  time_t curtime;

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

  //Host side loop to be executed once every second
  while(1)  {
  //Lookup system time in string format and print message
  time(&curtime);
  strcpy(time_str, ctime(&curtime));
  printf("Current time = %s", time_str);
  //Read time into variables
  sscanf(time_str, "%s %s %s %d:%d:%d %d", day, month, date, &h, &m, &sec, &year);
  //Verify that information was recorded correctly
  printf ("%d, %d, %d\n", h, m, sec);
  //Read in digits into Nixies array
  nixies[5] = h/10;
  nixies[4] = h%10;
  nixies[3] = m/10;
  nixies[2] = m%10;
  nixies[1] = sec/10;
  nixies[0] = sec%10;
  //
  // Send CMD_4 and get response
  obuff[0] = CMD_04;
  obuff[1] = 0x01;
  for(i=0; i<6; i++)
  	obuff[i+2] = nixies[i];
  
  r = libusb_bulk_transfer(tusb_handle, EP_OUT, obuff, 8, &num_bytes, 500);
  //Clear the input buffer from garbage
  for(i=0; i<8; i++)
    ibuff[i] = 0;

  r = libusb_bulk_transfer(tusb_handle, EP_IN, ibuff, 64, &num_bytes, 500);
  printf("CMD_04: Received %i bytes:\n", num_bytes);
  for(i=0; i<num_bytes; i++)
    printf("0x%02x\n", ibuff[i]);
  //Make host wait for 1s before updating time 
  //on next second
  sleep(1);
  }
  
  //Done
  i = libusb_release_interface(tusb_handle, 0);
  if(i<0) {
    printf("Cannot release intefrace\n");
    return 0;
  }

  libusb_close(tusb_handle);
  libusb_exit(NULL);
  
  return 0;
}
