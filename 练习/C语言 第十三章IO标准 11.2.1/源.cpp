#include "stdio.h" 
#include <stdlib.h>
int main() {
	FILE* fp;
	char ch;
	if ((fp = fopen("123.txt", "r")) == NULL) {
		printf("file cannot be opened/n");
		exit(1);
	}
	while ((ch = fgetc(fp)) != EOF)
		fputc(ch, stdout);
	fclose(fp);
}