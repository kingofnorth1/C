#include <stdio.h>
void report_count();
void accumulate(int k);
int count = 0;			//�ļ�������

int main(void) {
	int value;			//�Զ�����
	register int i;		//�Ĵ�������
    
	printf("Enter a positive integer (0 to quit):");
	while (scanf_s("%d", &value) == 1 && value > 0) {
		++count;
		for (i = value; i >= 0; i--)
			accumulate(i);
		printf("Enter a positive integer (0 to quit):");
	}
	report_count();

	return 0;
}

void report_count() {
	printf("Loop executed %d times\n", count);
}