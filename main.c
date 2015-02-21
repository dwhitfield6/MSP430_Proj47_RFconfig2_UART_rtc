#include <msp430.h>
#include "RF_a.h"
#include "Config.h"
#include "RF_a.c"

int ledcount= 1000;
unsigned char IN0_value;
unsigned char IN0_value_old;
unsigned char IN1_value;
unsigned char IN1_value_old;
unsigned char IN2_value;
unsigned char IN2_value_old;
unsigned char IN3_value;
unsigned char IN3_value_old;
unsigned char IN4_value;
unsigned char IN4_value_old;
unsigned char IN5_value;
unsigned char IN5_value_old;
unsigned char IN6_value;
unsigned char IN6_value_old;
unsigned char IN7_value;
unsigned char IN7_value_old;
unsigned char IN8_value;
unsigned char IN8_value_old;
unsigned char IN9_value;
unsigned char IN9_value_old;


const unsigned char TXdataE[12] = {0,2,2,2,2,2,0,0,1,0,0,0}; // Bedroom http://en.chiptrue.com/images/LX2260_en.pdf
const unsigned char TXdataD[12] = {2,2,2,2,2,2,0,0,1,0,0,0}; // Livingroom (A1 A0 x x x x x x)
const unsigned char TXdataF[12] = {2,0,2,2,2,2,0,0,1,0,0,0}; // bedshake (A1 A0 x x x x x x)
const unsigned char TXToiletMyBathroom[12] = {0,0,0,0,0,0,0,0,0,0,0,1}; // david toilet
const unsigned char TXToiletAlexBathroom[12] = {0,0,0,0,0,0,0,0,0,0,0,2}; // Alex toilet

/*had to switch opend and cloased code because i dont feel like reprogramming all 3 door  transmitters
 * these are the values ont he device
 unsigned char TXdataFrontOPENED[12] = {0,0,0,0,0,0,0,0,0,0,2,0}; // door opened
 unsigned char TXdataFrontCLOSED[12] = {0,0,0,0,0,0,0,0,0,0,1,0}; // door closed
 unsigned char TXdataBedroomOPENED[12] = {0,0,0,0,0,0,0,0,0,2,0,0}; // door opened
 unsigned char TXdataBedroomCLOSED[12] = {0,0,0,0,0,0,0,0,0,1,0,0}; // door closed
 unsigned char TXdataLabOPENED[12] = {0,0,0,0,0,0,0,0,2,0,0,0}; // door opened
 unsigned char TXdataLabCLOSED[12] = {0,0,0,0,0,0,0,0,1,0,0,0}; // door closed

 */

const unsigned char TXdataFrontOPENED[12] = {0,0,0,0,0,0,0,0,0,0,1,0}; // door opened
const unsigned char TXdataFrontCLOSED[12] = {0,0,0,0,0,0,0,0,0,0,2,0}; // door closed
const unsigned char TXdataBedroomOPENED[12] = {0,0,0,0,0,0,0,0,0,2,0,0}; // door opened
const unsigned char TXdataBedroomCLOSED[12] = {0,0,0,0,0,0,0,0,0,1,0,0}; // door closed
const unsigned char TXdataLabOPENED[12] = {0,0,0,0,0,0,0,0,1,0,0,0}; // door opened
const unsigned char TXdataLabCLOSED[12] = {0,0,0,0,0,0,0,0,2,0,0,0}; // door closed

//these have different timing then the one above
//zero is 650uS high folowed by 1.75mS low
//full pulse is 2.42mS
//one is 1.75mS high followed by 650uS high
//sync is short high foloowed by 11.89 mS low
//below is channel H
const unsigned char fanON[15] =  {0,1,1,0,1,0,0,0,0,0,1,0,0,0,0}; // door closed
const unsigned char fanOFF[15] = {0,1,1,0,1,0,0,0,0,0,0,1,0,0,0}; // door closed
const unsigned char BedON[15] =  {0,1,1,0,1,0,0,0,1,0,0,0,0,0,0}; // door closed
const unsigned char BedOFF[15] = {0,1,1,0,1,0,0,0,0,1,0,0,0,0,0}; // door closed
const unsigned char AuxON[15] =  {0,1,1,0,1,0,0,1,0,0,0,0,0,0,0}; // door closed
const unsigned char AuxOFF[15] = {0,1,1,0,1,0,1,0,0,0,0,0,0,0,0}; // door closed

//below is channel B
const unsigned char SubLightON[15] =  {0,1,1,0,1,0,0,0,0,0,1,0,0,1,0}; // door closed
const unsigned char SubLightOFF[15] = {0,1,1,0,1,0,0,0,0,0,0,1,0,1,0}; // door closed

int main(void) {
  WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer
  P2DIR |= LED + TX;
  P2OUT &= ~(LED + TX);
while(1)
{
    send_rf_conf2(TX, (unsigned char*)SubLightON);
    send_rf_conf2(TX, (unsigned char*)SubLightON);
    send_rf_conf2(TX, (unsigned char*)SubLightON);
    send_rf_conf2(TX, (unsigned char*)SubLightON);
    send_rf_conf2(TX, (unsigned char*)SubLightON);
    send_rf_conf2(TX, (unsigned char*)SubLightON);
    send_rf_conf2(TX, (unsigned char*)SubLightON);
    send_rf_conf2(TX, (unsigned char*)SubLightON);

    _delay_cycles(4000000);

    send_rf_conf2(TX, (unsigned char*)SubLightOFF);
    send_rf_conf2(TX, (unsigned char*)SubLightOFF);
    send_rf_conf2(TX, (unsigned char*)SubLightOFF);
    send_rf_conf2(TX, (unsigned char*)SubLightOFF);
    send_rf_conf2(TX, (unsigned char*)SubLightOFF);
    send_rf_conf2(TX, (unsigned char*)SubLightOFF);
    send_rf_conf2(TX, (unsigned char*)SubLightOFF);
    send_rf_conf2(TX, (unsigned char*)SubLightOFF);

     _delay_cycles(4000000);
}

  IN0_value = readSwitchP1(IN0);
  IN0_value_old = IN0_value;
  IN1_value = readSwitchP1(IN1);
  IN1_value_old = IN1_value;
  IN2_value = readSwitchP1(IN2);
  IN2_value_old = IN2_value;
  IN3_value = readSwitchP1(IN3);
  IN3_value_old = IN3_value;
  IN4_value = readSwitchP1(IN4);
  IN4_value_old = IN4_value;
  IN5_value = readSwitchP1(IN5);
  IN5_value_old = IN5_value;
  IN6_value = readSwitchP2(IN6);
  IN6_value_old = IN6_value;
  IN7_value = readSwitchP2(IN7);
  IN7_value_old = IN7_value;
  IN8_value = readSwitchP2(IN8);
  IN8_value_old = IN8_value;
  IN9_value = readSwitchP2(IN9);
  IN9_value_old = IN9_value;


  __enable_interrupt(); // enable all interrupts                                   // Enable CPU interrupts

  while(1)
  {
    _delay_cycles(100);

    IN0_value = readSwitchP1(IN0);
    if(IN0_value != IN0_value_old)
    {
      P2OUT |= LED;
      ledcount=0;
      if(IN0_value)
      {
        send_rf_conf2(TX, (unsigned char*)SubLightON);
        send_rf_conf2(TX, (unsigned char*)SubLightON);
        send_rf_conf2(TX, (unsigned char*)SubLightON);
        send_rf_conf2(TX, (unsigned char*)SubLightON);
        send_rf_conf2(TX, (unsigned char*)SubLightON);
        send_rf_conf2(TX, (unsigned char*)SubLightON);
        send_rf_conf2(TX, (unsigned char*)SubLightON);
        send_rf_conf2(TX, (unsigned char*)SubLightON);
      }
      else
      {
        send_rf_conf2(TX, (unsigned char*)SubLightOFF);
        send_rf_conf2(TX, (unsigned char*)SubLightOFF);
        send_rf_conf2(TX, (unsigned char*)SubLightOFF);
        send_rf_conf2(TX, (unsigned char*)SubLightOFF);
        send_rf_conf2(TX, (unsigned char*)SubLightOFF);
        send_rf_conf2(TX, (unsigned char*)SubLightOFF);
        send_rf_conf2(TX, (unsigned char*)SubLightOFF);
        send_rf_conf2(TX, (unsigned char*)SubLightOFF);
      }
    }

    IN1_value = readSwitchP1(IN1);
    if(IN1_value != IN1_value_old)
    {
      P2OUT |= LED;
      ledcount=0;
      if(IN1_value)
      {
        send_rf_conf2(TX, (unsigned char*)fanON);
        send_rf_conf2(TX, (unsigned char*)fanON);
        send_rf_conf2(TX, (unsigned char*)fanON);
        send_rf_conf2(TX, (unsigned char*)fanON);
        send_rf_conf2(TX, (unsigned char*)fanON);
        send_rf_conf2(TX, (unsigned char*)fanON);
        send_rf_conf2(TX, (unsigned char*)fanON);
        send_rf_conf2(TX, (unsigned char*)fanON);

      }
      else
      {
        send_rf_conf2(TX, (unsigned char*)fanOFF);
        send_rf_conf2(TX, (unsigned char*)fanOFF);
        send_rf_conf2(TX, (unsigned char*)fanOFF);
        send_rf_conf2(TX, (unsigned char*)fanOFF);
        send_rf_conf2(TX, (unsigned char*)fanOFF);
        send_rf_conf2(TX, (unsigned char*)fanOFF);
        send_rf_conf2(TX, (unsigned char*)fanOFF);
        send_rf_conf2(TX, (unsigned char*)fanOFF);
      }
    }
    IN2_value = readSwitchP1(IN2);
    if(IN2_value != IN2_value_old)
    {
      P2OUT |= LED;
      ledcount=0;
      if(IN2_value)
      {
        send_rf_conf2(TX, (unsigned char*)BedON);
        send_rf_conf2(TX, (unsigned char*)BedON);
        send_rf_conf2(TX, (unsigned char*)BedON);
        send_rf_conf2(TX, (unsigned char*)BedON);
        send_rf_conf2(TX, (unsigned char*)BedON);
        send_rf_conf2(TX, (unsigned char*)BedON);
        send_rf_conf2(TX, (unsigned char*)BedON);
        send_rf_conf2(TX, (unsigned char*)BedON);

      }
      else
      {
        send_rf_conf2(TX, (unsigned char*)BedOFF);
        send_rf_conf2(TX, (unsigned char*)BedOFF);
        send_rf_conf2(TX, (unsigned char*)BedOFF);
        send_rf_conf2(TX, (unsigned char*)BedOFF);
        send_rf_conf2(TX, (unsigned char*)BedOFF);
        send_rf_conf2(TX, (unsigned char*)BedOFF);
        send_rf_conf2(TX, (unsigned char*)BedOFF);
        send_rf_conf2(TX, (unsigned char*)BedOFF);
      }
    }

    IN3_value = readSwitchP1(IN3);
    if(IN3_value != IN3_value_old)
    {
      P2OUT |= LED;
      ledcount=0;
      if(IN3_value)
      {
        send_rf_conf2(TX, (unsigned char*)AuxON);
        send_rf_conf2(TX, (unsigned char*)AuxON);
        send_rf_conf2(TX, (unsigned char*)AuxON);
        send_rf_conf2(TX, (unsigned char*)AuxON);
        send_rf_conf2(TX, (unsigned char*)AuxON);
        send_rf_conf2(TX, (unsigned char*)AuxON);
        send_rf_conf2(TX, (unsigned char*)AuxON);
        send_rf_conf2(TX, (unsigned char*)AuxON);

      }
      else
      {
        send_rf_conf2(TX, (unsigned char*)AuxOFF);
        send_rf_conf2(TX, (unsigned char*)AuxOFF);
        send_rf_conf2(TX, (unsigned char*)AuxOFF);
        send_rf_conf2(TX, (unsigned char*)AuxOFF);
        send_rf_conf2(TX, (unsigned char*)AuxOFF);
        send_rf_conf2(TX, (unsigned char*)AuxOFF);
        send_rf_conf2(TX, (unsigned char*)AuxOFF);
        send_rf_conf2(TX, (unsigned char*)AuxOFF);
        send_rf_conf2(TX, (unsigned char*)AuxOFF);
      }
    }


    ledcount++;
    if(ledcount == 1000)
    {
      P2OUT &= ~(LED);
    }
    if(ledcount > 1050)
    {
      ledcount = 1050;
    }

    IN0_value_old = IN0_value;
    IN1_value_old = IN1_value;
    IN2_value_old = IN2_value;
    IN3_value_old = IN3_value;
    IN4_value_old = IN4_value;
    IN5_value_old = IN5_value;
    IN6_value_old = IN6_value;
    IN7_value_old = IN7_value;
    IN8_value_old = IN8_value;
    IN9_value_old = IN9_value;

  }
}

