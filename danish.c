// Danish Flag Program - uses loops to print the flag of Denmark
// Written by Jack Renshaw - j.renshaw@student.unsw.edu.au
// 1/04/2016

#include<stdio.h>

void showDanish(void)
{
	int i = 0;
	while(i<2) // 3 lines
	{
		printf("** *********\n"); // Top part of the flag
		i++;
	}
	printf("\n"); // Empty section of the cross (2 lines)
	while(i<4) // 3 more lines
	{
		printf("** *********\n"); // Bottom part of the flag
		i++;
	}
}

int main(void)
{
	showDanish();

	return 0;
}