// Charniya Krish
// 23CS10012

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int f(int x) // we are defining the funciton f(x) = 3x-100;
{
    return (3 * x - 100);
}

int upper_bound() // finding upper bound in powers of 10
{
    int val = 10, i = 1;
    while (i < 10)
    {
        if (f(val) >= 0)
            return val;
        else
            val *= 10;
        i++;
    }
    return INT_MAX;
}

int main()
{

    int l = 0, r = upper_bound(), m; // init r with upper bound
    while (l < r)                    // binary search on the answer
    {
        m = l + r >> 1;

        if (f(m) >= 0)
            r = m;
        else
            l = m + 1;
    }
    printf("The value of x = %d yields f(x) to be positive. \n", l);

    return 0;
}