// Charniya Krish
// 23CS10012

#include <stdio.h>
#include <stdlib.h>
#define MAX 100

int adj[MAX][MAX];
int c = 0;

// basically we are creating a tree and then transform into graph with preorder traversal.

int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}
typedef struct Node
{
    int data;
    int height;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct
{
    int items[MAX];
    int front;
    int rear;
} Queue;

void initQueue(Queue *q);
int isEmpty(Queue *q);
int isFull(Queue *q);
void enqueue(Queue *q, int value);
void dequeue(Queue *q);
int peek(Queue *q);

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
    return (q->rear == MAX);
}

void enqueue(Queue *q, int value)
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

int peek(Queue *q)
{
    if (isEmpty(q))
    {
        printf("Queue is empty\n");
        return -1;
    }
    return q->items[q->front + 1];
}

Node *newNode(int key) // creating and returning newNode.
{
    Node *a = (Node *)malloc(sizeof(Node));
    a->data = key;
    a->left = a->right = NULL;
    return a;
}

void preorder(Node *root, int *size, int *knownid, int knownval)
{
    if (!root)
        return;

    if (root->data == knownval)
    {
        *knownid = c;
    }

    *size += 1;
    root->data = c;
    c++;
    preorder(root->left, size, knownid, knownval);
    preorder(root->right, size, knownid, knownval);
}

void conversion(Node *root, int *size)
{
    if (!root)
        return;
    if (root->left != NULL)
    {
        adj[root->left->data][size[root->left->data]] = root->data;
        adj[root->data][size[root->data]] = root->left->data;
        size[root->left->data]++;
        size[root->data]++;
    }

    if (root->right != NULL)
    {
        adj[root->right->data][size[root->right->data]] = root->data;
        adj[root->data][size[root->data]] = root->right->data;
        size[root->right->data]++;
        size[root->data]++;
    }

    conversion(root->left, size);
    conversion(root->right, size);
}

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    int knownval = 3; // in our case 3 is the known id
    int knownid;      // we will obtain this from the traversal

    Node *root = newNode(1);
    root->left = newNode(5);
    root->right = newNode(3);
    root->left->right = newNode(4);
    root->left->right->right = newNode(2);
    root->left->right->left = newNode(9);
    root->right->left = newNode(10);
    root->right->right = newNode(6);

    int n = 0;
    // finding the knownid
    preorder(root, &n, &knownid, knownval);

    int size[n];

    for (int i = 0; i < n; i++)
        size[i] = 0;

    // conversion of tree to graph.
    conversion(root, size);

    int vis[n];
    for (int i = 0; i < n; i++)
    {
        vis[i] = 0;
    }

    int count[n];
    for (int i = 0; i < n; i++)
    {
        count[i] = 0;
    }

    // init the queue and doing the standard bfs.
    Queue q;
    initQueue(&q);

    enqueue(&q, knownid);

    while (!isEmpty(&q))
    {
        int l = peek(&q);
        dequeue(&q);
        vis[l] = 1;

        for (int i = 0; i < size[l]; i++)
        {
            if (!vis[adj[l][i]])
            {
                enqueue(&q, adj[l][i]);
                vis[adj[l][i]] = 1;
                count[adj[l][i]] = count[l] + 1;
            }
        }
    }

    // ans will be our max of all the counts.
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        ans = max(ans, count[i]);
    }

    printf("Total unit of time required is: %d\n", ans);

    return 0;
}