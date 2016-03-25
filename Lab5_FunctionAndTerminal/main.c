/* This project is created as a solution to Lab 5- FunctionsInC from UT6.03x course--- 
   The main structure is from Daniel Valvano, Jonathan Valvano and Ramesh Yerraballi-----
	 The author adds more comments explaining each register--------------------------------
	 Created by: Dinh-Nghi Nguyen----------------------------------------------------------
	 Date: 25.03.2016----------------------------------------------------------------------*/

/* Note: TExaS_Init() and EnableInterrupts() are not used in this project
	 since it is not used for grading-------------------------------------*/

#include <stdio.h>   // standard C library 
#include "uart.h"    // functions to implment input/output

void SystemInit(){}
unsigned long Calc_Area(unsigned long l, unsigned long w);
	
int main (void) {
  unsigned long length, width, area;
	
  UART_Init();    // initialize UART for printing
  printf("\nThis program calculates areas of rectangular rooms.\n");

  while(1) {
    printf("\nGive length: "); scanf("%ld", &length);  // Get input
    printf("\nGive width: ");  scanf("%ld", &width);   // Get input
    area = Calc_Area(length, width);
    printf("\nArea of the room = %ld\n",  area);
  }
}

// Computes the Area of a rectangular room whose sides are given
// Input:  the length (l) and width (w) are the dimensions of a rectangle
// Output: the area of the rectangular room 
// Notes:  Return a result of zero if 
//    the length is less than 3,  
//    the width is less than 3,  
//    the length is greater than 20 or  
//    the width is greater than 20. 
unsigned long Calc_Area(unsigned long l, unsigned long w) {
  unsigned long result;

// Put your Lab 5 code here
	if(l < 3 || w < 3 || l > 20 || w > 20)
		result = 0;
	else
		result = l * w;
  
  return(result);
}
