// Fancy Flag Program - uses hardcoding to print our various flags
// Written by Jack Renshaw - j.renshaw@student.unsw.edu.au
// 1/04/2016

#include<stdio.h>

void argentina(void) // Argentina 20x7
{
	printf("####################\n");
	printf("####################\n");
	printf("         $$         \n");
	printf("        $$$$        \n");
	printf("         $$         \n");
	printf("####################\n");
	printf("####################\n");
	printf("Argentina\n\n");
}

void japan(void) // Japan 20x7
{
	printf("                    \n");
	printf("         ##         \n");
	printf("        ####        \n");
	printf("      ########      \n");
	printf("        ####        \n");
	printf("         ##         \n");
	printf("                    \n");
	printf("Japan\n\n");
}

void switzerland(void) // Switzerland 22x8
{
	printf("######################\n");
	printf("#########    #########\n");
	printf("#########    #########\n");
	printf("#####            #####\n");
	printf("#####            #####\n");
	printf("#########    #########\n");
	printf("#########    #########\n");
	printf("######################\n");
	printf("Switzerland\n\n");

}

int main(void)
{
	argentina();
	japan();
	switzerland();
}