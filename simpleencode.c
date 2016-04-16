/*
 *  simpleEncode.c
 *
 *  reads in a permutation of the alphabet then encodes
 *  lower case letters using that permutation
 *  module 4 template code you asked for - might need some cleaning up...
*
 *  Created by Julian Saknussemm on 11/09/1752
 *  Licensed under Creative Commons BY 3.0.
 *
 */

 // Simple encoder program
 // Function created by Jack Renshaw - j.renshaw@student.unsw.edu.au
 // 2/04/2016

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define STOP -1
#define ALPHABET_SIZE 26

char encode (int plainChar, char *permuation);
void testEncode (void);

int main (int argc, char *argv[]) {

   testEncode(); // call testing function

   char permutation[ALPHABET_SIZE];

   scanf ("%s", permutation);

   // getchar() reads and returns one character from the keyboard
   // returns -1 when the input is finished / end-of-file is reached
   // signal this from the kayboard by pressing ^D in linux/^Z windows
   int plainCharacter = getchar();
   while (plainCharacter != STOP) {
      int encodedCharacter = encode (plainCharacter, permutation);
      printf ("%c", encodedCharacter);
      plainCharacter = getchar();
   }
   return EXIT_SUCCESS;
}

void testEncode (void) {
   assert (encode ('A',"abcdefghijklmnopqrstuvwxyz") == 'A');
   assert (encode ('?',"abcdefghijklmnopqrstuvwxyz") == '?');
   assert (encode (' ',"abcdefghijklmnopqrstuvwxyz") == ' ');
   assert (encode ('\n',"abcdefghijklmnopqrstuvwxyz") == '\n');

   assert (encode ('a',"abcdefghijklmnopqrstuvwxyz") == 'a');
   assert (encode ('m',"abcdefghijklmnopqrstuvwxyz") == 'm');
   assert (encode ('z',"abcdefghijklmnopqrstuvwxyz") == 'z');

   assert (encode ('a',"bcdefghijklmnopqrstuvwxyza") == 'b');
   assert (encode ('m',"bcdefghijklmnopqrstuvwxyza") == 'n');
   assert (encode ('z',"bcdefghijklmnopqrstuvwxyza") == 'a');

   assert (encode ('a',"qwertyuiopasdfghjklzxcvbnm") == 'q');
   assert (encode ('b',"qwertyuiopasdfghjklzxcvbnm") == 'w');
   assert (encode ('z',"qwertyuiopasdfghjklzxcvbnm") == 'm');
}

char encode (int plainChar, char *permuation) 
{
  char standardAlphabet[26],cipherAlphabet[26]; // declare clear and cipher arrays
  int i=0;
  while(i<ALPHABET_SIZE) // Create an element in an array for each character in the permuation
  {
  	cipherAlphabet[i] = permuation[i];
  	i++;
  }
  i = 0;
  while(i<ALPHABET_SIZE) // Create a reference array that is the standard alphabet
  {
  	standardAlphabet[i] = i+'a';
  	i++;
  }
  i=0;
  char currentCharacter = '0';
  while(i<ALPHABET_SIZE && currentCharacter != plainChar) // Loop through the standard alphabet array until you find the input character
  {
  	currentCharacter = standardAlphabet[i];
  	i++;
  }
  if(plainChar > 'z' || plainChar < 'a')
  {
  	return plainChar; // doesn't work for other characters
  }else{
  	return cipherAlphabet[(i-1)]; // the position of the character in the standard array is the position of the cipher character in the cipher array
  }
}
