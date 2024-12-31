// Charniya Krish
// 23CS10012

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int min(int a, int b) // return min value
{
    if (a > b)
        return b;
    return a;
}

int max(int a, int b) // return max value
{
    if (a > b)
        return a;
    return b;
}

int rec(int a[], int l, int r) // RECURSIVE APPROACH
{
    if (l == r)
        return 0;
    int mi = INT_MAX / 4, maxi = INT_MIN; // init mi with some big value and maxi with some min value
    for (int i = l; i <= r; i++)
    {
        mi = min(mi, a[i]);
        maxi = max(maxi, a[i]);
    }

    if (2 * mi > maxi) // if the condition is satisfied then we will return 0
    {
        return 0;
    }

    return min(1 + rec(a, l + 1, r), 1 + rec(a, l, r - 1)); // if it is not satisfied then we will delete from either front or back and finding minimum of that
}

int dynamic(int a[], int n)
{
    /*Init 2D dp array*/
    int **dp = (int **)malloc(sizeof(int) * (n + 2));

    for (int i = 0; i <= n; i++)
        dp[i] = (int *)malloc(sizeof(int) * (n + 2));

    /*dp [i][j] stores the value of minimum number of deletions from i to j */

    for (int len = 1; len < n; len++) // iterating len of the array
    {
        for (int i = 1; i <= n - len; i++) // iterating i & for each i, j = i+len.
        {
            int j = i + len;
            int maxi = INT_MIN, mi = INT_MAX / 4; // init maxi and mini

            for (int k = i; k <= j; k++)
            {
                maxi = max(maxi, a[k - 1]);
                mi = min(mi, a[k - 1]);
            }

            if (2 * mi > maxi) // if the condition is satisfied then dp[i][j] is zero i.e. 0 number of deletions needed.
                dp[i][j] = 0;
            else
                dp[i][j] = min(1 + dp[i + 1][j], 1 + dp[i][j - 1]); // if not then min of (1 + dp[i + 1][j]) and (1 + dp[i][j - 1]) will be our ans
        }
    }

    return dp[1][n]; // dp[1][n] will be our ans.
}

int main()
{
    int n;
    printf("Enter the number of elements : ");
    scanf("%d", &n);
    int *a = (int *)malloc(sizeof(int) * n); // allocating size

    printf("Enter the array S[] : ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    printf("Minimum Number of deletions (By Recursive Approach) is %d\n", rec(a, 0, n - 1)); // By Recursive Approach.
    printf("Minimum Number of deletions (by DP) is %d\n", dynamic(a, n));                    // By Dynamic Programming Approach.

    return 0;
}