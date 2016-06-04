#include <stdio.h>

int main()
{
	int n;
	int i = 0;
	int j = 0;
	printf("Please enter the number of rows you would like printed: ");
	scanf("%d",&n);
	while(i<n)
	{
		j = 0;
		while(j<n)
		{
			if(j == i || j == (n-i-1)){
				printf("#");
			}else{
				printf("-");
			}
			j++;
		}
		printf("\n");
		i++;
	}
	return 0;
}
