#include <stdio.h>
int main() {
	int num;
	int string[10];
	scanf("%d", &num);

	for (int i = 0; i < num; i++) {
		scanf("%d", &string[i]);
	}

	for (int i = 1; i < num; i++) {
		if (i == num - 1 || i % 3 == 0)
			printf("%d", string[i] - string[i-1]);
		else
			printf("%d ", string[i] - string[i-1]);
		if (i % 3 == 0 && i != num - 1)
			printf("\n");
	}
}