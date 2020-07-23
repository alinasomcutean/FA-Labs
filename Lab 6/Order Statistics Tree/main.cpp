/**
    Somcutean Alina-Ioana, Group 30424
    The Select operation has the complexity O(h), where h is the height of the tree and the Delete operation has the same complexity.
*/
#include <iostream>
#include "Profiler.h"
#define MAX_SIZE 10000
Profiler profiler ("OST");

using namespace std;

int Select = 0, Delete = 0;

typedef struct Node
{
    int value, length;
    Node *left, *right, *parent;
};

Node *create_node(int value)
{
    Node *node = (Node*)malloc(sizeof(Node));
    if(node)
    {
        node->value = value;
        node->left = NULL;
        node->right = NULL;
        node->parent = NULL;
        node->length = 1;
    }
    return node;
}

Node *build_tree(int a[], int left, int right, Node *parent)
{
    int i, median;
    if(left > right)
    {
        return NULL;
    }
    if(left <= right)
    {
        median = (left + right)/2;
        Node *node = create_node(a[median]);
        node->parent = parent;
        node->left = build_tree(a, left, median - 1, node);
        node->right = build_tree(a, median + 1, right, node);
        if(node->left != NULL)
        {
            node->length = node->length + node->left->length;
        }
        if(node->right != NULL)
        {
            node->length = node->length + node->right->length;
        }
        return node;
    }
}

void show_tree(Node *node, int level)
{
    if(node == NULL)
        return;
    show_tree(node->right, level+1);
    for(int i = 0; i < level; i++)
        cout << " \t";
    cout << node->value << " , " << node->length << "\n";
    show_tree(node->left, level+1);
}

Node *OS_Select(Node *root, int k, int n)
{
    int pos;
    Select++;
    if(root->left == NULL)
    {
        pos = 1;
        Select++;
    }
    else
    {
        pos = root->left->length + 1;
        Select++;
    }
    if(pos == k)
    {
        return root;
    }
    else
    {
        if(pos > k)
        {
            return OS_Select(root->left, k, n);
        }
        else
        {
            return OS_Select(root->right, k - pos, n);
        }
    }
}

int random(int n)
{
    return rand() % n + 1;
}

Node *find_tree_min(Node *root, int n)
{
    Delete++;
    while(root->left != NULL)
    {
        root = root->left;
        Delete++;
    }
    return root;
}

Node *find_tree_successor(Node *node, int n)
{
    Delete++;
    if(node->right != NULL)
    {
        return find_tree_min(node->right, n);
    }
    Delete++;
    Node *y = node->parent;
    Delete++;
    while(y != NULL)
    {
        node = y;
        y = node->parent;
        Delete = Delete + 3;
    }
    return y;
}

Node *OS_Delete(Node **root, Node *z, int n)
{
    Node *y = (Node*)malloc(sizeof(Node));
    Node *x = (Node*)malloc(sizeof(Node));
    if(z->left == NULL || z->right == NULL)
    {
        y = z;
        Delete = Delete + 2;
    }
    else
    {
        y = find_tree_successor(z, n);
        Delete = Delete + 2;
    }
    if(y->left != NULL) ///case 2
    {
        x = y->left;
        Delete = Delete + 2;
    }
    else
    {
        x = y->right;
        Delete = Delete + 2;
    }
    if(x != NULL)
    {
        x->parent = y->parent;
        Delete = Delete + 2;
    }
    if(y->parent == NULL)
    {
        (*root) = x;
        Delete = Delete + 2;
    }
    else
    {
        if(y == y->parent->left)
        {
            y->parent->left = x;
            Delete = Delete + 3;
        }
        else
        {
            y->parent->right = x;
            Delete = Delete + 3;
        }
    }
    Delete++;
    Node *aux;
    aux = y->parent;
    Delete++;
    while(aux != NULL)
    {
        aux->length--;
        aux = aux->parent;
        Delete = Delete + 3;
    }
    return y;
}

void free_tree(Node *root)
{
    if(root == NULL)
    {
        return;
    }
    free(root->left);
    free(root->right);
    free(root);
}

void test()
{
    int a[12], n = 12;
    FillRandomArray(a, 12, 1, 12, true, 1);
    Node *root = build_tree(a, 0, 11, NULL);
    show_tree(root, 0);
    Node *nodeP = (Node*)malloc(sizeof(Node));
    int i, k;
    for(i = 0; i < 12; i++)
    {
        k = random(n);
        nodeP = OS_Select(root, k, n);
        cout << "\nThe " << k << " smallest nr is: " << nodeP->value;
        Node *p = OS_Delete(&root, nodeP, n);
        cout << "\n";
        nodeP->value = p->value;
        show_tree(root, 0);
        n--;
        free(nodeP);
        free(p);
    }

}

void average()
{
    int a[MAX_SIZE], i, j, k, value, n;
    Node *root, *node, *nodeP;
    for(j = 100; j < MAX_SIZE; j = j+100)
    {
        for(i = 0; i < 5; i++)
        {
            FillRandomArray(a, j, 1, 50000, true, 1);
            root = build_tree(a, 0, j-1, NULL);
            n = j;
            for(k = 0; k < j; k++)
            {
                value = random(n);
                node = OS_Select(root, value, n);
                nodeP = OS_Delete(&root, node, n);
                node->value = nodeP->value;
                n--;
            }
        }
        free_tree(root);
        Delete = Delete/5;
        Select = Select/5;
        profiler.countOperation("Average select", j, Select);
        profiler.countOperation("Average delete", j, Delete);
    }
    profiler.createGroup("Order Statistics Tree", "Average select", "Average delete");
    profiler.showReport();
}

int main()
{
    test();
    ///profiler.reset("OST");
    ///average();
    return 0;
}
