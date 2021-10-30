#include <stdio.h>
#include <math.h>
int main()
{
    float x, result;
    scanf("%f", &x);
    if (x >= 0) {
        return 0;
    }

    else if (x < 0) {
        result = pow(x + 1, 2) + 2 * x + 1 / x;
        printf("f(%0.2f) = %0.2f", x, result);
    }

    return 0;
}