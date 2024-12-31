////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////          Assignment 1 Model Solution          ///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include<stdlib.h>



int parta(int*arr ,int size)
{
    for (int i = 1 ; i <= size - 2 ; i++) 
    {
        for (int j = i + 1 ; j <= size - 1 ; j++) 
        {
            for (int k = j + 1 ; k <= size ; k++)      //Upto this we know that i < j < k
            {
                // Finding the positions of (i,j,k) using Linear search
                int pos1 = -1, pos2 = -1, pos3 = -1;
                for (int l = 0; l < size; l++) 
                {
                    if (arr[l] == i) pos1 = l;
                    else if (arr[l] == j) pos2 = l;
                    else if (arr[l] == k) pos3 = l;
                }

                if (pos1 > pos3 && pos2 > pos1)   // Checking for invalid order
                {
                    return 0;                     // Invalid sequence
                }
            }
        }
    }

    return 1;  // Valid sequence

}

int partb(int* arr, int size) 
{
    for (int i = 0; i < size - 2; i++) 
    {
        for (int j = i + 1; j < size - 1; j++) 
        {
            for (int k = j + 1; k < size; k++) 
            {
                
                int s1 = arr[i];   // Here since i < j < k thus the relative order in the array is always maintained, 
                int s2 = arr[j];   // Only need to check for the invalid arrangement
                int s3 = arr[k];

                if (s1 > s3 && s3 > s2)  // Checking for invalid order
                {
                    return 0;            // Invalid sequence
                }
            }
        }
    }

    return 1; // Valid sequence
}

int partc(int* arr, int size)
{
    int last,curr;
    for(int i = 0 ; i < size-2 ; i++)
    {
        curr = arr[i];                       // Holds the current value at ith index
        last = arr[i];
        for(int j = i+1 ; j < size ; j++)    // Logic is if from i+1 to n it increases/decreases strictly then no invalid arrangement
        {                                    // But if it increases after decreasing then its invalid.
            if(arr[j] < curr)
            {
                if(arr[j] > last)      // Checking for invalid order
                    return 0;          // Invalid sequence
                last = arr[j];
            }
        }
    }
    return 1;   // Valid sequence
}

int partd(int* arr, int size)
{
    int stack[size], top = -1, a = 1;     //Implementing a stack based approach
    for(int i = 0 ; i < size ; i++)
    {
        while(a <= arr[i])
        {
            stack[++top] = a;              // If we have a current largest element lets say "5", the stack has elements from 1 to 5 and a is 6,
            a++;                           // Then 5 gets popped, and if any element except 4 comes up from 1 to 3 that means as per the given constraint,
        }                                  // 4 will definity appear later on thus making the arrangement invalid, so return 0.
        if(top == -1)
            return 0;
        
        if(stack[top] != arr[i])
            return 0;
        int ele = stack[top--];             //Popping
    }
    return 1;
}

void main()
{
    int size = 0;
    printf("\nEnter the size of the array : "); scanf("%d",&size);

    //Array declaration and initialization (Static declaration will also work)
    int* arr = (int*)malloc(sizeof(int)*size);
    if(arr == NULL)
    {
        printf("Memory Allocation Failed !!!");
        return;
    }
    
    printf("Enter the elements below :\n");
    for(int i = 0 ; i < size ; i++)
    {
        scanf("%d",&arr[i]);
    }

    int result = -1;

    //First part call
    result = parta(arr, size);
    (result)?printf("\nMethod(a) : Valid sequence"):printf("\nMethod(a) : Invalid sequence");
    
    //Second part call
    result = partb(arr, size);
    (result)?printf("\nMethod(b) : Valid sequence"):printf("\nMethod(b) : Invalid sequence");

    //Third part call
    result = partc(arr,size);
    (result)?printf("\nMethod(c) : Valid sequence"):printf("\nMethod(c) : Invalid sequence");

    //Fourth part call
    result = partd(arr,size);
    (result)?printf("\nMethod(d) : Valid sequence"):printf("\nMethod(d) : Invalid sequence");
    printf("\n");

    //Free the memory
    free(arr);
}