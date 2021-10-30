#include<stdio.h>
int main() {
	int a[10], b[11], num = 0, i, j, k = 1;

	scanf("%d", &i);
	for (int n = 0; n < i; n++) {
		scanf("%d", &a[n]);
	}

	scanf("%d", &j);
	for (int n = 0; n < j; n++) {
		scanf("%d", &b[n]);
	}

	for (int d = 0; d < i; d++) {
		for (int n = 0; n < j; n++) {
			if (k % 2 == 0 && a[d] == 3) {
				break;
			}

			if (a[d] == b[n]) {
				break;
			}

			else if (n == 10 && a[d] != b[n] && d != 9 ) {
				printf("%d ", a[d]);
				k++;

			}
			else if (n == 10 && d == 9 && a[d] != b[n]) {
				printf("%d", a[d]);
			}
		}
	}

	for (int d = 0; d < j; d++) {
		for (int n = 0; n < i; n++) {
			if (k % 6 == 0 && b[d] == 6) {
				break;
			}

			if (b[d] == a[n]) {
				break;
			}

			else if (n == 9 && b[d] != a[n] && d != 10 ) {
				printf("%d ", b[d]);
				k++;

			}
			else if (n == 9 && d == 10 && b[d] != a[n]) {
				printf("%d", b[d]);
			}
		}
	}
}