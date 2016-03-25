/* This project is created as a solution to Lab 5- FunctionsInC from UT6.03x course--- 
   The main structure is from Daniel Valvano, Jonathan Valvano and Ramesh Yerraballi-----
	 The author adds more comments explaining each register--------------------------------
	 Created by: Dinh-Nghi Nguyen----------------------------------------------------------
	 Date: 24.03.2016----------------------------------------------------------------------*/

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

// Register GPIO Data. Offset 0x000. To access all 8 bits, use 0x53FC
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
unsigned long SW1, SW2;

// Function Prototypes
void PortF_Init(void);
void Delay(void);
void SystemInit(){}
unsigned long Calc_Area(unsigned long l, unsigned long w); 

	