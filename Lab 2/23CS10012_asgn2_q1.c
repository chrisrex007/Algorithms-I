// Charniya Krish
// 23CS10012

#include <stdio.h>

void swap(int *a, int *b) // swap function to swap two elements
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int a[], int l, int *c, int r)
{
    int pivot = a[r]; // basic steps just like qsort
    int i = l - 1;

    for (int j = l; j < r; j++)
    {
        if (a[j] < pivot)
        {
            i++;
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[i + 1], &a[r]);
    int k = i + 2;

    int j = i + 2;

    for (; j < r; j++)
    {
        if (pivot != a[j]) // if there are numbers just after the pivot elements then they are already sorted we don't need to swap them
            break;
        else
            (*c)++; // increasing count
    }

    for (; j < r; j++)
    {
        if (pivot == a[j]) // if there is an element that is equal to pivot then it is swapped with some element which is not pivot.
        {
            while (k < r) // for finding the non pivot element to swap with
            {
                if (a[k] > pivot)
                    break;
                else
                    k++;
            }
            swap(&a[j], &a[k]);

            (*c)++;
        }
    }
    return i + 1; // return index of pivot element and count is already changing as we have passed it with address.
}

void quick_sort(int a[], int l, int r)
{
    if (l < r) // left pointer should be less than right pointer
    {
        int q;
        int count = 0;                  // for counting the number of same elements as pivot
        q = partition(a, l, &count, r); // returning pivot element and count and do the basic sorting as qsort

        quick_sort(a, l, q - 1);         // dividing from l to q-1
        quick_sort(a, q + 1 + count, r); // dividing from q+1+count to r (as the interval between q to q+1+count is already sorted.)
    }
}

int main()
{
    int n;
    printf("Enter the Number n: ");
    scanf("%d", &n); // input
    int a[n];
    printf("\nEnter the Numbers (separated by space): ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    quick_sort(a, 0, n - 1); // Time complexity : O(nlogn)

    printf("\nSorted Array : ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]); // output
    }
    printf("\n");
    return 0;
}
// 2 6 5 2 6 8 6 1 2 6