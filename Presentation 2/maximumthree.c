

#include<stdio.h>

int maximum( int x, int y, int z ); // function prototype

// function main begins program execution
int main( void )
{
	int number1; // first integer
	int number2; // second integer
	int number3; // third integer
	
	printf("Enter three integers: " );
	scanf( "%d%d%d", &number1, &number2, &number3 );
	
	// number1, number2 and number3 are arguments
	// to the maximum function call
	printf( "Maximum is: %d\n", maximum( number1, number2, number3 ) );
} // end main

// Function maximum definition
// x, y and z are parameters
int maximum( int x, int y, int z )
{
	int max = x; // assume x is largest
	
	if ( y > max ) { // if y is larger than max, assign y to max
		max = y;
	} // end if
	
	if ( z > max ) { // if z is larger than max, assign z to max
		max = z;
	} // end if
	
	return max; // max is largest value
} // end function maximum
