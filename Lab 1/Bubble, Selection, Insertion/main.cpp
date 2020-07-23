/**
Șomcutean Alina-Ioana, Groupe 30424

Best case:
    For Bubble Sort, the complexity of the algorithm is O(n*n) for comparators and in this case, this algorithm do not make any assignments;
    for Selection Sort, the complexity is O(n) for assignments and O(n*n) for comparators;
    for Insertion Sort, the complexity is O(n) for for both.
    As a total of operations, in this case, Bubble Sort works better as we can see in the graphs.

Worst case:
    For Bubble Sort, the complexity of the algorithm is again O(n*n) for comparators and also for assignments;
    for Selection Sort, the complexity is the same as in the best case;
    for Insertion Sort, the complexity is O(n*n) for comparators and for assignment.
    As a conclusion, Selection Sort is better in case of assignments, but Insertion Sort is better for comparators.
    So, as a conclusion, also Selection and Insertion works properly for this case, as it can be seen in the graphs.

Average case:
    For all 3 algorithms, the complexity is O(n*n).
    If we are looking at the graph, Selection Sort makes fewest assignments, but Insertion Sort makes fewest comparators.
    As a conclusion, in average case, Insertion Sort works the best.
*/

#include <iostream>
#include "Profiler.h"
#define MAX_SIZE 2000

Profiler profiler("Best");

int sumBubbleComp = 0, sumBubbleAssign = 0, sumInsertionComp = 0, sumInsertionAssign = 0, sumSelectionComp = 0, sumSelectionAssign = 0;
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
            profiler.countOperation("Bubble Comparisons", n, 1);
            if(a[i] > a[i+1])
            {
                sumBubbleAssign = sumBubbleAssign + 3;
                profiler.countOperation("Bubble Assignments", n, 3);
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
        sumInsertionAssign = sumInsertionAssign + 1;
        profiler.countOperation("Insertion Assignments", n, 1);
        buff = a[i];
        j = i-1;
        sumInsertionAssign = sumInsertionAssign + 1;
        profiler.countOperation("Insertion Comparisons", n, 1);
        while(buff < a[j] && j >= 0)
        {
            sumInsertionAssign = sumInsertionAssign + 1;
            profiler.countOperation("Insertion Assignments", n, 1);
            a[j+1] = a[j];
            j--;
        }
        sumInsertionComp = sumInsertionComp + 1;
        profiler.countOperation("Insertion Comparisons", n, 1);
        sumInsertionAssign = sumInsertionAssign + 1;
        profiler.countOperation("Insertion Assignments", n, 1);
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
            profiler.countOperation("Selection Comparisons", n, 1);
            if(a[j] < a[aux])
                aux = j;
        }
        sumSelectionAssign = sumSelectionAssign + 3;
        profiler.countOperation("Selection Assignments", n, 3);
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
    profiler.createGroup("Best case comparisons", "Bubble Comparisons", "Insertion Comparisons", "Selection Comparisons");
    profiler.createGroup("Bubble Comparisons", "Bubble Comparisons");
    profiler.createGroup("Best case assignments", "Insertion Assignments", "Selection Assignments");
    profiler.createGroup("Bubble Assignments", "Bubble Assignments");
    ///profiler.addSeries("Bubble", "Bubble Comparisons");
    profiler.addSeries("Insertion", "Insertion Comparisons", "Insertion Assignments");
    profiler.addSeries("Selection", "Selection Comparisons", "Selection Assignments");
    profiler.createGroup("Best case total operations", "Bubble Comparisons", "Insertion", "Selection");
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
    profiler.createGroup("Worst case comparisons", "Bubble Comparisons", "Insertion Comparisons", "Selection Comparisons");
    profiler.createGroup("Worst case assignments", "Bubble Assignments", "Insertion Assignments", "Selection Assignments");
    profiler.addSeries("Bubble", "Bubble Comparisons", "Bubble Assignments");
    profiler.addSeries("Insertion", "Insertion Comparisons", "Insertion Assignments");
    profiler.addSeries("Selection", "Selection Comparisons", "Selection Assignments");
    profiler.createGroup("Worst case total operations", "Bubble", "Insertion", "Selection");
    profiler.createGroup("Worst case total operations Insertion", "Insertion");
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
            FillRandomArray(a, MAX_SIZE, 10, 50000, false, 0);
            CopyArray(b, a, MAX_SIZE);
            bubble_sort(b, i);
            CopyArray(b, a, MAX_SIZE);
            insertion_sort(b, i);
            CopyArray(b, a, MAX_SIZE);
            selection_sort(b, i);
        }
        sumBubbleAssign = sumBubbleAssign/5;
        sumBubbleComp = sumBubbleComp/5;
        sumInsertionAssign = sumInsertionAssign/5;
        sumInsertionComp = sumInsertionComp/5;
        sumSelectionAssign = sumSelectionAssign/5;
        sumSelectionComp = sumSelectionComp/5;
        profiler.countOperation("Average Bubble Comp", i, sumBubbleComp);
        profiler.countOperation("Average Bubble Assignments", i, sumBubbleAssign);
        profiler.countOperation("Average Insertion Comp", i, sumInsertionComp);
        profiler.countOperation("Average Insertion Assignments", i, sumInsertionAssign);
        profiler.countOperation("Average Selection Comp", i, sumSelectionComp);
        profiler.countOperation("Average Selection Assignments", i, sumSelectionAssign);
    }
    profiler.addSeries("Bubble", "Average Bubble Comp", "Average Bubble Assignments");
    profiler.addSeries("Insertion", "Average Insertion Comp", "Average Insertion Assignments");
    profiler.addSeries("Selection", "Average Selection Comp", "Average Selection Assignments");
    profiler.createGroup("Average case comp", "Average Bubble Comp", "Average Insertion Comp", "Average Selection Comp");
    profiler.createGroup("Average case assignments", "Average Bubble Assignments", "Average Insertion Assignments", "Average Selection Assignments");
    profiler.createGroup("Average case total operations", "Bubble", "Insertion", "Selection");
    profiler.showReport();
}

int main()
{
    test();
    //profiler.reset("Best case");
    ///best_case();
    ///profiler.reset("Worst case");
    ///worst_case();
    ///profiler.reset("Average case");
    ///average_case();
    return 0;
}
