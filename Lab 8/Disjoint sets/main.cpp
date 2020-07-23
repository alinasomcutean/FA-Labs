/**
    Somcutean Alina-Ioana, Group 30424
    Union and Find takes O(n) in worst case. By implementing union by rank or height, their complexity will be improved to O(logn).
    For Kruskal algorithm, for sorting the edges I used insertion sort which will take at most O(n*n) in worst case.
    Then, for find the edges and unite them will take at most O(nrEdges * log nrVertices).
*/

#include <iostream>
#include <stdlib.h>
#include "Profiler.h"
Profiler profiler("Disjoint sets");

using namespace std;

struct Node
{
    int value, Rank;
    Node *parent;
};

struct Edge
{
    int weight, start, finish;
};

int nrResult;
int makeop = 0, findop = 0, unionop = 0;

void initializeOperation()
{
    makeop = 0;
    findop = 0;
    unionop = 0;
}

Node *makeSet(int value)
{
    Node *node = (Node*)malloc(sizeof(Node));
    node->parent = node;
    node->Rank = 0;
    node->value = value;
    makeop = makeop + 3;
    return node;
}

Node *findSet(Node *s)
{
    findop = findop + 2;
    if(s != s->parent)
    {
        s->parent = findSet(s->parent);
    }
    return s->parent;
}

void link(Node *s1, Node *s2)
{
    unionop++;
    if(s1->Rank > s2->Rank)
    {
        s2->parent = s1;
        unionop++;
    }
    else
    {
        unionop = unionop + 2;
        s1->parent = s2;
        if(s1->Rank == s2->Rank)
        {
            unionop++;
            s2->Rank = s2->Rank + 1;
        }
    }
}

void unite(Node *s1, Node *s2)
{
    link(findSet(s1), findSet(s2));
}

void sorting(Edge **edges, int nrEdges)
{
    Edge *buff;
    int i, j;
    for(i = 1; i < nrEdges; i++)
    {
        buff = edges[i];
        j = i - 1;
        while(buff->weight < edges[j]->weight && j >= 0)
        {
            edges[j+1] = edges[j];
            j--;
        }
        edges[j+1] = buff;
    }
}

Edge *createEdge(int start, int finish, int weight)
{
    Edge *edge = (Edge*)malloc(sizeof(Edge));
    edge->start = start;
    edge->finish = finish;
    edge->weight = weight;
    return edge;
}

Edge **kruskal(int nrVertices, int nrEdges, Edge **edge)
{
    Edge **result = (Edge**)malloc(nrEdges * sizeof(Edge*));
    nrResult = 0;

    Node **sets = (Node**)malloc(nrVertices * sizeof(Node*));

    for(int i = 0; i < nrVertices; i++)
    {
        sets[i] = makeSet(i);
    }

    sorting(edge, nrEdges);

    for(int i = 0; i < nrEdges; i++)
    {
        if(findSet(sets[edge[i]->start])->value != findSet(sets[edge[i]->finish])->value)
        {
            result[nrResult] = edge[i];
            nrResult++;
            unite(sets[edge[i]->start], sets[edge[i]->finish]);
        }
    }

    return result;
}

void test(int nr)
{
    Node **graph;
    graph = (Node**)malloc(nr * sizeof(Node*));

    for(int i = 0; i < nr; i++)
    {
        graph[i] = makeSet(i);
    }

    for(int i = 0; i < nr; i++)
    {
        cout << "Set: " << graph[i]->value << "\tHead:" << findSet(graph[i])->value << "\n";
    }

    unite(graph[1], graph[2]);
    unite(graph[0], graph[1]);
    unite(graph[3], graph[4]);
    unite(graph[6], graph[7]);
    unite(graph[7], graph[8]);
    cout << "\nAfter unite: \n";

    for(int i = 0; i < nr; i++)
    {
        cout << "Set: " << graph[i]->value << "\tHead:" << findSet(graph[i])->value << "\n";
    }
}

void testKruskal()
{
    int nrEdges = 7, nrVertices = 5;
    Edge **edge = (Edge**)malloc(nrEdges * sizeof(Edge*));
    Edge **result = (Edge**)malloc(nrEdges * sizeof(Edge*));

    edge[0] = createEdge(0,1,1);
    edge[1] = createEdge(0,3,3);
    edge[2] = createEdge(0,4,2);
    edge[3] = createEdge(1,2,4);
    edge[4] = createEdge(1,3,8);
    edge[5] = createEdge(2,3,5);
    edge[6] = createEdge(3,4,3);

    result = kruskal(nrVertices, nrEdges, edge);
    for(int i = 0; i < nrResult; i++)
    {
        cout << result[i]->start << " - " << result[i]->finish << " : " << result[i]->weight << "\n";
    }
}

Edge **generateEdges(int nrEdges, int nrVertices)
{
    int k = 0, i = 0, j = 0;
    int *start, *finish, *weights;
    Edge **edges = (Edge**)malloc(nrEdges * sizeof(Edge*));

    start = (int*)malloc(nrVertices * sizeof(int));
    finish = (int*)malloc(nrVertices * sizeof(int));
    weights = (int*)malloc(nrEdges * sizeof(int));

    FillRandomArray(start, nrVertices, 0, nrVertices-1, true, 0);
    FillRandomArray(finish, nrVertices, 0, nrVertices-1, true, 0);
    FillRandomArray(weights, nrEdges, 0, 100, false, 0);

    for(i = 0; i < nrVertices-1; i++)
    {
        for(j = i+1; j < nrVertices; j++)
        {
            if(start[i] != finish[j])
            {
                ///cout << k << ": " << start[i] << " " << finish[j] << "\n";
                edges[k] = createEdge(start[i], finish[j], weights[k]);
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
    return edges;
}

void average_case()
{
    int total;

    for(int i = 100; i <= 1000; i = i + 100)
    {
        nrResult = 0;
        initializeOperation();

        Edge **edges = (Edge**)malloc(4 * i * sizeof(Edge*));
        edges = generateEdges(4*i, i);

        Edge **result = (Edge**)malloc(4 * i * sizeof(Edge*));
        result = kruskal(i, 4*i, edges);

        total = makeop + findop + unionop;

        profiler.countOperation("Make operation", i, makeop);
        profiler.countOperation("Find operation", i, findop);
        profiler.countOperation("Union operation", i, unionop);
        profiler.countOperation("Total number of operations", i, total);
        free(edges);
    }

    profiler.createGroup("Total number of operations", "Total number of operations");
    profiler.createGroup("Disjoint Sets", "Make operation", "Union operation", "Find operation");
    profiler.showReport();
}

int main()
{
    test(10);
    cout << "\nKruskal:\n";
    testKruskal();
    ///average_case();
}
