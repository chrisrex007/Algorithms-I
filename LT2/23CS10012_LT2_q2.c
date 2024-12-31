// Charniya Krish
// 23CS10012

#include <stdio.h>
#include <stdlib.h>

// storing the answer
int ans = 0;

typedef struct Node
{
    int data;
    int height;
    struct Node *left;
    struct Node *right;
} Node;

// creating new Node
Node *newNode(int key)
{
    Node *a = (Node *)malloc(sizeof(Node));
    a->data = key;
    a->left = a->right = NULL;
    return a;
}

// Function prototype for solveUtil
void solveUtil(Node *root, int x, int sum);

/*
Approach: bruteforcing every node if there's path exist and that sum is equal to x.
*/
void solve(Node *root, int x)
{
    if (root == NULL)
        return;
    solveUtil(root, x, 0);
    solve(root->left, x);
    solve(root->right, x);
}

// For checking the path from a particular Node
void solveUtil(Node *root, int x, int sum)
{
    if (root == NULL)
        return;
    sum += root->data;
    if (sum == x)
        ans++;

    solveUtil(root->left, x, sum);
    solveUtil(root->right, x, sum);
    sum -= root->data;
}

int main()
{
    int x;
    printf("Enter the number x: ");
    scanf("%d", &x);

    // Building the Tree
    Node *root = newNode(-8);
    root->left = newNode(2);
    root->right = newNode(7);
    root->left->left = newNode(8);
    root->left->right = newNode(4);
    root->right->left = newNode(-1);
    root->right->right = newNode(6);
    root->left->right->left = newNode(2);
    root->right->left->left = newNode(7);
    root->right->left->right = newNode(7);
    root->right->right->right = newNode(1);

    solve(root, x);
    printf("Number of Paths = %d \n", ans);

    return 0;
}