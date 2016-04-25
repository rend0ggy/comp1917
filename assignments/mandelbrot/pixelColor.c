/*

Mandelbrot project - created by Jack Renshaw
email - j.renshaw97@gmail.com

*/
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <netinet/in.h>
#include <unistd.h>
#include <math.h>
#include "extract.h"


typedef unsigned char  bits8;
typedef unsigned short bits16;
typedef unsigned int   bits32;


#define BYTES_PER_PIXEL 3
#define BITS_PER_PIXEL (BYTES_PER_PIXEL*8)
#define NUMBER_PLANES 1
#define PIX_PER_METRE 2835
#define MAGIC_NUMBER 0x4d42
#define NO_COMPRESSION 0
#define OFFSET 54
#define DIB_HEADER_SIZE 40
#define NUM_COLORS 16777216
#define BMP_FILE "coloredMandelbrot.bmp"
bits8 byte;

void writeBMP(char* mandelbrot, int size);
void writeHeader (FILE *file,int size);
char* mandelbrotString(double x,double y,long z,int size);
int inMandelbrot(double x,double y);
double power(int base,int exponent);

int main()
{
	int size=512;
	char* plot = mandelbrotString(-1.0,-0.4,11,size); // Declare a new string which stores the the mandelbrot set
	writeBMP(plot,size); // Write the mandelbrot string to a BMP file
	return 0;
}

double power(int base,int exponent) // Function calculates an exponential
{
	double result = (double)base; // Set the output to be the base
	if(exponent>0) // If there is a positive exponent
	{
		int i = 1;
		while(i<exponent) // For every value between 1 and the exponent
		{
			result = result*base; // Multiply the result by the base
			i++;
		}
	}
	if(exponent<=0) // If there is a non-positive exponent
	{
		int i = -1;
		while(i<(-1*exponent)) // For every value between 1 and the absolute value of the exponent
		{
			result = result/base; // Divide the result by the base n+1 times
			i++;
		}
	}
	return result; // Result the result
}

// Credit to wikipedia for providing a pseudo-code description of the mandelbrot set
int inMandelbrot(double x,double y) // Function determines whether a vector defined by (x,y) lies in the mandelbrot set
{
	/*
	
	A number c is said to lie in the mandelbrot set if the modulus of the number remains less than two
	after an infinite amount of iterations of z(n+1) = z(n)^2+c

	This function returns a value between 0 and 255 inclusive. That colour represents a colour. 

	->Black means that the vector lies in the mandelbrot set
	->White means that the vector failed on the first pass
	->Grey means that the vector is close to the mandelbrot set
	*/
	int max_runthrough = 255; // Arbitrarily limit the amount of iterations at 256
	double xinit = 0.0;
	double yinit = 0.0;
	double xtemp;
	int i = 0;
	while(xinit*xinit+yinit*yinit < 2*2 && i < max_runthrough) // While the modulus is less than two and we haven't met our limit
	{
		xtemp = xinit*xinit-yinit*yinit + x; 
		yinit = 2*xinit*yinit + y; 
		xinit = xtemp;
		i++;
	}
	int returnC = 255-(double)i; // The value we're interested in is the opposite of the number of iterations (otherwise we'd have a white mandelbrot set on a black background)
	return returnC; // If number lies in the mandelbrot set, return 255. Otherwise, return a value between 0 and 255
}

char* mandelbrotString(double x,double y,long z,int size) // Function generates a string of characters which represents the mandelbrot set
{
	/*
	
	The function returns an array of characters. Each character represents a color. The ascii number of the character represents the greyscale colour.

	Function takes the centre of the image as x,y and the zoom as z. The string is calculated as per specifications given in the task

	*/
	char *returnString = (char*) malloc(size*size); // create a space in memory to store the return string
	// Zoom is defined as the distance between adjacent pixels
	// i.e. zoom of 8 means that there is a distance of 2^-8 between pixels
	double zoom = size/2*power(2,(-1*(z))); // The zoom variable enables us to define our boundaries
	//Define boundaries (remember, we start from the bottom with BMP)
	double leftBoundary = x - zoom;
	double rightBoundary = x + zoom;
	double upperBoundary = y - zoom;
	double lowerBoundary = y + zoom;
	int i = 0;
	int j = 0;
	double ycoordinate; // The y-coordinate of the vector
	double xcoordinate; // THe c-coordinate of the vector
	int isInMandelbrot; // The integer value returned by the InMandelbrot function
	while(i<size) // For each row
	{
		ycoordinate = upperBoundary - i*((upperBoundary-lowerBoundary)/size); //ascertain the y coordinate
		j=0;
		while(j<size) // For each square within specified precision
		{
			xcoordinate = leftBoundary - j*((leftBoundary-rightBoundary)/size); // ascertain the x coordinate
			isInMandelbrot = inMandelbrot(xcoordinate,ycoordinate); // check whether vector lies in the mandelbrot set and return pixel colour
			returnString[i*size+j] = (char)isInMandelbrot; // add this to the string as a character
			j++;
		}
		i++;
	}
	return returnString; // return the array of characters
}

void writeBMP(char* mandelbrot, int size) // Function generates a BMP file of the mandelbrot set based on the mandelbrot string
{
	// courtesy of chessboard.c
   FILE *outputFile;
 
   outputFile = fopen(BMP_FILE, "wb");
   assert ((outputFile!=NULL) && "Cannot open file");
 
   writeHeader(outputFile,size);

   bits8 byte;
   int i = 0;
	while(i < size*size*3) // For every pixel
   	{
   		byte = (int)mandelbrot[i/3]; //Set the colour of the current byte to be the value specified in the array of characters in the mandelbrot string
   		fwrite (&byte, sizeof byte, 1, outputFile); // Write the pixel
   		//fwrite (&byte, sizeof byte, 1, outputFile); // Write the pixel
   		//fwrite (&byte, sizeof byte, 1, outputFile); // Write the pixel
   		i++;
	}
   fclose(outputFile);
 
}

void writeHeader (FILE *file,int size) { // writeHeader function - courtesy of chessboard.c
   assert(sizeof (bits8) == 1);
   assert(sizeof (bits16) == 2);
   assert(sizeof (bits32) == 4);

   char header[55] = {0x42, 0x4D, 0x36, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x01, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x12, 0x0B, 0x00, 0x00, 0x12, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
 
   fwrite (header, sizeof header, 1, file);
 
}
