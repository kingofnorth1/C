#include <stdio.h>

int main() {
	int n = 0, a[10], g, t, num;
	while ((scanf_s("%d", &num) != 0)) {
		a[n] = num;
		n++;
		if (n > 9) {		//在赋值完成是跳出循环
			break;
		}
	}
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9 - i; j++) {
			if (a[j+1] > a[j]) {
				t = a[j+1];
				a[j+1] = a[j];
				a[j] = t;
			}
		}
	}

	for (int x = 0; x < 10; x++) {
		printf("%d ", a[x]);
	}
	return 0;
}