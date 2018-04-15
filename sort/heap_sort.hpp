/**
* Author: T_Zhehang 
* Date: 18-4-15
* 堆排序
*/

void Heap(int* a, int length, int i){

    int leftChild = i*2+1;
    int rightChild = i*2+2;
    int minNode = i;

    if(leftChild < length && a[leftChild] < a[minNode]) {
        minNode = leftChild;
    }
    if(rightChild < length && a[rightChild] < a[minNode]) {
        minNode = rightChild;
    }

    if(minNode != i) {
        swap(a[i], a[minNode]);
        Heap(a, length, minNode);
    }
}

void HeapSort(int* a, int length){

    int* result = new int[length];

    for(int i = (length-1)/2; i >= 0; i--){
        Heap(a, length, i);
    }

    int i = length;
    for(int i = 0; i < length; i++){
        result[i] = a[0];
        swap(a[0], a[i-1]);
        i--;
        Heap(a, i, 0);
    }

    for(int i = 0; i < length; i++)
        a[i] = result[i];
    delete result;

}