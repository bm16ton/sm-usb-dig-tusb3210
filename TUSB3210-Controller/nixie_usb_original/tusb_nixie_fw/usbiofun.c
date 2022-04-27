#include <8052.h>
#include "types.h"

#define bIEPDCTX_1              (* (char xdata *)0xFF4A)

xdata at 0xfe00 BYTE iep1_buffer[0x40];
xdata at 0xfd80 BYTE oep1_buffer[0x40];

void fn_cmd_01(void) {
  // Function for CMD_01
  // Simply send back 0x1b, the ESC character
  iep1_buffer[0] = 0x1b;
  bIEPDCTX_1 = 1;
}


void fn_cmd_02(void) {
  iep1_buffer[0] = 0x4e; // N
  iep1_buffer[1] = 0x49; // I
  iep1_buffer[2] = 0x58; // X
  iep1_buffer[3] = 0x49; // I
  iep1_buffer[4] = 0x45; // E
  iep1_buffer[5] = '\0'; // String terminator
  bIEPDCTX_1 = 6;
}

void fn_cmd_03(void) {
  // Add 1 to the received 8 bytes and send them back to the host
  int i;
  for(i=0; i<8; i++) {
    iep1_buffer[i] = oep1_buffer[i]+1;
  }
  bIEPDCTX_1 = 8; 
}

void fn_cmd_04(void) {}
void fn_cmd_05(void) {}
void fn_cmd_06(void) {}
void fn_cmd_07(void) {}
void fn_cmd_08(void) {}
