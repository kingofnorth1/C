#include <stdio.h>
#define COLS 4
int sum2d(const int ar[][COLS], int rows);
int sum(const int ar[], int n);
int main(void) {
	int tota11, tota12, tota13;
	int* pt1;
	int(*pt2)[COLS];

	pt1 = (int[2]){ 10,20 };
	pt2 = (int[2][COLS]){ { 1,2,3,-9 }, { 4,5,6,-8 } };

	tota11 = sum(pt1, 2);
	tota12 = sum2d(pt2, 2);
	tota13 = sum((int []) { 4, 4, 4, 5, 5, 5 }, 6);
	printf("tota11 = %d\n", tota11);
	printf("tota12 = %d\n", tota12);
	printf("tota13 = %d\n", tota13);

	return 0;
}

int sum(const int ar[], int n) {
	int i;
	int total = 0;

	for (i = 0; i < n; i++)
		total += ar[i];

	return total;
}

int sum2d(const int ar[][COLS], int rows) {
	int r;
	int c;
	int tot = 0;

	for (r = 0; r < rows; r++)
		for (c = 0; c < COLS; c++)
			tot += ar[r][c];
	return tot;
}