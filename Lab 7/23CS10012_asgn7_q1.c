// Charniya Krish
// 23CS10012

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int size = 0;

typedef struct
{
    int s;
    int p;
    int idx;
} task;

void swap(task *a, task *b)
{
    task tmp = *a;
    *a = *b;
    *b = tmp;
}

void merge(task a[], int p, int q, int r)
{
    int n1 = q - p + 1;
    int n2 = r - q;

    task left[n1 + 1], right[n2 + 1];

    for (int i = 0; i < n1; i++)
    {
        left[i] = a[p + i];
    }
    left[n1].s = INT_MAX;

    for (int i = 0; i < n2; i++)
    {
        right[i] = a[q + 1 + i];
    }
    right[n2].s = INT_MAX;

    int i = 0, j = 0;
    for (int k = p; k <= r; k++)
    {
        if (left[i].s < right[j].s)
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

// Mergesorting
void mergeSort(task a[], int p, int r)
{
    if (p >= r)
        return;

    int q = p + r >> 1;

    mergeSort(a, p, q);
    mergeSort(a, q + 1, r);
    merge(a, p, q, r);
}

// Heapifying
void heapify(task a[], int i)
{
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int smallest = i;

    if (l < size && a[l].p < a[smallest].p)
        smallest = l;
    if (r < size && a[r].p < a[smallest].p)
        smallest = r;

    if (i != smallest)
    {
        swap(&a[i], &a[smallest]);
        heapify(a, smallest);
    }
}

// Inserting
void insert(task a[], task val)
{
    a[size] = val;
    size++;

    for (int i = size / 2 - 1; i >= 0; i = i / 2 - 1)
        heapify(a, i);
}

// ExtractMin
task deleteRoot(task a[])
{
    if (size == 0)
    {
        printf("Heap is Empty.\n");
        exit(0);
    }
    task x = a[0];

    swap(&a[0], &a[size - 1]);
    size--;
    heapify(a, 0);
    return x;
}

int main()
{

    int n;
    printf("Enter the number n: ");
    scanf("%d", &n);

    task t[n];
    task heap[n];
    int ans[n], ansIdx = 0;

    printf("Enter the startTime-ProcessTime Pairs.\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &t[i].s, &t[i].p);
        t[i].idx = i;
    }

    // Sorting accrn to time
    mergeSort(t, 0, n - 1);

    int j = t[0].s, currIdx = 0;

    for (int i = 0; i < n; i++)
    {
        if (j == t[i].s)
        {
            insert(heap, t[i]);
            currIdx = i + 1;
        }
        else
            break;
    }

    // getting element one by one from priority queue which is set in the order of smallest processing time.
    while (size != 0)
    {
        task temp = deleteRoot(heap);
        ans[ansIdx] = temp.idx;
        ansIdx++;
        j += temp.p;

        while (currIdx < n && t[currIdx].s <= j)
        {
            insert(heap, t[currIdx]);
            currIdx++;
        }
    }
    printf("The Order is: ");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", ans[i]);
    }

    printf("\n");

    // 4 1 2 2 4 3 2 4 1
    // 5 7 10 7 12 7 5 7 4 7 2

    return 0;
}