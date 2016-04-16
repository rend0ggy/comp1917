// Sort 3 numbers - program sorts 3 numbers using bubble sort
// Written by Jack Renshaw - j.renshaw@student.unsw.edu.au
// 1/04/2016


#include<stdio.h>

void swap(int *first, int *second) // Let us use the swap function from a lab excersise
{

     if (first != second) {
         *first ^= *second;
         *second ^= *first;
         *first ^= *second;
     }

}


int main(void)
{
	int nums[3];
	scanf("%d%d%d",&nums[0],&nums[1],&nums[2]); // Prompt the used for 3 numbers

	int i=0;
	int j=0;
	while(j<2) // Two iterations
	{ 
		i = 0;
		while(i<2) // Loop through twice
		{
			if(nums[i] > nums[i+1]){ // If the integer to the left is greater than the integer to the right
				swap(&nums[i],&nums[i+1]); // Swap them around
			}
			i++;
		}
		j++;
	}

	// At this point the integers should be in order
	i = 0;
	while(i<3)
	{
		printf("%d\n",nums[i]);
		i++;
	}

	return 0;
}