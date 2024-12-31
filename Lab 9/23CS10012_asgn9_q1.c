// Charniya Krish
// 23CS10012

#include <stdio.h>
#include <stdlib.h>
#define MOD (int)(9973)

// we are creating a hash function and then store the values and the ids of the strings and then output the equivalent strings
int hash(char *c)
{
    int ans = 0;
    char prev = c[0];
    int diff = 0;
    int i = 0;
    while (c[i] != '\b')
    {
        ans = ((diff + 26) % 26 * 29 + 1 + ans) % MOD;
        diff = c[i] - prev;
        prev = c[i];
        i++;
    }
    return ans;
}

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int n;
    printf("Enter the numebr of strings : ");
    scanf("%d", &n);

    char c[n + 1][30];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            c[i][j] = '\b';
        }
    }

    for (int i = 0; i < n; i++)
    {
        scanf("%s", c[i]);
    }

    // ans is our hash table.
    // size array is for storing the size of each strings.
    int ans[9973][n];
    int size[9973];
    for (int i = 0; i < 9973; i++)
    {
        size[i] = 0;
    }

    for (int i = 0; i < 9973; i++)
    {
        for (int j = 0; j < n; j++)
        {
            ans[i][j] = -1;
        }
    }

    for (int i = 0; i < n; i++)
    {
        ans[hash(c[i])][size[hash(c[i])]] = i;
        size[hash(c[i])]++;
    }

    for (int i = 0; i < 9973; i++)
    {
        int j;
        for (j = 0; j < size[i]; j++)
        {
            if (ans[i][j] == -1)
                break;
            printf("%s ", c[ans[i][j]]);
        }
        if (j != 0)
            printf("\n");
    }

    return 0;
}