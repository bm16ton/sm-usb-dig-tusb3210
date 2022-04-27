#include <8052.h>
#include "types.h"

#define bIEPDCTX_1              (* (char xdata *)0xFF4A)

xdata at 0xfe00 BYTE iep1_buffer[0x40];
xdata at 0xfd80 BYTE oep1_buffer[0x40];

void fn_cmd_01(void) {
  P0 = 0x00;
  P1 = 0x00;
    
  // Function for CMD_01
  // Simply send back 0x1b, the ESC character
  iep1_buffer[0] = 0x1b;
  bIEPDCTX_1 = 1;
}


void fn_cmd_02(void) {
  P0 = 0xFF;
  P1 = 0xFF;
    
  // Function for CMD_01
  // Simply send back 0x1b, the ESC character
  iep1_buffer[0] = 0x1b;
  bIEPDCTX_1 = 1;
}

void fn_cmd_03(void) {
 
}

void fn_cmd_04(void) {
  P0 = 0xFE;
  P1 = 0xAF;
    
  // Function for CMD_01
  // Simply send back 0x1b, the ESC character
  iep1_buffer[0] = 0x1b;
  bIEPDCTX_1 = 1;
}

void fn_cmd_05(void) {
  P0 = 0xFF;
  P1 = 0xD7;
    
  // Function for CMD_01
  // Simply send back 0x1b, the ESC character
  iep1_buffer[0] = 0x1b;
  bIEPDCTX_1 = 1;
}

void fn_cmd_06(void) {
    P0 = 0xFE;
    P1 = 0x3B;
  
    // Function for CMD_01
    // Simply send back 0x1b, the ESC character
    iep1_buffer[0] = 0x1b;
    bIEPDCTX_1 = 1;
}

void fn_cmd_07(void) {}

void fn_cmd_08(void) {}
