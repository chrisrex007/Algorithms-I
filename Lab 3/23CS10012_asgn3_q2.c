// Charniya Krish
// 23CS10012

#include <stdio.h>

int max(int a, int b) //return maximum
{
    if (a < b)
        return b;
    return a;
}

int main()
{
    int n;
    printf("Enter the Number n : "); // input
    scanf("%d", &n);

    int a[n];
    int sum = 0;

    printf("Enter the parts array : "); // input

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
        sum += a[i];
    }
    int ans = 0;

    int m = 0;
    for (int i = 0; i < n; i++) // finding maxi element of the array
        m = max(a[i], m);

    if (sum < 2 * m) // if the remaining sum is still less than the max element than we can prove this by using gap method and max number will 2*remaining +1.
    {
        int rem = sum - m;
        printf("Total Weeks: %d\n", 2 * rem + 1);
    }
    else // if it's not the case then we can greedily see that we can always complete all the number of assignments.
        printf("Total Weeks: %d\n", sum);

    return 0;
}