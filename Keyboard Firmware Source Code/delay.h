/*----------------------------------------------------------------------------+
|                                                                             |
|                             Texas Instruments                               |
|                                                                             |
|                             Delay Header File                               |
|                                                                             |
+-----------------------------------------------------------------------------+
|  Source: delay.h, v 1.0 2000/01/24 21:31:23                                 |
|  Author: Horng-Ming Lobo Tai lobotai@ti.com                                 |
|  Header: (none)                                                             |
|                                                                             |
|  For more information, please contact                                       |
|                                                                             |
|  Lobo Tai                                                                   |
|  Texas Instruments                                                          |
|  8505 Forest Lane, MS 8761                                                  |
|  Dallas, TX 75243                                                           |
|  USA                                                                        |
|                                                                             |
|  Tel 972-480-3145                                                           |
|  Fax 972-480-3443                                                           |
|                                                                             |
|  Logs:                                                                      |
|                                                                             |
|  WHO     WHEN         WHAT                                                  |
|  ---     --------     ----------------------------------------------------- |
|  HMT     20000124     born                                                  |
|                                                                             |
+----------------------------------------------------------------------------*/

#ifndef _DELAY_H_
#define _DELAY_H_

/*----------------------------------------------------------------------------+
| Include files                                                               |
+----------------------------------------------------------------------------*/

// If no error occurs, return NO_ERROR(=0).
/*----------------------------------------------------------------------------+
| Function Prototype                                                          |
+----------------------------------------------------------------------------*/
VOID DelayuSecond(UINT uiCounter);
VOID DelaymSecond(UINT uiCounter);
VOID DelayTick(UINT uiCounter);
/*----------------------------------------------------------------------------+
| Type Definition & Macro                                                     |
+----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------+
| Constant Definition                                                         |
+----------------------------------------------------------------------------*/
#define SYS_CLOCK 12
#endif
//----------------------------- Cut along the line ----------------------------
