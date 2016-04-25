// ROT13 Program - encodes a letter used a secret algorithm (hint: it rotates it by 13 characters)
// Written by Jack Renshaw - j.renshaw@student.unsw.edu.au
// 1/04/2016

#include<stdio.h>
#include<assert.h>


char encode(char letter)
{

	int ascii = letter; // get the ascii representation of the letter

	if(ascii < 'A' || ascii > 'z' || (ascii >'Z' && ascii <'a')){ // If the letter is outside of the bounds
		return letter; // don't rotate it
	}

	int displacement = 97; // standard displacement (assume letter is lowercase)

	if(ascii <= 'Z') // If the letter is uppercase
	{
		displacement = 65; // change displacement
	}

	ascii = (ascii+13 - displacement)%26 + displacement; // rotate by 13 then take the remainder when divided by 26 to made z loop back to a
	char outputCharacter = ascii; 

	return outputCharacter; // return the output character
}

void testEncode()
{
	assert(encode('a') == 'n');
	assert(encode('A') == 'N');
	assert(encode('s') == 'f');
	assert(encode('!') == '!');
	assert(encode('S') == 'F');
}

int main(void)
{


	testEncode();
	return 0;

}