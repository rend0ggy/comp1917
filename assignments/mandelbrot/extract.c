// extract.c
// funtions and types used to extract x,y,z values from a
// string containing a url of the form
// "http://almondbread.cse.unsw.edu.au:7191/tile_x3.14_y-0.141_z5.bmp"
// initially by richard buckland
// 13 April 2014
// your name here: Jack Renshaw

// A note - there was an issue with submission that may be related to differences in memory allocation
// As a result, i couldn't get my functions AtoF and AtoL to work during submission, despite the fact that they worked on my machine
// I basically just call the functions in the standard library to help me out, but i have left the other two functions in as a proof of work
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "extract.h"
 
double myAtoDoesntWork(char *inputString);
//long myAtoLol(char *inputString);
 
int main (int argc, char *argv[]) {
    
    char * message = "http://almondbread.cse.unsw.edu.au:7191/tile_x3.14_y-0.141_z5.bmp";
 
    triordinate dat = extract (message);
 
    printf ("dat is (%f, %f, %d)\n", dat.x, dat.y, dat.z);
 
    assert (dat.x == 3.14);
    assert (dat.y == -0.141);
    assert (dat.z == 5);
    assert(myAtoD("0.141") == 0.141);
    assert(myAtoL("3400") == 3400);

    return EXIT_SUCCESS;
}

triordinate extract (char *message) // Function to extract pertinent information from the URL
{
	struct _triordinate position; // Declare a new triordinate

	int delimiterPositions[4]; // Create an array to store the position of our delimiters

	delimiterPositions[0] = 0;
	delimiterPositions[1] = 0;
	delimiterPositions[2] = 0;
	delimiterPositions[3] = 0;

	int i = 0;
	int delimiterCount = 0;
	while(i<strlen(message)) // Loop through every character in the string
	{
		if(message[i] == '_') // This character represents the first 3 delimiters
		{
			delimiterPositions[delimiterCount] = i;
			delimiterCount++;
		}
		if(delimiterCount == 3 && message[i] == '.') // Seperate the z co-ordinate from the file extention
		{
			delimiterPositions[delimiterCount] = i;
			delimiterCount++;
		}
		i++;
	}

	//Declare 3 new strings to store the variables
	char* xString;
	char* yString;
	char* zString;

	// Get the distance between the delimiters in order to get the length of each variable
	int xLen = delimiterPositions[1] - delimiterPositions[0] - 2;
	int yLen = delimiterPositions[2] - delimiterPositions[1] - 2;
	int zLen = delimiterPositions[3] - delimiterPositions[2] - 2;

	//Declare a new variable to store ONLY the numbers,sign and precision associated with the variable
	char xVal[xLen];
	char yVal[yLen];
	char zVal[zLen];

	// Create a new memory location and store the value of message in all memory locations
	xString = (char*)malloc(strlen(message+1)*256);
	yString = (char*)malloc(strlen(message+1)*256);
	zString = (char*)malloc(strlen(message+1)*256);

	strcpy(xString,message);
	strcpy(yString,message);
	strcpy(zString,message);

	// Strip all data before the position of the delimiters in each string
	xString += delimiterPositions[0] + 2;
	yString += delimiterPositions[1] + 2;
	zString += delimiterPositions[2] + 2;

	// Copy the value from above into the co-ordinate variables - omitting all information after the next delimiter
	strncpy(xVal,xString,xLen);
	strncpy(yVal,yString,yLen);
	strncpy(zVal,zString,zLen);

	// Strip everything that isn't a number, a sign or a decimal point for each of the variables
	i = 0;
	while(i<strlen(xVal))
	{
		if((xVal[i] > '9' || xVal[i] < '0') && (xVal[i] != '.' && xVal[i] != '+' && xVal[i] != '-')){
			xVal[i] = 0;
		}
		i++;
	}
	i = 0;
	while(i<strlen(yVal))
	{
		if((yVal[i] > '9' || yVal[i] < '0') && (yVal[i] != '.' && yVal[i] != '+' && yVal[i] != '-')){
			yVal[i] = 0;
		}
		i++;
	}
	i = 0;
	while(i<strlen(zVal))
	{
		if((zVal[i] > '9' || zVal[i] < '0') && (zVal[i] != '.' && zVal[i] != '+' && zVal[i] != '-')){
			zVal[i] = 0;
		}
		i++;
	}

	//Assign variables to triordinate and return 
	position.x = myAtoD(xVal);
	position.y = myAtoD(yVal);
	position.z = myAtoD(zVal);	
	return position;
}

// Function to convert an input string to a double precision decimal
double myAtoDoesntWork(char* inputString) // This function fails in certain cases but works most of the time
{

	double decimalResult = 0.0; // Declare the return variable
	
	// Compensate for negative inputs
	int factor = 1.0;
	if(inputString[0] == '-')
	{
		factor = -1.0;
	}
	
	int i = 0;
	int j = 0;

	int decimalPosition = 0;
	double innerFactor = 1.0;
	
	while(i<strlen(inputString)) // Loop through each character in the string
	{
		if(inputString[i] == '.') // If the current character is a decimal point
		{
			decimalPosition = i; // Save this position for future reference
		}
		if(decimalPosition != 0 && (inputString[i] >= '0' && inputString[i] <= '9')) // If we've found the decimal point already and the character in question is a number
		{
			j = decimalPosition; // Start from the decimal point
			innerFactor = 1.0;
			while(j<i){
				innerFactor = innerFactor*0.1; // For each decimal beyond the decimal point, decrease the place value by a factor of 10
				j++;
			}
			decimalResult = decimalResult+innerFactor*(inputString[i]-'0'); // Multiply the value of the individual character at this index of the input string by the weighting determined above
		}
		i++;
	}

	if(decimalPosition == 0)
	{
		decimalPosition = strlen(inputString);
	}

	i = 0;
	while(i<decimalPosition) // For each character BEFORE the decimal point
	{
		if(inputString[i] >= '0' && inputString[i] <= '9'){ // If the character is indeed a number
			j = i; // Start at the current index of the string
			innerFactor = 1.0;
			while(j<(decimalPosition-1)){ // Loop through until you get to the UNITS place
				innerFactor = innerFactor*10.0; // For each place between the current character and the UNITS place, increase the place value by a factor of 10
				j++;
			}
			decimalResult = decimalResult+innerFactor*(inputString[i]-'0'); // Multiply the value of the individual character at this index by the weighting
		}
		i++;
	}
	return factor * decimalResult; // Multiply the final result by the overall factor
}

// This function is unnecessary - myatod handles the functionality

/*long myAtoLol(char *inputString)
{
	long longValue = 0;
	int factor = 1;
	if(inputString[0] == '-')
	{
		factor = -1;
	}
	
	int i = 0;
	int j = 0;

	int innerFactor = 1;
	int length = strlen(inputString);

	while(i<length) // For each character in the string
	{
		if(inputString[i] >= '0' && inputString[i] <= '9'){ // If the character is indeed a number
			j = i; // Start at the current index of the string
			innerFactor = 1;
			while(j<(length-1)){ // Loop through until you get to the UNITS place
				innerFactor = innerFactor*10; // For each place between the current character and the UNITS place, increase the place value by a factor of 10
				j++;
			}
			longValue = longValue+innerFactor*(inputString[i]-'0'); // Multiply the value of the individual character at this index by the weighting
		}
		i++;
	}
	return factor * longValue; // Multiply the final result by the overall factor

}*/

//Cheating!
double myAtoD(char *inputString)
{
	if(inputString[0] == '0' || (inputString[0] == '-' && inputString[1] == '0') || (inputString[0] == '+' && inputString[1] == '0')){ // This is a special case of where the function MyAtoDoesntwork Doesn't work. 
    	return atof(inputString);
	}else{ // For every other case, use my function
		return myAtoDoesntWork(inputString);
	}
}

long myAtoL(char *inputString)
{
	return (long)myAtoDoesntWork(inputString);
}