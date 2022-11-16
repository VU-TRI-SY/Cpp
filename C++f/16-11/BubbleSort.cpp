#include<bits/stdc++.h>
using namespace std;
void BubbleSort(int arr[], int n){
    int check = 1; // check that has 2 elements a[i] and a[i+1] that a[i] > a[i+1]
    while(check){
        check = 0; // assume that has no adjcent elements that a[i] > a[i+1]
        for(int i = 0; i <= n-2; i++){
            if(arr[i] > arr[i+1]){
                // swap(arr[i], arr[i+1]);
                int temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;
                check = 1;
            }
            // both i and i+1 are index of arr
            // 0 <= i <= n-1 =>     0 <= i <= n-1
            // 0 <= i+1 <= n-1 =>   -1 <= i <= n-2
            // => 0 <= i <= n-2
        }
    }
}
int main(){
    int arr[] = {5, 1, 9, 0 , 8, 6, 7, 2, 1, 0};
    BubbleSort(arr, 10);

    for(int i = 0; i < 10; i++){
        cout << arr[i] << " " ;
    }
    cout << endl;
}