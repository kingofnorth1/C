#include <stdio.h>
int one(int a);
void two(void);
void three(void);
int main(){
	printf("starting now:\n");
	one(5);
	two();
	three();

	while(1);
	return 0;
}
int one(int a){
	printf("one\n");
	return a;
}
void two(void){
	printf("tow\n");
}
void three(void){
	printf("three\n");
}