/**
* Author: T_Zhehang 
* Date: 18-3-1
* 归并排序
* 
*/
#include <assert.h>

void Merge(int a[], int l[], int r[], int left_length, int right_length){

    int left_index = 0;
    int right_index = 0;
    int index = 0;
    while(left_index < left_length && right_index < right_length){
        if(l[left_index] <= r[right_index])
            a[index++] = l[left_index++];
        else
            a[index++] = r[right_index++];
    }
    while(left_index < left_length)
        a[index++] = l[left_index++];
    while(right_index < right_length)
        a[index++] = r[right_index++];
    assert(index == left_index + right_length);

}


void MergeSort(int a[], int length){

    if(length < 2)
        return;

    int mid = length/2;

    int* l = new int[mid];
    int* r = new int[length-mid];

    for(int i = 0; i < mid; i++)
        l[i] = a[i];
    for(int j = mid; j < length; j++)
        r[j-mid] = a[j];

    MergeSort(l, mid);
    MergeSort(r, length-mid);
    Merge(a, l, r, mid, length-mid);
    delete l;
    delete r;
}