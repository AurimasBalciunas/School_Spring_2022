
#include <stdint.h>
#include "msp.h"
#include "../inc/CortexM.h"
#include "../inc/SysTickInts.h"
#include "../inc/Reflectance.h"
#include "../inc/Bump.h"
#include "../inc/LaunchPad.h"
#include "../inc/Clock.h"

#define LEDOUT (*((volatile uint8_t *)(0x42098040)))
volatile uint32_t Time,MainCount;
volatile uint32_t ref_counter;
volatile uint8_t result;
volatile uint8_t bump_shared;

void setPart1LEDs(void)
{
    if(result<2)
    {
        P2->OUT = (P2->OUT&0xF8)|0x00;
    }
    else if(result<4)
    {
        P2->OUT = (P2->OUT&0xF8)|0x01;
    }
    else if(result<8)
    {
        P2->OUT = (P2->OUT&0xF8)|0x02;
    }
    else if(result<16)
    {
        P2->OUT = (P2->OUT&0xF8)|0x03;
    }
    else if(result<32)
    {
        P2->OUT = (P2->OUT&0xF8)|0x04;
    }
    else if(result<64)
    {
        P2->OUT = (P2->OUT&0xF8)|0x05;
    }
    else if(result<128)
    {
        P2->OUT = (P2->OUT&0xF8)|0x06;
    }
    else if(result<256)
    {
        P2->OUT = (P2->OUT&0xF8)|0x07;
    }

}

void setPart3LEDs(uint8_t bumps)
{
    if(bumps==0)
    {
        P2->OUT = (P2->OUT&0xF8)&0x00;
    }
    else if(bumps<2)
    {
        P2->OUT = (P2->OUT&0xF8)|0x06;
    }
    else if(bumps<4)
    {
        P2->OUT = (P2->OUT&0xF8)|0x01;
    }
    else if(bumps<8)
    {
        P2->OUT = (P2->OUT&0xF8)|0x02;
    }
    else if(bumps<16)
    {
        P2->OUT = (P2->OUT&0xF8)|0x03;
    }
    else if(bumps<32)
    {
        P2->OUT = (P2->OUT&0xF8)|0x04;
    }
    else if(bumps<64)
    {
        P2->OUT = (P2->OUT&0xF8)|0x05;
    }
}

void SysTick_Handler(void){ // PWM

    bump_shared = Bump_Read();
    setPart3LEDs(bump_shared);



    if(ref_counter%10==0)
    {
        Reflectance_Start();
        ref_counter++;
    }

    else if(ref_counter%11==0)
    {
        result = Reflectance_End();
        //setPart1LEDs();
        ref_counter=1;
    }
    else
    {
        ref_counter++;
    }
    SysTick->LOAD = 48000;

}



int main(void){
  Clock_Init48MHz();      // running on crystal
  Time = MainCount = 0;
  SysTick_Init(48000,2);  // set up SysTick for 8 Hz interrupts
  LaunchPad_Init();       // P1.0 is red LED on LaunchPad
  Reflectance_Init();
  Bump_Init();
  ref_counter=1;

  EnableInterrupts();
  while(1){
    WaitForInterrupt();

    //start foreground thread
    uint32_t i, j, temp, length;

    uint32_t a[100]={5000,5308,5614,5918,6219,6514,
    6804,7086,7361,7626,7880,8123,8354,8572,8776,8964,9137,
    9294,9434,9556,9660,9746,9813,9861,9890,9900,9890,9861,
    9813,9746,9660,9556,9434,9294,9137,8964,8776,8572,8354,
    8123,7880,7626, 7361,7086,6804,6514,6219,5918,5614,
    5308,5000,4692,4386,4082,3781,3486,3196,2914,2639,2374,
    2120,1877,1646,1428,1224,1036,863,706,566,444,340,254,
    187,139,110,100,110,139,187,254,340,444,566,706,863,
    1036, 1224, 1428, 1646,1877,2120,2374,2639,2914,
    3196,3486,3781,4082,4386,4692};

    length = 100;

    for (i = 0; i < length; i++)
    {
        for (j = 0; j < length - i - 1; j++)
        {
            if (a[j + 1] < a[j])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    //end foreground thread
    MainCount++;
  }
}


