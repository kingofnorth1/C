//ˮ�ɻ�����ָһ��Nλ��������N��3��������ÿ��λ�ϵ����ֵ�N����֮�͵������������磺153=13+53+33�� ����Ҫ���д����,��������Nλˮ�ɻ�����  
//Input
//������һ���и���һ��������N��3��N��7����  
//Output
//������˳���������Nλˮ�ɻ�����ÿ������ռһ�С�  
//Input example
//3  
//�������
//Output example
//153
//370
//371
//407 
#include <stdio.h>
#include <math.h>
int main()
{
    double n, i, x, a=0, b;//aΪ�ж�ֵ 
    scanf("%lf", &n);
    if (n >= 3 && n <= 7)
    {
        x = pow(10, n - 1);
        for (i = x; i < 10 * x; i++)
        {
            for (b = i; b > 0; b = b / 10)
            {
                a += pow((int)b % 10, n);
            }
            if (a == i)
            {
                printf("%lf\n", a);
            }
            a = 0;
        }
    }
    return 0;
}