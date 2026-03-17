#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <chrono>

#include "bubblesort.h"
#include "mergesort.h"
#include "quicksort.h"

#define MAX 100000

using namespace std;

int main()
{
    int data[MAX];
    srand(time(NULL));

    for(int i=0; i<MAX; i++)
        data[i] = rand()%(MAX*10);

    BubbleSort<int> bs;
    //MergeSort<int> ms;
    //QuickSort<int> qs;

    auto start = std::chrono::high_resolution_clock::now();
    bs.sort(data, MAX);
    //ms.sort(data, MAX);
    //qs.sort(data, MAX);
    //qsort(data, MAX, sizeof(int), compare); // usar com qsort (implementação da biblioteca padrão)

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;

    /*
    for(int i=0; i<n; i++)
        cout << data[i] << " ";
    cout << endl;
    */

    cout << MAX << " " << setprecision(7) << fixed << duration.count() << endl;
}

