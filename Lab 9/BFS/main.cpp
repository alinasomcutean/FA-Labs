/**
    Somcutean Alina-Ioana, Group 30424
    The complexity of BFS algorithm is O(nrVertices + nrEdges).
    If number of vertices is fixed, the complexity is O(nrEdges).
    If number of edges is fixed, the complexity is O(nrVertices).
*/

#include <iostream>
#include <stdlib.h>
#include "Profiler.h"
Profiler profiler("BFS");

using namespace std;

int operations = 0;

struct Node
{
    int value;
    Node *next;
};

struct Queue
{
    Node *first, *last;
    int length;
};

struct Graph
{
    int nrVertices, *visited;
    Node **adjList;
};

typedef struct NodeR2
{
    int value, length;
    NodeR2 *children;
};

NodeR2 initNode(int value)
{
    NodeR2 node;
    node.length = 0;
    node.value = value;
    node.children = (NodeR2*)malloc(50*sizeof(NodeR2));
    return node;
}

Queue *initQueue()
{
    Queue *pQueue = (Queue*)malloc(sizeof(Queue));
    pQueue->first = NULL;
    pQueue->last = NULL;
    pQueue->length = 0;
    return pQueue;
}

Node *createNode(int value)
{
    Node *node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    return node;
}

Graph *createGraph(int nrVertices)
{
    Graph *graph = (Graph*)malloc(sizeof(Graph));
    graph->nrVertices = nrVertices;
    graph->adjList = (Node**)malloc(nrVertices * sizeof(struct Node*));
    graph->visited = (int*)malloc(nrVertices * sizeof(int));

    for(int i = 0; i < nrVertices; i++)
    {
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

void enqueue(Queue *pQueue, int value)
{
    Node *node = createNode(value);
    node->next = NULL;
    if(pQueue->last != NULL)
    {
        pQueue->last->next = node;
    }
    else
    {
        pQueue->first = node;
    }
    pQueue->last = node;
    pQueue->length++;
}

int dequeue(Queue *pQueue)
{
    Node *node;
    if(pQueue->first != NULL)
    {
        node = pQueue->first;
        pQueue->first = pQueue->first->next;
        pQueue->length --;
        if(pQueue->first == NULL)
        {
            pQueue->last = NULL;
        }
        return node->value;
    }
    return -1;
}

void addEdge(Graph *graph, int start, int finish)
{
    Node *node = createNode(finish);
    node->next = graph->adjList[start];
    graph->adjList[start] = node;

    node = createNode(start);
    node->next = graph->adjList[finish];
    graph->adjList[finish] = node;
}

int parent_vector[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

void BFS_component(Graph *graph, int start)
{
    int parent = start;
    Queue *pQueue = initQueue();
    graph->visited[start] = 1;
    operations++;

    enqueue(pQueue, start);
    operations++;

    while (pQueue->length != 0)
    {
        operations++;
        int current = dequeue(pQueue);
        cout << current << " ";
        parent = current;

        Node *element = graph->adjList[current];
        operations++;

        while (element != NULL)
        {
            operations++;
            int adjValue = element->value;

            operations = operations + 2;
            if (graph->visited[adjValue] == 0)
            {
                graph->visited[adjValue] = 1;
                parent_vector[adjValue] = parent;
                enqueue(pQueue, adjValue);
                operations++;
            }
            element = element->next;
            operations++;
        }
    }

}

void BFS(Graph *graph, int start)
{
    for(int i = 0; i < graph->nrVertices; i++)
    {
        operations++;
        if (graph->visited[i] == 0)
        {
            BFS_component(graph, i);
        }
    }
}

NodeR2 *tree;

NodeR2 *transformParentToMultiWay(int parent_vector[], int n)
{
    tree = (NodeR2*)malloc(n * sizeof(NodeR2));
    for(int i = 1; i <= n; i++)
    {
        tree[parent_vector[i]] = initNode(parent_vector[i]);
    }
    for(int i = 1; i <= n; i++)
    {
        if(parent_vector[i] != -1)
        {
            if(tree[parent_vector[i]].length > n )
            {
                tree[parent_vector[i]] = initNode(parent_vector[i]);
            }
            if(tree[i].length > n )
            {
                tree[i] = initNode(i);
            }
            tree[parent_vector[i]].length++;
            tree[parent_vector[i]].children[tree[parent_vector[i]].length] = initNode(i);
        }
    }
    return tree;
}

void showMultiWay()
{
    int i;
    NodeR2 *tree = transformParentToMultiWay(parent_vector, 10);
    for(i = 0; i < 10; i++)
    {
        cout << "node " << i << ": ";
        if(tree[i].length < 1)
        {
            cout << "it doesn't have";
        }
        else
        {
            if(i == 0)
            {
                for(int j = 1; j < tree[i].length; j++)
                {
                    cout << tree[i].children[j].value << " ";
                }
            }
            else
            {
                for(int j = 1; j <= tree[i].length; j++)
                {
                    cout << tree[i].children[j].value << " ";
                }
            }
        }
        cout << "\n";
    }
}

void test()
{
    Graph *graph = createGraph(10);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 4);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 9);
    addEdge(graph, 3, 4);
    addEdge(graph, 5, 6);
    addEdge(graph, 6, 7);
    addEdge(graph, 5, 7);
    BFS(graph, 1);
    cout << "\n\nParent vector: ";
    for(int i = 0; i < 10; i++)
    {
        cout <<parent_vector[i] << " ";
    }
    cout << "\n\n";
    showMultiWay();
}

void generateEdges(Graph *graph, int nrEdges, int nrVertices)
{
    graph = createGraph(nrVertices);
    int k = 0, i = 0, j = 0;
    int *start, *finish;

    start = (int*)malloc(nrVertices * sizeof(int));
    finish = (int*)malloc(nrVertices * sizeof(int));

    FillRandomArray(start, nrVertices, 0, nrVertices-1, true, 0);
    FillRandomArray(finish, nrVertices, 0, nrVertices-1, true, 0);

    for(i = 0; i < nrVertices-1; i++)
    {
        for(j = i+1; j < nrVertices; j++)
        {
            if(start[i] != finish[j])
            {
                addEdge(graph, start[i], finish[j]);
                k++;
            }
            if(k == nrEdges)
            {
                break;
            }
        }
        if(k == nrEdges)
        {
            break;
        }
    }
}

void average_case_fixed_vertices()
{
    int nrVertices = 100;
    operations = 0;
    for(int nrEdges = 1000; nrEdges <= 4500; nrEdges = nrEdges + 100)
    {
        Graph *graph = createGraph(nrVertices);
        generateEdges(graph, nrEdges, nrVertices);
        BFS(graph, 0);
        free(graph);
        profiler.countOperation("Graph for fixed vertices", nrVertices + nrEdges, operations);
    }
    profiler.showReport();
}

void average_case_fixed_edges()
{
    int nrEdges = 9000;
    operations = 0;
    for(int nrVertices = 100; nrVertices <= 200; nrVertices = nrVertices + 10)
    {
        Graph *graph = createGraph(nrVertices);
        generateEdges(graph, nrEdges, nrVertices);
        BFS(graph, 0);
        free(graph);
        profiler.countOperation("Graph for fixed edges", nrVertices + nrEdges, operations);
    }
    profiler.showReport();
}

int main()
{
    test();
    ///average_case_fixed_edges();
    ///average_case_fixed_vertices();
    return 0;
}
