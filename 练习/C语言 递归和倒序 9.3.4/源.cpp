#include <stdio.h>
void to_binary(unsigned long n);

int main(void) {
	unsigned long number;
	printf("Enter an integer (q to quit):\n");
	while (scanf("%lu", &number) == 1) {
		printf("Binary equivalent: ");
		to_binary(number);
		putchar('\n');
		printf("Enter an integer (q to quit): \n");
	}
	printf("Done.\n");

	return 0;
}

