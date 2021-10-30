#include <stdio.h>
#define PI 3.1415926
int main(void){
	int number = 7;
	float pies = 12.75;
	int cost = 7800;

	printf("The %d contestans are %f berry pies.\n", number, pies);
	printf("The value of pi is %f.\n",PI);
	printf("%c%d\n", '$', 2 * cost); 

	while(1);
	return 0;
}