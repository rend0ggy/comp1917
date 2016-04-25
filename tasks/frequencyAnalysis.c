#include<stdio.h>

int main(void)
{
	int upperBoundary = '~'-'0'+1;
	int characterArray[upperBoundary];
	int i = 0;
	while(i<upperBoundary)
	{
		characterArray[i] = 0;
		i++;
	}

	//FILE *file;
	//file = fopen("test.txt", "r");

    char c;
    i = 0;
    int z = 0;
    c = getchar();
    while(c != EOF)
    {
    	//c = fgetc(file);
    	z = c - '0';
    	characterArray[z] += 1;
    	i++;
    	c = getchar();
    }
    long long int characterCount = i;
    i=0;
    printf("This file contained %lld characters\n",characterCount);
    while(i<upperBoundary)
    {
    	printf("%c => %d\n",(i + '0'),characterArray[i]);
    	i++;
    }

    //

    //fclose(file);


	return 0;
}