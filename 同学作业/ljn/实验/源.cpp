//水仙花数是指一个N位正整数（N≥3），它的每个位上的数字的N次幂之和等于它本身。例如：153=13+53+33。 本题要求编写程序,计算所有N位水仙花数。  
//Input
//输入在一行中给出一个正整数N（3≤N≤7）。  
//Output
//按递增顺序输出所有N位水仙花数，每个数字占一行。  
//Input example
//3  
//样本输出
//Output example
//153
//370
//371
//407 
#include <stdio.h>
#include <math.h>
int main()
{
    double n, i, x, a=0, b;//a为判断值 
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