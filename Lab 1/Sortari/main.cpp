#include <iostream>
#include "Profiler.h"
#define MAX_SIZE 2000

Profiler profiler("Best");

int sumBubbleComp = 0, sumBubbleAssig = 0, sumInsertionComp = 0, sumInsertionAssig = 0, sumSelectionComp = 0, sumSelectionAssig = 0;
int totalBubble = 0, totalInsertion = 0, totalSelection = 0;

using namespace std;

void bubble_sort(int a[], int n)
{
    int i;
    bool swaped = true;
    while(swaped)
    {
        swaped = false;
        for(i = 0; i < n-1; i++)
        {
            sumBubbleComp = sumBubbleComp + 1;
            profiler.countOperation("BubbleComp", n, 1);
            if(a[i] > a[i+1])
            {
                sumBubbleAssig = sumBubbleAssig + 3;
                profiler.countOperation("BubbleAssig", n, 3);
                swap(a[i], a[i+1]);
                swaped = true;
            }
        }
    }
}

void insertion_sort(int a[], int n)
{
    int i, j, buff;
    for(i = 1; i < n; i++)
    {
        sumInsertionAssig = sumInsertionAssig + 1;
        profiler.countOperation("InsertionAssig", n, 1);
        buff = a[i];
        j = i-1;
        sumInsertionAssig = sumInsertionAssig + 1;
        profiler.countOperation("InsertionComp", n, 1);
        while(buff < a[j] && j >= 0)
        {
            sumInsertionAssig = sumInsertionAssig + 1;
            profiler.countOperation("InsertionAssig", n, 1);
            a[j+1] = a[j];
            j--;
        }
        sumInsertionComp = sumInsertionComp + 1;
        profiler.countOperation("InsertionComp", n, 1);
        sumInsertionAssig = sumInsertionAssig + 1;
        profiler.countOperation("InsertionAssig", n, 1);
        a[j+1] = buff;
    }
}

void selection_sort(int a[], int n)
{
    int i, j, aux;
    for(i = 0; i < n-1; i++)
    {
        aux = i;
        for(j = i+1; j < n; j++)
        {
            sumSelectionComp = sumSelectionComp + 1;
            profiler.countOperation("SelectionComp", n, 1);
            if(a[j] < a[aux])
                aux = j;
        }
        sumSelectionAssig = sumSelectionAssig + 3;
        profiler.countOperation("SelectionAssig", n, 3);
        swap(a[i], a[aux]);
    }
}

void test()
{
    int a[10] = {1, 0, 4, 2, -1, 8, 20, -3, 6, 0};
    int b[10];
    cout << "Unsorted: ";
    for(int i = 0; i < 10; i++)
    {
        cout << a[i] << " ";
    }
    cout << "\n";
    CopyArray(b, a, 10);
    for(int i = 0; i < 10; i++)
    {
        cout << b[i] << " ";
    }
    cout << "\n";
    bubble_sort(b, 10);
    cout << "Bubble Sort: ";
    for(int i = 0; i < 10; i++)
    {
        cout << b[i] << " ";
    }
    cout << "\n";
    CopyArray(b, a, 10);
    insertion_sort(b, 10);
    cout << "Insertion Sort: ";
    for(int i = 0; i < 10; i++)
    {
        cout << b[i] << " ";
    }
    cout << "\n";
    CopyArray(b, a, 10);
    selection_sort(b, 10);
    cout << "Selection Sort: ";
    for(int i = 0; i < 10; i++)
    {
        cout << b[i] << " ";
    }
    cout << "\n";
}

void best_case()
{
    int a[MAX_SIZE], b[MAX_SIZE];
    int i;
    FillRandomArray(a, MAX_SIZE, 10, 50000, false, 1);
    for(i = 100; i < MAX_SIZE; i = i+100)
    {
        CopyArray(b, a, MAX_SIZE);
        bubble_sort(b, i);
        CopyArray(b, a, MAX_SIZE);
        insertion_sort(b, i);
        CopyArray(b, a, MAX_SIZE);
        selection_sort(b, i);
    }
    profiler.createGroup("Best case comp", "BubbleComp", "InsertionComp", "SelectionComp");
    profiler.createGroup("Best case assig", "BubbleAssig", "InsertionAssig", "SelectionAssig");
    profiler.createGroup("BubbleComp", "BubbleComp");
    profiler.createGroup("BubbleAssig", "BubbleAssig");
    profiler.addSeries("Bubble", "BubbleComp", "BubbleAssig");
    profiler.addSeries("Insertion", "InsertionComp", "InsertionAssig");
    profiler.addSeries("Selection", "SelectionComp", "SelectionAssig");
    profiler.createGroup("Best case total operations", "Bubble", "Insertion", "Selection");
    profiler.showReport();
}

void worst_case()
{
    int a[MAX_SIZE], b[MAX_SIZE];
    int i;
    FillRandomArray(a, MAX_SIZE, 10, 50000, false, 2);
    for(i = 100; i < MAX_SIZE; i = i+100)
    {
        CopyArray(b, a, MAX_SIZE);
        bubble_sort(b, i);
        CopyArray(b, a, MAX_SIZE);
        insertion_sort(b, i);
        CopyArray(b, a, MAX_SIZE);
        selection_sort(b, i);
    }
    profiler.createGroup("Worst case comp", "BubbleComp", "InsertionComp", "SelectionComp");
    profiler.createGroup("Worst case assig", "BubbleAssig", "InsertionAssig", "SelectionAssig");
    profiler.addSeries("Bubble", "BubbleComp", "BubbleAssig");
    profiler.addSeries("Insertion", "InsertionComp", "InsertionAssig");
    profiler.addSeries("Selection", "SelectionComp", "SelectionAssig");
    profiler.createGroup("Worst case total operations", "Bubble", "Insertion", "Selection");
    profiler.createGroup("Worst case total operations Insertion", "Insertion");
    profiler.showReport();
}

void average_case()
{
    int a[MAX_SIZE], b[MAX_SIZE];
    int i, j;
    ///FillRandomArray(a, MAX_SIZE, 10, 50000, false, 0);
    for(i = 100; i < MAX_SIZE; i = i+100)
    {
        for(j = 1; j <= 5; j++)
        {
            FillRandomArray(a, MAX_SIZE, 10, 50000, false, 0);
            CopyArray(b, a, MAX_SIZE);
            bubble_sort(b, i);
            CopyArray(b, a, MAX_SIZE);
            insertion_sort(b, i);
            CopyArray(b, a, MAX_SIZE);
            selection_sort(b, i);
        }
        sumBubbleAssig = sumBubbleAssig/5;
        sumBubbleComp = sumBubbleComp/5;
        sumInsertionAssig = sumInsertionAssig/5;
        sumInsertionComp = sumInsertionComp/5;
        sumSelectionAssig= sumSelectionAssig/5;
        sumSelectionComp = sumSelectionComp/5;
        profiler.countOperation("Average Bubble Comp", i, sumBubbleComp);
        profiler.countOperation("Average Bubble Assig", i, sumBubbleAssig);
        profiler.countOperation("Average Insertion Comp", i, sumInsertionComp);
        profiler.countOperation("Average Insertion Assig", i, sumInsertionAssig);
        profiler.countOperation("Average Selection Comp", i, sumSelectionComp);
        profiler.countOperation("Average Selection Assig", i, sumSelectionAssig);
    }
    profiler.createGroup("Average case comp", "Average Bubble Comp", "Average Insertion Comp", "Average Selection Comp");
    profiler.createGroup("Average case assig", "Average Bubble Assig", "Average Insertion Assig", "Average Selection Assig");
    profiler.addSeries("Bubble", "Average Bubble Comp", "Average Bubble Assig");
    profiler.addSeries("Insertion", "Average Insertion Comp", "Average Insertion Assig");
    profiler.addSeries("Selection", "Average Selection Comp", "Average Selection Assig");
    profiler.createGroup("Average case total operations", "Bubble", "Insertion", "Selection");
    profiler.showReport();
}

int main()
{
    ///test();
    ///profiler.reset("Best case");
    ///best_case();
    ///profiler.reset("Worst case");
    ///worst_case();
    //profiler.reset("Average case");
    //average_case();
    return 0;
}
