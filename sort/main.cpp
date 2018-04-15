/**
* Author: T_Zhehang 
* Date: 18-2-28
*/

#include <string>
#include "util.h"
#include "tic_toc.h"
#include "quick_sort.hpp"
#include "bubble_sort.hpp"
#include "selection_sort.hpp"
#include "merge_sort.hpp"
#include "heap_sort.hpp"
#define NUM 10000

int main() {

    int a[NUM];
    CreateUnSortedArray(a, NUM);
    PrintArray(a, NUM);
    TicToc t;

    int a_quick[NUM];
    CopyArray(a, a_quick, NUM);
    t.tic();
    QuickSort(a_quick, 0, NUM - 1);
    float t_quick = t.toc();
    PrintArray(a_quick, NUM);

    int a_bubble[NUM];
    CopyArray(a, a_bubble, NUM);
    t.tic();
    BubbleSort(a_bubble, NUM);
    float t_bubble = t.toc();
    PrintArray(a_bubble, NUM);

    int a_selection[NUM];
    CopyArray(a, a_selection, NUM);
    t.tic();
    SelectionSort(a_selection, NUM);
    float t_selection = t.toc();
    PrintArray(a_selection, NUM);

    int a_merge[NUM];
    CopyArray(a, a_merge, NUM);
    t.tic();
    MergeSort(a_merge, NUM);
    float t_merge = t.toc();
    PrintArray(a_merge, NUM);

    int a_heap[NUM];
    CopyArray(a, a_heap, NUM);
    t.tic();
    MergeSort(a_heap, NUM);
    float t_heap = t.toc();
    PrintArray(a_heap, NUM);

    cout << "Quick Sort: " << t_quick << "ms" <<endl;
    cout << "Bubble Sort: " << t_bubble << "ms" <<endl;
    cout << "Selection Sort: " << t_selection << "ms" <<endl;
    cout << "Merge Sort: " << t_merge << "ms" <<endl;
    cout << "Heap Sort: " << t_heap << "ms" <<endl;


    return 0;
}
