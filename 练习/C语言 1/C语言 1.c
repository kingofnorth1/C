#include <stdio.h>
void buthler(void);
int main(void)
{
	printf("I will summon the butler function:\n");
	buthler();
	printf("yes,Bring me some tea and writeable DVDs.\n");

	while(1);
	return 0;
}

void buthler(void)
{
	printf("You rang, sir?\n");
}
