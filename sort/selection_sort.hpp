/**
* Author: T_Zhehang 
* Date: 18-2-28
* 选择排序
*/

void SelectionSort(int a[], int length){

    for(int i = 0; i < length; i++) {
        int min = a[i];
        int index = i;
        for ( int j = i+1; j < length; j++ ) {
            if( min>a[j] ){
                min = a[j];
                index = j;
            }
        }
        a[index] = a[i];
        a[i] = min;
    }

}
