#include <stdio.h>
#include <limits.h>
#include <float.h>
int main(void){
	printf("Some number limits for system:\n");
	printf("Biggest int: %d\n", INT_MAX);
	//printf("Smallest long long: %lld\n", LLONG_MIN);
	printf("One byte = %d bits on this system.\n", CHAR_BIT);
	printf("Largetst double: %e\n", DBL_MAX);
	printf("Smallest notmal float: %e\n", FLT_MIN);
	printf("float prtcision = %d digits\n",FLT_DIG);
	printf("float epsion = %e\n",FLT_EPSILON);

	while(1);
	return 0;
}