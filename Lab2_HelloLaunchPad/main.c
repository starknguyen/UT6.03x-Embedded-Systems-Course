/* This project is created as a solution to Lab 2- Hello Launchpad from UT6.03x course--- 
   The main structure is from Daniel Valvano, Jonathan Valvano and Ramesh Yerraballi-----
	 The author adds more comments explaining each register--------------------------------
	 Created by: Dinh-Nghi Nguyen----------------------------------------------------------
	 Date: 23.03.2016----------------------------------------------------------------------*/

/* Note: TExaS_Init() and EnableInterrupts() are not used in this project
	 since it is not used for grading-------------------------------------*/

// 1. Pre-processor Directices Section
// Constant declarations to access port registers using 
// symbolic names instead of addresses
// Note: the values are the addresses to access, NOT the value to read/write
// In this project, we will use PORTF

// LaunchPad built-in hardware (see Table 2-2 TM4C123 Launchpad User Manual)
// SW1 left switch is negative logic PF4 on the Launchpad
// SW2 right switch is negative logic PF0 on the Launchpad
// red LED connected to PF1 on the Launchpad
// blue LED connected to PF2 on the Launchpad
// green LED connected to PF3 on the Launchpad

// Using Bit-Specific Addressing method
// Use typecast of unsigned long to convert to unsigned 32-bit
// Use volatile because value of a port can change beyond the direct action of the software
// It forces the C compiler to read a new value each time through a loop and not rely on the previous one

// Register GPIO Data. Offset 0x000 (?)
#define GPIO_PORTF_DATA_R							(*((volatile unsigned long *)(0x400253FC)))
	
// Register GPIO Direction. Offset 0x400
#define GPIO_PORTF_DIR_R							(*((volatile unsigned long *)(0x40025400)))

// Register GPIO Alternate Function Select. Offset 0x420
#define GPIO_PORTF_AFSEL_R						(*((volatile unsigned long *)(0x40025420)))
	
// Register GPIO Pull-Up Select. Offset 0x510
#define GPIO_PORTF_PUR_R							(*((volatile unsigned long *)(0x40025510)))
	
// Register GPIO Digital Enable. Offset 0x51C
#define GPIO_PORTF_DEN_R							(*((volatile unsigned long *)(0x4002551C)))

// Register GPIO Lock. Offset 0x520
#define GPIO_PORTF_LOCK_R							(*((volatile unsigned long *)(0x40025520)))
	
// Register GPIO Commit. Offset 0x524
#define GPIO_PORTF_CR_R								(*((volatile unsigned long *)(0x40025524)))
	
// Register GPIO Analog Mode Select. Offset 0x528
#define GPIO_PORTF_AMSEL_R						(*((volatile unsigned long *)(0x40025528)))
	
// Register GPIO Port Control. Offset 0x52C
#define GPIO_PORTF_PCTL_R							(*((volatile unsigned long *)(0x4002552C)))
	
// Register 2 Run Mode Clock Gating Control. Offset 0x108
#define SYSCTL_RCGC2_R								(*((volatile unsigned long *)(0x400FE108)))
	
// 2. Declarations Section
// Global Variables
unsigned long Input;

// Function Prototypes
void PortF_Init(void);
void Delay(void);
void SystemInit(){}

// 3. Subroutines Section
// main function
int main(void)
{
	// Initialize port F
	PortF_Init();
	
	// forever loop
	while(1)
	{
			Input = GPIO_PORTF_DATA_R & 0x10;	// Set PF4 as Input, PF3-2-1 Output: 0b00010000

			if(!Input)	// Switch is pressed
			{
				GPIO_PORTF_DATA_R = 0x08; // Green LED
			}
			else // If switch is not pressed
			{
				GPIO_PORTF_DATA_R = 0x02;	// Red LED
			}
			Delay();
			GPIO_PORTF_DATA_R = 0x04; // Blue LED
			Delay();
	}
}

// Subroutine to initialize port F
void PortF_Init(void)
{
	volatile unsigned long delay;
	
	// Step 1: Activate clock for port F = Enable bit 5 in RCGC2, others not set.
	SYSCTL_RCGC2_R |= 0x20;; // Set bit 5 = 0b00100000
	// It takes time for the clock to stabilize
	delay = SYSCTL_RCGC2_R;
	// Step 2: Unlock port F.
	GPIO_PORTF_LOCK_R |= 0x4C4F434B;	// Write value to address
	// After unlock port, we need to commit the change from PF0 to PF4
	GPIO_PORTF_CR_R |= 0x1F; // Set bit 4-0 = 0b00011111
	// Step 3: Disable analog function
	GPIO_PORTF_AMSEL_R |= 0x00;
	// Step 4: GPIO clear bit PCTL
	GPIO_PORTF_PCTL_R |= 0x00;
	// Step 5: Set DIR input/output for each bit
	// In this project: PF0 and PF4 are inputs (swtiches), PF1-2-3 are outputs (LEDs)
	GPIO_PORTF_DIR_R |= 0x0E; // 0b01110
	// Enable Pull-Up resistors (PUR) for PF4 and PF0 (switches)
	GPIO_PORTF_PUR_R |= 0x11; // 0b10001
	// Step 6: Enable DEN, from PF4 to PF0
	GPIO_PORTF_DEN_R |= 0x1F;	// 0b11111
}

// Subroutine to delay 0.1 second
void Delay(void)
{
	unsigned long volatile time;
	time = 727240*200/91;		// 0.1 sec
	while(time)
	{
		time--;
	}
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
