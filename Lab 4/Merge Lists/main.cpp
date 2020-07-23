/**
    The complexity of the algorithm is O(*log(k))
    When n is fixed, the complexity of the algorithm is O(log k )
    When k is fixed, the complexity of the algorithm is O(n)
*/
#include <iostream>
#include "Profiler.h"
#define MAX_SIZE 10000

Profiler profiler("Average for merge k lists");

using namespace std;

typedef struct Node
{
    int data;
    Node *next;
};

typedef struct List
{
    int length;
    Node *first;
    Node *last;
};

typedef struct element
{
    int data;
    int l;
};

List *rezult;
List **listPtr[500];
int heapsize;
element heap[MAX_SIZE], item;

int assign_k5, comp_k5, assign_k10, comp_k10, assign_k100, comp_k100;

Node *create_node(int data)
{
    Node *node = (Node*)malloc(sizeof(Node));
    if(node)
    {
        node->data = data;
        node->next = NULL;
    }
    return node;
}

void init_list(List **listPtr)
{
    (*listPtr) = (List*)malloc(sizeof(List));
    (*listPtr)->first = (*listPtr)->last = NULL;
    (*listPtr)->length = 0;
}

void print_list(List *listPtr)
{
    Node *current = listPtr->first;
    if(current == NULL)
    {
        cout << "None.";
    }
    else
    {
        while(current != NULL)
        {
            cout << current->data << " ";
            current = current->next;
        }
    }
    cout << "\n";
}

void insert_node(List **listPtr, int data)
{
    Node *node = create_node(data);

    comp_k5++;
    comp_k10++;
    comp_k100++;

    if((*listPtr)->last != 0)
    {
        (*listPtr)->last->next = node;
        (*listPtr)->last = node;
    }
    else
    {
        (*listPtr)->first = node;
        (*listPtr)->last = node;
    }
    (*listPtr)->length++;
}

void delete_node(List **listPtr)
{
    Node *node = (Node*)malloc(sizeof(Node));

    comp_k5++;
    comp_k10++;
    comp_k100++;

    if((*listPtr)->first != NULL)
    {
        node = (*listPtr)->first;
        (*listPtr)->first = (*listPtr)->first->next;
        free(node);

        comp_k5++;
        comp_k10++;
        comp_k100++;

        if((*listPtr)->first == NULL)
        {
            (*listPtr)->last = NULL;
        }
        (*listPtr)->length--;
    }
}

List *generate_list(int length)
{
    int a[length];
    FillRandomArray(a, length, 10, 50000, false, 1);

    List *listPtr;
    init_list(&listPtr);

    for(int i = 0; i < length; i++)
    {
        insert_node(&listPtr, a[i]);
    }
    return listPtr;
}

List **generate_vector_lists(int k, int n)
{
    int length;
    List **listPtr;

    listPtr = (List**)malloc(k*sizeof(List));

    for(int i = 0; i < k; i++)
    {
        length = n/k;
        if(i < n%k)
        {
            length++;
        }
        listPtr[i] = generate_list(length);
        cout << "List " << i << ": ";
        print_list(listPtr[i]);
    }
    return listPtr;
}

void heapify_min(element a[], int length, int i)
{
    int index, left, right;
    index = i;
    left = 2*i + 1;
    right = 2*i + 2;

    if(left < length && a[left].data < a[index].data)
    {
        comp_k5++;
        comp_k10++;
        comp_k100++;
        index = left;
    }

    if(right < length && a[right].data < a[index].data)
    {
        comp_k5++;
        comp_k10++;
        comp_k100++;
        index = right;
    }

    if(index != i)
    {
        comp_k5++;
        comp_k10++;
        comp_k100++;
        assign_k5 = assign_k5 + 3;
        assign_k10 = assign_k10 + 3;
        assign_k100 = assign_k100 + 3;

        swap(a[index], a[i]);
        heapify_min(a, length, index);
    }
}

void build_heap(element a[], int length)
{
    for(int i = length/2 -1; i >= 0; i--)
    {
        heapify_min(a, length, i);
    }
}

void insert_heap(element heap[], int &heapsize, element item)
{
    heapsize++;
    heap[heapsize-1] = item;

    assign_k5++;
    assign_k10++;
    assign_k100++;

    build_heap(heap, heapsize);
}

element delete_min_heap(element heap[], int &heapsize)
{
    element item;
    if(heapsize > 0)
    {
        item = heap[0];
        heap[0] = heap[heapsize-1];

        assign_k5 = assign_k5 + 2;
        assign_k10 = assign_k10 + 2;
        assign_k100 = assign_k100 + 2;

        heapsize--;
        heapify_min(heap, heapsize, 0);
    }
    return item;
}

void merge_lists(int k, int n)
{
    List **listPtr = generate_vector_lists(k, n);
    heapsize = 0;

    rezult = (List*)malloc(sizeof(List));
    init_list(&rezult);

    for(int i = 0; i < k; i++)
    {
        if(listPtr[i]->first != 0)
        {
            item.data = listPtr[i]->first->data;
            item.l = i;
            insert_heap(heap, heapsize, item);
        }
    }

    while(heapsize != 0)
    {
        item = delete_min_heap(heap, heapsize);
        insert_node(&rezult, item.data);
        delete_node(&listPtr[item.l]);
        if(listPtr[item.l]->first != 0)
        {
            item.data = listPtr[item.l]->first->data;
            insert_heap(heap, heapsize, item);
        }
    }
    print_list(rezult);
}

void test()
{
    int n, k;
    cout << "Write the nr of lists: ";
    cin >> k;
    cout << "Write the nr of elements: ";
    cin >> n;
    merge_lists(k, n);
}

void init_variable()
{
    assign_k5 = 0;
    comp_k5 = 0;
    assign_k10 = 0;
    comp_k10 = 0;
    assign_k100 = 0;
    comp_k100 = 0;
}

void graph_for_k5()
{
    int k = 5, n;
    for(n = 100; n < MAX_SIZE; n = n + 100)
    {
        init_variable();
        merge_lists(k, n);
        profiler.countOperation("Assignments for k = 5", n, assign_k5);
        profiler.countOperation("Comparations for k = 5", n, comp_k5);
    }
    profiler.addSeries("Total operations for k = 5", "Assignments for k = 5", "Comparations for k = 5");
}

void graph_for_k10()
{
    int k = 10, n;
    for(n = 100; n < MAX_SIZE; n = n + 100)
    {
        init_variable();
        merge_lists(k, n);
        profiler.countOperation("Assignments for k = 10", n, assign_k10);
        profiler.countOperation("Comparations for k = 10", n, comp_k10);
    }
    profiler.addSeries("Total operations for k = 10", "Assignments for k = 10", "Comparations for k = 10");
}

void graph_for_k100()
{
    int k = 100, n;
    init_variable();
    for(n = 100; n < MAX_SIZE; n = n + 100)
    {
        init_variable();
        merge_lists(k, n);
        profiler.countOperation("Assignments for k = 100", n, assign_k100);
        profiler.countOperation("Comparations for k = 100", n, comp_k100);
    }
    profiler.addSeries("Total operations for k = 100", "Assignments for k = 100", "Comparations for k = 100");
}

void graph_for_k()
{
    graph_for_k5();
    graph_for_k10();
    graph_for_k100();
    profiler.createGroup("Total operations for k = 5 / 10 / 100", "Total operations for k = 5", "Total operations for k = 10", "Total operations for k = 100");
    profiler.showReport();
}

void graph_for_constant_n()
{
    int n = MAX_SIZE;
    int k;
    for(k = 10; k < 500; k = k +10)
    {
        init_variable();
        merge_lists(k, n);
        profiler.countOperation("Assignments for constant n", k, assign_k100);
        profiler.countOperation("Comparations for constant n", k, comp_k100);
    }
    profiler.addSeries("Total operations for constant n", "Assignments for constant n", "Comparations for constant n");
    profiler.showReport();
}

int main()
{
    test();
    ///graph_for_k();
    ///graph_for_constant_n();
    return 0;
}
