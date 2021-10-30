#include <io.h>
#include <conio.h>
#include <stdlib.h>

int main(void) {
	double i;
	int n;
	n = cscanf("%lf", &i);
	cprintf("%d", n);
	return 0;
}