#include <stdio.h>
#define PI 3.14159
int main(void){
	double area, circum, radius;
	
	printf("What is the radius of your pizza?\n");
	scanf("%d", &radius);
	area = PI * radius * radius;
	circum = 2.0 * PI * radius;
	printf("Your basic pizza parameters are as follows:\n");
	printf("circumference = %1.2d, area = %1.2d\n",circum,area);

	while(1);
	return 0;}
