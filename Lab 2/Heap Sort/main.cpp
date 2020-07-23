/**
Somcutean Alina-Ioana, Groupe 30424

Best case:
    It is when the given array is already a heap. We can obtain this case, for a max heap, when the array is order descending.
    In case of the bottom up strategy, for best case, the algorithm would do the same no of comparisons, but no assignment.

Average case:
    For bottom up strategy, the complexity of the algorithm is O(n).
    For top down strategy, the complexity of the algorithm is O(n * lg n ).
    As we can see from the graph, the bottom up strategy has less operations. Even if this strategy has much less assignments than top down strategy, it has also the no of
comparisons almost the same with no of comparisons in the second strategy.

Worst case:
    In case of the bottom up strategy, the worst case is when the last level of the tree is exactly half full.
*/

#include <iostream>
#include <math.h>
#include "Profiler.h"

#define MAX_SIZE 2000

Profiler profiler("Build Heap");

using namespace std;

int sum_Bottom_Up_Comp = 0, sum_Bottom_Up_Assign = 0, sum_Top_Down_Comp = 0, sum_Top_Down_Assign = 0;

void heapify(int a[], int n, int i)
{
    int index, left, right;

    index = i;
    left = 2*i+1;
    right = 2*i+2;

    profiler.countOperation("Bottom Up Comp", n);
    sum_Bottom_Up_Comp++;

    if(a[left] > a[index] && left < n)
    {
        index = left;
    }

    sum_Bottom_Up_Comp++;
    profiler.countOperation("Bottom Up Comp", n);
    if(a[right] > a[index] && right < n)
        index = right;

    if(index != i)
    {
        sum_Bottom_Up_Assign = sum_Bottom_Up_Assign + 3;
        profiler.countOperation("Bottom Up Assign", n, 3);
        swap(a[index], a[i]);
        heapify(a, n, index);
    }
}

void build_heap_bottom_up(int a[], int n)
{
    int i;
    for(i = n/2-1; i >= 0; i--)
    {
        heapify(a, n, i);
    }
}

void increase_key(int a[], int n, int key)
{
    profiler.countOperation("Top Down Assign", n);
    sum_Top_Down_Assign++;

    a[n] = key;

    while(n > 0 && a[n/2] < a[n])
    {
        profiler.countOperation("Top Down Comp", n);
        sum_Top_Down_Comp++;
        profiler.countOperation("Top Down Assign", n, 3);
        sum_Top_Down_Assign = sum_Top_Down_Assign + 3;

        swap(a[n], a[n/2]);
        n = n/2;
    }
    profiler.countOperation("Top Down Comp", n);
    sum_Top_Down_Comp++;
}

void insert_key(int a[], int n, int key)
{
    profiler.countOperation("Top Down Assign", n);
    sum_Top_Down_Assign++;

    a[n] = INT_MIN;
    increase_key(a, n, key);
}

void build_heap_top_down(int a[], int n)
{
    int i, heap_size = 0;
    for(i = 1; i < n; i++)
    {
        heap_size++;
        insert_key(a, heap_size, a[i]);
    }
}

void test()
{
    int a[10] = {4,1,3,2,16,9,10,14,8,7};
    int b[10] = {4,1,3,2,16,9,10,14,8,7};

    cout << "Initial array: ";
    for(int i = 0; i < 10; i++)
        cout << a[i] << " ";
    cout << "\n";

    cout << "Bottom Up: ";
    build_heap_bottom_up(a, 10);
    for(int i = 0; i < 10; i++)
        cout << a[i] << " ";
    cout << "\n";

    cout << "Top Down: ";
    build_heap_top_down(b, 10);
    for(int i = 0; i < 10; i++)
        cout << b[i] << " ";
}

void worst_case()
{
    int a[MAX_SIZE], b[MAX_SIZE], nr_of_levels, nodes;
    for(int i = 100; i < MAX_SIZE; i = i+100)
    {
        nr_of_levels = log(i)/log(2);
        nodes = pow(2, nr_of_levels) - pow(2, nr_of_levels-2);
        FillRandomArray(a, nodes, 10, 50000, false, 0);
        CopyArray(b, a, i);
        build_heap_bottom_up(b, nodes);
        ///CopyArray(b, a, i);
        ///build_heap_top_down(b, nodes);
    }
    profiler.addSeries("Bottom Up Operations", "Bottom Up Comp", "Bottom Up Assign");
    ///profiler.addSeries("Top Down Operations", "Top Down Comp", "Top Down Assign");
    profiler.createGroup("Worst case bottom up", "Bottom Up Comp", "Bottom Up Assign", "Bottom Up Operations");
    ///profiler.createGroup("Worst case comp", "Bottom Up Comp", "Top Down Comp");
    ///profiler.createGroup("Worst case assign", "Bottom Up Assign", "Top Down Assign");
    ///profiler.createGroup("Worst case total operations", "Bottom Up Operations", "Top Down Operations");
    profiler.showReport();
}

void average_case()
{
    int a[MAX_SIZE], b[MAX_SIZE];
    int i, j;
    for(i = 100; i < MAX_SIZE; i = i+100)
    {
        for(j = 1; j <= 5; j++)
        {
            FillRandomArray(a, i, 10, 50000, false, 0);
            CopyArray(b, a, i);
            build_heap_bottom_up(b, i);
            CopyArray(b, a, i);
            build_heap_top_down(b, i);
        }
        sum_Bottom_Up_Assign = sum_Bottom_Up_Assign/5;
        sum_Bottom_Up_Comp = sum_Bottom_Up_Comp/5;
        sum_Top_Down_Assign = sum_Top_Down_Assign/5;
        sum_Top_Down_Comp = sum_Top_Down_Comp/5;
        profiler.countOperation("Average Bottom Up Assign", i, sum_Bottom_Up_Assign);
        profiler.countOperation("Average Bottom Up Comp", i, sum_Bottom_Up_Comp);
        profiler.countOperation("Average Top Down Assign", i, sum_Top_Down_Assign);
        profiler.countOperation("Average Top Down Comp", i, sum_Top_Down_Comp);
    }
    profiler.addSeries("Bottom Up Operations", "Average Bottom Up Comp", "Average Bottom Up Assign");
    profiler.addSeries("Top Down Operations", "Average Top Down Comp", "Average Top Down Assign");
    profiler.createGroup("Average case comp", "Average Bottom Up Comp", "Average Top Down Comp");
    profiler.createGroup("Average case assign", "Average Bottom Up Assign", "Average Top Down Assign");
    profiler.createGroup("Average case total operations", "Bottom Up Operations", "Top Down Operations");
    profiler.showReport();
}

int main()
{
    test();
    ///profiler.reset("Average case");
    ///average_case();
    ///profiler.reset("Worst case bottom up");
    ///worst_case();
    return 0;
}
