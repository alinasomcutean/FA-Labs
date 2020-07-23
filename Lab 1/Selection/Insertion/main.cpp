#include <iostream>

using namespace std;

void bubble_sort(int a[], int n)
{
    int i;
    bool swaped = true;
    while(swaped)
    {
        swaped = false;
        for(i = 1; i <= n-1; i++)
        {
            if(a[i] > a[i+1])
            {
                swap(a[i], a[i+1]);
                swaped = true;
            }
        }
    }
}

void insertion(int a[], int n)
{
    int i, j, buff;
    for(i = 2; i <= n; i++)
    {
        buff = a[i];
        j = i-1;
        while(buff < a[j] && j >= 1)
        {
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = buff;
    }
}

void selection(int a[], int n)
{
    int i, j, aux;
    for(i = 1; i <= n-1; i++)
    {
        aux = i;
        for(j = i+1; j <= n; j++)
        {
            if(a[j] < a[aux])
                aux = j;
        }
        swap(a[i], a[aux]);
    }
}

int main()
{
    int a[100], n;
    cin>>n;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    selection(a, n);
    ///insertion(a, n);
    ///bubble_sort(a, n);
    for(int i = 1; i <= n; i++)
        cout << a[i] << ' ';
    return 0;
}
