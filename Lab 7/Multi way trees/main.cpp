/**
    Somcutean Alina-Ioana, Group 30424
*/
#include <iostream>
#include <stdlib.h>

using namespace std;

int parent[10] = {0, 2, 7, 5, 2, 7, 7, -1, 5, 2};

typedef struct NodeR2
{
    int value, length;
    NodeR2 *children;
};

typedef struct NodeR3
{
    int value;
    NodeR3 *leftChild, *rightChild;
};

NodeR2 initNode(int value)
{
    NodeR2 node;
    node.length = 0;
    node.value = value;
    node.children = (NodeR2*)malloc(50*sizeof(NodeR2));
    return node;
}

NodeR3 *createNode(int value)
{
    NodeR3 *node = (NodeR3*)malloc(sizeof(NodeR3));
    node->value = value;
    node->leftChild = NULL;
    node->rightChild = NULL;
    return node;
}

NodeR3 *root;
NodeR2 *tree;

NodeR2 *transformParentToMultiWay(int parent[], int n)
{
    tree = (NodeR2*)malloc(n * sizeof(NodeR2));
    for(int i = 1; i <= n; i++)
    {
        tree[parent[i]] = initNode(parent[i]);
    }
    for(int i = 1; i <= n; i++)
    {
        if(parent[i] != -1)
        {
            if(tree[parent[i]].length > n )
            {
                tree[parent[i]] = initNode(parent[i]);
            }
            if(tree[i].length > n )
            {
                tree[i] = initNode(i);
            }
            tree[parent[i]].length++;
            tree[parent[i]].children[tree[parent[i]].length] = initNode(i);
        }
        else
        {
            root = createNode(i);
        }
    }
    return tree;
}

void showMultiWay()
{
    int i;
    NodeR2 *tree = transformParentToMultiWay(parent, 9);
    for(i = 1; i <= 9; i++)
    {
        cout << "node " << i << ": ";
        if(tree[i].length < 1)
        {
            cout << "it doesn't have";
        }
        else
        {
            for(int j = 1; j <= tree[i].length; j++)
            {
                cout << tree[i].children[j].value << " ";
            }
        }
        cout << "\n";
    }
}

void add_children(NodeR3 *root3, NodeR2 *root2, NodeR2 *node)
{
    if(root2[node->value].length < 1)
    {
        return;
    }
    root3->leftChild = createNode(root2[node->value].children[1].value);
    NodeR3 *current;
    current = root3->leftChild;
    for(int i = 2; i <= root2[node->value].length; i++)
    {
        current->rightChild = createNode(root2[node->value].children[i].value);
        add_children(current, root2, &root2[node->value].children[i-1]);
        current = current->rightChild;
    }
}

void show_tree(NodeR3 *node, int level)
{
    if(node == NULL)
        return;
    cout << "\n";
    show_tree(node->rightChild, level+1);
    for(int i = 0; i < level; i++)
        cout << "\t";
    cout << node->value;
    cout << "\n";
    show_tree(node->leftChild, level+1);
}

int main()
{
    for(int i = 0; i < 10; i++)
    {
        cout << parent[i] << " ";
    }
    cout << "\n";
    showMultiWay();
    add_children(root, tree, &tree[root->value]);
    show_tree(root, 0);
    return 0;
}
