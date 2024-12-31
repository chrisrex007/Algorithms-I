#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_SIZE 1000

typedef struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
} Node;

// Function Prototypes
Node *newNode(int key);
Node *buildTree(int nodes[], int n);
void levelOrderTraversal(Node *root);
void inOrderTraversal(Node *root);
void interchangeNodes(Node *node1, Node *node2);
void restoreBST(Node *root);
Node *insertNode(Node *root, int val);

int tmp = 0;     // temp variable
Node *f1;        // storing the first node
Node *f2;        // storing the second node
Node *prevNode2; // temp variable

Node *prevNode; // for inorder traversal checks
Node *find(Node *root) // finding the first node, invalidity of inorder traversal is being checked here.
{
    static int prev = -1;

    if (root == NULL)
        return NULL;

    find(root->left);

    if (root->data < prev)
    {
        f1 = prevNode;
        f2 = root;
    }
    else
    {
        prev = root->data;
        prevNode = root;
    }

    find(root->right);
    return root;
}

Node *find2(Node *root) // finding the second node when first node is already found
{
    static int prev2 = -1;

    if (root == NULL)
        return NULL;

    find2(root->left);

    if (f1 != NULL && f2 == NULL)
    {
        if (root->data < prev2)
        {
            f2 = root;
        }
        else
        {
            prev2 = root->data;
            prevNode2 = root;
        }
    }

    find2(root->right);
    return root;
}

void restoreBST(Node *root) // main function
{
    find(root);
    find2(root);
    interchangeNodes(f1, f2); // finally interchanging the nodes.
}

int main()
{
    int n;
    printf("Enter the number of Nodes : ");
    scanf("%d", &n);

    int *a = (int *)malloc(sizeof(int) * n);

    printf("Enter tree Nodes (Separated by space) : ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    Node *root = newNode(a[0]);

    for (int i = 1; i < n; i++)
    {
        insertNode(root, a[i]);
    }

    printf("Building the BST is done.. \n");
    printf("Inorder Traversal of the BST is : ");
    inOrderTraversal(root);
    printf(" \n\n");

    printf("Interchanging the values of two nodes.. \n");
    interchangeNodes(root->left, root->left->right);
    printf("Inorder Traversal of the BST is : ");
    inOrderTraversal(root);
    printf(" \n\n");

    printf("Rebuilding the tree is done.. \n");
    restoreBST(root);
    printf("Inorder Traversal of the BST is : ");
    inOrderTraversal(root);
    printf(" \n\n");

    // 7 15 10 20 8 12 16 25

    return 0;
}

Node *newNode(int key)
{
    Node *a = (Node *)malloc(sizeof(Node));
    a->data = key;
    a->left = a->right = NULL;
    return a;
}

// inorderTraversaling
void inOrderTraversal(Node *root)
{
    if (root == NULL)
        return;

    inOrderTraversal(root->left);
    printf("%d ", root->data);
    inOrderTraversal(root->right);
}

// interchanging nodes
void interchangeNodes(Node *node1, Node *node2)
{
    int tmp = node1->data;
    node1->data = node2->data;
    node2->data = tmp;
}

// inserting node
Node *insertNode(Node *root, int val) // O(depth)
{
    if (root == NULL)
        root = newNode(val);

    else if (val > root->data)
        root->right = insertNode(root->right, val);
    else if (val < root->data)
        root->left = insertNode(root->left, val);

    return root;
}
