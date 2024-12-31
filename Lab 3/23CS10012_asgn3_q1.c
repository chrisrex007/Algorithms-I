// Charniya Krish
// 23CS10012

#include <stdio.h>
#include <stdlib.h>
#define MAXL 20000 // please change according to the input if the time is taking too much.

int prefix[MAXL]; // prefix array for the overlapping part.

int max(int a, int b) // returning max function
{
    if (a < b)
        return b;
    else
        return a;
}

typedef struct // struct to record starting and ending times.
{
    double start;
    double end;
} reg;

void swap(reg *x, reg *y) // used in quicksort
{
    reg tmp = *x;
    *x = *y;
    *y = tmp;
}

int partition(reg arr[], int l, int r)
{
    // choosing pivot = first element
    int pivot = arr[l].end;
    int i = l, j = r;

    while (i < j)
    {
        while (arr[i].end <= pivot && i < r)
            i++;
        while (arr[j].end > pivot && j > l)
            j--;

        if (i < j)
            swap(&arr[i], &arr[j]);
    }

    swap(&arr[l], &arr[j]);

    return j;

    // choosing pivot = last element
    /*
    int pivot= arr[r];
    int i=l;

    for(int j=l;j<=r;j++){
        if(arr[j]<pivot){
            swap(&arr[i],&arr[j]);
            i++;
        }
    }

    swap(&arr[r],&arr[i]);

    return i;
    */
}
void fill(int prefix[])
{
    for (int i = 0; i < MAXL; i++)
    {
        prefix[i] = 0;
    }
}

void quickSort(reg arr[], int l, int r)
{
    if (l >= r)
        return;

    int pi = partition(arr, l, r);
    quickSort(arr, l, pi - 1);
    quickSort(arr, pi + 1, r);
}

int main()
{
    int n;
    int res = 1;

    printf("Enter the n : "); // input
    scanf("%d", &n);

    reg a[n];
    printf("Enter the starting times :");
    for (int i = 0; i < n; i++)
    {
        scanf("%lf", &a[i].start);
    }

    printf("\nEnter the Ending times :");

    for (int i = 0; i < n; i++)
    {
        scanf("%lf", &a[i].end);
    }

    quickSort(a, 0, n - 1); // sorting
    fill(prefix);           // init prefix array with 0

    for (int i = 0; i < n; i++)
    {
        prefix[(int)(a[i].start * 100)]++;
        prefix[(int)(a[i].end * 100)]--;
    }

    for (int i = 1; i < MAXL; i++) // counting the overlaps in the given time period
        prefix[i] += prefix[i - 1];

    for (int i = 0; i < MAXL; i++) // maximum number of overlaps is our answer
        res = max(res, prefix[i]);

    printf("\nMinimum Volunteers : %d\n", res);

    // Used Testcases.

    // 2.00 2.07 2.10 3.05 3.06 3.07 3.10 3.20 3.50 4.12 5.00 5.15 2.30 2.55 3.40 3.09 3.08 3.15 3.17 4.30 4.00 4.32 5.20 5.27

    // 2.00 2.34 3.10 2.32 2.56 3.30

    // 2.00 2.10 3.00 3.20 3.50 5.00 2.30 3.40 3.20 4.30 4.00 5.20
}