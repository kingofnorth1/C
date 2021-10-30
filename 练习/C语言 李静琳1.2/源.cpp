#include<stdio.h>
#include <string.h>

int main()
{
    int i, j, n=0;
    char str[5][50] = { 0 }, num, temp[50] = {0};

    scanf("%s %s %s %s %s", str[0], str[1], str[2], str[3], str[4]);

    for (i = 0; i < 4; ++i) {
        for (j = i + 1; j < 5; ++j)
        {
            if (strcmp(str[i], str[j]) > 0)
            {
                strcpy(temp, str[i]);
                strcpy(str[i], str[j]);
                strcpy(str[j], temp);
            }
        }
    }

    printf("After sorted:\n");
    for (i = 0; i < 5; ++i)
    {
        puts(str[i]);
    }

    return 0;
}