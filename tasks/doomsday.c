/*
 *  doomsday.c
 *  A program to test a function dayOfWeek which determines which
 *  day of the week a particular date falls on.
 *  (only for dates after the start of the Gregorian calendar).
 *
 *  Program stub created by Richard Buckland on 17/03/14
 *  This program by Jack Renshaw - j.renshaw@student.unsw.edu.au
 *  Freely licensed under Creative Commons CC-BY-3.0
 *
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
 #include <math.h>
 
#define THURSDAY 0
#define FRIDAY   1
#define SATURDAY 2
#define SUNDAY   3
#define MONDAY   4
#define TUESDAY  5
#define WEDNESDAY 6
 
#define TRUE 1
#define FALSE 0
#define DAYS_PER_WEEK 7
 
int dayOfWeek (int doomsday, int leapYear, int month, int day);


int main (int argc, char *argv[]) {
   assert (dayOfWeek (THURSDAY,  FALSE,  4,  4) == THURSDAY);
   assert (dayOfWeek (FRIDAY,    FALSE,  6,  6) == FRIDAY);
   assert (dayOfWeek (MONDAY,    FALSE,  8,  8) == MONDAY);
   assert (dayOfWeek (WEDNESDAY, FALSE, 10, 10) == WEDNESDAY);
   assert (dayOfWeek (FRIDAY,    FALSE, 12, 12) == FRIDAY);
   assert (dayOfWeek (THURSDAY,  FALSE,  9,  5) == THURSDAY);
   assert (dayOfWeek (FRIDAY,    FALSE,  5,  9) == FRIDAY);
   assert (dayOfWeek (SUNDAY,    FALSE,  7, 11) == SUNDAY);
   assert (dayOfWeek (TUESDAY,   FALSE, 11,  7) == TUESDAY);
   assert (dayOfWeek (WEDNESDAY, FALSE,  3,  7) == WEDNESDAY);
 
   assert (dayOfWeek (THURSDAY,  FALSE,  4,  5) == FRIDAY);
   assert (dayOfWeek (SATURDAY,  FALSE,  6,  5) == FRIDAY);
   assert (dayOfWeek (MONDAY,    FALSE,  8,  9) == TUESDAY);
   assert (dayOfWeek (WEDNESDAY, FALSE, 10,  9) == TUESDAY);
   assert (dayOfWeek (FRIDAY,    FALSE, 12, 20) == SATURDAY);
   assert (dayOfWeek (THURSDAY,  FALSE,  9,  9) == MONDAY);
   assert (dayOfWeek (FRIDAY,    FALSE,  5,  5) == MONDAY);
   assert (dayOfWeek (SUNDAY,    FALSE,  7,  7) == WEDNESDAY);
   assert (dayOfWeek (TUESDAY,   FALSE, 11, 11) == SATURDAY);
   assert (dayOfWeek (THURSDAY,  FALSE,  3, 30) == SATURDAY);
 
   assert (dayOfWeek (TUESDAY,   FALSE,  2,  28) == TUESDAY);
   assert (dayOfWeek (TUESDAY,   FALSE,  2,  27) == MONDAY);
   assert (dayOfWeek (THURSDAY,  FALSE,  1,  3)  == THURSDAY);
 
   printf ("all tests passed - You are awesome!\n");
   return EXIT_SUCCESS;
}
 
 
// given the doomsday for a year, and whether or not it is a
// leap year, this function return the day of the week for any
// given month and day in the year.

int dayOfWeek (int doomsday, int leapYear, int month, int day) {
   int dayOfWeek;

   month = month-1;
 
   int doomsDays[14] = {
   		3, // January
   		7, // February
   		7, // March
   		4, // April
   		2, // May
   		6, // June
   		4, // July
   		1, // August
   		5, //September
   		3, // October
   		7, // November
   		5, // December
   		4, // Leap January
   		1 // Leap February
   	};
 
   	if(leapYear == TRUE && (month == 0 || month == 1)) // If we're in a leap year (and if we're in a month affected by the leap year)
   	{
   		month = month+12; // From now on refer to the special doomsday cases
   	}

   	int closestDoomsDay = doomsDays[month]; // Pick the first doomsday of the input month
   	int dayDifference = day - closestDoomsDay; // How far away are we?

	dayOfWeek = doomsday + dayDifference; // Count up from the doomsday to the input day

	if(dayOfWeek < 0){ // If we counted back beyond 0
		dayOfWeek = 7+dayOfWeek; // Add 7 to return us to positive numbers (modular arithmetic dictates that this is valid)
	}

	dayOfWeek = dayOfWeek%7; // Take the remainder when divided by 7 to give us a value 0-->6


   return (dayOfWeek); // return the day of the week
}