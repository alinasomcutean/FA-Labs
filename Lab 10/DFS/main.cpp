#include <iostream>
#include <stdlib.h>
#include "Profiler.h"
Profiler profiler("DFS");
using namespace std;

int operations = 0;

struct Node
{
    int value;
    Node *next;
};

struct AdjList
{
    Node *first, *parent;
    int color, discovered_time, finish_time, low_link;
    bool on_stack;
};

struct Graph
{
    int nrVertices;
    AdjList *adjList;
};

struct List
{
    int length;
    Node *first, *last;
};

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
    graph->adjList = (AdjList*)malloc(nrVertices * sizeof(AdjList));
    graph->nrVertices = nrVertices;
    for(int i = 0; i < nrVertices; i++)
    {
        graph->adjList[i].first = createNode(i);
    }
    return graph;
}

void addEdge(Graph *graph, int start, int finish)
{
    Node *node = createNode(finish);
    Node *aux = graph->adjList[start].first;
    while(aux->next != NULL)
    {
        aux = aux->next;
    }
    aux->next = node;
}

void addNode(Node *first, int value)
{
    Node *node = createNode(value);
    node->next = first->next;
    first->next = node->next;
}

void initList(List **pList)
{
    (*pList)->first = (*pList)->last = NULL;
    (*pList)->length = 0;
}

void insertFirst(List **pList, int value)
{
    Node *node = createNode(value);
    if((*pList) == NULL)
    {
        (*pList)->first = (*pList)->last = node;
    }
    else
    {
        node->next = (*pList)->first;
        (*pList)->first = node;
    }
    (*pList)->length++;
}

void deleteList(List **pList)
{
    if((*pList)->first != NULL)
    {
        (*pList)->first = (*pList)->first->next;
        (*pList)->length--;
        if((*pList)->first == NULL)
        {
            (*pList)->last = NULL;
        }
    }
}

void showList(List *pList)
{
    Node *node;
    node = pList->first;
    if(node == NULL)
        printf("None");
    else
    {
        while(node != NULL)
        {
            cout << node->value << " ";
            node = node->next;
        }
    }
    printf("\n");
}

int Time;

List *pList;

void DFS_component(Graph *graph, int start)
{
    Time++;
    graph->adjList[start].discovered_time = Time;
    graph->adjList[start].color = 1; ///gray
    operations = operations + 2;

    Node *aux = graph->adjList[start].first->next;
    cout << start << " ";
    operations++;

    while(aux != NULL)
    {
        operations++;

        if(graph->adjList[aux->value].color == 0)///white
        {
            operations++;
            graph->adjList[aux->value].parent = aux;
            DFS_component(graph, aux->value);
        }

        aux = aux->next;
        operations++;
    }

    graph->adjList[start].color = 2;///black
    operations++;

    insertFirst(&pList, start);
    Time++;
    graph->adjList[start].finish_time = Time;
    operations++;
}

void DFS(Graph *graph, int start)
{
    for(int i = 0; i < graph->nrVertices; i++)
    {
        graph->adjList[i].color = 0;
        graph->adjList[i].parent = NULL;
    }
    Time = 0;
    for(int i = 0; i < graph->nrVertices; i++)
    {
        operations++;
        if(graph->adjList[i].color == 0)
        {
            DFS_component(graph, i);
        }
    }
}

void printAdjList(Graph *graph)
{
    for(int i = 0; i < graph->nrVertices; i++)
    {
        Node *node = graph->adjList[i].first;
        cout << "Node " << i << ": ";
        if(node->next == NULL)
        {
            cout << "-";
        }
        while(node->next != NULL)
        {
            cout << node->next->value << " ";
            node = node->next;
        }
        cout << "\n";
    }
}

int step = 0;

void SCC_component(Graph *graph, int start, List *new_stack)
{
    graph->adjList[start].discovered_time = graph->adjList[start].low_link = ++step;
    graph->adjList[start].on_stack = true;
    insertFirst(&new_stack, start);

    Node *aux = graph->adjList[start].first->next;
    int minimum1, minimum2;

    while(aux != NULL)
    {
        if(graph->adjList[aux->value].discovered_time == -1)
        {
            SCC_component(graph, aux->value, new_stack);
            if(graph->adjList[start].low_link < graph->adjList[aux->value].low_link)
            {
                minimum1 = graph->adjList[start].low_link;
            }
            else
            {
                minimum1 = graph->adjList[aux->value].low_link;
            }
            graph->adjList[start].low_link = minimum1;
        }
        else
        {
            if(graph->adjList[aux->value].on_stack == true)
            {
                if(graph->adjList[start].low_link < graph->adjList[aux->value].discovered_time)
                {
                    minimum2 = graph->adjList[start].low_link;
                }
                else
                {
                    minimum2 = graph->adjList[aux->value].discovered_time;
                }
                graph->adjList[start].low_link = minimum2;
            }
        }
        aux = aux->next;
    }

    if(graph->adjList[start].low_link == graph->adjList[start].discovered_time)
    {
        while(new_stack->first->value != start)
        {
            cout << new_stack->first->value << " ";
            graph->adjList[new_stack->first->value].on_stack = false;
            deleteList(&new_stack);
        }

        cout << new_stack->first->value << " ";
        cout << "\n";
        graph->adjList[start].on_stack = false;
        deleteList(&new_stack);
    }
}

void SCC(Graph *graph)
{
    List *new_stack = (List*)malloc(sizeof(List));
    initList(&new_stack);
    for(int i = 0; i < graph->nrVertices; i++)
    {
        graph->adjList[i].discovered_time = -1;
        graph->adjList[i].low_link = -1;
        graph->adjList[i].on_stack = false;
    }
    for(int i = 0; i < graph->nrVertices; i++)
    {
        if(graph->adjList[i].discovered_time == -1)
        {
            SCC_component(graph, i, new_stack);
        }
    }
}

void test()
{
    int nrVertices = 8;
    Graph *graph = createGraph(nrVertices);
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 3);
    addEdge(graph, 3, 2);
    addEdge(graph, 2, 0);
    addEdge(graph, 2, 1);
    addEdge(graph, 2, 4);
    addEdge(graph, 5, 6);
    addEdge(graph, 6, 5);

    pList = (List*)malloc(sizeof(List));
    initList(&pList);

    DFS(graph, 0);
    cout << "\n\n";
    printAdjList(graph);

    cout << "\nTopological sort: ";
    showList(pList);

    cout << "\nTarjan: \n";
    SCC(graph);
}

void generateEdges(Graph *graph, int nrEdges, int nrVertices)
{
    free(graph);
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
        DFS(graph, 0);
        free(graph);
        profiler.countOperation("Graph for fixed vertices", nrVertices, operations);
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
        DFS(graph, 0);
        free(graph);
        profiler.countOperation("Graph for fixed edges", nrEdges, operations);
    }
    profiler.showReport();
}

int main()
{
    test();
    ///average_case_fixed_vertices();
    ///average_case_fixed_edges();
    return 0;
}
