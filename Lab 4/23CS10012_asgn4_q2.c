// Charniya Krish
// 23CS10012

#include <stdio.h>
#define INT_MIN -10000 //as kgp value can be negative too.

void fill(int a[], int n, int val) // to fill the whole array with val
{
    for (int i = 0; i < n; i++)
        a[i] = val;
}

int maxi(int a, int b) // returning max element of a and b
{
    if (a > b)
        return a;
    return b;
}

int main()
{
    int n;
    printf("Enter the number n: ");
    scanf("%d", &n);

    int a[n];
    printf("Enter the array elements : ");

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    int dpw[n + 1], dpx[n + 1], dpy[n + 1], dpz[n + 1]; // creating 4 dp arrays with size n+1

    // Filling all arrays with some Minimum value.
    fill(dpw, n + 1, INT_MIN);
    fill(dpx, n + 1, INT_MIN);
    fill(dpy, n + 1, INT_MIN);
    fill(dpz, n + 1, INT_MIN);

    for (int i = n - 1; i > 2; i--) // at index i we are storing the maximum value of from s[i+1] to s[n-1]
    {
        int val = a[i];
        dpw[i] = maxi(dpw[i + 1], val);
    }

    for (int i = n - 2; i > 1; i--) // at index i we are storing the maximum value of s[w] -s[x], w is already optimally chosen from s[i+1] to s[n-1] and then doing also maximum of these answers for index i
    {
        int val = a[i];
        dpx[i] = maxi(dpx[i + 1], dpw[i + 1] - val);
    }

    for (int i = n - 3; i > 0; i--) // similarly we are storing the maximum value of s[w]-s[x]+s[y] minding that w and x are already best chosen after index i.
    {
        int val = a[i];
        dpy[i] = maxi(dpy[i + 1], dpx[i + 1] + val);
    }

    for (int i = n - 4; i >= 0; i--) // and finally maximum value of s[w]-s[x]+s[y]-s[z].
    {
        int val = a[i];
        dpz[i] = maxi(dpz[i + 1], dpy[i + 1] - val);
    }

    int ans = dpz[0]; // our answer is dpz[0]

    printf("Maximum value of Kgp is %d \n", ans);
    return 0;
}