// extract.c
// funtions and types used to extract x,y,z values from a
// string containing a url of the form
// "http://almondbread.cse.unsw.edu.au:7191/tile_x3.14_y-0.141_z5.bmp"
// initially by richard buckland
// 13 April 2014
// your name here:
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "extract.h"
 
 
int main (int argc, char *argv[]) {
    
    char * message = "http://almondbread.cse.unsw.edu.au:7191/tile_x3.14_y-0.141_z5.bmp";
 
    triordinate dat = extract (message);
 
    printf ("dat is (%f, %f, %d)\n", dat.x, dat.y, dat.z);
 
    long int num2 = myAtoL("5.");

    assert (dat.x == 3.14);
    assert (dat.y == 0.141);
    assert (dat.z == 5);
    assert(myAtoD("3.14") == 3.14);
    assert(myAtoL("3400") == 3400);
 
    return EXIT_SUCCESS;
}

triordinate extract (char *message)
{
	struct _triordinate position;

	int delimiterPositions[4];

	delimiterPositions[0] = 0;
	delimiterPositions[1] = 0;
	delimiterPositions[2] = 0;
	delimiterPositions[3] = 0;

	int i = 0;
	int delimiterCount = 0;
	while(i<strlen(message))
	{
		if(message[i] == '_')
		{
			delimiterPositions[delimiterCount] = i;
			delimiterCount++;
		}
		if(delimiterCount == 3 && message[i] == '.')
		{
			delimiterPositions[delimiterCount] = i;
			delimiterCount++;
		}
		i++;
	}

	char* xString;
	char* yString;
	char* zString;

	int xLen = delimiterPositions[1] - delimiterPositions[0] - 2;
	int yLen = delimiterPositions[2] - delimiterPositions[1] - 2;
	int zLen = delimiterPositions[3] - delimiterPositions[2] - 2;

	char xVal[xLen];
	char yVal[yLen];
	char zVal[zLen];

	xString = message;
	yString = message;
	zString = message;

	xString += delimiterPositions[0]+2;
	yString += delimiterPositions[1]+2;
	zString += delimiterPositions[2] + 2;

	strncpy(xVal,xString,xLen);
	strncpy(yVal,yString,yLen);
	strncpy(zVal,zString,zLen);

	position.x = myAtoD(xVal);
	position.y = myAtoD(yVal);
	position.z = myAtoL(zVal);
	
	return position;
}

double myAtoD(char* inputString)
{
	double result = 0;
	int nonNumerical = 0;
	int i = 0;
	int j = 0;
	float scaleFactor = 1;
	while(i<strlen(inputString))
	{
		scaleFactor = 1;
		j=nonNumerical;
		while(j<i)
		{
			scaleFactor = scaleFactor*0.1;
			j++;
		}
		if(inputString[i] > '9' || inputString[i] < '0'){
			nonNumerical++;
		}else{
			result += scaleFactor*(inputString[i]-'0');
		}
		i++;
	}
	if(inputString[0] == '-')
	{
		return -1*result;
	}else{
		return result;
	}
}
long myAtoL(char* inputString)
{
	long result = 0;
	int nonNumerical = 0;
	int i = strlen(inputString)-1;
	int j = 0;
	int scaleFactor = 1;
	while(i>=0)
	{
		scaleFactor = 1;
		j=strlen(inputString)-1-nonNumerical;
		while(j>i){
			scaleFactor = scaleFactor*10;
			j--;
		}
		if(inputString[i] > '9' || inputString[i] < '0'){
			nonNumerical++;
		}else{
			result += scaleFactor*(inputString[i]-'0');
		}
		i--;
	}
	if(inputString[0] == '-'){
		return -1*result;
	}else{
		return result;
	}
}