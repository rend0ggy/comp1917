// Swap Program - swaps two variables 
// Written by Jack Renshaw - j.renshaw@student.unsw.edu.au
// 1/04/2016

#include<stdio.h>

void swap(int *first, int *second)
{

     if (first != second) {
         *first ^= *second;
         *second ^= *first;
         *first ^= *second;
     }

}

int main()
{
	return 0;

}