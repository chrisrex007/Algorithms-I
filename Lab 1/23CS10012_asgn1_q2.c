// Charniya Krish
// 23CS10012

#include <stdio.h>

int min(int a, int b) // minimum of two elements
{
    if (a < b)
        return a;
    else
        return b;
}

int max(int a, int b) // max of two elements
{
    if (a < b)
        return b;
    else
        return a;
}

int main()
{
    int n;
    printf("\nEnter number of Frames : ");
    scanf("%d", &n);

    printf("\nEnter the frame Sequence (separated by space): \n");

    int s[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &s[i]);
    }

    int suff[n]; // Suffix Array , basically keeps a record of minimum suffix.
    suff[n - 1] = s[n - 1];

    for (int i = n - 2; i >= 0; i--)
    {
        suff[i] = min(suff[i + 1], s[i]);
    }

    int m = 0;  //prefix Maximum variable
    int ans = -1;
    for (int i = 1; i < n - 1; i++) //assuming the frame index is in range [1,n-1).
    {
        if (s[i] > m && s[i] < suff[i + 1]) //given condition checking
        {
            ans = i;
            break;
        }
        m = max(m, s[i]);
    }
    printf("Required Frame index is %d\n", ans);

    return 0;
}