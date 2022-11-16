#include<bits/stdc++.h>
using namespace std;
void merge(int arr[], int left, int mid, int right){
    //2 sub array
    // left - mid
    // mid+1 - right
    int n1 = mid - left + 1; // number of elements in subarray 1
    int n2 = right - (mid+1) + 1; // number of elements in subarray 2
    int leftArr[n1];
    int rightArr[n2];
    for(int i = 0; i < n1; i++){//copy elements from subarray 1 -> leftArr
        leftArr[i] = arr[left + i];
    }

    for(int  i = 0; i < n2; i++){
        rightArr[i] = arr[mid+1 + i];
    }

    //merge
    int i = 0; // i is index that move straight on leftArr
    int j = 0; // j is index that move straight on rightArr
    int ct = 0;
    while(i < n1 && j < n2){
        if(leftArr[i] < rightArr[j]){
            arr[left + ct] = leftArr[i];
            i++; //move i on leftArr
        }else{
            arr[left + ct] = rightArr[j];
            j++; //move j on rightArr
        }
        ct++; //move to next cell to insert into arr
    }
    //case 1: i = n1 -> leftArray is over
    while(j < n2){ //insert remainder eles of rightArr to arr
        arr[left + ct] = rightArr[j];
        j++;
        ct++;
    }

    while(i < n1){
        arr[left + ct] = leftArr[i];
        i++;
        ct++;
    }
}

void mergeSort(int arr[], int left, int right){
    if(left >= right){//base case -> exit recursive
        return; //stop
    }

    int mid = (left + right)/2;

    mergeSort(arr, left, mid); // divide
    mergeSort(arr, mid+1, right); //divide

    merge(arr, left, mid, right); // conquer - merge two subarrays
}

int main(){
    int arr[] = {5, 1, 9, 0 , 8, 6, 7, 2, 1, 0};
    mergeSort(arr, 0, 9);

    for(int i = 0; i < 10; i++){
        cout << arr[i] << " " ;
    }
    cout << endl;
}