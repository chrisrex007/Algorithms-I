// Charniya Krish
// 23CS10012

#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1000
#define MAX 10000

typedef struct Node
{
    int data;
    int height;
    struct Node *left;
    struct Node *right;
} Node;

// Inserting new Node
Node *newNode(int key)
{
    Node *a = (Node *)malloc(sizeof(Node));
    a->data = key;
    a->left = a->right = NULL;
    return a;
}

// returns max value of two values
int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

// returns min value of two values
int min(int a, int b)
{
    if (a < b)
        return a;
    return b;
}

// insert function for BST
Node *insert(Node *root, int key)
{
    if (root == NULL)
        return newNode(key);

    if (key == root->data)
        printf("Key %d is already present in the tree.\n", key);
    else if (key < root->data)
        root->left = insert(root->left, key);
    else if (key > root->data)
        root->right = insert(root->right, key);

    return root;
}

/*
Finding xi
Approach: if we find the key value then we'll return that. if the curr node value is greater than key then we'll traverse left otherwise right,if we have to traverse right then that current node value is larger than the key value, however we have to find smallest larger value so we have to search for left tree.
*/
void findx(Node *root, int key, int *x)
{
    if (root == NULL)
    {
        *x = max(*x, -1);
        return;
    }
    if (root->data == key)
    {
        *x = max(*x, key);
        return;
    }
    else if (root->data > key)
    {
        findx(root->left, key, x);
    }
    else if (root->data < key)
    {
        *x = max(*x, root->data);
        findx(root->right, key, x);
        *x = max(root->data, *x);
    }
}

/*
Finding yi
Approach: same approach applied as xi but in this case we're finding smallest greater than element.
*/
void findy(Node *root, int key, int *y)
{
    if (root == NULL)
    {
        *y = min(*y, MAX);
        return;
    }
    if (root->data == key)
    {
        *y = min(key, *y);
        return;
    }
    else if (root->data > key)
    {
        *y = min(*y, root->data);
        findy(root->left, key, y);
        *y = min(root->data, *y);
    }
    else if (root->data < key)
    {
        findy(root->right, key, y);
    }
}

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int n;
    printf("Enter the number n: ");
    scanf("%d", &n);
    printf("Enter n elements \n");
    int a[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    int m;
    printf("Enter the size of S array: ");
    scanf("%d", &m);
    printf("Enter array elements \n");

    int s[m];
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &s[i]);
    }

    // creating the Tree
    Node *root = newNode(a[0]);
    for (int i = 1; i < n; i++)
    {
        if (a[i] == -1)
            continue;
        insert(root, a[i]);
    }

    printf("K array elements are given below. \n");

    // for each element in the S array we're finding xi and yi with utilFuncs.
    for (int i = 0; i < m; i++)
    {
        int x = -1, y = MAX;
        findx(root, s[i], &x);
        findy(root, s[i], &y);

        printf("%d %d\n", x, ((y == MAX) ? -1 : y));
    }

    // testcases used
    /*
    input.txt
    14
    6 2 13 1 4 9 15 -1 -1 -1 -1 -1 -1 14
    3
    2 5 16


    3
    4 -1 9
    1
    3
    */

    return 0;
}