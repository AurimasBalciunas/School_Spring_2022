// Lab11_UARTmain.c
// Runs on MSP432
// Test the functions in UART0.c by printing various
// Busy-wait device driver for the UART UCA0.
// Daniel Valvano
// May 24, 2019

/* This example accompanies the book
   "Embedded Systems: Introduction to Robotics,
   Jonathan W. Valvano, ISBN: 9781074544300, copyright (c) 2019
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/

Simplified BSD License (FreeBSD License)
Copyright (c) 2019, Jonathan Valvano, All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are
those of the authors and should not be interpreted as representing official
policies, either expressed or implied, of the FreeBSD Project.
*/

#include "msp.h"
#include <string.h>
#include "../inc/Clock.h"
#include "../inc/UART0.h"
#include "../inc/LaunchPad.h"

// dark     ---    0
#define dark 0x00
// red      R--    0x01
#define red 0x01
// blue     --B    0x04
#define blue 0x04
// green    -G-    0x02
#define green 0x02
// yellow   RG-    0x03
#define yellow 0x03
// sky blue -GB    0x06
#define skyblue 0x06
// white    RGB    0x07
#define white 0x07
// pink     R-B    0x05
#define pink 0x05


/**
 * main.c
 */
void main(void)
{

  Clock_Init48MHz();                   // set system clock to 48 MHz
  UART0_Init();
  LaunchPad_Init();

  char input[3];
  LaunchPad_Output(dark);
  //part 3:
  while(1)
  {
      UART0_InString(input, 3);
      UART0_OutString(input);

      if(strcmp(input, "dar")==0)
          LaunchPad_Output(dark);
      if(strcmp(input, "red")==0)
          LaunchPad_Output(red);
      if(strcmp(input, "blu")==0)
          LaunchPad_Output(blue);
      if(strcmp(input, "gre")==0)
          LaunchPad_Output(green);
      if(strcmp(input, "yel")==0)
          LaunchPad_Output(yellow);
      if(strcmp(input, "sky")==0)
          LaunchPad_Output(skyblue);
      if(strcmp(input, "whi")==0)
          LaunchPad_Output(white);
      if(strcmp(input, "pin")==0)
          LaunchPad_Output(pink);
  }
}
