/**

Somcutean Alina-Ioana, Groupe 30424

HeapSort:
    I implemented heapSort using bottom-up strategy and maxHeap. The complexity of this algorithm is O(n * lg n) in average case.

QuickSort:
    In average case, I implemented this algorithm choosing the pivot always as the last element and the complexity is O(n * lg n).
    In best case, I choose the pivot always as the middle of the array. In this case, the complexity is O(n * lg n)
    In worst case, I choose the pivot at the end of the array, when the array is sorted ascending, such that, the pivot is always the bigger number.
In this case, the complexity is O(n*n).

*/
#include <iostream>
#include "Profiler.h"
#define MAX_SIZE 2000

Profiler profiler("HeapSort and QuickSort");

using namespace std;

int sum_heapSort_comp = 0, sum_heapSort_assign = 0, sum_quickSort_assign = 0, sum_quickSort_comp = 0;
int length;

void heapify(int a[], int n, int i)
{
    int index, left, right;
    index = i;
    left = 2*i+1;
    right = 2*i+2;

    profiler.countOperation("HeapSort Comp", n);
    sum_heapSort_comp++;

    if(left < n && a[left] > a[index])
    {
        index = left;
    }

    profiler.countOperation("HeapSort Comp", n);
    sum_heapSort_comp++;

    if(right < n && a[right] > a[index])
    {
        index = right;
    }

    if(index != i)
    {
        profiler.countOperation("HeapSort Assign", n, 3);
        sum_heapSort_assign = sum_heapSort_assign + 3;

        swap(a[index], a[i]);
        heapify(a, n, index);
    }
}

void build_max_heap(int a[], int n)
{
    int i;
    for(i = n/2-1; i >= 0; i--)
    {
        heapify(a, n, i);
    }
}

void heapSort(int a[], int n)
{
    int i;
    int heap_size = n-1;
    build_max_heap(a, n);
    for(i = heap_size; i >= 0; i--)
    {
        profiler.countOperation("HeapSort Assign", n, 3);
        sum_heapSort_assign = sum_heapSort_assign + 3;

        swap(a[0], a[i]);
        heap_size--;
        heapify(a, heap_size, 0);
    }
}

int partition_quickSort(int a[], int start, int finish)
{
    int pivot = a[finish];

    profiler.countOperation("QuickSort Assign", length);
    sum_quickSort_assign++;

    int index = start-1;
    for(int i = start; i < finish; i++)
    {
        profiler.countOperation("QuickSort Comp", length);
        sum_quickSort_comp++;

        if(a[i] < pivot)
        {
            index++;

            profiler.countOperation("QuickSort Assign", length, 3);
            sum_quickSort_assign = sum_quickSort_assign + 3;

            swap(a[i], a[index]);
        }
    }

    profiler.countOperation("QuickSort Assign", length, 3);
    sum_quickSort_assign = sum_quickSort_assign + 3;

    swap(a[index+1], a[finish]);

    return index+1;
}

void quickSort(int a[], int start, int finish)
{
    int pos;
    if(start < finish)
    {
        pos = partition_quickSort(a, start, finish);
        quickSort(a, start, pos-1);
        quickSort(a, pos+1, finish);
    }
}

void quickSort_best(int a[], int start, int finish)
{
    int pivot, i, j;

    profiler.countOperation("QuickSort for Best Assign", length);
    pivot = a[(start+finish)/2];

    i = start;
    j = finish;

    while(i <= j)
    {
        profiler.countOperation("QuickSort for Best Comp", length);
        while(a[i] < pivot)
        {
            profiler.countOperation("QuickSort for Best Comp", length);
            i++;
        }

        profiler.countOperation("QuickSort for Best Comp", length);
        while(a[j] > pivot)
        {
            profiler.countOperation("QuickSort for Best Comp", length);
            j--;
        }

        if(i <= j)
        {
            profiler.countOperation("QuickSort for Best Assign", length, 3);
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }

    if(start < j)
        quickSort_best(a, start, j);

    if(i < finish)
        quickSort_best(a, i, finish);
}

void print_array(int a[], int n)
{
    for(int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << "\n";
}

void test()
{
    int a[10] = {4,6,1,0,12,5,8,-2,100,7};
    int b[10] = {4,6,1,0,12,5,8,-2,100,7};
    int c[10] = {4,6,1,0,12,5,8,-2,100,7};

    cout << "Initial array: ";
    print_array(a, 10);

    heapSort(a, 10);
    cout << "HeapSort: ";
    print_array(a, 10);

    quickSort(b, 0, 9);
    cout << "QuickSort, pivot at the end: ";
    print_array(b, 10);

    quickSort_best(c, 0, 9);
    cout << "QuickSort, pivot in middle: ";
    print_array(c, 10);
}

void worst_case_quickSort()
{
    int a[MAX_SIZE];
    FillRandomArray(a, MAX_SIZE, 10, 50000, false, 1);
    for(int i = 100; i < MAX_SIZE; i = i+100)
    {
        length = i;
        quickSort(a, 0, i-1);
    }
    profiler.addSeries("QuickSort total operations", "QuickSort Assign", "QuickSort Comp");
    profiler.createGroup("Worst case", "QuickSort Assign", "QuickSort Comp", "QuickSort total operations");
    profiler.showReport();
}

void best_case_quickSort()
{
    int a[MAX_SIZE];
    FillRandomArray(a, MAX_SIZE, 10, 50000, false, 1);
    for(int i = 100; i < MAX_SIZE; i = i+100)
    {
        length = i;
        quickSort_best(a, 0, i-1);
    }
    profiler.addSeries("QuickSort total operations for Best", "QuickSort for Best Assign", "QuickSort for Best Comp");
    profiler.createGroup("Best case for QuickSort", "QuickSort for Best Assign", "QuickSort for Best Comp", "QuickSort total operations for Best");
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
            heapSort(b, i);
            CopyArray(b, a, i);
            quickSort(b, 0, i-1);
        }

        sum_heapSort_assign = sum_heapSort_assign/5;
        sum_heapSort_comp = sum_heapSort_comp/5;
        sum_quickSort_assign = sum_quickSort_assign/5;
        sum_quickSort_comp = sum_quickSort_comp/5;

        profiler.countOperation("Average HeapSort Assign", i, sum_heapSort_assign);
        profiler.countOperation("Average HeapSort Comp", i, sum_heapSort_comp);
        profiler.countOperation("Average QuickSort Assign", i, sum_quickSort_assign);
        profiler.countOperation("Average QuickSort Comp", i, sum_quickSort_comp);
    }
    profiler.addSeries("Average HeapSort total operations", "Average HeapSort Assign", "Average HeapSort Comp");
    profiler.addSeries("Average QuickSort total operations", "Average QuickSort Assign", "Average QuickSort Comp");
    profiler.createGroup("Average case comp", "Average HeapSort Comp", "Average QuickSort Comp");
    profiler.createGroup("Average case assignments", "Average HeapSort Assign", "Average QuickSort Assign");
    profiler.createGroup("Average case total operations", "Average HeapSort total operations", "Average QuickSort total operations");
    profiler.showReport();
}

int partition_random(int a[], int start, int finish)
{
    int pivot_pos = start + rand() % (finish - start + 1);
    int pivot = a[pivot_pos];

    swap(a[pivot_pos], a[finish]);
    int index = start - 1;

    for(int i = start; i < finish; i++)
    {
        if(a[i] < pivot)
        {
            index++;
            swap(a[index], a[i]);
        }
    }

    swap(a[index+1], a[finish]);
    return index+1;
}

int quick_select(int a[], int k, int start, int finish)
{
    if(start == finish)
        return a[start];
    int pos;
    pos = partition_random(a, start, finish);
    int relative_pos = pos-start+1;

    if(k > 0 && relative_pos == k)
        return a[pos];
    else
    {
        if(relative_pos > k)
            return quick_select(a, k, start, pos-1);
        else
            return quick_select(a, k-relative_pos, pos+1, finish);
    }
}

void test_quickSelect()
{
    int a[10] = {4,6,1,0,12,5,8,-2,100,7};
    cout << "\nThe array is: ";
    print_array(a, 10);
    cout << "Al 5-lea cel mai mic element este " << quick_select(a, 5, 0, 9) << "\n";
}

int main()
{
    test();
    test_quickSelect();
    ///profiler.reset("Average case");
    ///average_case();
    ///profiler.reset("QuickSort Worst case");
    ///worst_case_quickSort();
    profiler.reset("QuickSort Best case");
    best_case_quickSort();
    return 0;
}
