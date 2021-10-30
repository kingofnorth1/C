#include <stdio.h>
#define PAGES 959
#define BLURB "Authentic imitation!"
int main(void){
	printf("*%d*\n", PAGES);
	printf("*%d*\n", PAGES);
	printf("*%10d*\n", PAGES);
	printf("*%-10d*", PAGES);

	printf("[%2s]\n", BLURB);
	printf("[%24s]\n", BLURB);
	printf("[%24.5s]\n", BLURB);
	printf("[%-24.5s]", BLURB);
		

	while(1);
	return 0;
}