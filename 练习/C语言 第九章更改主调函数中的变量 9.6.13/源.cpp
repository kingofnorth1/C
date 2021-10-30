#include <stdio.h>
#include "hotel.h"

int main(void) {
	int x = 5, y = 10;

	printf("Originally x = %d and y = %d.\n", x, y);
	x=interchange(x, 0);
	y =interchange(0, y);
	printf("Now x = %d and y = %d.\n", x, y);

	return 0;
}

int interchange(int u, int v) {
	int temp;

	//printf("Originally u = %d and v = %d.\n", u, v);
	temp = u;
	u = v;
	v = temp;
	//printf("Now u = %d and v = %d.\n", u, v);
	return u,v;
}