/**
* Author: T_Zhehang
* Date: 18-2-28
*
* 排序相关的通用函数
*/

#include <iostream>
#include <time.h>
#define MAX 1000

using namespace std;

void CreateUnSortedArray(int a[], int length){

    srand((int)time(NULL));
    for(int i=0; i<length; i++){
        a[i] = rand() % MAX;
    }

}

void CopyArray(int source[], int target[], int length){

    for(int i=0; i<length; i++){
        target[i] = source[i];
    }

}

void PrintArray(int array[], int length){

    for(int i=0; i<length; i++){
        cout << array[i] << " ";
    }
    cout << endl << endl;

}