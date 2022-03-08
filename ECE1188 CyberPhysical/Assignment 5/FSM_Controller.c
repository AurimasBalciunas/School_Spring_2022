// FSM_Controller.c
// Aurimas Balciunas
// ECE1185 Assignment #5

#include <stdint.h>
#include "msp.h"
#include "../inc/Clock.h"
#include "../inc/TExaS.h"

struct State {
  uint32_t mycurstate; //THIS IS REDUNDANT BUT GOOD FOR THE SCREENSHOTS
  uint8_t out;             // 6-bit output //was Out
  uint32_t delay;           // 10 ms //was time
  uint8_t sodaornot; //soda or not

  //add a property to your state for the color, or in this case the output
  const struct State *next[4];};// depends on 2-bit input //was next
typedef const struct State State_t;
#define S1 &FSM[0]
#define S2 &FSM[1]
#define S3 &FSM[2]
#define S4 &FSM[3]
#define S5 &FSM[4]
/*
State_t FSM[5]={
 {0x01,0x01,250, 0x00, {S1,S3,S2,S1}}, //the idea here is is like {00->goN, 01->waitN, 10->goN, 11->waitN}. Not sure about endianness or largest to smallest but this is the idea
 {0x02,0x04,250,0x00,{S2,S4,S5,S2}},
 {0x03,0x02,250,0x00,{S3,S2,S4,S3}},
 {0x04,0x03,250,0x01,{S1,S1,S1,S4}},
 {0x05,0x06,250,0x01,{S3,S3,S3,S5}}
};
*/

State_t FSM[5]={
 {0x01,0x01,250, 0x00, {S1,S3,S2,S1}}, //the idea here is is like {00->goN, 01->waitN, 10->goN, 11->waitN}. Not sure about endianness or largest to smallest but this is the idea
 {0x02,0x04,250,0x00,{S2,S4,S3,S2}},
 {0x03,0x02,250,0x00,{S3,S5,S4,S3}},
 {0x04,0x03,250,0x01,{S1,S1,S1,S4}},
 {0x05,0x06,250,0x01,{S2,S2,S2,S5}}
};

// SENSOR is set to P5IN and LIGHT is set to P4OUT, making the code more readable.
#define SENSOR  (*((volatile uint8_t *)0x40004C40))
#define LIGHT   (*((volatile uint8_t *)0x40004C23))

State_t *Spt;  // pointer to the current state
uint32_t Input;
uint32_t Output;
uint32_t soda;
uint32_t myCurState;

int main(void){
  Clock_Init48MHz();
  LaunchPad_Init();
  Spt = S1;
  while(1){
    Output = Spt->out;            // set output from FSM //your LED color
    soda = Spt->sodaornot; //whether you got soda
    myCurState = Spt->mycurstate;
    LaunchPad_Output(Output);     // do output to two motors
    Clock_Delay1ms(Spt->delay);   // wait
    Input = LaunchPad_Input();    // read sensors
    Spt = Spt->next[Input];       // next depends on input and state
    LaunchPad_LED(soda);         //setting whether or not we got soda in the last state
  }
}


// Color    LED(s) Port2
// dark     ---    0
// red      R--    0x01
// blue     --B    0x04
// green    -G-    0x02
// yellow   RG-    0x03
// sky blue -GB    0x06
// white    RGB    0x07
// pink     R-B    0x05

