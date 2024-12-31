// Charniya Krish
// 23CS10012

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void merge(int a[], int p, int q, int r) // merging algo
{
    int n1 = q - p + 1;
    int n2 = r - q;

    int left[n1 + 1], right[n2 + 1];

    for (int i = 0; i < n1; i++)
    {
        left[i] = a[p + i];
    }
    left[n1] = INT_MAX;

    for (int i = 0; i < n2; i++)
    {
        right[i] = a[q + 1 + i];
    }
    right[n2] = INT_MAX;

    int i = 0, j = 0;
    for (int k = p; k <= r; k++)
    {
        if (left[i] < right[j])
        {
            a[k] = left[i];
            i++;
        }
        else
        {
            a[k] = right[j];
            j++;
        }
    }
}

void mergeSort(int a[], int p, int r) // divide and conquer mergesort algo
{
    if (p >= r)
        return;

    int q = p + r >> 1;

    mergeSort(a, p, q);
    mergeSort(a, q + 1, r);
    merge(a, p, q, r);
}

int main()
{
    int n, m, drinks, d;
    printf("Enter the size of array Jumps : ");
    scanf("%d", &n);

    int *a = (int *)malloc(sizeof(int) * n); // allocating memory.

    printf("Enter the array Jumps : ");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    printf("Enter the size of array Members : ");
    scanf("%d", &m);

    int *b = (int *)malloc(sizeof(int) * m); // allocating memory.

    printf("Enter the array Members : ");

    for (int i = 0; i < m; i++)
    {
        scanf("%d", &b[i]);
    }

    printf("Enter the value of n : ");
    scanf("%d", &drinks);
    printf("Enter the value of d : ");
    scanf("%d", &d);

    mergeSort(a, 0, n - 1); // sorting Jumps array
    mergeSort(b, 0, m - 1); // sorting ascending array

    int *occupied_jumps = (int *)malloc(n * sizeof(int));   // allocating size for occupied jumps and init with 0
    int *occupied_members = (int *)malloc(m * sizeof(int)); // allocating size for occupied members and init with 0

    int i = n - 1, j = m - 1, ans = 0; // starting from end indexs of jumps and members array

    // in the first step forget about the drinks and just focus on natural skills of players.
    while (i >= 0 && j >= 0)
    {
        if (a[i] <= b[j]) // if highest jump can be fulfilled by highest pro player then we will assign that jump to that member
        {
            ans++;
            occupied_jumps[i] = 1;
            occupied_members[j] = 1;
            i--;
            j--;
        }
        else // if not then we will find the jump that he can achieve
        {
            i--;
        }
    }

    i = 0, j = 0;
    /*now comes the part with drinks, starting with initial indexs*/

    while (i < n && j < m)
    {
        if (occupied_jumps[i] == 1) // if the jump is made already then continue
        {
            i++;
            continue;
        }

        if (occupied_members[j] == 1) // if the member has jumped already then continue
        {
            j++;
            continue;
        }

        if (b[j] + d >= a[i] && n > 0) // if the drinks are available and our lowest pro player can jump with that drink then we'll give him that drink.
        {
            ans++;
            i++;
            j++;
            n--;
        }
        else // if he cannot jump then we won't select that player and move on ahead.
            j++;
    }

    printf("Maximum number of games can be win is %d \n", ans);

    return 0;
}

// 2 5 4 3 0 0 5 1 5
// 3 10 15 30 5 0 10 10 10 10 3 10