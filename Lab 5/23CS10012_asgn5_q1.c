// Charniya Krish
// 23CS10012

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

typedef struct
{
    Node *items[MAX_SIZE];
    int front;
    int rear;
} Queue;

// defining queue functions
void initQueue(Queue *q);
int isEmpty(Queue *q);
int isFull(Queue *q);
void enqueue(Queue *q, Node *value);
void dequeue(Queue *q);
Node *peek(Queue *q);

Node *newNode(int key);
Node *buildTree(int nodes[], int n);
void levelOrderTraversal(Node *root);
Node *createDummyNode();
Node *insertNode(Node *root, int val);

int sum = 0;
Node *x;

// modifying as required, basically rightmost element is largest and hence it will count towards each node, RIGHT ROOT LEFT Traversal storing sum at each node.
void modify(Node *root)
{
    if (root == NULL)
        return;

    modify(root->right);
    sum += root->data;
    root->data = sum;
    modify(root->left);
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

    modify(root);
    x = createDummyNode();

    printf("Building the BST is done.. \nModified Tree is : ");
    levelOrderTraversal(root);
    printf("\n");

    return 0;
}

// 4 1 6 0 2 5 7 3 8

// creating new node
Node *newNode(int key)
{
    Node *a = (Node *)malloc(sizeof(Node));
    a->data = key;
    a->left = a->right = NULL;
    return a;
}

// lvl order traversal using queue
void levelOrderTraversal(Node *root)
{
    Queue *q;
    q = (Queue *)malloc(sizeof(Queue));
    initQueue(q);
    enqueue(q, root);

    while (!isEmpty(q))
    {
        Node *y = peek(q);
        dequeue(q);
        printf("%d ", y->data);

        if (y->data != -1)
        {
            if (y->left != NULL)

                enqueue(q, y->left);
            else
                enqueue(q, x);

            if (y->right != NULL)
                enqueue(q, y->right);
            else
                enqueue(q, x);
        }
    }
}
// functions for enqueue dequeue etcc
void initQueue(Queue *q)
{
    q->front = -1;
    q->rear = 0;
}

int isEmpty(Queue *q)
{
    return (q->front == q->rear - 1);
}

int isFull(Queue *q)
{
    return (q->rear == MAX_SIZE);
}

void enqueue(Queue *q, Node *value)
{
    if (isFull(q))
    {
        printf("Queue is full\n");
        return;
    }
    q->items[q->rear] = value;
    q->rear++;
}

void dequeue(Queue *q)
{
    if (isEmpty(q))
    {
        printf("Queue is empty\n");
        return;
    }
    q->front++;
}

Node *peek(Queue *q)
{
    if (isEmpty(q))
    {
        printf("Queue is empty\n");
        return NULL;
    }
    return q->items[q->front + 1];
}

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

Node *createDummyNode()
{
    Node *a = (Node *)malloc(sizeof(Node));
    a->data = -1;
    a->left = a->right = NULL;
    return a;
}