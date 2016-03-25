/* This project is created as a solution to Lab 6- BranchingFunctionsDelays from UT6.03x course--- 
   The main structure is from Daniel Valvano, Jonathan Valvano and Ramesh Yerraballi-----
	 The author adds more comments explaining each register--------------------------------
	 Created by: Dinh-Nghi Nguyen----------------------------------------------------------
	 Date: 25.03.2016----------------------------------------------------------------------*/

/* Note: TExaS_Init() and EnableInterrupts() are not used in this project
	 since it is not used for grading-------------------------------------*/
	 
#include "lab6.h"

#define PF2							(*((volatile unsigned long *)(0x40025010)))

int main(void)
{
	// Initialization
	PortF_Init();
	PF2 = 0x04;	// start with LED ON
	// main procedure
	while(1)
	{
		Delay100ms(1);
		SW = GPIO_PORTF_DATA_R & 0x10;	// Switch is PF4
		if(!SW)
			PF2 = ~PF2;
		else
			PF2 = 0x04;	// LED is ON
	}
}

void PortF_Init(void)
{
	volatile unsigned long delay;
	
	SYSCTL_RCGC2_R = 0x20; // activate clock at port F
	delay = SYSCTL_RCGC2_R; // wait for clock stabilize
	GPIO_PORTF_LOCK_R = 0x4C4F434B;	// unlock port F
	GPIO_PORTF_CR_R = 0x14;	// commit PF2 and PF4
	GPIO_PORTF_AMSEL_R = 0x00;	// disable analog functions
	GPIO_PORTF_PCTL_R = 0x00;	// clear PCTL
	GPIO_PORTF_DIR_R = 0x04;	// PF4 is input, PF2 is output
	GPIO_PORTF_PUR_R = 0x10;	// enable Pull-Up resistor for PF4
	GPIO_PORTF_AFSEL_R = 0x00;	// clear AFSEL
	GPIO_PORTF_DEN_R = 0x14;	// enable digital port for PF2 and PF4
}

void Delay100ms(unsigned long time)
{
	unsigned long i;
	while(time > 0)
	{
		i = 1333333;	// 100ms
		while(i > 0)
		{
			i--;
		}
		time--;	// decrement every 100ms
	}
}
