/* main.c - Hello World example for MPC5744P */
/* Description:  Measures eTimer pulse/period measurement */
/* Rev 1 Sept 06 2016 D Chung - initial version */
/* Copyright NXP Semiconductor, Inc 2016 All rights reserved. */

/*******************************************************************************
* NXP Semiconductor Inc.
* (c) Copyright 2016 NXP Semiconductor, Inc.
* ALL RIGHTS RESERVED.
********************************************************************************
Services performed by NXP in this matter are performed AS IS and without
any warranty. CUSTOMER retains the final decision relative to the total design
and functionality of the end product. NXP neither guarantees nor will be
held liable by CUSTOMER for the success of this project.
NXP DISCLAIMS ALL WARRANTIES, EXPRESSED, IMPLIED OR STATUTORY INCLUDING,
BUT NOT LIMITED TO, IMPLIED WARRANTY OF MERCHANTABILITY OR FITNESS FOR
A PARTICULAR PURPOSE ON ANY HARDWARE, SOFTWARE ORE ADVISE SUPPLIED TO THE PROJECT
BY NXP, AND OR NAY PRODUCT RESULTING FROM NXP SERVICES. IN NO EVENT
SHALL NXP BE LIABLE FOR INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF
THIS AGREEMENT.

CUSTOMER agrees to hold NXP harmless against any and all claims demands or
actions by anyone on account of any damage, or injury, whether commercial,
contractual, or tortuous, rising directly or indirectly as a result of the advise
or assistance supplied CUSTOMER in connection with product, services or goods
supplied under this Agreement.
********************************************************************************
* File              main.c
* Owner             David Chung
* Version           1.0
* Date              Sept-6-2016
* Classification    General Business Information
* Brief             Produces MPC5744P CLKOUT
********************************************************************************
* Detailed Description:
* MPC5744P's default clock source is 16 MHz IRCOSC.  This code example
* divides IRCOSC by 10 for output frequency of 1.6 MHz.
* Configures MPC5744P CLKOUT signal to 1.6 MHz. Connect to LED so LED
* flashes at frequency of CLKOUT. Onboard red RGB turns on to let user
* know program is running, but does not flash.
*
* ------------------------------------------------------------------------------
* Test HW:         XDEVKIT-MPC5744P
* MCU:             MPC5744P
* Terminal:        None
* Fsys:            16 MHz IRC
* Debugger:        OpenSDA
* Target:          FLASH
* EVB connection:  Connect CLKOUT (PB6 - J1_16) to oscilloscope or any external component
* 					such as an external LED. Onboard RGB LED does not support external connection.
* 					If external LED used, connect one end to J1_16 and the other to GND (J2_13),
* 					in series with current-limiting resistor (typically 330 ohm).  The external LED will
* 					flash at the CLKOUT frequency but if frequency is fast, the naked eye
* 					will perceive the flash as a PWM, meaning the LED will be seen as on
* 					at a certain brightness.
*
********************************************************************************
Revision History:
Version  Date         Author  			Description of Changes
1.0      Sept-06-2016  David Chung	  	Initial version

*******************************************************************************/
#include "derivative.h" /* include peripheral declarations */
#include "project.h" /* Board Configuration */

extern void xcptn_xmpl(void);

void memory_config_16mhz(void);
void clock_out_FIRC(void);

__attribute__ ((section(".text")))
int main(void)
{
	int counter = 0;
	
	xcptn_xmpl ();              /* Configure and Enable Interrupts */

	memory_config_16mhz(); /* Configure wait states, flash master access, etc. */

	SIUL2.MSCR[PC11].B.OBE = 1; /* Pad PC11 - Red LED. */

	clock_out_FIRC();           /* Pad PB6 = CLOCKOUT = FIRC / 10 */

	for(;;) {	   
	   	counter++;
	}
	
	return 0;
}
