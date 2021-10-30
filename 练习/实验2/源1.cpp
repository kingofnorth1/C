#include <stdio.h>

void zh1(char str1[])  //字符串大小写转换
{
    int i;
    for (i = 0; str1[i] != '\0'; i++)
    {
        if (str1[i] >= 'A' && str1[i] <= 'Z')
            str1[i] += 32;
        else if (str1[i] <= 'z' && str1[i] >= 'a')
            str1[i] -= 32;
    }
}

int zh2(char str1[], char str2[])  //字符串大小比较
{
    int i, j; j = 0;
    for (i = 0; str1[i] != '\0' || str2[i] != '0'; i++)
    {
        if (str1[i] > str2[i])
        {
            return 1; break;
        }
        else if (str1[i] < str2[i])
        {
            return 0; break;
        }
        else
            j = j + 1;
    }
    if (str1[i] != '0') return 0;
    else if (str1[j] == '\0' || str2[j] == '\0') return 2;
    else return 1;
}

int zh3(char str1[])
{
    int i, j, n;
    n = 0;
    for (i = 0; str1[i] != '\0'; i++)
        n++;

    if (n % 2 == 0)
    {
        n = n / 2; j = n + 1;
        for (; str1[j] == str1[n] && j >= 0; j++, n--) {}
        if (j + 1 == 0)return 1;
        else return 0;
    }
    else n = n / 2;
    {
        for (j = 0; str1[n + j] == str1[n - j] && j < n; j++, n--) {}
        if (j + 1 == n)return 1;
        else return 0;
    }
}

int zh4(char str1[])
{
    int i, j, n;
    for (i = 0;; i++)
    {
        if (str1[i] == '\0')
        {
            return 1; break;
        }
        if (str1[i] < '0' || str1[i]>'9')
        {
            return 0; break;
        }
    }
}

int zh5(char str1[], char str2[], int in[])
{
    int n1, n2, n, i, j;
    char str3[100], str4[100];
    n1 = 0; n2 = 0; j = 0;
    for (i = 0; str1[i] != '\0'; i++)
    {
        n1++;
        str1[i] = str1[i] - '0';
    }
    for (i = 0; str2[i] != '\0'; i++)
    {
        n2++;
        str2[i] = str2[i] - '0';
    }



    for (i = n1 - 1; i >= 0; j++, i--)
        str3[j] = str1[i];
    j = 0;
    for (i = n2 - 1; i >= 0; j++, i--)
        str4[j] = str2[i];
    if (n1 > n2)
    {
        n = n1;
        for (i = n2; i <= n1; i++)
            str3[i] = 0;
    }
    else
    {
        n = n2;
        for (i = n1; i <= n2; i++)
            str4[i] = 0;
    }
    for (i = 0; i <= n - 1; i++)
    {
        if (str3[i] + str4[i] > 9)  str3[i + 1]++;
        in[i] = (str3[i] + str4[i]) % 10;
    }
    for (i = 0; i <= n; i++)
        printf("%d", in[i]);
}
