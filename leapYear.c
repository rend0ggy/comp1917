// Leap year program - determines whether or not an input year is a lear year
// Written by Jack Renshaw - j.renshaw@student.unsw.edu.au
// 1/04/2016

#include<stdio.h>
#include<assert.h>

int leapYearFunction(int year) // Primary leap year function
{
	assert(year > 1582); // The gregorian calendar only began in 1582
	if(year%4 == 0 && (year%100 != 0 || (year%100 == 0 && year%400 == 0))){ // Every 4th year except those that fall on centuries NOT divisible by 4 is a leap year
		return 1;
	}else{
		return 0;
	}
}

int main(void) // Main function with the same functionality
{
	int year;
	printf("please enter the year you are interested in\n");
	scanf("%d",&year); // Prompt the user for some year

	assert(year >= 1582);

	if(year%4 == 0 && (year%100 != 0 || (year%100 == 0 && year%400 == 0))){ // Every 4th year except those that fall on centuries NOT divisible by 4 is a leap year
		printf("%d is a leap year!\n",year);
	}else{
		printf("%d is not a leap year!\n",year);
	}

	return 0;
}