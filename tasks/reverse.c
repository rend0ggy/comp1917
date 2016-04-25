// Function to reverse a string
// Written by Jack Renshaw
// j.renshaw@student.unsw.edu.au

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char *reverse (char *message); // declare relevant function

int main() // Main function for testing
{
	char* string = "Hello World!";
	char * reversedString;
	reversedString = reverse(string);
	printf("%s\n",reversedString);
	return 0;
}

char *reverse (char *message) // Function returns an array of characters (string) and takes the same as input
{
	char * reversedString = (char*)malloc((strlen(message)+1)*256); // Allocate a block of memory the same size as that of the input
	int i = 0;
	while(i<strlen(message)) // Loop through each character of the string
	{
		reversedString[i] = message[strlen(message)-1-i]; // Set the nth index of the new string to be the Nth character from the end of the input string 
		i++;
	}
	reversedString[strlen(message)] = 0; // We need to make sure that the string terminates correctly by adding a null character
	return reversedString; // Return the reversed string
}