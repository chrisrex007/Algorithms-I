// Charniya Krish
// 23CS10012

// This question is done keeping in mind that string will contain only characters a and b.

#include <stdio.h>
#define MAX 10000 // replace MAX if the string length if going larger than 1e5 in the test cases.

char s[MAX];
int min(int a, int b) // returning Minimum of Two Numbers.
{
    if (a < b)
        return a;
    return b;
}

int main()
{
    int n = 0;
    char p;
    printf("Enter Input String : ");

    while (1)
    {
        scanf("%c", &p);
        if (p == '\n')
            break;
        s[n] = p;
        n++;
    }

    int dp[n + 1]; // dp at i+1 index stores the minimum number of deletions needed till string index i.

    for (int i = 0; i <= n; i++) // created and init dp with 0
        dp[i] = 0;

    int count = 0; // count for b

    for (int i = 1; i <= n; i++)
    {
        char c = s[i - 1];
        dp[i] = dp[i - 1]; // storing previous dp value

        if (c == 'b') // if the char is b then simply increase the count
            count++;
        else
            dp[i] = min(dp[i - 1] + 1, count); // if the char is a then we either remove all the prev b to make it aaaaa.... or we remove current a to make it valid.
    }

    printf("Minimum number of deletion needed is %d\n", dp[n]); // our ans is dp[n].
    return 0;
}