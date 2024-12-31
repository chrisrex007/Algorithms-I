#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1000

int n; // size of the arrays.

typedef struct Node
{
    int data;
    int height;
    struct Node *left;
    struct Node *right;
} Node;

Node *newNode(int key) // creating and returning newNode.
{
    Node *a = (Node *)malloc(sizeof(Node));
    a->data = key;
    a->left = a->right = NULL;
    return a;
}

int j = 0; // keeping the track of the occurence of leaf nodes.

Node *createBT(int pre[], int l[], int i)
{
    if (i >= n) // base case where index exceeds size of the array.
        return NULL;

    if (l[i] == 1) // if we reach leaf node then we keep the track of that index and return the leaf node.
    {
        j = i;
        return newNode(pre[i]);
    }

    Node *a = newNode(pre[i]);         // creating the root node.
    a->left = createBT(pre, l, i + 1); // recursively constructing left subtree & right subtree
    a->right = createBT(pre, l, j + 1);
    return a;
}

void inOrderTraversal(Node *root) // printing inOrderTraversal
{
    if (root == NULL)
        return;
    inOrderTraversal(root->left);
    printf("%d ", root->data);
    inOrderTraversal(root->right);
}

void outOrderTraversal(Node *root) // printing postOrderTraversal
{
    if (root == NULL)
        return;
    outOrderTraversal(root->left);
    outOrderTraversal(root->right);
    printf("%d ", root->data);
}

void preOrderTraversal(Node *root) // printing preOrderTraversal
{
    if (root == NULL)
        return;
    printf("%d ", root->data);
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
}

int main()
{
    printf("Enter the number of Nodes : ");
    scanf("%d", &n);
    printf("Enter the Preorder Elements : ");
    int pre[n], l[n];

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &pre[i]);
    }

    printf("Enter the Boolean Elements : ");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &l[i]);
    }

    Node *root; // creating the root.
    root = newNode(pre[0]);

    if (l[0] != 1) // if the root isn't a leaf node then we will construct left and right subtree recursively.
        root = createBT(pre, l, 0);

    printf("The reconstructed tree's Traversals are as follows : \n");
    printf("Inorder : ");
    inOrderTraversal(root);
    printf("\nPreorder : ");
    preOrderTraversal(root);
    printf("\nPostorder : ");
    outOrderTraversal(root);
    printf("\n");

    // Testcase
    //  9 1 2 4 5 3 6 8 9 7 0 0 1 1 0 0 1 1 1
    return 0;
}