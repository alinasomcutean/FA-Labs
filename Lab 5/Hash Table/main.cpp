/**
Somcutean Alina-Ioana, Group: 30424
    In an unsuccessful search, the expected of probes is at most 1/(1-alfa)
    Inserting an element into an open-adress hash table with load factor alfa requires at most 1/(1-alfa) probes on average
    In a successful search, the expected of probes is at most (1/alfa)*ln(1/(1-alfa))
    The complexity of the algorithm is O(1)
*/
#include <iostream>
#include "Profiler.h"
#define N 9973

using namespace std;

int found = 0, not_found = 0;

int hash_function(int key, int i, int dimension)
{
    int h, f;
    h = key + i + i*i;
    f = h % dimension;
    return f;
}

int hash_insert(int T[], int key, int dimension)
{
    int i = 0, j;
    do
    {
        j = hash_function(key, i, dimension);
        if(T[j] == key)
        {
            return j;
        }
        else
        {
            if(T[j] == 0)
            {
                T[j] = key;
                return j;
            }
            else
            {
                i++;
            }
        }
    }
    while(i <= dimension);
    return -1;
}

void init_hash(int T[], int dimension)
{
    for(int i = 0; i < dimension; i++)
    {
        T[i] = 0;
    }
}

int hash_search(int T[], int key, int dimension)
{
    int i = 0, j;
    do
    {
        j = hash_function(key, i, dimension);
        found++;
        not_found++;
        if(T[j] == key)
        {
            return 1;
        }
        i++;
    }
    while(T[j] != 0 && i != dimension);
    return -1;
}

void test()
{
    int T[20], v[15];
    FillRandomArray(v, 15, 1, 20, false, 0);
    init_hash(T, 20);
    for(int i = 0; i < 15; i++)
    {
        cout << v[i] << " ";
    }
    cout << "\n";

    for(int i = 0; i < 15; i++)
    {
        hash_insert(T, v[i], 20);
    }

    for(int i = 0; i < 20; i++)
    {
        cout << T[i] << " ";
    }
    cout << "\n";

    int c;
    cout << "\nWrite the nr you want to search: ";
    cin >> c;
    cout << "\n";

    if(hash_search(T, c, 20) == 1)
    {
        cout << "Nr. found";
    }
    else
    {
        cout << "Nr not found";
    }
}

void test_2()
{
    int T[10], v[9] = {2, 5, 8, 2, 1, 7, 4, 10, 12};
    init_hash(T, 10);

    for(int i = 0; i < 9; i++)
    {
        cout << v[i] << " ";
    }
    cout << "\n";

    for(int i = 0; i < 9; i++)
    {
        hash_insert(T, v[i], 10);
    }

    for(int i = 0; i < 10; i++)
    {
        cout << T[i] << " ";
    }
    cout << "\n";

    cout << "Search for nr 8: ";
    if(hash_search(T, 8, 10) == 1)
    {
        cout << "Nr. found";
    }
    else
    {
        cout << "Nr. not found";
    }

    cout <<"\nSearch for nr 3: ";
    if(hash_search(T, 3, 5) == 1)
    {
        cout << "Nr. found";
    }
    else
    {
        cout << "Nr. not found";
    }

    cout << "\nSearch for nr 2: ";
    if(hash_search(T, 2, 10) == 1)
    {
        cout << "Nr. found";
    }
    else
    {
        cout << "Nr. not found";
    }
}

void average()
{
    cout << "Filling factor\t Average Effort found\t Max Effort found\t Average Effort not found\t Max Effort not found";
    float alfa[6] = {0.8, 0.85, 0.9, 0.95, 0.99};
    int max_effort_found = 0;
    int max_effort_not_found = 0;
    float average_effort_found = 0, average_effort_not_found = 0;
    int found_1, found_2;
    for(int index = 0; index < 5; index++)
    {
        for(int i = 0; i < 5; i++)
        {
            int n = alfa[i]*N;
            int T[N];
            init_hash(T, N);
            int vect[n];

            FillRandomArray(vect, 1500, 1, 3000, true, 0);

            int arr[n];
            FillRandomArray(arr, n, 3000, 20000, true, 0);

            for(int j = 0; j < 1500; j++)
            {
                hash_insert(T,vect[j],n);
            }

            for(int j = 1500; j < n; j++)
            {
                hash_insert(T,arr[j],N);
            }

            max_effort_found = 0;
            max_effort_not_found = 0;

            for(int k = 0; k < n - 1500; k++)
            {
                found_1 = found;
                hash_search(T, vect[k], N);
                if(max_effort_found < found - found_1)
                {
                    max_effort_found = found - found_1;
                }
                average_effort_found = average_effort_found + found - found_1;
            }

            for(int k = 0; k < 1500; k++)
            {
                found_2 = not_found;
                hash_search(T, arr[k], n);
                if(max_effort_not_found < not_found - found_2)
                {
                    max_effort_not_found = not_found - found_2;
                }
                average_effort_not_found = average_effort_not_found + not_found - found_2;
            }
            average_effort_found = average_effort_found / 1500;
            average_effort_not_found = average_effort_not_found / 1500;
        }
        average_effort_found = average_effort_found / 5;
        average_effort_not_found = average_effort_not_found / 5;
        cout << "\n " << alfa[index] << "\t\t\t " << average_effort_found << "\t\t\t " << max_effort_found;
        cout << "\t\t\t" << average_effort_not_found << "\t\t\t" << max_effort_not_found;
    }
}

int main()
{
    test_2();
    cout << "\n\n";
    average();
    ///test();
    return 0;
}
