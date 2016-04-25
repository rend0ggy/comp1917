//
//  main.c
//  memory
//
//  Created by Richard Buckland on 20/11/12.
//
 
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>


long add (int x, int y);
 
int main(int argc, const char * argv[]) {
 
   int x;
   int y;
   long total;
 
   x = 40;
   y = 2;
 
   total = add (x, y);
 
   printf("the sum of %d and %d is %ld\n", x, y, total);
 
   char c ='a';
 
   unsigned long ul       = 0;
   unsigned int ui        = 1;
   unsigned long long ull = 2;
   unsigned short us      = 3;
 
   signed long sl       = 4;
   signed int si        = 5;
   signed long long sll = 6;
   signed short ss      = 7;
 
   long l       = 8;
   int i        = 9;
   long long ll = 10;
   short s      = 11;
 
   float f = 3.1;
   double d = 3.14;
 
   // add them all together just to make use of them so the compiler
   // doesn't grumble that they are unused in the program
 
   double grandTotal;
   grandTotal =  c +
                 ul + ui + ull + us +
                 sl + si + sll + ss +
                  l +  i +  ll +  s +
                  f + d;
 
   printf ("all these things added together make %f\n", grandTotal);

   int sizes[15] = 
 	{
 		sizeof(ui), // size of unsigned int
 		sizeof(us), // size of unsigned short
 		sizeof(ul), // size of unsigned long
 		sizeof(ull), // size of unsigned long long
 		sizeof(si), // size of signed int
 		sizeof(ss), // size of signed short
 		sizeof(sl), // size of signed long
 		sizeof(sll), // size of signed long long
 		sizeof(i), // size of long
 		sizeof(s), // size of int
 		sizeof(l), // size of long long
 		sizeof(ll), // size of short
 		sizeof(f), // size of float
 		sizeof(d), // size of double
 		sizeof(c) // size of char
 	};

 	printf("Terms of Reference for the results document: \n\n");
 	printf("ui=>Unsigned Int\nus=>Unsigned Short\nul=>Unsigned Long\null=>Unsigned Long Long\nsi=>Signed Int\nss=>Signed Short\nsl=>Signed Long\nsll=>Signed Long Long\ni=>Int\ns=>Short\nl=>Long\nll=>Long Long\nf=>Float\nd=>Double\nc=>Char\n");
 	printf("\nVariables Sizes:\n");
 	printf("ui=>%d\nus=>%d\nul=>%d\null=>%d\nsi=>%d\nss=>%d\nsl=>%d\nsll=>%d\ni=>%d\ns=>%d\nl=>%d\nll=>%d\nf=>%d\nd=>%d\nc=>%d\n",sizes[0],sizes[1],sizes[2],sizes[3],sizes[4],sizes[5],sizes[6],sizes[7],sizes[8],sizes[9],sizes[10],sizes[3],sizes[11],sizes[12],sizes[13],sizes[14],sizes[15]);
  	printf("\nMemory Locations:\n");
 	printf("ui=>%p\nus=>%p\nul=>%p\null=>%p\nsi=>%p\nss=>%p\nsl=>%p\nsll=>%p\ni=>%p\ns=>%p\nl=>%p\nll=>%p\nf=>%p\nd=>%p\nc=>%p\n",&ui,&us,&ul,&ull,&si,&ss,&sl,&sll,&i,&s,&l,&ll,&f,&d,&c);


 	// Testing component of the task

 	printf("\nunsigned variables underflow values: \n");
 	printf("ui = %u\n",UINT_MAX);
  	printf("us = %u\n",USHRT_MAX);
 	printf("ul = %lu\n",ULONG_MAX);
 	printf("ull = %llu\n",ULLONG_MAX);
 	printf("c = %c\n",UCHAR_MAX);
 	printf("\nsigned variables underflow values: \n");
 	printf("i = %u\n",INT_MAX);
  	printf("s = %u\n",SHRT_MAX);
 	printf("l = %lu\n",LONG_MAX);
 	printf("ll = %llu\n",LLONG_MAX);
 	printf("i = %u\n",INT_MAX);
  	printf("s = %u\n",SHRT_MAX);
 	printf("l = %lu\n",LONG_MAX);
 	printf("ll = %llu\n",LLONG_MAX);
 	printf("f = %G\n",FLT_MAX);
 	printf("d = %G\n",DBL_MAX);
 	//
 	printf("\nunsigned variables overflow values: \n");
 	printf("ui = %u\n",0);
  	printf("us = %u\n",0);
 	printf("ul = %lu\n",0);
 	printf("ull = %llu\n",0);
 	printf("c = (NULL)\n");
 	printf("\nsigned variables overflow values: \n");
 	printf("i = %u\n",INT_MIN);
  	printf("s = %u\n",SHRT_MIN);
 	printf("l = %lu\n",LONG_MIN);
 	printf("ll = %llu\n",LLONG_MIN);
 	printf("i = %u\n",INT_MIN);
  	printf("s = %u\n",SHRT_MIN);
 	printf("l = %Ld\n",LONG_MIN);
 	printf("ll = %llu\n",LLONG_MIN);
 	printf("f = %G\n",FLT_MIN);
 	printf("d = %G\n",DBL_MIN);
 
   return EXIT_SUCCESS;
}
 
long add (int x, int y) {
   long answer;
   answer = x + y;
 
   return answer;
}
 