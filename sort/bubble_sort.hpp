/**
* Author: T_Zhehang 
* Date: 18-2-28
*
* 冒泡排序
* 时间复杂度下界为为O(n^2)
*/

void BubbleSort(int a[], int length){

    for(int i=0; i<length-1; i++)
        for(int j=0; j<length-i-1; j++){
            if(a[j] > a[j+1]){
                int tmp = a[j];
                a[j] = a[j+1];
                a[j+1] = tmp;
            }
        }
}

