#include <stdio.h>
#include <string.h>

#define ANSWER "Grant"
#define SIZE 40
char* s_gets(char* st, int n);

int main(void) {
	char tyr[SIZE];

	puts("Who is buried in Grant's tomb?");
	s_gets(tyr, SIZE);
	while (strcmp(tyr, ANSWER)) {
		puts("NO, that's wrong. Try again.");
		s_gets(tyr, SIZE);
	}
	puts("That's right!");

	return 0;
}

char* s_gets(char* st, int n) {
	char* ret_val;
	int i = 0;

	ret_val = fgets(st, n, stdin);
	if (ret_val) {
		while (st[i] != '\n' && st[i] != '\0')
			i++;
		if (st[i] == '\n')
			st[i] == '\0';
		else
			while (getchar() != '\n')
				continue;
	}
	return ret_val;
}