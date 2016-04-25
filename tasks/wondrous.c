// C Wonderous Function program - prints out the wonderous numbers starting at some given input
// Written by Jack Renshaw - j.renshaw@student.unsw.edu.au
// 1/04/2016

#include<stdio.h>

int nextTerm (int currentTerm) // Function derives the next term based on the rule given by task
{
	if(currentTerm%2 == 0){ // If the input number is even
		return currentTerm/2; // return half
	}else{ // If the input number is odd
		return currentTerm*3+1; // Return 3x number+1
	}
}

int printWondrous (int start) // Main wondrous function
{

	int currentTerm = start; 
	int count = 0;
	while(currentTerm != 1){ // Termination condition is the current term is 1
		printf("%d ", currentTerm); // Print the current term
		currentTerm = nextTerm(currentTerm); // Iterate to the next term
		count++;
	}
	printf("1\n"); // Print 1 and end

	return count+1;

}

int main(void)
{
	printf("\n%d terms were printed\n",printWondrous(3)); // Call the wondrous function

	return 0;
}