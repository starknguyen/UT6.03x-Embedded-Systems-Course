/* This project is created as a solution to Lab 4- Input/Output from UT6.03x course--- 
   The main structure is from Daniel Valvano, Jonathan Valvano and Ramesh Yerraballi-----
	 The author adds more comments explaining each register--------------------------------
	 Created by: Dinh-Nghi Nguyen----------------------------------------------------------
	 Date: 24.03.2016----------------------------------------------------------------------*/

/* Note: TExaS_Init() and EnableInterrupts() are not used in this project
	 since it is not used for grading-------------------------------------*/
	 
/* System requirements:--------------------- 
	Both SW1 and SW2 are pressed: BLUE LED----
	SW1 is pressed: RED LED-------------------
	SW2 is pressed: GREEN LED-----------------
	Neither of them: LED OFF----------------*/
	
#include "lab4.h"

int main(void)
{
	// Initialize Port F
	PortF_Init();
	
	// main procedure
	while(1)
	{
		// Initialize inputs for switch 1 and 2
		SW1 = GPIO_PORTF_DATA_R & 0x10;
		SW2 = GPIO_PORTF_DATA_R & 0x01;
		// note: switches are negative logic
		if(!SW1 && !SW2)
		{
			GPIO_PORTF_DATA_R = 0x04;
		}
		else if(!SW1 && SW2)
		{
			GPIO_PORTF_DATA_R = 0x02;
		}
		else if(SW1 && !SW2)
		{
			GPIO_PORTF_DATA_R = 0x08;
		}
		else if(SW1 && SW2)
			GPIO_PORTF_DATA_R = 0x00;
	}
}

void PortF_Init(void)
{
	volatile unsigned long delay;
	
	SYSCTL_RCGC2_R |= 0x20; // activate clock at port F
	delay = SYSCTL_RCGC2_R; // wait for clock stabilize
	GPIO_PORTF_LOCK_R = 0x4C4F434B; // unlock port F
	GPIO_PORTF_CR_R |= 0x1F; // commit PF4-3-2-1-0
	GPIO_PORTF_AMSEL_R = 0x00;	// disable analog function
	GPIO_PORTF_PCTL_R = 0x00;	// clear PCTL
	GPIO_PORTF_DIR_R |= 0x0E;	// PF0, PF4: input, PF1-2-3: output
	GPIO_PORTF_PUR_R |= 0x11;	// allow pull-up resistors for PF0 and PF4
	GPIO_PORTF_AFSEL_R = 0x00;	// clear AFSEL
	GPIO_PORTF_DEN_R |= 0x1F;	// enable PF4-3-2-1-0 digital ports
}

// Color    LED(s) PortF
// dark     ---    0
// red      R--    0x02
// blue     --B    0x04
// green    -G-    0x08
// yellow   RG-    0x0A
// sky blue -GB    0x0C
// white    RGB    0x0E
// pink     R-B    0x06

