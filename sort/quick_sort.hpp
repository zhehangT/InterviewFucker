/**
* Author: T_Zhehang
* Date: 18-1-20
*
* 快速排序
* 时间复杂度下界为O(nlogn)，最坏情况为O(n^2)。在实际应用中，快速排序的平均时间复杂度为O(nlogn)
*/

#include <assert.h>


int Partition( int* a, int start, int end ){

    int i = start - 1;
    int flag = a[end];

    for(int j = start; j < end; j++){
        if(a[j] < flag) {
            i++;
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }
    i++;
    a[end] = a[i];
    a[i] = flag;
    return i;
}


int Partition2( int* a, int start, int end ){

    int i = start;
    int j = end;
    int flag = a[end];

    while( i<j ){

        while(a[i] < flag && i < j)
            i++;
        a[j] = a[i];
        while(a[j] >= flag && i < j)
            j--;
        a[i] = a[j];
    }

    assert( i == j);
    a[i] = flag;
    return i;
}

int Partition3( int* a, int start, int end ){

    int i = start;
    int j = end;
    int flag = a[end];

    while( i < j ){

        while(a[i] < flag && i <= end)
            i++;
        while(a[j] >= flag && j >= start)
            j--;
        if( i < j ){
            int tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
        }
    }

    a[end] = a[i];
    a[i] = flag;

    return i;
}


void QuickSort( int* a, int start, int end ){

    if(start < end){
        int index = Partition(a, start, end);
        QuickSort(a, start, index - 1);
        QuickSort(a, index + 1, end);
    }
}





