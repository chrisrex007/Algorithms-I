#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 20

typedef struct Node
{
    char c[MAX_SIZE];
    struct Node *left;
    struct Node *right;
} Node;

Node *newNode(char key[]) // creates the new Node
{
    Node *a = (Node *)malloc(sizeof(Node));
    int n = 0;
    while (key[n] != '\0')
        n++;

    for (int i = 0; i < n; i++)
        a->c[i] = key[i];

    a->left = a->right = NULL;
    return a;
}

int isNumber(char key[]) // check if string is number.
{
    if (key[0] >= '0' && key[0] <= '9')
        return 1;
    return 0;
}

// alternative we can use inbuilt atoi function also.
int stringToInt(char key[]) // coverts the string into integer.
{
    int n = 0;
    while (key[n] != '\0')
        n++;
    int counter = 1;
    int ans = 0;

    for (int i = n - 1; i >= 0; i--)
    {
        ans += (key[i] - '0') * counter;
        counter *= 10;
    }
    return ans;
}

// TC : O(logn)
int pow1(int base, int power) // calculates the exponential.
{
    if (power == 0)
        return 1;

    int l = pow1(base, power / 2);
    if (power % 2)
    {
        return base * l * l;
    }
    else
        return l * l;
}

int postOrder(Node *root)
{
    if (isNumber(root->c)) // if we reach leaf node then we return the int value of that string
        return atoi(root->c);

    int l = postOrder(root->left);  // storing the left value in l
    int r = postOrder(root->right); // storing the right value in r

    // doing operations and returning the value as required.
    if (root->c[0] == '-')
        return l - r;
    else if (root->c[0] == '*')
        return l * r;
    else if (root->c[0] == '+')
        return l + r;
    else if (root->c[0] == '/')
        return l / r;
    else if (root->c[0] == '^')
        return pow1(l, r);
}

int main()
{
    // Building the tree
    Node *root = newNode("+");
    root->left = newNode("*");
    root->right = newNode("/");
    root->left->left = newNode("-");
    root->left->right = newNode("5");
    root->right->left = newNode("21");
    root->right->right = newNode("7");
    root->left->left->left = newNode("10");
    root->left->left->right = newNode("5");

    // output
    printf("The value of the expression is : %d \n", postOrder(root));
    return 0;
}