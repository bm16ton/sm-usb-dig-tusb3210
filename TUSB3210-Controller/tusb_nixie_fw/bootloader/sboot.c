#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <libusb-1.0/libusb.h>

#define VID 0x0451
#define PID 0x2136

#define ENDPOINT_OUT 0x01


int main(int argc, char *argv[])
{
  FILE *in;
  int i;
  struct stat s;
  int len;

  libusb_device **devs;
  libusb_device_handle *tusb_handle;
  int r;
  int num_bytes;
  ssize_t cnt;
  
  char firmware[8200];

  if(argc!=2) {
    fprintf(stderr,"Usage: %s filename\n",*argv);
    fprintf(stderr,"Downloads a file to the TUSB3210 and executes it\n");
    return 1;
  }


  if((in=fopen(argv[1],"rb"))==NULL) {
    printf("Error: could not open file for read\n");
    return -1;
  }


  if(fstat(fileno(in),&s)<0) {
    printf("Error: could not retrieve file information\n");
    return -1;
  }

  if(s.st_size>8192) {
    printf("Error: input file is too large (max 8192 bytes)\n");
    fclose(in);
    return 1;
  }

  /* When sending firmware directly to endpoint 1:
     - the first two bytes specify the length (LSB first); 
     - the third byte specifies the checksum
     - the firmware follows
     - each packet can be up to 255 bytes.
  */
  
  /* Read firmware file to boot */
  len=fread(&firmware[3], 1, 8192, in);
  fclose(in);

  if(len<=0) {
    fprintf(stderr,"Error: input file is empty!\n");
    return -1;
  }

  // Store the length
  firmware[0] = (unsigned char)(len & 0xff);
  firmware[1] = (unsigned char)((len & 0xff00) >> 8);

  // Calculate ans store the checksum
  firmware[2]=0;
  for(i=0;i<len;i++)
    firmware[2] += firmware[3+i];
  
  // USB handling

  r = libusb_init(NULL);
  if (r < 0)
    return r;
  
  cnt = libusb_get_device_list(NULL, &devs);
  if (cnt < 0)
    return (int) cnt;
  
tusb_handle = libusb_open_device_with_vid_pid(NULL, VID, PID);
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

  len += 3; // including the 3-byte header
  r = libusb_bulk_transfer(tusb_handle, ENDPOINT_OUT, firmware, len, &num_bytes, 500);

  i = libusb_release_interface(tusb_handle, 0);
  if(i<0) {
    printf("Cannot release intefrace\n");
    return 0;
  }

  libusb_close(tusb_handle);
  libusb_exit(NULL);

  if((r==0) && (len==num_bytes)) 
    printf("Wrote %i bytes to TUSB3210\n", num_bytes);

  else
    printf("Error bootstrapping\n");
  
  return 0;
}
