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
#define NUM_COLORS 0
#define BMP_FILE "requested.bmp"
bits8 byte;

 
int waitForConnection (int serverSocket);
int makeServerSocket (int portno);
void serveHTML (int socket);
void serveBMP (int socket);
void writeBMP(char* mandelbrot, int size);
char* parseRequest(char* request);
int isTile(char info[5]);
void writeHeader (FILE *file,int size);
char* mandelbrotString(double x,double y,long z,int size);
int inMandelbrot(double x,double y);
double power(int base,int exponent);

#define REQUEST_BUFFER_SIZE 1000
#define DEFAULT_PORT 7191
#define NUMBER_OF_PAGES_TO_SERVE 100000
 
int main (int argc, char* argv[]) {
	int size = 512; // declare the size of the mandelbrot string and the output BMP file

	// Server stuff - credit to poetryserver.c
    int serverSocket = makeServerSocket(DEFAULT_PORT); // Start a server socket on port specified
    char request[REQUEST_BUFFER_SIZE]; // declare a character array to store user request
    int numberServed = 0; // we haven't served any pages yet
    while (numberServed < NUMBER_OF_PAGES_TO_SERVE) { // Cap the amount of pages we will serve
        int connectionSocket = waitForConnection(serverSocket); // Create a new connection socket to user
        int bytesRead = recv (connectionSocket, request, sizeof(request) - 1, 0);
        assert (bytesRead >= 0);
        char *parsedRequest = parseRequest(request); // Break down the HTTP request and acertain the URL (minus hostname)
        char tileinfo[5];
        strncpy(tileinfo,parsedRequest,6); // Take the first 6 characters of the parsed request
        tileinfo[5] = 0; // Make the string terminate at some point
        if(isTile(tileinfo) == 1){ // call function tileinfo to determine whether the URL requested is of a tile
            triordinate dat = extract (parsedRequest); // If this is so, parse the URL for the 3 coordinate variables
			      char* plot = mandelbrotString(dat.x,dat.y,dat.z,size); // Declare a new string which stores the the mandelbrot set
            writeBMP(plot,size); // Write the mandelbrot string to a BMP file
            serveBMP (connectionSocket); // Serve the BMP to the user
        }else{ // If the user isn't directly requesting a tile
            serveHTML (connectionSocket);  // Serve the standard page
        }
        close (connectionSocket); // close the connection
        ++numberServed; // we're one step closer the the server shutting down
    }
     close (serverSocket); // Shut down the server
  
    return EXIT_SUCCESS;
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
 
void serveHTML(int socket) { // Function serves standard HTML page which includes script
  char* message;
 
   // first send the http response header
   message =
      "HTTP/1.0 200 Found\n"
      "Content-Type: text/html\n"
      "\n";
   write (socket, message, strlen (message));
 
   message =
      "<!DOCTYPE html>\n"
      "<script src=\"http://almondbread.cse.unsw.edu.au/tiles.js\"></script>"
      "\n";      
   write (socket, message, strlen (message));
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
   		i++;
	}
   fclose(outputFile);
 
}

void serveBMP (int socket) // Function serves the BMP file generated to the user
{
	// Courtesy of stackoverflow
  char* message;
    long fsize;
    FILE *fp = fopen(BMP_FILE, "rb"); // open the file

    if (fseek(fp, 0, SEEK_END) == -1){ // Make sure that the file is okay
        perror("The file was not seeked");
        exit(1);
    }

    fsize = ftell(fp); // get the file size
    if (fsize == -1) {
        perror("The file size was not retrieved");
        exit(1);
    }
    rewind(fp);

    char *msg = (char*) malloc(fsize); // Allocate a block of memory of that size
    if (!msg){
        perror("The file buffer was not allocated\n");
        exit(1);
    }

    if (fread(msg, fsize, 1, fp) != 1){ // read the file to the string
        perror("The file was not read\n");
        exit(1);
    }
    fclose(fp);

   // first send the http response header
   message =
      "HTTP/1.0 200 Found\n"
      "Content-Type: image/bmp\n"
      "\n";
    write (socket, message, strlen (message));
    write (socket, msg, fsize); // Serve the file
 
 }
 
// start the server listening on the specified port number
int makeServerSocket (int portNumber) {
 
    // create socket
    int serverSocket = socket (AF_INET, SOCK_STREAM, 0);
    assert (serverSocket >= 0);
    // check there was no error in opening the socket
 
    // bind the socket to the listening port  (7191 in this case)
    struct sockaddr_in serverAddress;
    serverAddress.sin_family      = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port        = htons (portNumber);
 
    // tell the server to restart immediately after a previous shutdown
    // even if it looks like the socket is still in use
    // otherwise we might have to wait a little while before rerunning the
    // server once it has stopped
    const int optionValue = 1;
    setsockopt (serverSocket, SOL_SOCKET, SO_REUSEADDR, &optionValue, sizeof (int));
 
    int bindSuccess = bind (serverSocket, (struct sockaddr*)&serverAddress, sizeof (serverAddress));
 
    assert (bindSuccess >= 0);
    // if this assert fails wait a short while to let the operating
    // system clear the port before trying again
 
    return serverSocket;
}
 
// wait for a browser to request a connection,
// returns the socket on which the conversation will take place
int waitForConnection (int serverSocket) {
 
    // listen for a connection
    const int serverMaxBacklog = 10;
    listen (serverSocket, serverMaxBacklog);
 
    // accept the connection
    struct sockaddr_in clientAddress;
    socklen_t clientLen = sizeof (clientAddress);
    int connectionSocket = accept (serverSocket, (struct sockaddr*)&clientAddress, &clientLen);
    assert (connectionSocket >= 0);
    // check for connection error
 
    return connectionSocket;
}

char* parseRequest(char* request) // Function takes the GET request as input and returns the URL less hostname
{
    char* inputRequest = (char*)malloc(strlen(request+1)); // Allocate a block of memory for the request
    strcpy(inputRequest,request); // copy the request to the new memory block
    int i = 0;
    int j = 0;
    while(inputRequest[i] != '/') //Find the first slash and make the index i
    {
        i++;
    }
    j=i;
    while(inputRequest[j] != ' ') //  Find the first space after the first slash
    {
        j++;
    }
    char* url = (char*)malloc((j-i+1)); // Allocate a block of memory that is of length j-i
    inputRequest += i; // Strip everything before the first slash
    strncpy(url,inputRequest,(j-i)); // Copy the data between the slash and space into the variable URL
    url[strlen(url)] = 0; // Make the last character NULL
    return url; // Return variable
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
    position.x = atof(xVal);
    position.y = atof(yVal);
    position.z = atoi(zVal);  
    return position;
}

int isTile(char info[5]) // Function determines whether a character array is exactly equal to "/tile"
{
    char tile[5] = "/tile";
    int i = 0;
    int isTrue = 1;
    while(i<5)
    {
        if(info[i] != tile[i]){
            isTrue = 0;
        }
        i++;
    }
    return isTrue;
}

void writeHeader (FILE *file,int size) { // writeHeader function - courtesy of chessboard.c
   assert(sizeof (bits8) == 1);
   assert(sizeof (bits16) == 2);
   assert(sizeof (bits32) == 4);

   char* header = "";
 
   bits16 magicNumber = MAGIC_NUMBER;
   fwrite (&magicNumber, sizeof magicNumber, 1, file);
 
   bits32 fileSize = OFFSET + (size * size * BYTES_PER_PIXEL);
   fwrite (&fileSize, sizeof fileSize, 1, file);
 
   bits32 reserved = 0;
   fwrite (&reserved, sizeof reserved, 1, file);
 
   bits32 offset = OFFSET;
   fwrite (&offset, sizeof offset, 1, file);
 
   bits32 dibHeaderSize = DIB_HEADER_SIZE;
   fwrite (&dibHeaderSize, sizeof dibHeaderSize, 1, file);
 
   bits32 width = size;
   fwrite (&width, sizeof width, 1, file);
 
   bits32 height = size;
   fwrite (&height, sizeof height, 1, file);
 
   bits16 planes = NUMBER_PLANES;
   fwrite (&planes, sizeof planes, 1, file);
 
   bits16 bitsPerPixel = BITS_PER_PIXEL;
   fwrite (&bitsPerPixel, sizeof bitsPerPixel, 1, file);
 
   bits32 compression = NO_COMPRESSION;
   fwrite (&compression, sizeof compression, 1, file);
 
   bits32 imageSize = (size * size * BYTES_PER_PIXEL);
   fwrite (&imageSize, sizeof imageSize, 1, file);
 
   bits32 hResolution = PIX_PER_METRE;
   fwrite (&hResolution, sizeof hResolution, 1, file);
 
   bits32 vResolution = PIX_PER_METRE;
   fwrite (&vResolution, sizeof vResolution, 1, file);
 
   bits32 numColors = NUM_COLORS;
   fwrite (&numColors, sizeof numColors, 1, file);
 
   bits32 importantColors = NUM_COLORS;
   fwrite (&importantColors, sizeof importantColors, 1, file);
 
}
