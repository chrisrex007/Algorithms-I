// Charniya Krish
// 23CS10012

#include <stdio.h>
#include <stdlib.h>
#define MAX 10000

int ans = 10000;

// returns minimum of two values
int min(int a, int b)
{
    if (a < b)
        return a;
    return b;
}

// solve using recursion
/*
Approach: two counters stored in each recursion, currentSum and count, if the currSum exeeceds the total sum value then we'll return and at any point if currSum == x then we will store that to the ans. Bruteforcing every possibilites.
*/
void rec(int s[], int n, int x, int cs, int count)
{
    if (cs == x)
    {
        ans = min(count, ans);
        return;
    }
    if (cs > x)
        return;

    for (int i = 1; i <= n; i++)
    {
        if (cs + s[i] <= x)
            rec(s, n, x, cs + s[i], count + 1);
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int n, x;
    printf("Enter the number of coins n: ");
    scanf("%d", &n);

    printf("Enter the target value: ");
    scanf("%d", &x);

    printf("Enter the values of coins. \n");
    int a[n + 1];
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }

    rec(a, n, x, 0, 0);
    printf("Answer by Recursion: %d \n", ans);

    // Memory allocation
    int **dp = (int **)malloc((x + 1) * sizeof(int *));
    for (int i = 0; i <= x; i++)
        dp[i] = (int *)malloc((n + 1) * sizeof(int));

    // base cases
    for (int i = 0; i <= x; i++)
    {
        dp[i][0] = MAX;
    }
    for (int i = 0; i <= n; i++)
    {
        dp[0][i] = 0;
    }

    /*
    dp[i][j] stores the minimum number of values to obtain the sum i with using first j coins.
    Approach: at given point we are taking the minimum of (including that coin + subproblem solution) && (not including the coin and taking subproblem solution with j-1 coins)
    */
    for (int i = 1; i <= x; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            dp[i][j] = dp[i][j - 1];
            if (i - a[j] >= 0)
                dp[i][j] = min(dp[i][j], dp[i - a[j]][j] + 1);
        }
    }

    printf("Answer by DP: %d \n", dp[x][n]);

    return 0;
}