#include<stdio.h>//��ͳ��ʽ�ͱ䳤��ʽ 
void T_trots(double ar[], int n);
//void Vla_trots(int n, double ar[n]);//VS��֧�ֱ䳤����
int main(void)
{
	double trots[20];
	short clops[10][30];
	long shots[5][10][15];

	T_trots(trots, 20);
	//	Vla_trots(20, trots);

	return 0;
}
void T_trots(double ar[], int n)
{
	int i;
	printf("tradional trots says:\n");
	for (i = 0; i < n; i++)
	{
		ar[i] = i + 1;
		printf("%.lf ", ar[i]);
	}
	printf("\n");
}/*
void Vla_trots(int n, double ar[n])
{
	int i;
	printf("vla trots says:\n");
	for(i = 0;i < n;i++)
	{
		ar[i] = i+1;
		printf("%.2f ",ar[i]);
	}
	printf("\n");
}*/