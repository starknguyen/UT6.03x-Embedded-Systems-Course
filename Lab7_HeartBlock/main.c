/* This project is created as a solution to Lab 7- HeartBlock from UT6.03x course--- 
   The main structure is from Daniel Valvano, Jonathan Valvano and Ramesh Yerraballi-----
	 The author adds more comments explaining each register--------------------------------
	 Created by: Dinh-Nghi Nguyen----------------------------------------------------------
	 Date: 26.03.2016----------------------------------------------------------------------*/

/* Note: TExaS_Init() and EnableInterrupts() are not used in this project
	 since it is not used for grading-------------------------------------*/
	 
#include "lab7.h"

int main(void)
{
	// Initialization
	PortF_Init();
	
	// main procedure
	while(1)
	{
		// Make Ready signal go high
		SetReady();
		// Wait for AS to be 0 (switch to be pressed)
		WaitForASLow();
		// Make Ready signal go low
		ClearReady();
		// Wait 10 ms
		Delay1ms(10);
		// Wait for AS to be 1 (switch to be released)
		WaitForASHigh();
		// Wait 250 ms
		Delay1ms(250);
		// Make VT signal go high
		SetVT();
		// Wait 250 ms
		Delay1ms(250);
		// Make VT signal go low
		ClearVT();
	}
}

void PortF_Init(void)
{
	volatile unsigned long delay;
	
	SYSCTL_RCGC2_R = 0x20;	// activate clock for port F
	delay = SYSCTL_RCGC2_R;	// wait for clock stabilize
	GPIO_PORTF_LOCK_R = 0x4C4F434B;	// unlock port F
	GPIO_PORTF_CR_R = 0x1A;	// commit for PF4, PF3 and PF1
	GPIO_PORTF_AMSEL_R = 0x00;	// disable analog functions
	GPIO_PORTF_PCTL_R = 0x00;	// clear PCTL
	GPIO_PORTF_DIR_R = 0x0A;	// Input: PF4, Output: PF3, PF1
	GPIO_PORTF_PUR_R = 0x10;	// enable Pull-Up resistor for PF4
	GPIO_PORTF_AFSEL_R = 0x00;	// clear AFSEL
	GPIO_PORTF_DEN_R = 0x1A;	// enable digital ports
}

// Subroutine reads AS input and waits for signal to be low
// If AS is already low, it returns right away
// If AS is currently high, it will wait until it to go low
// Inputs:  None
// Outputs: None
void WaitForASLow(void)
{
	 /* do {
		AtrialSensor = GPIO_PORTF_DATA_R & 0x10;	// AS = PF4 = SW1
	} while(AtrialSensor == 0x10); */
	
	while(GPIO_PORTF_DATA_R & 0x10);	// AS = PF4 = SW1
}

// Subroutine reads AS input and waits for signal to be high
// If AS is already high, it returns right away
// If AS is currently low, it will wait until it to go high
// Inputs:  None
// Outputs: None
void WaitForASHigh(void)
{
	while(!(GPIO_PORTF_DATA_R & 0x10));	// AS = PF4 = SW1
}

// Subroutine sets VT high
// Inputs:  None
// Outputs: None
// Notes:   friendly means it does not affect other bits in the port
void SetVT(void)
{
	GPIO_PORTF_DATA_R |= 0x02;	// VT = PF1
}

// Subroutine clears VT low
// Inputs:  None
// Outputs: None
// Notes:   friendly means it does not affect other bits in the port
void ClearVT(void)
{
	GPIO_PORTF_DATA_R = 0x00;
}

// Subroutine sets Ready high
// Inputs:  None
// Outputs: None
// Notes:   friendly means it does not affect other bits in the port
void SetReady(void)
{
	GPIO_PORTF_DATA_R |= 0x08;	// Ready = PF3
}

// Subroutine clears Ready low
// Inputs:  None
// Outputs: None
// Notes:   friendly means it does not affect other bits in the port
void ClearReady(void)
{
	GPIO_PORTF_DATA_R = 0x00;
}

// Subroutine to delay in units of milliseconds
// Inputs:  Number of milliseconds to delay
// Outputs: None
// Notes:   assumes 80 MHz clock
void Delay1ms(unsigned long msec)
{
	unsigned long i;
	
	while(msec > 0)
	{
		i = 13333;
		while(i > 0)
		{
			i--;
		}
		msec--;
	}
}